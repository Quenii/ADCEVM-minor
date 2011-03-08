#pragma  once

#include "qserver.h"

class QSarPackets;
class QSar;
class QDev;

class QSarServer : public QServer
{
public:
	QSarServer(QObject* parent = 0);
	~QSarServer();

protected:
	const QList<QRdmPacket*>& rdmPackets() const;
	qint16 port() const; 
	QDev* dev() const;

private:
	QSar* m_sar;
	QSarPackets* m_packets;
};

