#ifndef QPOWERMONITOR_H
#define QPOWERMONITOR_H

#include "types.h"
#include "qtoggleviewdialog.h"
#include "ui_qpowermonitor.h"

#include <QWidget>

class QPowerMonitor : public QToggleViewDialog
{
	Q_OBJECT

public:
	QPowerMonitor(QWidget *parent = 0);
	~QPowerMonitor();

public slots:
	void set(const PowerMonitorData& data);

private:
	Ui::QPowerMonitorClass ui;
};

#endif // QPOWERMONITOR_H
