#include "stdafx.h"
#include "gkhy/mfcminus/FastFileWriter.hpp"
#include <assert.h>
#include <fstream>

#ifdef IMPLEMENT_FastFileWriter

using namespace std;
using namespace gkhy::MfcMinus;


class FastFilewriterPrivate
{
public:
	FastFilewriterPrivate()
	{
		DWORD sectorsPerCluster, bytesPerSector, numberOfFreeClusters, 
			totalNumberOfClusters;		
		BOOL Okay = GetDiskFreeSpace(
			NULL, &sectorsPerCluster, &bytesPerSector, &numberOfFreeClusters,
			&totalNumberOfClusters);
		assert(Okay);

		m_bufSize = ((4 * 1024 * 1024 + bytesPerSector - 1 ) / bytesPerSector) * bytesPerSector;

		m_buf = (char*)VirtualAlloc(
			NULL,						// system selects address
			m_bufSize,					// size of allocation
			MEM_RESERVE | MEM_COMMIT,   // allocate reserved pages
			PAGE_READWRITE);			// protection = no access
		assert(m_buf);

		m_bytesInBuf = 0;	
		m_bOpen = false;				 
	}

	virtual ~FastFilewriterPrivate()
	{
		bool okay = close();  assert(okay);

		BOOL Okay = VirtualFree(
			m_buf,		    // base address of block
			0,				// bytes of committed pages
			MEM_RELEASE);	// decommit the pages

		ASSERT(Okay);
	}

public:
	bool isOpen()
	{
		return m_bOpen;
	}

	bool open(const char* filename)
	{
		//USES_CONVERSION;

		assert(0 == m_bytesInBuf);	

		if (m_bOpen) // already open
		{
			assert(false);
			return false;	
		}		

		m_fileName = filename;

		if ( (m_hFile = CreateFileA(
			/*A2T*/(filename),        // name of the write
			GENERIC_WRITE,	      // open for writing
			0,                    // do not share
			NULL,                 // default security
			CREATE_ALWAYS,        // overwrite existing
			FILE_ATTRIBUTE_NORMAL | FILE_FLAG_NO_BUFFERING,  // normal file
			NULL)) == INVALID_HANDLE_VALUE)
		{
			assert(false); 
			return false;
		}

		m_bytesInBuf = 0;
		m_bOpen = true;

		return true;
	}

	bool close()
	{
		if (!m_bOpen) // not open
			return true;

		if (!CloseHandle(m_hFile))
		{
			return false;
		}
		
		if (m_bytesInBuf > 0)		
		{ 
			try
			{
				// write all pending data to file
				fstream of(m_fileName.c_str(), ios_base::binary | ios_base::app | ios_base::out);
				of.write(m_buf, m_bytesInBuf);
				m_bytesInBuf = 0;
				of.close();
			}
			catch(...)			
			{
				assert(false);
				return false;				
			}
		}

		m_bOpen = false;		

		return true;
	}

	bool write(const char* data, int len)
	{
		if (!m_bOpen)
		{
			assert(false);
			return false;
		}
		
		int count = 0;
		while (count < len)
		{
			int subWrite = min(len - count, m_bufSize - m_bytesInBuf);
			memcpy(m_buf + m_bytesInBuf, data + count, subWrite);
			m_bytesInBuf += subWrite;
			count += subWrite;

			if (m_bytesInBuf == m_bufSize)
			{
				if (!buf2File()) 
					return false;			
				m_bytesInBuf -= m_bufSize;
			}			
		}

		return true;
	}

private:
	bool buf2File()
	{
		DWORD written = 0;
		BOOL Okay = WriteFile(m_hFile, m_buf, m_bufSize, &written, NULL);
		if ( TRUE == Okay && written == m_bufSize )
		{
			return true;
		}
		else
		{
			assert(false);
			return false;			
		}
	}

private:
	HANDLE m_hFile;
	bool m_bOpen;
	char* m_buf;
	int m_bufSize;
	int m_bytesInBuf;
	string m_fileName;
};


FastFileWriter::FastFileWriter() : m_p(*new FastFilewriterPrivate)
{
	m_size = 0;
}

FastFileWriter::~FastFileWriter()
{
	close();
	delete &m_p;
}

bool FastFileWriter::isOpen()
{
	return m_p.isOpen();
}

bool FastFileWriter::open(const char* fileName)
{
	m_size = 0;
	return m_p.open(fileName);
}


bool FastFileWriter::write(const char *buf, int len)
{
	m_size += len;
	return m_p.write(buf, len);
}

bool FastFileWriter::close()
{
	return m_p.close();
}

#endif
