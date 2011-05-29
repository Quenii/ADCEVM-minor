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

public slots:
	void on_pushButtonSetDynTest_clicked();


private:
	Ui::QDynamicTestWidgetClass ui;
};

#endif // QDYNAMICTESTWIDGET_H
