#include "qsessionalrepository.h"
#include "gkhy/pagoda/FixedSizeArchive.h"

#include <QMutexLocker>
#include <QTime>
#include <QDate>
#include <QDir>
#include <QElapsedTimer>
#include <QMutex>
#include <QMutexLocker>
#include <Windows.h>
#include <shlwapi.h>


using namespace::gkhy::pagoda;

static qint64 freeBytesAvailable(QString path)
{
	qint64 size = 0;
	ULARGE_INTEGER _freeBytesAvailable;
	BOOL ret;
	ret = GetDiskFreeSpaceExA((const char*)path.toAscii(), &_freeBytesAvailable, NULL, NULL);
	if (ret)
		size = _freeBytesAvailable.QuadPart;
	return size;
}

static qint64 totalNumberOfBytes(QString path)
{
	qint64 size = 0;
	QFileInfoList list = QDir(path).entryInfoList(QDir::Files);
	for (int i = 0; i < list.size(); ++i)
	{
		QFileInfo fileInfo = list.at(i);
		size += fileInfo.size();
	}

	list =  QDir(path).entryInfoList(QDir::Dirs | QDir::NoDot | QDir::NoDotDot);
	for (int i = 0; i < list.size(); ++i)
	{
		QFileInfo fileInfo = list.at(i);
		size += totalNumberOfBytes(fileInfo.filePath());
	}

	return size;
}


static QStringList orderedSubDirList(QString reposDir)
{
	QStringList list =  QDir(reposDir).entryList(QDir::Dirs | QDir::NoDot | QDir::NoDotDot,
		QDir::IgnoreCase | QDir::Name);

	return list;
}

static QStringList orderedSubFileList(QString taskDir)
{
	QStringList list = QDir(taskDir).entryList(QDir::Files, QDir::IgnoreCase | QDir::Name);
	return list;
}

static bool removeFileSystemObject(QString fileName)
{
	SHFILEOPSTRUCTA op;
	memset(&op, 0, sizeof(op));
	op.hwnd = 0;
	op.wFunc = FO_DELETE;
	op.pFrom = fileName.toAscii().data(); // &szszpath[0]; //string(path + "\0\0").c_str();
	op.pTo = 0;
	op.fFlags = 
		FOF_NOCONFIRMATION | 
		FOF_NOCONFIRMMKDIR | 
		FOF_NOERRORUI |
		/*FOF_NORECURSION |*/ // recursion is what we need.
		FOF_SILENT;

	int error = SHFileOperationA(&op);
	return (error == 0) ? true : false;
}


class QSessionalRepositoryManager
{
public:
	QSessionalRepositoryManager(QString dir, qint64 preferredFootPrint)
		: m_dir(dir)
		, m_footPrint(0)	
	{
		qint64 guardSpace = qint64(10) * 1024 * 1024 * 1024; // 10 Giga Bytes
		m_footPrint = freeBytesAvailable(m_dir) + totalNumberOfBytes(m_dir) - guardSpace;
		m_footPrint = qMin(m_footPrint, preferredFootPrint);
		m_footPrint = qMax(m_footPrint, qint64(0));
	}

	virtual ~QSessionalRepositoryManager() {}

	qint64 makeSpace(qint64 size)
	{
		qint64 reposSize = totalNumberOfBytes(m_dir); 
		qint64 allocationNeeded = reposSize + size - m_footPrint;
		if (allocationNeeded <= 0)
		{
			return size;
		}

		qint64 toAllocate = qMin(reposSize, allocationNeeded);
		if (toAllocate <= 0)
		{
			return toAllocate;
		}

		qint64 count = 0; // toAllocate;
		while (count < toAllocate)
		{
			if (m_fileList.count() == 0 && refreshFileList() == 0)
			{
				break;
			}

			QFileInfo fileInfo(m_fileList[0]);
			int fileSize = fileInfo.size();			
			if (removeFileSystemObject(m_fileList[0]))
				count += fileSize;
			m_fileList.pop_front();
		}

		return count;
	}	

private:
	bool tryReserve(qint64 space)
	{

	}

	qint64 refreshFileList()
	{
		m_fileList = orderedSubFileList(m_dir);
		QStringList subDirs = orderedSubDirList(m_dir); 
		if (subDirs.count() > 0)
		{
			
			m_fileList += orderedSubFileList(subDirs[0]);
			m_fileList += subDirs[0];
		}	

		return m_fileList.count();
	}

private:
	QString m_dir;	
	qint64 m_footPrint;
	QStringList m_fileList;
};

