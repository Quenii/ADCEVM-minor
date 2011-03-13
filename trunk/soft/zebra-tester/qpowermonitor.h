#ifndef QPOWERMONITOR_H
#define QPOWERMONITOR_H

#include <QWidget>
#include "ui_qpowermonitor.h"

class QPowerMonitor : public QWidget
{
	Q_OBJECT

public:
	QPowerMonitor(QWidget *parent = 0);
	~QPowerMonitor();

private:
	Ui::QPowerMonitorClass ui;
};

#endif // QPOWERMONITOR_H
