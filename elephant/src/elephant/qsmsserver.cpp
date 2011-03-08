#include "qsmsserver.h"
#include "qsms.h"
#include "qsmssettings.h"

QSmsServer::QSmsServer(QObject *parent)
	: QServer(parent)
	, m_sms(0)
	, m_packets(0)
{
	m_sms = new QSms(this);
	m_packets = new QSmsPackets(this);

	m_sms->start();

}

QSmsServer::~QSmsServer()
{
	m_sms->stop();
}


qint16 QSmsServer::port() const
{
	QSmsSettings s;

	return s.serverPort();
}

QDev* QSmsServer::dev() const
{
	return m_sms;
}

const QList<QRdmPacket*>& QSmsServer::rdmPackets() const
{
	return m_packets->list;
}