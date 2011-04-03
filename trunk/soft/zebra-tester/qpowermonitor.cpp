#include "qpowermonitor.h"

QPowerMonitor::QPowerMonitor(QWidget *parent)
	: QToggleViewDialog(parent)
{
	ui.setupUi(this);
}

QPowerMonitor::~QPowerMonitor()
{

}

void QPowerMonitor::set(const PowerMonitorData& data)
{
	ui.ia->setText(QString("%L1").arg(data.ia));
	ui.id->setText(QString("%L1").arg(data.id));
	ui.va->setText(QString("%L1").arg(data.va));
	ui.vd->setText(QString("%L1").arg(data.vd));
	ui.p->setText(QString("%L1").arg(data.p));

}