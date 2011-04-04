#ifndef QCENTRALWIDGET_H
#define QCENTRALWIDGET_H

#include "types.h"

#include "ui_qcentralwidget.h"

#include <QStackedWidget>

class QStaticTestPlot;
class QDynamicTestPlot;

class QCentralWidget : public QStackedWidget
{
	Q_OBJECT

public:
	QCentralWidget(QWidget *parent = 0);
	~QCentralWidget();

public slots:
	void changeMode(TestMode mode);

private:
	Ui::QCentralWidgetClass ui;
	QStaticTestPlot* staticPlot;
	QDynamicTestPlot* dynamicPlot;
};

#endif // QCENTRALWIDGET_H
