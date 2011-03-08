#pragma once

#include "gkhy/mfcplus/WorkerThread.hpp"
#include "gkhy/mfcminus/AsyncHugeRingBuffer.hpp"
#include <assert.h>
#include <vector>
#include <iostream>
#include <iomanip>

class DataScanCore : private gkhy::mfcplus::WorkerThread
{
public:
	DataScanCore(int bufferSize = 64 * 1024 * 1024) : m_buff(32 * 1024 * 1024), WorkerThread()
	{
		m_buff.syncResize(bufferSize);
		m_bStarted = false;		
		AllocConsole();
	}
	virtual ~DataScanCore() 
	{
		Stop();
		FreeConsole();
	}

	void start()
	{
		if (m_bStarted)
		{
			assert(false);
			return;
		}

		WorkerThread::Start(0, THREAD_PRIORITY_ABOVE_NORMAL);			
		m_bStarted = true;
	}

	void stop()
	{		
		if (!m_bStarted)
		{
			return ;
		}
		
		WorkerThread::Stop();
		m_bStarted = false;
	}

	void write(const char* buf, int len)
	{
		if (!m_bStarted)
		{
			assert(false);
			_tcprintf(_T("Not yet started.\n"));
			return ;
		}

		int written = m_buff.write(buf, len);
		if (written < len)
		{
			_tcprintf(_T("Buffer overflows with %d bytes lost.\n"), len - written);
		}
	}

	UINT ThreadProc(LPVOID lpvoid, volatile bool& enabled) = 0; 	

public:	
	gkhy::MfcMinus::AsyncHugeRingBuffer m_buff;
	bool m_bStarted;		
};