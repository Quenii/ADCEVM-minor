#pragma once

#include "gkhy/pagoda/qrdmpeer.h"
#include "qsar.h"
#include "qsms.h"

#include <QPointer>
#include <qtcpserver>

using namespace gkhy::pagoda;
using namespace gkhy::PcieDab2;

class QDev;

class QServer : public QTcpServer
{
	Q_OBJECT

public:
	QServer(QObject *parent);
	~QServer();

public:
	bool listen();
	bool isEmulator();
	
	virtual qint16 port() const = 0;

protected:
	virtual const QList<QRdmPacket*>& rdmPackets() const = 0;
	virtual const QDev* dev() const = 0;	
	void incomingConnection(int socket);

private slots:
	void update();

private:
	QList< QPointer<QRdmPeer> > m_rdmpeerList;
};

