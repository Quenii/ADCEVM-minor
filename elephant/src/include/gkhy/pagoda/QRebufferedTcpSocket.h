#pragma  once 
#include "gkhy/pagoda/pagoda_global.h"
#include "gkhy/pagoda/PumpBuffer.h"
#include "gkhy/pagoda/RingBuffer.h"

#include <QObject>
#include <QTcpSocket>

namespace gkhy
{
	namespace pagoda
	{
		class PAGODA_EXPORT QRebufferedTcpSocket : public QObject
		{
			Q_OBJECT

		public:
			QRebufferedTcpSocket(QObject * parent = 0, int writeBufferSize = 32 * 1024, int readBufferSize = 32 * 1024);
			~QRebufferedTcpSocket();
		private:
			Q_DISABLE_COPY(QRebufferedTcpSocket);

		public:			
			void connectToHost(const QString & hostName, quint16 port);
			bool setSocketDescriptor(int socketDescriptor);
			void close();
			void abort();

			QAbstractSocket::SocketState state() { return m_tcpSocket->state(); }

			int freeWriteBufferSize() { return m_obuf.totalWritableSize(); }			
			qint64 write(const char * data, qint64 maxSize); 			
			qint64 read(char * data, qint64 maxSize);

			int bytesAvailable() { return m_ibuf.count(); }
			char* readBuffer() { return m_ibuf.readBuffer(); }
			void chop(int n) { m_ibuf.chop(n); }


			int readBufferSize() {	return m_ibuf.size(); }
			int writeBufferSize() { return m_obuf.size(); }

			void setReadBufferSize(int size) { m_ibuf.resize(size); }
			void setWriteBufferSize(int size) {	m_obuf.resize(size); }			

		signals:
			void connected();
			void disconnected();
			void error(QAbstractSocket::SocketError socketError);
			void stateChanged(QAbstractSocket::SocketState socketState);

			void bytesWritten(qint64 bytes);
			void readyRead();

				
		private:
			int writeBuffer2TcpSocket();
		private slots:
			void on_tcpSocket_bytesWritten(qint64 bytes);
			void on_tcpSocket_readyRead(); 

		private:
			RingBuffer<char> m_obuf;
			PumpBuffer<char> m_ibuf;		
			QTcpSocket* m_tcpSocket;
		};
	}
}