#include "StdAfx.h"
#include "gkhy/mfcplus/ThruputMeter.hpp"

using namespace gkhy::mfcplus;

CThruputMeter::CThruputMeter(void)
{
	Reset();
}

CThruputMeter::~CThruputMeter(void)
{
}

void CThruputMeter::SetUp(UNIT unit, clock_t nInstTimeval)
{
	m_Unit = unit;
	m_nInstTimeval = nInstTimeval;
	Reset();
}

void CThruputMeter::Reset()
{
	m_nInstTimeval = 1000;
	m_Unit = UNIT_KB;

	m_nTotalCount = 0;
	m_nInstCount = 0;

	m_nAvgThruput = 0;
	m_nInstThruput = 0;

	m_JustNow = m_Now = m_Start = clock();	
}

void CThruputMeter::GetMeter(MeterValue& m)
{
	Flow(0);

	m.nStartTime = m_Start;
	m.nNowTime = m_Now;

	m.nTotal = m_nTotalCount;

	m.nAvgThruput = m_nAvgThruput;
	m.nInstThruput = m_nInstThruput;
}

void CThruputMeter::Flow(int nCount)
{
	m_nTotalCount += nCount;
	m_nInstCount += nCount;

	m_Now = clock();

	clock_t nTimeval = int(m_Now - m_JustNow);
	//calculate the instant throughput only after a specific time interval
	if (nTimeval >= m_nInstTimeval)
	{
		m_nInstThruput = m_nInstCount / nTimeval;
		m_nAvgThruput = int(m_nTotalCount / int(m_Now - m_Start));
		m_JustNow = m_Now;
		m_nInstCount = 0;
	}
}
