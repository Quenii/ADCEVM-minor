#include "stdafx.h"
#include "gkhy/mfcminus/AsyncSocket.hpp"
#include <WinSock2.h>
#include <cassert>

using namespace gkhy::MfcMinus;

AsyncSocket::AsyncSocket(void):m_socket(INVALID_SOCKET)
{
}
AsyncSocket::~AsyncSocket(void)
{
	close();
}

int AsyncSocket::socketDescriptor()
{
	return m_socket;
}

bool AsyncSocket::connectToServer(const char *ipAddr, unsigned short port)
{
	if (INVALID_SOCKET != m_socket)
	{
		assert(false);
		return false;
	}

	// Create a tmp socket. 
	m_socket = (int)socket( AF_INET, SOCK_STREAM, IPPROTO_TCP ); 
	if ( INVALID_SOCKET == m_socket )
	{  
		return false; 
	} 

	// Connect to a server. 
	sockaddr_in clientService; 
	clientService.sin_family = AF_INET; 
	clientService.sin_addr.s_addr = inet_addr( ipAddr ); 
	clientService.sin_port = htons( port ); 
	u_long nonBlock = 1;
	if (SOCKET_ERROR == ::ioctlsocket(m_socket, FIONBIO, &nonBlock))
	{
		close();
		return false;
	}

	int nConn = connect(m_socket, (SOCKADDR*)&clientService, sizeof(clientService));
	//With a nonblocking socket, the connection attempt cannot be completed immediately. 
	//In this case, connect will return SOCKET_ERROR, and WSAGetLastError will return 
	//WSAEWOULDBLOCK.In the case, try again unless it is timeout. 
	if (SOCKET_ERROR == nConn && WSAEWOULDBLOCK != WSAGetLastError())
	{
		close();
		return false;
	}

	return true;
}

bool AsyncSocket::isConnected()
{
	fd_set wfd;
	FD_ZERO(&wfd);
	FD_SET(m_socket, &wfd);
	timeval stimeout = 
	{
		0, 	/* sec */
		0 * 1000  /* microseconds */
	};

	int nSel = select(NULL, NULL, &wfd, NULL, &stimeout);	
	if ( nSel < 0 )
	{		
		return false;
	}

	return true;
}

bool AsyncSocket::setSocketDescriptor(int socketDescriptor)
{
	assert(INVALID_SOCKET == m_socket);

	u_long nonBlock = 1;
	m_socket = socketDescriptor;
	
	if (SOCKET_ERROR == ::ioctlsocket(m_socket, FIONBIO, &nonBlock))
	{		
		return false;
	}
       
	return true;
}

void AsyncSocket::close()
{
	if (INVALID_SOCKET != m_socket)
	{
		int res = ::shutdown(m_socket, SD_SEND);
		//assert(0 == res);
		res = ::closesocket(m_socket);
		assert(0 == res);
		m_socket = INVALID_SOCKET;
	}	
}

int AsyncSocket::waitForReadOrWrite( bool bWaitRead, bool bWaitWrite, bool& bReadable, bool& bWritable, unsigned int timeout/* = 10000*/)
{
	bReadable = false;
	bWritable = false;
	if ( !bWaitRead && !bWaitWrite)
	{
		assert(false);
		return 0;
	}

	fd_set rdFds;
	fd_set wrFds;
	timeval stimeout = 
	{
		0, 	/* sec */
		timeout * 1000  /* microseconds */
	};

	FD_ZERO(&rdFds);
	FD_ZERO(&wrFds);

	if ( bWaitRead )
	{
		FD_SET(m_socket, &rdFds);
	}
	if ( bWaitWrite )
	{
		FD_SET(m_socket, &wrFds);
	}

	int nReturn = select(NULL, &rdFds, &wrFds, NULL, &stimeout);
	if (-1 == nReturn ) // -1 for error
	{
		return -1;
	}	

	if (nReturn > 0)
	{

		if (FD_ISSET(m_socket, &rdFds)) 
		{
			bReadable = true;
		}

		if (FD_ISSET(m_socket, &wrFds))
		{
			bWritable = true;
		}
	}		
	return 0;
}


int AsyncSocket::receiveData(char* buff, const int nToRecv)
{
	int nRecv = ::recv(m_socket, buff, nToRecv, 0);

	//the connection has been gracefully closed
	//Socket is invalid
	if ( 0 == nRecv )
	{
		return -1;
	}
	else if ( SOCKET_ERROR == nRecv )
	{
		//A value of SOCKET_ERROR is returned with the error code set to WSAEWOULDBLOCK.
		//It indicas that no incoming data is available at the socket
		if ( WSAEWOULDBLOCK == WSAGetLastError())
		{
			return 0;
		}
		else
		{
			//SOCKET_ERROR
			return -2;
		}
	}
	else
	{
		//no error occurs, recv returns the number of bytes received
		return nRecv;
	}
}

int AsyncSocket::sendData(const char* buff, const int nToSend)
{
	int nSend = ::send(m_socket, buff, nToSend, 0);
	if ( SOCKET_ERROR == nSend )
	{

		//A value of SOCKET_ERROR is returned with the error code set to WSAEWOULDBLOCK.
		//It indicates that no buffer space is available within the transport system to 
		//hold the data to be transmitted.
		if ( WSAEWOULDBLOCK == WSAGetLastError() )
		{
			return 0;
		}

		//SOCKET_ERROR
		return -1;
	}
	//no error occurs, send returns the number of bytes transmitted
	return  nSend;
}