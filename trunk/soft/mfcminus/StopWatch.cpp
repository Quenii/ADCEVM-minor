#include "stdafx.h"
#include "gkhy/mfcminus/StopWatch.hpp"
#include <assert.h>

using namespace gkhy::MfcMinus;

void StopWatch::reset()
{
	m_start = GetTickCount();
}

unsigned int StopWatch::getTime_ms()
{
	unsigned int now = GetTickCount();
	unsigned int interval = (now >= m_start) ? now - m_start : unsigned int(int(-1)) - (m_start - now);
	return interval;
}
