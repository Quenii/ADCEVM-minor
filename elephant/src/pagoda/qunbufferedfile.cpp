#include "QUnbufferedFile.h"

#include <assert.h>
#include <Windows.h>
#include <QFileInfo>
#include <qdir>
#include <string.h>

using namespace std;
using namespace gkhy::pagoda;

class File : public QObject
{
	Q_OBJECT

public:
	File(QObject* parent = 0) 
		: QObject(parent)
		, m_hFile(INVALID_HANDLE_VALUE)
		, m_bOpen(false)
		, m_fileName("")
		, m_size (0)
	{	 
	}

	virtual ~File()
	{
		close();
	}

public:
	bool isOpen() const
	{
		return m_bOpen;
	}

	bool open(QString filename)
	{	
		if (m_bOpen) // already open
		{
			assert(false);
			return false;	
		}	

		QDir dir = QFileInfo(filename).dir();
		if (!dir.exists())
			QDir().mkpath(dir.path());

		if ( (m_hFile = CreateFileW(
			LPCWSTR(filename.unicode()),        // name of the write
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

		
		m_fileName = filename;
		m_size = 0;

		m_bOpen = true;

		emit fileCreated(filename);

		return true;
	}

	void close()
	{
		if (m_bOpen) // not open
		{
			bool okay = CloseHandle(m_hFile);
			if (!okay)
			{
				assert(false);
			}

			m_bOpen = false;		
		}
	}

	int write(const char* alignedBuf, int len)
	{
		assert(len >= 0);

		DWORD written = 0;
		BOOL Okay = WriteFile(m_hFile, alignedBuf, len, &written, NULL);
		if ( (!Okay) || written != len)
		{
			assert(false);
			return -1;
		}

		m_size += len;
		
		return len;
	}


	QString fileName() const { return m_fileName; }
	qint64 size() const { return m_size; }

signals:
	void fileCreated(QString fileName);

private:
	HANDLE m_hFile;
	bool m_bOpen;
	QString m_fileName;
	qint64 m_size;
};

class AlignedBuffer
{
public:	
	AlignedBuffer(int size) 
		: m_size(0)
		, m_buf(0)
		, m_count(0)
	{
		allocate(size);
	}

	~AlignedBuffer()
	{
		free();
	}

	bool allocate(int size)
	{
		free();

		if (size > 0)
		{
			DWORD sectorsPerCluster, bytesPerSector, numberOfFreeClusters, totalNumberOfClusters;		
			BOOL Okay = GetDiskFreeSpace(
				NULL, &sectorsPerCluster, &bytesPerSector, &numberOfFreeClusters, &totalNumberOfClusters);
			if (!Okay)
			{
				assert(false);
				return false;
			}

			m_size = ((size + bytesPerSector - 1 ) / bytesPerSector) * bytesPerSector;

			m_buf = (char*)VirtualAlloc(
				NULL,						// system selects address
				m_size,					// size of allocation
				MEM_RESERVE | MEM_COMMIT,   // allocate reserved pages
				PAGE_READWRITE);			// protection = no access

			if (!m_buf)
			{
				assert(false);
				return false;
			}
			
			assert(m_buf);			

		}

		return true;
	}

	void free()
	{
		if (m_buf)
		{
			BOOL okay = VirtualFree(
				m_buf,		    // base address of block
				0,				// bytes of committed pages
				MEM_RELEASE);	// decommit the pages
			assert(okay);
		}

		m_buf = 0;
		m_size = 0;
		m_count = 0;
	}

	int push(const char* buf, int count)
	{
		Q_ASSERT(count >= 0);
		int cpy = qMin(count, space());
		if (cpy > 0)
			memcpy(m_buf + m_count, buf, cpy);

		m_count += cpy;
		return cpy;
	}

	char* data()
	{
		return m_buf;
	}

	void clear()
	{
		m_count = 0;
	}

	char* addr() { return m_buf; }
	int size() const { return m_size; }
	int space() const { return m_size - m_count; }
	bool full() const { return (m_size == m_count) ? true : false; }	
	int count() const { return m_count; } 
private:
	int m_size;
	char* m_buf;
	int m_count;
};


#include "qunbufferedfile.moc"

QUnbufferedFile::QUnbufferedFile(int writeBufferSize /* = 512 * 1024 */, QObject* parent/* = 0*/) 
: QObject(parent)
, m_file(*(new File))
, m_obuf(*(new AlignedBuffer(writeBufferSize)))
{	

	bool okay = connect(&m_file, SIGNAL(fileCreated(QString)), this, SIGNAL(fileCreated(QString)));
	Q_ASSERT(okay);
}

QUnbufferedFile::~QUnbufferedFile()
{
	close();

	delete &m_obuf;
	delete &m_file;
}

bool QUnbufferedFile::open(QString fileName)
{
	return m_file.open(fileName);
}

bool QUnbufferedFile::isOpen() const
{
	return m_file.isOpen();
}

int QUnbufferedFile::write(const char *buf, int len)
{
	Q_ASSERT(len >= 0);

	if (! m_file.isOpen())
	{
		return false;
	}

	int count = 0;
	while(count < len)
	{
		int pushed = m_obuf.push(buf + count, len - count); 
		if (m_obuf.full())
		{
			bool ok = m_file.write(m_obuf.addr(), m_obuf.size());
			if (!ok)
				return -1;

			m_obuf.clear();
		}			

		count += pushed;
	}

	return len;
}

void QUnbufferedFile::close()
{
	QString fileName = m_file.fileName();
	m_file.close();
	
	if (m_obuf.count() > 0)
	{
		QFile ofile(fileName);
		ofile.open(QIODevice::WriteOnly | QIODevice::Append);
		ofile.write(m_obuf.addr(), m_obuf.count());
		m_obuf.clear();
	}
}

qint64 QUnbufferedFile::size() const
{
	return m_obuf.count() + m_file.size();
}