template<typename T>
QSessionalRepository<T>::QSessionalRepository(QString dir, long long footPrint, long long fileSize, int timeout_s /* = -1 */, bool makeTimeSubDir /* = true */, int bufferSize /* = 100 * 1024 * 1024 */)
: QWorkerThread()
, m_inMeter(1000)
, m_outMeter(1000)
, m_buffer(bufferSize, 16 * 1024 * 1024, true)
, m_dir(dir)
, m_fileSize(fileSize)
, m_timeout_s(timeout_s)
, m_makeTimeSubDir(makeTimeSubDir)
, m_abort(0)
, m_lock(new QMutex)
, m_sessionalRepositoryManager(new QSessionalRepositoryManager(dir, footPrint))
{
}

template<typename T>
QSessionalRepository<T>::~QSessionalRepository(void)
{
	abort();

	delete m_lock;
	delete m_sessionalRepositoryManager;
}

template<typename T>
bool QSessionalRepository<T>::open()
{
	if (QWorkerThread::started())
	{
		Q_ASSERT(false);
		return false;
	}

	m_abort = 0;

	m_inMeter.reset();
	m_outMeter.reset();

	QWorkerThread::start();

	return true;
}

template<typename T>
void QSessionalRepository<T>::close()
{
	QWorkerThread::stop();
}

template<typename T>
void QSessionalRepository<T>::abort()
{
	m_abort = 1;
	QWorkerThread::stop();
}

template<typename T>
int QSessionalRepository<T>::totalWritableSize() const
{
	return m_buffer.totalWritableSize();
}

template<typename T>
int QSessionalRepository<T>::nextWriteBlockSize()
{
	return m_buffer.nextWriteBlockSize();
}

template<typename T>
T* QSessionalRepository<T>::nextWriteBlock()
{
	return m_buffer.nextWriteBlock();
}

template<typename T>
int QSessionalRepository<T>::commit(int len)
{
	int ret = m_buffer.commit(len);
	m_inMeter.flow(ret);	
	return ret;
}

template<typename T>
int QSessionalRepository<T>::write(const T* data, int maxLen)
{
	int ret = m_buffer.write(data, maxLen);
	m_inMeter.flow(ret);
	return ret;
}

template<typename T>
SessionalRepositoryStatistics QSessionalRepository<T>::statistics() const
{
	SessionalRepositoryStatistics data;
	data.in = m_inMeter.value();
	
	QMutexLocker lock(m_lock);

	data.out = m_outMeter.value();
	
	return data;
}

template<typename T>
void QSessionalRepository<T>::run()
{
	while(1)
	{	
		if (shouldStop())
		{
			if (m_abort)
			{
				break;
			}
			else if (m_buffer.count() == 0)
			{
				break;
			}
		}

		run_session();
	}
}

template<typename T>
QString QSessionalRepository<T>::taskDir()
{
	QString dir = m_dir;

	if (m_makeTimeSubDir)
	{
		QString data = QDate::currentDate().toString("yyyyMMdd");
		QString time = QTime::currentTime().toString("HHmmss");

		dir = QDir(dir).absoluteFilePath(QString("%1-%2").arg(data, time));
	}

	dir = dir + QDir::separator();

	return dir;
}

template<typename T>
void QSessionalRepository<T>::run_session()
{	
	FixedSizeArchive archive;	
	archive.open(taskDir(), ".dat", m_fileSize);

	QElapsedTimer timer;
	timer.start();
	while (1)
	{
		if (m_abort || ( m_timeout_s >= 0 && timer.hasExpired(m_timeout_s * 1000)))
			break ;
		
		if (m_buffer.count() == 0)
		{
			msleep(5);
			continue;
		}

		qint64 toWrite = qMin(m_buffer.nextReadBlockSize(), 4 * 1024 * 1024); 
		qint64 written = archive.write((const char*)(m_buffer.nextReadBlock()), toWrite * sizeof(*(m_buffer.nextReadBlock())));

		Q_ASSERT(toWrite*4  == written);
		m_buffer.chop(written);

		timer.restart();	

		QMutexLocker lock(m_lock);
		m_outMeter.flow(written);
		lock.unlock();
	}
}

template<typename T>
void QSessionalRepository<T>::fileCreated(QString fileName)
{
	qint64 ret = m_sessionalRepositoryManager->makeSpace(m_fileSize);
	if (ret < m_fileSize)
	{
		abort();
	}
}
