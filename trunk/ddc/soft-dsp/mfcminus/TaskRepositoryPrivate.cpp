#include "StdAfx.h"
#include "TaskRepositoryPrivate.hpp"
#include "gkhy/mfcminus/StopWatch.hpp"
#include "gkhy/mfcminus/DiskManager.hpp"
#include "gkhy/mfcminus/FixedSizeArchive.hpp"
#include "gkhy/mfcplus/StringEx.hpp"
#include <string>
#include <list>
#include <fstream>
#include <shlwapi.h>
#include <atlpath.h>
#include <assert.h>

using namespace std;
using namespace gkhy::MfcMinus;
using namespace gkhy::mfcplus;

class TaskRepositoryManager
{
public:
	TaskRepositoryManager(const std::string& dir, long long footPrint, long long fileSize) :
	  m_dir(dir), m_footPrint(footPrint), m_fileSize(fileSize) 
	  {
		  assert(m_footPrint != 0);
	  }	
	
	long long fileSize() { return m_fileSize; }	
	long long footprint() { return m_footPrint; }

	long long freeSapce()
	{
		Dir dir(m_dir);
		
		long long toAllocate = 0;
		long long dirFreeSpace = dir.freeBytesAvailable();

		if (m_footPrint < 0) // allocate all 
		{
			toAllocate = dirFreeSpace;
		}
		else
		{
			long long occupation = dir.bytesOfOccupation();
			toAllocate = (m_footPrint > occupation) ? (m_footPrint - occupation) : 0;		
		}

		return min(toAllocate, dirFreeSpace);
	}	

	void beginNewTask()
	{
		CTime now = CTime::GetCurrentTime();
		CStringA dirName;
		dirName.Format("%04d%02d%02d_%02d%02d%02d", 
			now.GetYear(), now.GetMonth(), now.GetDay(),
			now.GetHour(), now.GetMinute(), now.GetSecond());

		Dir dir(m_dir);
		m_taskDir = dir.pathAppend((const char*)dirName);
		
		CreateDirectoryA(m_taskDir.c_str(), 0);		
		
		Dir taskDir(m_taskDir);
		m_taskDataPath = taskDir.pathAppend(".dat");
		m_taskErrLogPath = taskDir.pathAppend("err.log");
	}

	string& taskDir() { return m_taskDir; }
	string& taskDataPath() { return m_taskDataPath; }
	void reportErr(const char* msg)
	{
		ofstream errlog(m_taskErrLogPath.c_str(), ios_base::app);
		errlog << msg << endl;
	}

	
	bool reserveSpace(long long size)
	{	
		do
		{
			if (freeSapce() >= size)
				return true;
		}
		while(deleteOneListedFile());

		// list maybe empty, so refresh list.
		list<string> dirs;
		Dir dir(m_dir);
		dir.subDirs(dirs, "*");								
		dirs.sort();


		//list<string>::const_iterator last = --dirs.end();
		CStringA taskDirName = PathFindFileNameA(m_taskDir.c_str());
		for (list<string>::const_iterator it = dirs.begin(); it != dirs.end(); ++it)
		{
			list<string> dats;
			Dir subDir(*it);
			subDir.subItems(dats, "*.dat");								
			dats.sort();

			m_deleteList.splice(m_deleteList.end(), dats);

			// delete sub-directory itself, but if not current task dir.
			CStringA dirName = PathFindFileNameA(it->c_str());

			bool euqal = (dirName.CompareNoCase(taskDirName) == 0) ? true : false; 
			if (!euqal)
			{
				m_deleteList.push_back(*it); 
			}
		}

		// let's try again with new list.
		do
		{
			if (freeSapce() >= size)
				return true;
		}
		while(deleteOneListedFile());

		return false;
	}

private:
	bool deleteOneListedFile()
	{
		USES_CONVERSION;

		if (m_deleteList.size() <= 0)
			return false;

		string& path = *(m_deleteList.begin());

		vector<char> szszpath;
		szszpath.resize(path.size() + 2);
		memcpy(&szszpath[0], path.c_str(), path.size());

		SHFILEOPSTRUCTA op;
		memset(&op, 0, sizeof(op));
		op.hwnd = 0;
		op.wFunc = FO_DELETE;
		op.pFrom = &szszpath[0]; //string(path + "\0\0").c_str();
		op.pTo = 0;
		op.fFlags = 
			FOF_NOCONFIRMATION | 
			FOF_NOCONFIRMMKDIR | 
			FOF_NOERRORUI |
			/*FOF_NORECURSION |*/ // recursion is what we need.
			FOF_SILENT;

		int error = SHFileOperationA(&op);
		assert(!error);

		m_deleteList.pop_front();

		return true;
	}

private:		
	const std::string m_dir;
	const long long m_footPrint;
	const long long m_fileSize;	

