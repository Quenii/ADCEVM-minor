#include "FixedSizeArchive.h"
#include "qunbufferedfile.h"

#include <cassert>

using namespace gkhy::pagoda;



FixedSizeArchive::FixedSizeArchive(QObject* parent)
: QObject(parent)
, m_fileNameBase("")
, m_fileNameSN(0)
// , m_file()
, m_perFileSize(0)
, m_totalSize(0)
{
	bool okay = connect(&m_file, SIGNAL(fileCreated(QString)), this, SIGNAL(fileCreated(QString)));
	Q_ASSERT(okay);
}

FixedSizeArchive::~FixedSizeArchive()
{
	close();
}


QString FixedSizeArchive::newFileName()
{
	return QString("%1%2%3").arg(m_fileNameBase).arg(m_fileNameSN++, 8, 16, QLatin1Char('0')).arg(m_fileNameExt);
}

bool FixedSizeArchive::open(QString fileNameBase, QString fileNameExt, qint64 perFileSize)
{
	m_fileNameBase = fileNameBase;
	m_fileNameSN = 0;
	m_fileNameExt = fileNameExt;

	m_perFileSize = perFileSize;
	m_totalSize = 0;

	if (!m_file.open(newFileName().toAscii().data()))
	{
		assert(false);
		return false;
	}

	return true;
}

qint64 FixedSizeArchive::write(const char* buf, qint64 len)
{
	assert(m_file.isOpen());
	assert(len >= 0);

	qint64 count = 0;
	
	while(count < len)
	{
		if (m_file.isOpen() && m_file.size() == m_perFileSize)
		{
			m_file.close();
		}

		if (!m_file.isOpen())
		{
			if (!m_file.open(newFileName().toAscii().data()))
				return -1;
		}

		qint64 toWrite = qMin(m_perFileSize - m_file.size(), len - count);
		int written = m_file.write(buf + count, toWrite);
		if (written != toWrite)
		{
			return -1;
		}

		count += written;

	}

	m_totalSize += len;
	
	return len;
}

void FixedSizeArchive::close()
{
	if (m_file.isOpen())
		m_file.close();	
}

