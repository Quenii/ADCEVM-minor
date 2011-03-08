#pragma  once

#include "qserver.h"

class QSmsPackets;
class QSms;
class QDev;

 class QSmsServer : public QServer
 {
 public:
 	QSmsServer(QObject* parent = 0);
 	~QSmsServer();

 protected:
	const QList<QRdmPacket*>& rdmPackets() const;
	qint16 port() const; 
	QDev* dev() const;
 
 private:
 	QSms* m_sms;
	QSmsPackets* m_packets;
 };

