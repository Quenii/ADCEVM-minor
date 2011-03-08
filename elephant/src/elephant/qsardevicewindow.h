#pragma once

#include "qdevicewindow.h"
#include "gkhy/pagoda/qrdmpacket.h"

class QSarPackets; 

using namespace gkhy::pagoda;

class QSarDeviceWindow : public QDeviceWindow
{
	Q_OBJECT

public:
	QSarDeviceWindow(QWidget*parent);
	~QSarDeviceWindow();

private slots:
	void on_packetReceived(const QRdmPacket& packet);

private:	
	QSarPackets* m_packets;
};
