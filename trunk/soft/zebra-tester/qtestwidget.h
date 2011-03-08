#ifndef QTESTWIDGET_H
#define QTESTWIDGET_H

#include <QWidget>
#include "ui_qtestwidget.h"

class QTestWidget : public QWidget
{
	Q_OBJECT

public:
	QTestWidget(QWidget *parent = 0);
	~QTestWidget();

private:
	Ui::QTestWidgetClass ui;
};

#endif // QTESTWIDGET_H
