#pragma once

#include "gkhy\qzebralib\qzebra_lib_global.hpp"
#include "gkhy\qzebralib\DynamicRingBuffer.hpp"
#include <QtGlobal>
#include <QObject>
#include <QPointer>

class QString;
class QHostAddress;
class QSocketNotifier;
class QTimer;

namespace gkhy
{
	namespace MfcMinus
	{
		class AsyncSocket;		
	}
	namespace QZebraLib
	{
		class QZEBRA_LIB_EXPORT YaTcpSocket : public QObject
		{
			Q_OBJECT

		public:
			enum Mode { WriteOnly, ReadOnly, ReadWrite };
			enum SocketState { UnconnectedState, ConnectingState, ConnectedState };

		public:
			YaTcpSocket(QObject* parent = 0, int writebufferSize = 64 * 1024);
			virtual ~YaTcpSocket();

		private:
			Q_DISABLE_COPY(YaTcpSocket);

		public:		
			bool connectToHost(
				const QString& hostIP, 
				quint16 port,
				YaTcpSocket::Mode mode,
				bool autoConnect = false);			

			// when set, the class enters the ConnectedState.
			bool setSocketDescriptor(
				int socketDescriptor,
				YaTcpSocket::Mode mode,
				YaTcpSocket::SocketState state = ConnectedState);

			void close();
			void abort() { close(); }

			int socketDescriptor() const;
			
			bool isValid() const;

			int freeWriteBufferSize() { return m_writeBuffer.totalWritableSize(); }

			int write(const char* buf, int len);
			int read(char* buf, int len);

			Mode mode() { return m_mode; }
			QString hostIp() { return m_hostIp; }
			quint16 port() { return m_port; }

		protected:
			//DynamicRingBuffer& writeBuffer() { return m_writeBuffer; }		
			void timerEvent (QTimerEvent* event);

		signals:
			void connected();
			void disconnected();	
			void bytesWritten (qint64 bytes);
			void readyRead();
			void error();

		private:
			void createNotifiers();

		private slots:
			void writeActivated (int socket);
			void readActivated (int socket);		

		private:			
			int m_timerId;
			QString m_hostIp;
			quint16 m_port;
			Mode m_mode;
			SocketState m_state;		
			QPointer<QSocketNotifier> m_readNotifier;
			DynamicRingBuffer m_writeBuffer;
			QPointer<QSocketNotifier> m_writeNotifier;
			gkhy::MfcMinus::AsyncSocket* m_asyncSocket;			
		};
	}
}