#pragma once

#include <WinSock2.h>
#include <iostream>

namespace gkhy
{
	namespace mfcplus
	{
		class AFX_EXT_CLASS CNonblockingSocket
		{
		public:
			CNonblockingSocket(SOCKET sock);
			CNonblockingSocket(void);
			virtual ~CNonblockingSocket(void);
		private:
			CNonblockingSocket(const CNonblockingSocket&);
		public:

			/** 
			 * connectToServer - 连接服务器。
			 *
			 * @param ipAddr ip地址。
			 * @param port  端口号
			 * @param timeout 以毫秒为单位的时间
			 * @return 失败返回-1；成功返回0；
			 * 
			 * 本函数的设计意图是在timeout时间内连上服务器。
			 */
			int connectToServer(const char *ipAddr, u_short port, DWORD timeout = 10);

	
			/**
			 * setSocketDescriptor- 设置socket
			 * @param 出错返回-1；无错返回0.
			 *
			 * CNonblockingSocket将完全接管，并最终在适当的时候关闭socketDescriptor。
			 * 调用者不要另行关闭！
			 */
			int setSocketDescriptor(SOCKET socketDescriptor);

			/** 
			 * close - 关闭socket。
			 *
			 * @return 如果出现socket错误，返回-1；如果成功关闭了socket，返回1；
			 * 
			 */
			int close();

			/** 
			 * waitForReadOrWrite - 检测socket是否可读可写。
			 *
			 * @param timeout 以毫秒为单位的时间
			 * @return 如果出现socket错误，返回-1；如果成功在timeout时间内socket可读或可写，返回1；
			 * 如果超时，返回0
			 * 
			 */
			int waitForReadOrWrite(bool bWaitRead, bool bWaitWrite, bool& bReadable, bool& bWritable, DWORD timeout = 10);

			
			/** 
			 * receiveData - 从socket上接收数据。
			 *
			 * @param buff 将接收到的数据存放在buff中
			 * @param nTonToRecv 想要接收数据的长度
			 * @return 如果出现socket错误，返回-1；如果连接被关闭，返回-1；
			 * 如果出现WSAEWOULDBLOCK，返回0；
			 * 如果成功接收了数据，返回实际接收到的数据长度
			 * 
			 */
			int receiveData(char* buff, const int nToRecv);

			/** 
			 * sendData - 从socket上发送数据。
			 *
			 * @param buff  将要被发送的数据
			 * @param nTonToRecv 待发送数据的长度
			 * @return 如果出现socket错误，返回-1；如果出现WSAEWOULDBLOCK，返回0；
			 * 如果成功发送了数据，返回发送的数据长度
			 * 
			 */
			int sendData(const char* buf, const int nToSend);
			
		private:
			SOCKET m_socket;
		};
	}
}

