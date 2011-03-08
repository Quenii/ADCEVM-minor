#pragma once

#include "gkhy/mfcplus/WorkerThread.hpp"
#include "gkhy/mfcminus/AsyncHugeRingBuffer.hpp"
#include <string>

class TaskRepositoryPrivate : public gkhy::mfcplus::WorkerThread
{
public:
	TaskRepositoryPrivate(
		const std::string& dir, 
		long long footPrint, // assign -1 if all free diskspace is wanted.
		long long fileSize, 
		int timeout_s, // assign -1 if timeout feature is not wanted.
		int bufferSize = 100 * 1024 * 1024); // 100 MBytes
	virtual ~TaskRepositoryPrivate(void);

public:
	bool open();
	void close();
	void abort();	
	bool write(const char* buf, int len);

protected:
	virtual void thread_OnNewTaskStarted() { } 
	virtual void thread_OnBytesWritten(int cnt) { }
	virtual void onOverflow(int cnt) { }
	virtual int bufferPeakUse() { return int(m_buffer.peakCount() * 100.0f / m_buffer.size()); }

private:
	UINT ThreadProc(LPVOID lpvoid, volatile bool& enabled);
	
private:
	gkhy::MfcMinus::AsyncHugeRingBuffer m_buffer;
	const std::string m_dir;
	const long long m_footPrint;
	const long long m_fileSize;
	const unsigned int m_timeout_s;
	
	volatile unsigned int m_writeOverflow;

	volatile bool m_abort;
};
