#include "StdAfx.h"

#include "gkhy\mfcplus\BlockingTcpSocket.hpp"
#include <assert.h>

using namespace gkhy::mfcplus;

// servers may use	
BOOL CBlockingTcpSocket::Listen(unsigned short port, const char* addr, int connectionBacklog /*= 5*/)
{	
	// Create a SOCKET for listening for
	// incoming connection requests.
	if ((m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) 
	{
		return FALSE;
	}

	// The sockaddr_in structure specifies the address family,
	// IP address, and port for the socket that is being bound.
	sockaddr_in service;
	service.sin_family = AF_INET;
	service.sin_addr.s_addr = addr ? inet_addr(addr) : INADDR_ANY;
	service.sin_port = htons(port);

	if (bind( m_socket, (SOCKADDR*) &service, sizeof(service)) == SOCKET_ERROR) 
	{
		return FALSE;
	}

	//----------------------
	// Listen for incoming connection requests.
	// on the created socket
	if (listen( m_socket, connectionBacklog ) == SOCKET_ERROR)
		return FALSE;

	return TRUE;
}

BOOL CBlockingTcpSocket::Accept(CBlockingTcpSocket& rConnectedSocket)
{
	SOCKET AcceptSocket;

	// Accept the connection.				
	if ( (AcceptSocket = accept( m_socket, NULL, NULL)) == INVALID_SOCKET)
		return FALSE;

	rConnectedSocket.Attach(AcceptSocket);

	return TRUE;				
}

void CBlockingTcpSocket::Attach(const SOCKET& socket)
{
	m_socket = socket;
}

// clients may use
BOOL CBlockingTcpSocket::Connect(const char* addr, unsigned short port)
{
	// Create a SOCKET for connecting to server
	if ( (m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET )
	{
		return FALSE;
	}

	//----------------------
	// The sockaddr_in structure specifies the address family,
	// IP address, and port of the server to be connected to.
	sockaddr_in clientService; 
	clientService.sin_family = AF_INET;
	clientService.sin_addr.s_addr = inet_addr(addr);
	clientService.sin_port = htons( port );

	//----------------------
	// Connect to server.
	if ( connect( m_socket, (SOCKADDR*) &clientService, sizeof(clientService) ) == SOCKET_ERROR)
	{
		return FALSE;
	}

	return TRUE;
}

// common 
void CBlockingTcpSocket::Close()
{
	closesocket(m_socket);
}

void CBlockingTcpSocket::OtherThreadClose()
{
	closesocket(m_socket);
}

// BOOL CBlockingTcpSocket::Recv(char* buf, int len )
// {
// 
// }
 
BOOL CBlockingTcpSocket::Send(const char* buf, int len)
{
	int count = 0;
	while (count < len)
	{
		int sent = send( m_socket, buf + count, len - count, 0 );
		if (SOCKET_ERROR == sent)
		{	
			return FALSE;
		}

		count += sent;
	}

	return TRUE;
}

