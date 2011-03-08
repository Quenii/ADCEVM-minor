#include "stdafx.h"
#include "gkhy\mfcplus\WorkerThread.hpp"
#include <assert.h>

using namespace gkhy::mfcplus;

WorkerThread::WorkerThread(void)
{
	m_Enabled = false;
	m_Alive = false;
}

WorkerThread::~WorkerThread(void)
{
	if (m_Alive)
		Stop();
}

void WorkerThread::Start(LPVOID lpvoid, int nPriority, UINT nStackSize, DWORD dwCreateFlags, LPSECURITY_ATTRIBUTES lpSecurityAttrs)
{
	m_Enabled = true;
	m_lpvoid = lpvoid;
	assert(!m_Alive);
	m_pThreadObj = AfxBeginThread(InternalThreadProc, this, nPriority, nStackSize, dwCreateFlags, lpSecurityAttrs);
// 	while(!m_Alive) // it is buggy because the thread may quit right before this line.
// 		Sleep(0);
}

void WorkerThread::Stop()
{
	m_Enabled = false;
	while (m_Alive)
		Sleep(0);
}

UINT WorkerThread::InternalThreadProc(LPVOID lpvoid)
{	
	WorkerThread& obj = *(WorkerThread*)lpvoid;	
	obj.m_Alive = true;
	UINT ret = obj.ThreadProc(obj.m_lpvoid, obj.m_Enabled);	
	obj.m_Alive = false;
	return ret;
}

UINT WorkerThread::ThreadProc(LPVOID lpvoid, volatile bool& enabled)
{
	while (enabled)
		Sleep(1);

	return 0;
}
