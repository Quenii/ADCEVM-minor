#ifndef QCENTRALWIDGET_H
#define QCENTRALWIDGET_H

#include <QStackedWidget>
#include "ui_qcentralwidget.h"
#include "qtestwidget.h"

class QStaticTestPlot;
class QDynamicTestPlot;

class QCentralWidget : public QStackedWidget
{
	Q_OBJECT

public:
	QCentralWidget(QWidget *parent = 0);
	~QCentralWidget();

public slots:
	void activateMode(Mode mode);

private:
	Ui::QCentralWidgetClass ui;
	QStaticTestPlot* staticPlot;
	QDynamicTestPlot* dynamicPlot;
};

#endif // QCENTRALWIDGET_H
