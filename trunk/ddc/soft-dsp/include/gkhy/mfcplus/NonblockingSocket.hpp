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
			 * connectToServer - ���ӷ�������
			 *
			 * @param ipAddr ip��ַ��
			 * @param port  �˿ں�
			 * @param timeout �Ժ���Ϊ��λ��ʱ��
			 * @return ʧ�ܷ���-1���ɹ�����0��
			 * 
			 * �������������ͼ����timeoutʱ�������Ϸ�������
			 */
			int connectToServer(const char *ipAddr, u_short port, DWORD timeout = 10);

	
			/**
			 * setSocketDescriptor- ����socket
			 * @param ������-1���޴���0.
			 *
			 * CNonblockingSocket����ȫ�ӹܣ����������ʵ���ʱ��ر�socketDescriptor��
			 * �����߲�Ҫ���йرգ�
			 */
			int setSocketDescriptor(SOCKET socketDescriptor);

			/** 
			 * close - �ر�socket��
			 *
			 * @return �������socket���󣬷���-1������ɹ��ر���socket������1��
			 * 
			 */
			int close();

			/** 
			 * waitForReadOrWrite - ���socket�Ƿ�ɶ���д��
			 *
			 * @param timeout �Ժ���Ϊ��λ��ʱ��
			 * @return �������socket���󣬷���-1������ɹ���timeoutʱ����socket�ɶ����д������1��
			 * �����ʱ������0
			 * 
			 */
			int waitForReadOrWrite(bool bWaitRead, bool bWaitWrite, bool& bReadable, bool& bWritable, DWORD timeout = 10);

			
			/** 
			 * receiveData - ��socket�Ͻ������ݡ�
			 *
			 * @param buff �����յ������ݴ����buff��
			 * @param nTonToRecv ��Ҫ�������ݵĳ���
			 * @return �������socket���󣬷���-1��������ӱ��رգ�����-1��
			 * �������WSAEWOULDBLOCK������0��
			 * ����ɹ����������ݣ�����ʵ�ʽ��յ������ݳ���
			 * 
			 */
			int receiveData(char* buff, const int nToRecv);

			/** 
			 * sendData - ��socket�Ϸ������ݡ�
			 *
			 * @param buff  ��Ҫ�����͵�����
			 * @param nTonToRecv ���������ݵĳ���
			 * @return �������socket���󣬷���-1���������WSAEWOULDBLOCK������0��
			 * ����ɹ����������ݣ����ط��͵����ݳ���
			 * 
			 */
			int sendData(const char* buf, const int nToSend);
			
		private:
			SOCKET m_socket;
		};
	}
}

