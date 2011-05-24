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

void QPowerMonitor::update(const PowerMonitorData& data)
{
	ui.ia->setText(QString("%L1").arg(data.ia));
	ui.id->setText(QString("%L1").arg(data.id));
	ui.va->setText(QString("%L1").arg(data.va));
	ui.vd->setText(QString("%L1").arg(data.vd));
	ui.p->setText(QString("%L1").arg(data.p));

}