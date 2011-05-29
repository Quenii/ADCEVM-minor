#include "qpowermonitor.h"
#include "DacBoard.h"

QPowerMonitor::QPowerMonitor(QWidget *parent)
	: QToggleViewDialog(parent)
{
	ui.setupUi(this);

	DacBoard* board = DacBoard::instance();
	bool ok = connect(board, SIGNAL(powerMonitorDataUpdated(const PowerMonitorData&)),
		this, SLOT(update(const PowerMonitorData&)));
	Q_ASSERT(ok);
}

QPowerMonitor::~QPowerMonitor()
{

}

void QPowerMonitor::update(const PowerMonitorData& status)
{
	ui.ia->setText(QString("%L1").arg(status.ia, 0, 'f', 2));
	ui.id->setText(QString("%L1").arg(status.id, 0, 'f', 2));
	ui.va->setText(QString("%L1").arg(status.va, 0, 'f', 2));
	ui.vd->setText(QString("%L1").arg(status.vd, 0, 'f', 2));
	ui.p->setText(QString("%L1").arg(status.p, 0, 'f', 2));

}