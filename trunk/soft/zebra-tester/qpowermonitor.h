#ifndef QPOWERMONITOR_H
#define QPOWERMONITOR_H

#include "types.h"
#include "qtoggleviewdialog.h"
#include "ui_qpowermonitor.h"
#include "DacBoard.h"

#include <QDialog>

class QPowerMonitor : public QToggleViewDialog
{
	Q_OBJECT

public:
	QPowerMonitor(QWidget *parent = 0);
	~QPowerMonitor();

public slots:
	void update(const PowerMonitorData& data);

private:
	Ui::QPowerMonitorClass ui;
};

#endif // QPOWERMONITOR_H
