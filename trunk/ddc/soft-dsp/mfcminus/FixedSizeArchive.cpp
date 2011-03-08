#include "stdafx.h"
#include "gkhy/mfcminus/FixedSizeArchive.hpp"
#include "gkhy/mfcminus/FastFilewriter.hpp"
#include <cassert>

using namespace gkhy::MfcMinus;

FixedSizeArchive::FixedSizeArchive()
{
	m_bOpen = false;
	m_pwriter = 0;
	m_archiveSize = 0;
	m_fileSize = 0;
	m_seed = 0;
}

FixedSizeArchive::~FixedSizeArchive()
{
	close();
	assert(0 == m_pwriter);
}

bool FixedSizeArchive::open(const char* fileName, long long fileSize)
{
	if (m_bOpen)
	{
		assert(false);
		return false;
	}

	m_fileName = fileName;
	m_fileSize = fileSize;
	m_seed = 0;
	if ( 0 == (m_pwriter = createwriter()) )
	{
		return false;
	}

	m_bOpen = true;
	return true;
}

bool FixedSizeArchive::write(const char* buf, int len)
{
	assert(m_pwriter);

	int count = 0;
	while (count < len)
	{
		int subWrite = int(min(m_fileSize - m_pwriter->size(), len - count));
		if (!m_pwriter->write(buf + count, subWrite))
			return false;

		count += subWrite;

		if (m_pwriter->size() >= m_fileSize)
		{
			bool okay = m_pwriter->close();			
			delete m_pwriter;
			m_pwriter = 0;
			if (!okay)
				return false;			

			if ((m_pwriter = createwriter()) == 0)
				return false;
		}
	}

	m_archiveSize += len;

	return true;
}

bool FixedSizeArchive::close()
{
	if (m_bOpen)
	{
		if (m_pwriter)
		{
			m_pwriter->close();
			delete m_pwriter;
			m_pwriter = 0;
		}

		m_bOpen = false;
	}

	return true;
}

FastFileWriter* FixedSizeArchive::createwriter()
{
	std::string fileNameBase, ext;
	int dot = int(m_fileName.rfind('.'));
	fileNameBase = m_fileName.substr(0, dot);
	ext = m_fileName.substr(dot, m_fileName.size() - dot);
	char buf[20];
	sprintf_s(buf, sizeof(buf), "%08X", m_seed);

	std::string name = fileNameBase + std::string(buf) + ext;
	
	FastFileWriter* writer = new FastFileWriter;		
	if (!writer)
		return 0;
	
	if (!writer->open(name.c_str()))
		return 0;

	m_seed++;

	return writer;
}