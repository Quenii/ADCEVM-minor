//////////////////////////////////////////////////////////////////////////
// CTcpServer - A TCP connection-oriented server.
//
// Author: Liu Peng
// Email:  liupengee@126.com
// Copyright 2008-2009, GKHY
//
// You may freely use or modify this code provided this
// Copyright is included in all derived versions.
//
// Created : 9/8/09 Liu Peng
//              
// General Description
// ===================
// This class implements a TCP connection-oriented server, it accepts clients'
// connections and put established connections into a internal queue(the
// pending queue). 
//
// Following rules are important:
//
// 1 User of this class could take out connections if any and
//   use freely. But it's the user's responsibility to closed the taken 
//   connections
//   finally.
// 2 It's free to leave connections in this class on calling close().
//
// Example
// =======
// CTcpServer server;
// server.listen("192.168.10.67", (u_short)6666);
//
// for (int i = 0; i < 10; ++i)
// {
//    while(!server.waitForNewConnection(50)) ;
//
//	   while(server.hasPendingConnections())
//	   {
//			SOCKET sock = server.nextPendingConnection();
//            
//          // do job with sock
//
//          // close sock
//     }
//  } 
//
//  server.close();
//
//////////////////////////////////////////////////////////////////////////


#pragma once

#include <afxmt.h>
#include "gkhy/mfcplus/workerthread.hpp"
#include <queue>
#include <WinSock2.h>
#include <iostream>

namespace gkhy
{
	namespace mfcplus
	{
		class AFX_EXT_CLASS CTcpServer
		{
		private:
			class  AcceptThread : public WorkerThread
			{		

			protected:
				virtual UINT ThreadProc(LPVOID lpvoid, volatile bool& enabled);
			};

		public:
			CTcpServer();
			virtual ~CTcpServer(void);

		public:

			/**
			 * listen - Tells the server to listen for incoming connections
			 * on address address and port port. 
			 *
			 * @param addr If port is 0, a port is chosen automatically. 
			 * @param port If addr is NULL, the server will listen on all
			 * network interfaces.
			 * @return true if okay, or else false on error.
			 */
			bool listen(const char *addr = NULL, u_short port = 0);

			/**
			 * close - Stop the TCP server.
			 */
			void close();

			/**
			 * isListening - To check if the TCP server is waiting for 
			 * incoming connections.
			 */
			bool isListening();

			/**
			 * waitForNewConnection - Wait for at least one connection
			 * accepted with timeout time.
			 */
			bool waitForNewConnection(DWORD timeout);

			/**
			 * hasPendingConnections - To check if any connection accepted.
			 */
			bool hasPendingConnections();

			/**
			 * nextPendingConnection - Fetch a connection from internal queue.
			 */
			SOCKET nextPendingConnection();

		private:
			void pushPendingSock(SOCKET sock);
			SOCKET popPendingSock();
			int getPendingSockCnt();

		private:
			AcceptThread m_acceptThread;
			SOCKET m_listenFd;
			
			CCriticalSection m_pendingSockQueueLock;
			std::queue< SOCKET > m_pendingSockQueue;
			CEvent m_pendingSockQueueNotEmpty;
		};
	}
}
