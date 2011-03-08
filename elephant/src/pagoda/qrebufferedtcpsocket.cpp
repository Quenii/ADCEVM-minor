#include "qrebufferedtcpsocket.h"

#include <QTcpSocket>
#include <QMetaObject>

using namespace gkhy::pagoda;

#define TCPSOCKET_BUFFER_SIZE 32768

QRebufferedTcpSocket::QRebufferedTcpSocket(QObject * parent, int writeBufferSize, int readBufferSize)
: QObject(parent)
, m_ibuf(readBufferSize)
, m_obuf(writeBufferSize)
{
	m_tcpSocket = new QTcpSocket(this);
	
	bool ok = connect(m_tcpSocket, SIGNAL(connected()), this, SIGNAL(connected()));
	Q_ASSERT(ok);
	ok = connect(m_tcpSocket, SIGNAL(disconnected()), this, SIGNAL(disconnected()));
	Q_ASSERT(ok);
	ok = connect(m_tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SIGNAL(error(QAbstractSocket::SocketError)));
	Q_ASSERT(ok);
	ok = connect(m_tcpSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SIGNAL(stateChanged(QAbstractSocket::SocketState)));
	Q_ASSERT(ok);
	ok = connect(m_tcpSocket, SIGNAL(bytesWritten(qint64)), this, SLOT(on_tcpSocket_bytesWritten(qint64)));
	Q_ASSERT(ok);
	ok = connect(m_tcpSocket, SIGNAL(readyRead()), this, SLOT(on_tcpSocket_readyRead()));
	Q_ASSERT(ok);
}

QRebufferedTcpSocket::~QRebufferedTcpSocket()
{

}

void QRebufferedTcpSocket::connectToHost(const QString & hostName, quint16 port) 
{
	m_ibuf.clear();
	m_obuf.clear();
	m_tcpSocket->connectToHost(hostName, port); 
}

bool QRebufferedTcpSocket::setSocketDescriptor(int socketDescriptor) 
{
	m_ibuf.clear();
	m_obuf.clear();
	return m_tcpSocket->setSocketDescriptor(socketDescriptor); 
}

void QRebufferedTcpSocket::close() 
{
	m_tcpSocket->close(); 
}

void QRebufferedTcpSocket::abort()
{
	m_tcpSocket->abort(); 
}

qint64 QRebufferedTcpSocket::write(const char * data, qint64 maxSize)
{
	if (maxSize <= 0)
		return 0;

	int done = m_obuf.write(data, maxSize);	
	int subWritten = writeBuffer2TcpSocket();
	if (subWritten < 0)
	{
		return -1;
	}

	if (done < maxSize) // more to write...
	{
		done += m_obuf.write(data + done, maxSize - done);
	}

	return done;
}

qint64 QRebufferedTcpSocket::read(char * data, qint64 maxSize)
{
	int toRead = (int)qMin<qint64>(maxSize, m_ibuf.count());
	memcpy(data, m_ibuf.readBuffer(), toRead);
	m_ibuf.chop(toRead);
	return toRead;
}

int QRebufferedTcpSocket::writeBuffer2TcpSocket()
{
	int toWrite = (int) qMin<qint64>(m_obuf.count(), TCPSOCKET_BUFFER_SIZE - m_tcpSocket->bytesToWrite());
	int left = toWrite;
	while (left)
	{
		int subToWrite = qMin<int>(left, m_obuf.nextReadBlockSize());
		int subWritten = m_tcpSocket->write(m_obuf.nextReadBlock(), subToWrite);
		if (subWritten <= 0) // must be some kinds or error.
		{
			Q_ASSERT(false);
			return -1;
		}

		m_obuf.chop(subWritten);
		left -= subWritten;
	}

	return toWrite;
}

void QRebufferedTcpSocket::on_tcpSocket_bytesWritten(qint64 bytes)
{
	writeBuffer2TcpSocket();	
	
	emit bytesWritten(bytes);
}

void QRebufferedTcpSocket::on_tcpSocket_readyRead()
{
	m_ibuf.squeeze();

	char* buff = m_ibuf.writeBuffer();
	int buffSize = m_ibuf.writeBufferSize();
	int toRead = qMin<qint64>(buffSize, m_tcpSocket->bytesAvailable());	
	int read = m_tcpSocket->read(buff, toRead);
	if (read > 0)
	{
		m_ibuf.commit(read);
	}

	// make sure there are bytes waiting to be read out.
	if (m_ibuf.count() > 0) 
	{	
		emit readyRead();
	}
}
