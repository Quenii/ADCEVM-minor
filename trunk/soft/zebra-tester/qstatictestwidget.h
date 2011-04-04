#ifndef QSTATICTESTWIDGET_H
#define QSTATICTESTWIDGET_H

#include <QWidget>
#include "ui_qstatictestwidget.h"
#include "qtester.h"

class QStaticTestWidget : public QWidget
{
	Q_OBJECT

public:
	QStaticTestWidget(QWidget *parent = 0);
	~QStaticTestWidget();

public slots:
	void on_pushButtonStartStop_clicked();

private:
	Ui::QStaticTestWidgetClass ui;
};

#endif // QSTATICTESTWIDGET_H
