#include "QConnectionBar.h"

#include <cassert>
#include <QSettings>

QConnectionBar::QConnectionBar(QWidget *parent)
	: QWidget(parent)
	, m_tcpSocket(0)
{
	ui.setupUi(this);

	//ui.statusLabel->setLabel(tr("Connection: "));
	ui.statusLabel->setStatus(QStatusLabel::Unconnected);

	startTimer(300);

	enableConnection(false);
}

QConnectionBar::~QConnectionBar()
{

}

void QConnectionBar::loadSettings(QString path)
{
	QSettings settings;
	settings.beginGroup(path);

	QString ip = settings.value(tr("IP Addr"), "127.0.0.1").toString();
	ui.ipEdit->setText(ip);
	QString port = settings.value(tr("Port"), 4000).toString();
	ui.portEdit->setText(port);
	bool enabled = settings.value(tr("Connection Enabled"), false).toBool();
	enableConnection(enabled);	

}

void QConnectionBar::saveSettings(QString path)
{
	QSettings settings;
	settings.beginGroup(path);

	settings.setValue(tr("IP Addr"), ui.ipEdit->text());
	settings.setValue(tr("Port"), ui.portEdit->text());
	
	settings.setValue(tr("Connection Enabled"), isEnabled());	
}

void QConnectionBar::setSocket(QRebufferedTcpSocket* tcpSocket)
{
	if (!tcpSocket)
		return ;
	
	if (m_tcpSocket)
	{
		bool ok = m_tcpSocket->disconnect(this);
		Q_ASSERT(ok);
	}		
	
	m_tcpSocket = tcpSocket;
	bool ok = false;
	ok = connect(m_tcpSocket, SIGNAL(connected()), this, SLOT(slot_tcpSocket_connected()));
	Q_ASSERT(ok);
	
	ok = connect(m_tcpSocket, SIGNAL(disconnected()), this, SLOT(slot_tcpSocket_disconnected()));
	Q_ASSERT(ok);
	
	ok = connect(m_tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slot_tcpSocket_error()));
	Q_ASSERT(ok);
	
	ok = connect(m_tcpSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
		this, SLOT(slot_tcpSocket_stateChanged(QAbstractSocket::SocketState)));		
	Q_ASSERT(ok);
}

void QConnectionBar::slot_tcpSocket_connected()
{
}

void QConnectionBar::slot_tcpSocket_disconnected()
{
}

void QConnectionBar::slot_tcpSocket_error()
{
	if (m_tcpSocket && m_tcpSocket->state() != QTcpSocket::ConnectedState)
	{
		m_tcpSocket->close();
	}
}

void QConnectionBar::slot_tcpSocket_stateChanged(QAbstractSocket::SocketState socketState)
{
	switch (socketState)
	{
	case QTcpSocket::ConnectingState:
		ui.statusLabel->setStatus(QStatusLabel::Connecting);
		break;

	case QTcpSocket::ConnectedState:
		ui.statusLabel->setStatus(QStatusLabel::Connected);
		break;

	default: // case QTcpSocket::UnconnectedState:
		ui.statusLabel->setStatus(QStatusLabel::Unconnected);
		break;
	}
}

void QConnectionBar::enableConnection(bool enable)
{
	m_enableConnection = enable;

	ui.enableConnectionPushButton->setText(m_enableConnection ? tr("Disable") : tr("Enable"));	

	if (!m_enableConnection)
	{
		if (m_tcpSocket)
			m_tcpSocket->close();
		ui.statusLabel->setStatus(QStatusLabel::Unconnected);

	}	
}

void QConnectionBar::on_enableConnectionPushButton_clicked()
{
	enableConnection(!isConnectionEnabled());
}

void QConnectionBar::timerEvent(QTimerEvent *event)
{	
	if (m_enableConnection && m_tcpSocket &&
		m_tcpSocket->state() != QTcpSocket::ConnectedState)
	{
			m_tcpSocket->abort();
			QString ip = ui.ipEdit->text();
			qint16 port = qint16(ui.portEdit->text().toInt());
			m_tcpSocket->connectToHost(ip, port);

			ui.statusLabel->setStatus(QStatusLabel::Connecting);
	}	
}