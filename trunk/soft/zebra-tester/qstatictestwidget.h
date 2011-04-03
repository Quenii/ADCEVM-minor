#ifndef QSTATICTESTWIDGET_H
#define QSTATICTESTWIDGET_H

#include <QWidget>
#include "ui_qstatictestwidget.h"

class QStaticTestWidget : public QWidget
{
	Q_OBJECT

public:
	QStaticTestWidget(QWidget *parent = 0);
	~QStaticTestWidget();

private:
	Ui::QStaticTestWidgetClass ui;
};

#endif // QSTATICTESTWIDGET_H
