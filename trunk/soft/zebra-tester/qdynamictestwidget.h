#ifndef QDYNAMICTESTWIDGET_H
#define QDYNAMICTESTWIDGET_H

#include <QWidget>
#include "ui_qdynamictestwidget.h"

class QDynamicTestWidget : public QWidget
{
	Q_OBJECT

public:
	QDynamicTestWidget(QWidget *parent = 0);
	~QDynamicTestWidget();

private:
	Ui::QDynamicTestWidgetClass ui;
};

#endif // QDYNAMICTESTWIDGET_H
