#include "stdafx.h"
#include "gkhy/mfcminus/DiskManager.hpp"
#include <shlwapi.h>
#include <atlpath.h>
#include <assert.h>

using namespace gkhy::MfcMinus;

bool DiskManager::getFreeSpace(const char* dir,
							   long long* pFreeBytesAvailable,
							   long long* pTotalNumberOfBytes /* = 0 */, 
							   long long* pTotalNumberOfFreeBytes /* = 0 */)
{
	// __int64 i64FreeBytesToCaller, i64TotalBytes, i64FreeBytes;

	if (!GetDiskFreeSpaceExA(
		dir,
		(PULARGE_INTEGER)pFreeBytesAvailable,
		(PULARGE_INTEGER)pTotalNumberOfBytes,
		(PULARGE_INTEGER)pTotalNumberOfFreeBytes))
	{
		return false;
	}
	else
	{
		return true;
	}
}

long long GetDirSize(LPCTSTR path)
{
	long long count = 0;

	CFileFind finder; 		
	BOOL bWorking = finder.FindFile(path);
	while(bWorking)
	{	
		bWorking = finder.FindNextFile();

		if (!finder.IsDots())
		{
			if (finder.IsDirectory()) 
			{
				CString subDir = finder.GetFilePath();				
				count += GetDirSize(subDir + _T("\\*"));
			}
			else
			{
				count  += finder.GetLength();
			}
		}
	}

	return count;
}

long long Dir::bytesOfOccupation()
{	
	USES_CONVERSION;
	return GetDirSize(A2T(pathAppend("*").c_str()));	
}

std::string Dir::pathAppend(const std::string &more)
{
	CPathA path(m_dir.c_str());
	path.Append(more.c_str());

	return (const char*)path;
}

void Dir::subDirs(std::list<std::string>& ref, const std::string& wildCard)
{
	USES_CONVERSION;

	CFileFind finder; 	

	ref.clear();

	BOOL bWorking = finder.FindFile(A2T(pathAppend("*").c_str()));
	while(bWorking)
	{	
		bWorking = finder.FindNextFile();

		// skip . and .. files; 
		if ((!finder.IsDots()) && finder.IsDirectory())		
		{
			ref.push_back(T2A(finder.GetFilePath()));
		}
	}
}

void Dir::subItems(std::list<std::string>& ref, const std::string& wildCard /* =  */)
{
	USES_CONVERSION;

	CFileFind finder; 	

	ref.clear();

	BOOL bWorking = finder.FindFile(A2T(pathAppend("*").c_str()));
	while(bWorking)
	{	
		bWorking = finder.FindNextFile();

		// skip . and .. files; 
		if (!finder.IsDots())		
		{
			ref.push_back(T2A(finder.GetFilePath()));
		}
	}
}