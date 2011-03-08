#include "StdAfx.h"

#include "gkhy\mfcplus\NonblockingSocket.hpp"
#include <assert.h>


using namespace std;
using namespace gkhy::mfcplus;

CNonblockingSocket::CNonblockingSocket(void):m_socket(INVALID_SOCKET)
{
}

CNonblockingSocket::CNonblockingSocket(SOCKET sock)
{
	setSocketDescriptor(sock);
}
CNonblockingSocket::~CNonblockingSocket(void)
{
	close();
}

int CNonblockingSocket::connectToServer(const char *ipAddr, u_short port, DWORD timeout /* = 10 */)
{
	// Create a tmp socket. 
	m_socket = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP ); 

	if ( INVALID_SOCKET == m_socket )
	{  
		cout << "Error at socket(): %ld " << WSAGetLastError();
		return -1; 
	} 

	// Connect to a server. 
	sockaddr_in clientService; 

	clientService.sin_family = AF_INET; 
	clientService.sin_addr.s_addr = inet_addr( ipAddr ); 
	clientService.sin_port = htons( port ); 

	u_long nonBlock = 1;
	if (SOCKET_ERROR == ::ioctlsocket(m_socket, FIONBIO, &nonBlock))
	{
		cout << "Enable nonBlocking socket failed : " << WSAGetLastError();
		return -1;
	}
	
	int nConn = connect(m_socket, (SOCKADDR*)&clientService, sizeof(clientService));

	//With a nonblocking socket, the connection attempt cannot be completed immediately. 
	//In this case, connect will return SOCKET_ERROR, and WSAGetLastError will return 
	//WSAEWOULDBLOCK.In the case, try again unless it is timeout. 
	if ((SOCKET_ERROR == nConn) && (WSAEWOULDBLOCK != WSAGetLastError()))
	{
		return -1;
	}

	fd_set wfd;
	FD_ZERO(&wfd);
	FD_SET(m_socket, &wfd);
	timeval stimeout = 
	{
		0, 	/* sec */
		timeout * 1000  /* microseconds */
	};

	int nSel = select(NULL, NULL, &wfd, NULL, &stimeout);	
	if ( nSel < 0 )
	{
		return -1;
	}
	if (nSel == 0 )
	{
		// time out
		closesocket(m_socket);
		m_socket = INVALID_SOCKET;
		return -1;
	}

	assert(FD_ISSET(m_socket, &wfd));

	return 0;

}


int CNonblockingSocket::setSocketDescriptor(SOCKET socketDescriptor)
{
	u_long nonBlock = 1;
	m_socket = socketDescriptor;

	if (SOCKET_ERROR == ::ioctlsocket(m_socket, FIONBIO, &nonBlock))
	{
		return -1;
	}
	
	return 0;
}

int CNonblockingSocket::close()
{
	if (INVALID_SOCKET == m_socket)
	{
		return 0;
	}
	int res = ::shutdown(m_socket,SD_SEND);
	assert(0 == res);
	if ( 0 == ::closesocket(m_socket) )
	{
		m_socket = INVALID_SOCKET;
		return 0;
	}
	return -1;
}

int CNonblockingSocket::waitForReadOrWrite( bool bWaitRead, bool bWaitWrite, bool& bReadable, bool& bWritable, DWORD timeout/* = 10000*/)
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


int CNonblockingSocket::receiveData(char* buff, const int nToRecv)
{
	int nRecv = ::recv(m_socket, buff, nToRecv, 0);

	//the connection has been gracefully closed
	//Socket is invalid
	if ( 0 == nRecv )
	{
		return -1;
	}
	if ( SOCKET_ERROR == nRecv )
	{
		//A value of SOCKET_ERROR is returned with the error code set to WSAEWOULDBLOCK.
		//It indicas that no incoming data is available at the socket
		if ( WSAEWOULDBLOCK == WSAGetLastError())
		{
			return 0;
		}

		//SOCKET_ERROR
		return -1;
	}

	//no error occurs, recv returns the number of bytes received
	return nRecv;
}
int CNonblockingSocket::sendData(const char* buff, const int nToSend)
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