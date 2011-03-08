
#pragma once

#include "gkhy/mfcminus/mfcminus_global.hpp"

namespace gkhy
{
	namespace MfcMinus
	{
		class MFCMINUS_API AsyncSocket
		{
		public:
			AsyncSocket(void);
			virtual ~AsyncSocket(void);
		private:
			AsyncSocket(const AsyncSocket&);
			void operator=(const AsyncSocket&);

		public:

			int socketDescriptor();

			/** 
			* connectToServer - 连接服务器。
			*
			* @param ipAddr ip地址。
			* @param port  端口号
			* @param timeout 以毫秒为单位的时间
			* @return 失败返回false；成功返回true；
			*/
			bool connectToServer(const char *ipAddr, unsigned short port); 
			bool isConnected();


			/**
			* setSocketDescriptor- 设置socket
			* @param 出错返回-1；无错返回0.
			*
			* AsyncSocket将完全接管，并最终在适当的时候关闭socketDescriptor。
			* 调用者不要另行关闭！
			*/
			bool setSocketDescriptor(int socketDescriptor);

			/** 
			* close - 关闭socket。
			*/
			void close();

			/** 
			* waitForReadOrWrite - 检测socket是否可读可写。
			*
			* @param timeout 以毫秒为单位的时间
			* @return 如果出现socket错误，返回-1；如果成功在timeout时间内socket可读或可写，返回1；
			* 如果超时，返回0
			* 
			*/
			int waitForReadOrWrite(bool bWaitRead, bool bWaitWrite, bool& bReadable, bool& bWritable, unsigned int timeout = 10);


			/** 
			* receiveData - 从socket上接收数据。
			*
			* @param buff 将接收到的数据存放在buff中
			* @param nTonToRecv 想要接收数据的长度
			* @return 如果出现socket错误，返回-2；如果连接被关闭，返回-1；
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
			int m_socket;
		};
	}
}