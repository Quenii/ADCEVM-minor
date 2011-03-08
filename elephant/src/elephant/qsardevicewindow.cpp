#include "qsardevicewindow.h"
#include "qsarparamwindow.h"
#include "qsartypes.h"
#include "gkhy/pagoda/qrdmpeer.h"

QSarDeviceWindow::QSarDeviceWindow(QWidget *parent)
	: QDeviceWindow(parent)
	, m_packets(0)
{
	m_packets = new QSarPackets(this);

	setWindowTitle(tr("SAR Emulator"));

    // create param widget
	QSarParamWindow* sarParamWindow = new QSarParamWindow(this);
	setCentralWindow(sarParamWindow);

	// create rdm peer object
	gkhy::pagoda::QRdmPeer* rdmPeer = new gkhy::pagoda::QRdmPeer(this);
	rdmPeer->installPacket(m_packets->list);
	ui.connectionBar->setSocket(rdmPeer);

	// create all packets	
	bool ok = connect(&m_packets->sarConfig, SIGNAL(setLocal(const SarConfig&, int&)),
		sarParamWindow, SLOT(set(const SarConfig&, int&))); Q_ASSERT(ok);
	ok = connect(&m_packets->sarConfig, SIGNAL(getLocal(SarConfig&, int&)),
		sarParamWindow, SLOT(get(SarConfig&, int&))); Q_ASSERT(ok);

	ok = connect(&m_packets->sarStatus, SIGNAL(setLocal(const SarStatus&, int&)),
		sarParamWindow, SLOT(set(const SarStatus&, int&))); Q_ASSERT(ok);

	ok = connect(rdmPeer, SIGNAL(packetReceived(const QRdmPacket&)), 
		this, SLOT(on_packetReceived(const QRdmPacket&))); Q_ASSERT(ok);

	// load settings
	loadSettings(windowTitle());
}

QSarDeviceWindow::~QSarDeviceWindow()
{
 
}

void QSarDeviceWindow::on_packetReceived(const QRdmPacket &packet)
{
	packet.setLocal();
}