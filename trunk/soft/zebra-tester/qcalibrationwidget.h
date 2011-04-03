#ifndef QCALIBRATIONWIDGET_H
#define QCALIBRATIONWIDGET_H

#include <QWidget>
#include "ui_qcalibrationwidget.h"

class QCalibrationWidget : public QWidget
{
	Q_OBJECT

public:
	QCalibrationWidget(QWidget *parent = 0);
	~QCalibrationWidget();

private:
	Ui::QCalibrationWidgetClass ui;
};

#endif // QCALIBRATIONWIDGET_H
