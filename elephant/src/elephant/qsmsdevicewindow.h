#pragma once

#include "qdevicewindow.h"
#include "gkhy/pagoda/qrdmpacket.h"

class QSmsPackets; 

using namespace gkhy::pagoda;

class QSmsDeviceWindow : public QDeviceWindow
{
	Q_OBJECT

public:
	QSmsDeviceWindow(QWidget*parent);
	~QSmsDeviceWindow();

private slots:
	void on_packetReceived(const QRdmPacket& packet);

private:	
	QSmsPackets* m_packets;
};
