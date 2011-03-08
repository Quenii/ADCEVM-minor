#include "StdAfx.h"
#include "gkhy/mfcminus/NetRepository.hpp"
#include "gkhy/mfcplus/WorkerThread.hpp"
#include "gkhy/mfcminus/AsyncHugeRingBuffer.hpp"
#include "gkhy/mfcplus/BlockingTcpSocket.hpp"
#include <afxsock.h>
#include <assert.h>

using namespace gkhy::MfcMinus;
using namespace gkhy::mfcplus;

class NetRepositoryPrivate : private WorkerThread
{
public:
	NetRepositoryPrivate(unsigned short port, int fifoSize) 
		: m_writeBuffer(64 * 1024 * 1024), WorkerThread()
	{
		m_writeBuffer.syncResize(fifoSize);
		m_port = port;
		m_bOpen = false;
		m_accepted = false;

		if (!AfxSocketInit())
		{
			assert(false);
		}	
	}

	virtual ~NetRepositoryPrivate()
	{
		abort();
	}

private:
	void Start(
		LPVOID lpvoid = NULL,
		int nPriority = THREAD_PRIORITY_NORMAL,
		UINT nStackSize = 0,
		DWORD dwCreateFlags = 0,
		LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL)
	{
		assert(false);
	}
	void Stop()
	{
		assert(false);
	}

public:
	bool open()
	{
		if (m_bOpen)
		{
			assert(false);
			return false;
		}

		m_bAbort = false;
		WorkerThread::Start(this);

		m_bOpen = true;

		return true;
	}

	void close()
	{		
		if (!m_bOpen)
			return ;

		m_listener.OtherThreadClose();

		WorkerThread::Stop();

		m_bOpen = false;	
	}

	void abort()
	{
		m_bAbort = true;
		close();
	}

	// false if overflow
	bool write(const char* buff, int size)
	{
		if (!m_accepted)
		{
			return true;
		}

		int sent = m_writeBuffer.write(buff, size);
		return (sent == size) ? true : false;
	}

	UINT ThreadProc(LPVOID lpvoid, volatile bool& enabled)
	{
		NetRepositoryPrivate& obj = *(NetRepositoryPrivate*)lpvoid;

		if (!obj.m_listener.Listen(m_port, 0))
		{
			return false;
		}	

		while (enabled)
		{
			m_accepted = false;

			CBlockingTcpSocket serv;				
			if (!obj.m_listener.Accept(serv))
			{
				DWORD err = GetLastError();
				continue; //return 0; 
			}

			// reset buffer
			obj.m_writeBuffer.syncClear();

			m_accepted = true;

			// serving
			ThreadProc_Serve(lpvoid, serv, enabled);			

			serv.Close();			
		}

		//obj.m_listener.Close();

		return 0;
	}

	BOOL ThreadProc_Serve(LPVOID lpvoid, CBlockingTcpSocket& serv, volatile bool& enabled)
	{
		NetRepositoryPrivate& obj = *(NetRepositoryPrivate*)lpvoid;		
		bool shouldServe = true;
		while(shouldServe)
		{
			int cnt = obj.m_writeBuffer.count();
			int dataLen = qMin(2 * 1024 * 1024, cnt);
			// sof and len
			unsigned int header[2];
			header[0] = /*htonl*/(0x01020304);
			header[1] = /*htonl*/(dataLen);

			if (!serv.Send((char*)header, sizeof(header)))
				return FALSE;

			if(dataLen == 0)
			{
				Sleep(10);
			}
			else
			{
				int count = 0;
				while (count < dataLen)
				{
					int b = obj.m_writeBuffer.nextReadBlockSize();
					int subSend = qMin(dataLen - count, b);
					if (!serv.Send(obj.m_writeBuffer.nextReadBlock(), subSend))
						return FALSE;
					count += subSend;

					int chopped = obj.m_writeBuffer.chop(subSend); 
					assert(chopped == subSend);
				}

				assert(count == dataLen);
			}	

			shouldServe = true;

			if ((!enabled) && (!obj.m_bAbort) && obj.m_writeBuffer.count() <= 0)
				shouldServe = false;
			else if ((!enabled) && obj.m_bAbort)
				shouldServe = false;		
		}

		return TRUE;
	}

private:
//	RepositoryPerformance	
	bool m_bOpen;
	volatile bool m_bAbort;
	unsigned short m_port;
	AsyncHugeRingBuffer m_writeBuffer;
	CBlockingTcpSocket m_listener;	
	volatile bool m_accepted;
};


//NetRepository::NetRepository(unsigned short port, int fifoSize) :
//m_port(port), m_fifoSize(fifoSize), m_server(*new SimpleSvrHDR)
//{
//
//}
//
//NetRepository::~NetRepository(void)
//{
//	abort();
//	delete &m_server;
//}
//
//bool NetRepository::open()
//{
//	return m_server.Start(m_port, m_fifoSize);
//}
//
//void NetRepository::close()
//{	
//	m_server.Stop();
//}
//
//void NetRepository::abort()
//{
//	close();
//}
//
//// false if overflow
//bool NetRepository::write(const char* buff, int size)
//{	
//	m_server.Write(const_cast<char*>(buff), size);
//	return true;
//}
//
//void NetRepository::getPerformance(RepositoryPerformance& rf)
//{
//	m_server.GetPerformance(rf);
//}
//

NetRepository::NetRepository(unsigned short port, int fifoSize) :
m_p(*new NetRepositoryPrivate(port, fifoSize))
{
}

NetRepository::~NetRepository(void)
{
	abort();
	delete &m_p;
}

bool NetRepository::open()
{
	return m_p.open();
}

void NetRepository::close()
{	
	m_p.close();
}

void NetRepository::abort()
{
	m_p.abort();
}

// false if overflow
bool NetRepository::write(const char* buff, int size)
{	
	return m_p.write(const_cast<char*>(buff), size);
}

void NetRepository::getPerformance(RepositoryPerformance& rf)
{
	// m_server.GetPerformance(rf);
}