	string m_taskDir;
	string m_taskDataPath;
	string m_taskErrLogPath;

	list<string> m_deleteList;
};

TaskRepositoryPrivate::TaskRepositoryPrivate(const std::string& dir, long long footPrint, long long fileSize, int timeout_s, int bufferSize /*= 100 * 1024 * 1024*/)
: m_buffer(32 * 1024 * 1024),
m_dir(dir),
m_footPrint(footPrint),
m_fileSize(fileSize),
m_timeout_s(timeout_s)
{		
	m_buffer.syncResize(bufferSize);

	m_writeOverflow = 0;
	m_abort = false;	

	CPathA path(dir.c_str());
	if (!path.FileExists())	
		CreateDirectoryA(dir.c_str(), 0);
}

TaskRepositoryPrivate::~TaskRepositoryPrivate(void)
{
	abort();
}

bool TaskRepositoryPrivate::open()
{
	m_abort = false;
	WorkerThread::Start(this);
	return true;
}

void TaskRepositoryPrivate::close()
{
	WorkerThread::Stop();
}

void TaskRepositoryPrivate::abort()
{
	m_abort = true;
	close();
}


bool TaskRepositoryPrivate::write(const char* buf, int len)
{
	int written = m_buffer.write(buf, len);
	int overflow = len - written;
	m_writeOverflow += overflow;
	onOverflow(overflow);
	return (overflow <= 0) ? true : false;
}

UINT TaskRepositoryPrivate::ThreadProc(LPVOID lpvoid, volatile bool& enabled)
{
	StopWatch dataWatchDog;
	
	FixedSizeArchive task;

	long long taskFileLen = 0;
	string currentArchiveDir;	

	TaskRepositoryManager taskManager(m_dir, m_footPrint, m_fileSize);

	unsigned int readOverflow = 0;
	long long taskOverflow = 0;

	while (1)	
	{
		if (m_abort)
		{
			break; // aborted
		}
		
		if ((!enabled) && m_buffer.count() <= 0) 
		{
			break; // not aborted, not enabled and buffer empty.
		}
		
		if (m_buffer.count() <= 0)
		{
			Sleep(10);

			if (m_timeout_s > 0 && dataWatchDog.getTime_s() > m_timeout_s) // timeout, close current task.
			{
				if (task.isOpen()) task.close();
			}
		}
		else // data available
		{
			dataWatchDog.reset();

			if (!task.isOpen())  // task is not yet started...
			{			
				if (taskManager.reserveSpace(taskManager.fileSize()))
				{
					taskManager.beginNewTask();
					task.open(taskManager.taskDataPath().c_str(), taskManager.fileSize());					
					taskFileLen = 0;
					readOverflow = m_writeOverflow;
					taskOverflow = 0;

					thread_OnNewTaskStarted();
				}
			}

			if (task.isOpen())
			{
				long long a = taskManager.fileSize() - taskFileLen;
				int b = m_buffer.nextReadBlockSize();
				int c = 16 * 1024 * 1024; // atomic write size
				int toWrite = int(min(a, min(b, c)));				
				
				task.write(m_buffer.nextReadBlock(), toWrite);
				m_buffer.chop(toWrite);
				
				taskFileLen += toWrite;			
				
				thread_OnBytesWritten(toWrite);

				if (taskFileLen >= taskManager.fileSize())
				{	
					taskFileLen = 0;
					if (!taskManager.reserveSpace(taskManager.fileSize())) 
					{  // unable to allocate disk space to continue...					
						task.close();
					}

				}

				// overflow
				
				unsigned int writeOverflow = m_writeOverflow;
				if (readOverflow != writeOverflow)
				{
					unsigned int deltaOverflow = writeOverflow - readOverflow;
					taskOverflow += deltaOverflow;

					CStringEx strDeltaOverflow, strTaskOverflow;
					strDeltaOverflow.ToSeperatedDec(deltaOverflow);
					strTaskOverflow.ToSeperatedDec(taskOverflow);

					CStringA msg;
					msg.Format("Overflow: %S bytes, %S in total. (writeCnt = 0x%X, readCnt = 0x%X)",
					(LPCTSTR)strDeltaOverflow, (LPCTSTR)strTaskOverflow, writeOverflow, readOverflow);
					taskManager.reportErr((const char*)msg);

					readOverflow = writeOverflow;
				}
			}	
		}
	}		

	return 0;
}