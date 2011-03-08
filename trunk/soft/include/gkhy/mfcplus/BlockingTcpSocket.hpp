#pragma once

#include <WinSock2.h>
#include <iostream>

namespace gkhy
{
	namespace mfcplus
	{
		class AFX_EXT_CLASS CBlockingTcpSocket// : CSocket
		{	
		public:
			// servers may use	
			BOOL Listen(unsigned short port, const char* addr, int connectionBacklog = 5);			
			BOOL Accept(CBlockingTcpSocket& rConnectedSocket);
			void Attach(const SOCKET& socket);
			
			// clients may use
			BOOL Connect(const char* addr, unsigned short port);

			// common 
			void Close();

			void OtherThreadClose(); 

			//BOOL Recv(void* lpBuf, int nBufLen);
			BOOL Send(const char* buf, int len);	

		private:
			SOCKET m_socket;
		};
	}
}

