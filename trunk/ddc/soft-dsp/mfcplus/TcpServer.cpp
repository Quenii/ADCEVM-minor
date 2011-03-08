#include "StdAfx.h"
#include "gkhy/mfcplus/TcpServer.hpp"
#include <assert.h>

using namespace std;
using namespace gkhy::mfcplus;

UINT CTcpServer::AcceptThread::ThreadProc(LPVOID lpvoid, volatile bool& enabled)
{
	CTcpServer& obj = *(CTcpServer*)lpvoid;
	assert(obj.m_listenFd != INVALID_SOCKET);

	SOCKET sock;
	while(enabled) 
	{		
		sock = accept(obj.m_listenFd, NULL, NULL);
		if (sock == INVALID_SOCKET)
		{
			break;
		}
		else
		{
			obj.pushPendingSock(sock);	
			cout << "accept successfully." << endl;
		}
	}

	return 0;
}

void CTcpServer::pushPendingSock(SOCKET sock)
{
	CSingleLock lock(&m_pendingSockQueueLock);
	lock.Lock();

	m_pendingSockQueue.push(sock);
	m_pendingSockQueueNotEmpty.SetEvent();
}


SOCKET CTcpServer::popPendingSock()
{
	CSingleLock lock(&m_pendingSockQueueLock);
	lock.Lock();

	assert(m_pendingSockQueue.size() > 0);

	SOCKET sock = m_pendingSockQueue.back();
	m_pendingSockQueue.pop();

	if (m_pendingSockQueue.size() == 0)
	{
		m_pendingSockQueueNotEmpty.ResetEvent();
	}

	return sock;
}

int CTcpServer::getPendingSockCnt()
{
	CSingleLock lock(&m_pendingSockQueueLock);
	lock.Lock();

	return int(m_pendingSockQueue.size());
}

CTcpServer::CTcpServer() :
m_listenFd(INVALID_SOCKET)
{
	
}

CTcpServer::~CTcpServer(void)
{	
	close();	
}

bool CTcpServer::isListening()
{
	return m_acceptThread.IsRunning();
}

bool CTcpServer::listen(const char *addr /* = NULL */, u_short port /* = 0 */)
{	
	assert(!isListening());

	//----------------------
	// Create a SOCKET for listening for
	// incoming connection requests.
	m_listenFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_listenFd == INVALID_SOCKET) {
		TRACE("socket() failed.\n");
		return false;
	}
	
	//----------------------
	// The sockaddr_in structure specifies the address family,
	// IP address, and port for the socket that is being bound.
	sockaddr_in service;
	service.sin_family = AF_INET;

	if (NULL == addr)
	{
		service.sin_addr.s_addr = INADDR_ANY; 
	}
	else
	{
		service.sin_addr.s_addr = inet_addr(addr);
	}
	
	service.sin_port = htons(port);
	if (bind( m_listenFd, (SOCKADDR*) &service, sizeof(service)) == SOCKET_ERROR) {
			TRACE("bind() failed.\n");
			return false;
	}

	//----------------------
	// Listen for incoming connection requests.
	// on the created socket
	if (::listen( m_listenFd, 1 ) == SOCKET_ERROR)
		printf("Error listening on socket.\n");

	m_acceptThread.Start(this);
	
	return true;
}

void CTcpServer::close()
{
	/*assert(m_listenFd != INVALID_SOCKET);*/
	if ( INVALID_SOCKET == m_listenFd )// 如果没有开始或者已经关闭，直接返回
	{
		return;
	}

	// call this first to unblock accept()
	closesocket(m_listenFd); 

	// stop thread
	m_acceptThread.Stop();	

	// close all pending sockets
	while (getPendingSockCnt() > 0)
	{
		closesocket(popPendingSock());
	}
	
}

bool CTcpServer::waitForNewConnection(DWORD timeout)
{
	CSingleLock lock(&m_pendingSockQueueNotEmpty);
	if (lock.Lock(timeout))
		return true;
	else
		return false;
}

bool CTcpServer::hasPendingConnections() 
{
	if (getPendingSockCnt() > 0)
		return true;
	else
		return false;
}

SOCKET CTcpServer::nextPendingConnection()
{
	assert(hasPendingConnections());
	return popPendingSock();
}

