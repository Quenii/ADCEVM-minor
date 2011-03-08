#include "stdafx.h"
#include "gkhy/mfcminus/DataScan.hpp"
#include "DataScanCore_cul32.hpp"
#include "DataScanCore_1279pack_cul32.hpp"
#include <assert.h>

using namespace gkhy::MfcMinus;

DataScan::DataScan(Mode mode, int bufferSize /* = 256 * 1024 * 1024 */)
{
	switch (mode)
	{
	case CUL32:
		m_p = new DataScanCore_cul32(bufferSize);
		break;

	case CUL32_1279Pack_CUB32:
		m_p = new DataScanCore_1279Pack_cul32(bufferSize);
		break;

	default:
		m_p = 0;
		break;
	}

	assert(m_p);
}

DataScan::~DataScan()
{
	stop();	
	delete m_p;
}

void DataScan::start()
{
	m_p->start();	
}

void DataScan::stop()
{
	m_p->stop();	
}

void DataScan::write(const char *buf, int len)
{
	return m_p->write(buf, len);
}