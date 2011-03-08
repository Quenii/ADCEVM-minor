#include "qsarserver.h"
#include "qsar.h"
#include "qsarsettings.h"
#include "qdev.h"

QSarServer::QSarServer(QObject *parent)
	: QServer(parent)
	, m_sar(0)
	, m_packets(0)
{
	m_sar = new QSar(this);
	m_packets = new QSarPackets(this);

	// set to local
	bool ok = connect(&m_packets->sarConfig, SIGNAL(setLocal(const SarConfig&, int&)), 
		m_sar, SLOT(set(const SarConfig&, int&))); Q_ASSERT(ok);
	ok = connect(&m_packets->sarCommand, SIGNAL(setLocal(const SarCommand&, int&)), 
		m_sar, SLOT(set(const SarCommand&, int&))); Q_ASSERT(ok);

	// get form local
	ok = connect(&m_packets->sarStatus, SIGNAL(getLocal(SarStatus&, int&)),
		m_sar, SLOT(get(SarStatus&, int&))); Q_ASSERT(ok);
 
	m_sar->start();
}

QSarServer::~QSarServer()
{
	m_sar->stop();
}


qint16 QSarServer::port() const
{
	QSarSettings s;

	return s.serverPort();
}

QDev* QSarServer::dev() const
{
	return m_sar;
}


const QList<QRdmPacket*>& QSarServer::rdmPackets() const
{
	return m_packets->list;
}
	

