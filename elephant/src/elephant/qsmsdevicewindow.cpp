#include "qsmsdevicewindow.h"
#include "qsmsparamwindow.h"
#include "qsmstypes.h"
#include "gkhy/pagoda/qrdmpeer.h"

QSmsDeviceWindow::QSmsDeviceWindow(QWidget *parent)
	: QDeviceWindow(parent)
	, m_packets(0)
{
	m_packets = new QSmsPackets(this);

	setWindowTitle(tr("SAR Emulator"));

    // create param widget
	QSmsParamWindow* smsParamWindow = new QSmsParamWindow(this);
	setCentralWindow(smsParamWindow);

	// create rdm peer object
	gkhy::pagoda::QRdmPeer* rdmPeer = new gkhy::pagoda::QRdmPeer(this);
	rdmPeer->installPacket(m_packets->list);
	ui.connectionBar->setSocket(rdmPeer);

	// create all packets	
	bool ok = connect(&m_packets->smsConfig, SIGNAL(setLocal(const SmsConfig&, int&)),
		smsParamWindow, SLOT(set(const SmsConfig&, int&))); Q_ASSERT(ok);
	ok = connect(&m_packets->smsConfig, SIGNAL(getLocal(SmsConfig&, int&)),
		smsParamWindow, SLOT(get(SmsConfig&, int&))); Q_ASSERT(ok);

	ok = connect(&m_packets->smsStatus, SIGNAL(setLocal(const SmsStatus&, int&)),
		smsParamWindow, SLOT(set(const SmsStatus&, int&))); Q_ASSERT(ok);

	ok = connect(rdmPeer, SIGNAL(packetReceived(const QRdmPacket&)), 
		this, SLOT(on_packetReceived(const QRdmPacket&))); Q_ASSERT(ok);

	// load settings
	loadSettings(windowTitle());
}

QSmsDeviceWindow::~QSmsDeviceWindow()
{
 
}

void QSmsDeviceWindow::on_packetReceived(const QRdmPacket &packet)
{
	packet.setLocal();
}