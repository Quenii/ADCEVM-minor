
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
			* connectToServer - ���ӷ�������
			*
			* @param ipAddr ip��ַ��
			* @param port  �˿ں�
			* @param timeout �Ժ���Ϊ��λ��ʱ��
			* @return ʧ�ܷ���false���ɹ�����true��
			*/
			bool connectToServer(const char *ipAddr, unsigned short port); 
			bool isConnected();


			/**
			* setSocketDescriptor- ����socket
			* @param ������-1���޴���0.
			*
			* AsyncSocket����ȫ�ӹܣ����������ʵ���ʱ��ر�socketDescriptor��
			* �����߲�Ҫ���йرգ�
			*/
			bool setSocketDescriptor(int socketDescriptor);

			/** 
			* close - �ر�socket��
			*/
			void close();

			/** 
			* waitForReadOrWrite - ���socket�Ƿ�ɶ���д��
			*
			* @param timeout �Ժ���Ϊ��λ��ʱ��
			* @return �������socket���󣬷���-1������ɹ���timeoutʱ����socket�ɶ����д������1��
			* �����ʱ������0
			* 
			*/
			int waitForReadOrWrite(bool bWaitRead, bool bWaitWrite, bool& bReadable, bool& bWritable, unsigned int timeout = 10);


			/** 
			* receiveData - ��socket�Ͻ������ݡ�
			*
			* @param buff �����յ������ݴ����buff��
			* @param nTonToRecv ��Ҫ�������ݵĳ���
			* @return �������socket���󣬷���-2��������ӱ��رգ�����-1��
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
			int m_socket;
		};
	}
}