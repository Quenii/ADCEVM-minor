#include "StdAfx.h"
#include "gkhy/mfcminus/TaskRepository.hpp"
#include "gkhy/mfcplus/ThruputMeter.hpp"
#include "gkhy/mfcminus/StopWatch.hpp"
#include "TaskRepositoryPrivate.hpp"

using namespace gkhy::MfcMinus;
using namespace gkhy::mfcplus;

class TaskRepositoryPrivateEx: public TaskRepositoryPrivate
{
public:
	TaskRepositoryPrivateEx(const std::string& dir, long long footPrint, long long fileSize, 
		int timeout_s, int bufferSize = 100 * 1024 * 1024)  // 100 MBytes
		: TaskRepositoryPrivate(dir, footPrint, fileSize, timeout_s, bufferSize)
	{
		m_fileSize = fileSize;

		m_iMeter.Reset();
		m_oMeter.Reset();
		m_stopWatch.reset();
		m_overflow = 0;
	}	
	virtual ~TaskRepositoryPrivateEx()
	{
		abort();
	}

	bool open()
	{
		m_iMeter.Reset();
		m_oMeter.Reset();
		m_stopWatch.reset();
		m_overflow = 0;

		return TaskRepositoryPrivate::open();
	}

	bool write(const char* buf, int len)
	{
		m_iMeter.Flow(len);
		return TaskRepositoryPrivate::write(buf, len);
	}

	void getPerformance(RepositoryPerformance& rf)
	{
		MeterValue meterVal;
		m_iMeter.GetMeter(meterVal);				
		rf.nInTotal = meterVal.nTotal;
		rf.nInAvgThruput = meterVal.nAvgThruput;
		rf.nInInstThruput = meterVal.nInstThruput;
		m_oMeter.GetMeter(meterVal);				
		rf.nOutTotal = meterVal.nTotal;
		rf.nOutAvgThruput = meterVal.nAvgThruput;
		rf.nOutInstThruput = meterVal.nInstThruput;

		rf.nCurrentFilePercent = int((rf.nOutTotal % m_fileSize) * 100.0f / m_fileSize);
		rf.nFifoLeakCount = m_overflow;
		rf.nFifoPercent = bufferPeakUse();

		rf.secTimeElapsed = m_stopWatch.getTime_s();
	}

	void onOverflow(int cnt)
	{
		m_overflow += cnt;
	}

	void thread_OnNewTaskStarted()
	{

	}

	void thread_OnBytesWritten(int cnt)
	{
		m_oMeter.Flow(cnt);			
	}

private:
	CThruputMeter m_iMeter;
	CThruputMeter m_oMeter;
	StopWatch m_stopWatch;
	long long m_overflow;
	long long m_fileSize;
};

TaskRepository::TaskRepository(const std::string& dir, long long footPrint, long long fileSize,
							   int timeout_s, int bufferSize /* = 100 * 1024 * 1024 */) :
m_p(*new TaskRepositoryPrivateEx(dir, footPrint, fileSize, timeout_s, bufferSize))
{

}

TaskRepository::~TaskRepository(void)
{
	delete &m_p;
}

bool TaskRepository::open()
{
	return m_p.open();
}

void TaskRepository::close()
{
	m_p.close();
}

void TaskRepository::abort()
{
	m_p.abort();
}

// false if overflow
bool TaskRepository::write(const char* buff, int size)
{
	return m_p.write(buff, size);
}

void TaskRepository::getPerformance(RepositoryPerformance& rf)
{
	m_p.getPerformance(rf);
}