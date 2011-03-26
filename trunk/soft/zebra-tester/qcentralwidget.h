#ifndef QCENTRALWIDGET_H
#define QCENTRALWIDGET_H

#include <QStackedWidget>
#include "ui_qcentralwidget.h"

class QCentralWidget : public QStackedWidget
{
	Q_OBJECT

public:
	QCentralWidget(QWidget *parent = 0);
	~QCentralWidget();

private:
	Ui::QCentralWidgetClass ui;
};

#endif // QCENTRALWIDGET_H
