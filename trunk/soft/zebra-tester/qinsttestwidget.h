#ifndef QINSTTESTWIDGET_H
#define QINSTTESTWIDGET_H

#include <QWidget>
#include "ui_qinsttestwidget.h"

class QInstTestWidget : public QWidget
{
	Q_OBJECT

public:
	QInstTestWidget(QWidget *parent = 0);
	~QInstTestWidget();

private:
	Ui::QInstTestWidgetClass ui;
};

#endif // QINSTTESTWIDGET_H
