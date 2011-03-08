#pragma once
#include "gkhy/qzebralib/qzebra_lib_global.hpp"
#include "gkhy/qzebralib/Message.hpp"
#include "gkhy/qzebralib/PumpBuffer.hpp"
#include "gkhy/qzebralib/DynamicRingBuffer.hpp"
#include "gkhy/qzebralib/YaTcpSocket.hpp"
#include <vector>
#include <QTcpSocket>
#include <QObject>
#include <QByteArray>
#include <QHostAddress>
#include <QPointer>

namespace gkhy
{
	namespace MfcMinus
	{
		class CircularFifo;
	}

	namespace QZebraLib 
	{
		class QZEBRA_LIB_EXPORT Messenger : public QObject
		{				
			Q_OBJECT

		public:
			Messenger(QObject *parent = 0 );
			virtual ~Messenger(void);
		
		private:
			Q_DISABLE_COPY(Messenger)

		public:			
			
			/**
			 * setSocketDescriptor- ����socket
			 */
			void setTcpSocket(int socket);	
			/** 
			 * connectToServer - ���ӷ�������
			 *
			 * @param address ip��ַ��
			 * @param port  �˿ں�
			 * 
			 */
			void connectToServer(QHostAddress & address, quint16 port, bool autoConnect = false);
		   /*
			* �ر����ӣ����������ݶ�����
			*/
			void close();

		   /**
			* Messenger�Ƿ�alive
			*/
			bool isAlive();

			// Fifo limit is max(max_len_sent, len) * bufferLimitFactor;
			bool isReadyToWrite(int len);			
			/**
			 * writeMsg - write a piece of message 
			 *
			 * @param msg pointer to the message to write
			 * @return 1 if written, 0 if not written , -1 if socket is invalid.
			 */
			int writeMsg(Message& msg);			

		signals:
			void messageReceived(Message& msg);
			void connected();
			void disconnected();			

		private slots:
			void slotReadyRead();
			void slotConnected();
			void slotInvalidated();
		private:
			void configNewConnection();
			
		private:			
			int m_maxMsgLenSent;
			Message m_msg;			
			QPointer<YaTcpSocket> m_socket;
			bool m_bAlive;				
			PumpBuffer m_recvMsgBuff;
		};
	}
}