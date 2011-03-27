#ifndef QTESTWIDGET_H
#define QTESTWIDGET_H

#include <QWidget>
#include "ui_qtestwidget.h"

enum Mode 
{
	StaticTest,
	DynamicTest,
	InstantTest,
	Calibration,	
};


class QTestWidget : public QWidget, private Ui::QTestWidgetClass
{
	Q_OBJECT

public:
	QTestWidget(QWidget *parent = 0);
	~QTestWidget();

signals:
	void modeActivated(Mode mode);

private slots:
	void on_tabWidget_currentChanged(/*int index*/);

	void on_pushButtonSetStaticTest_clicked();
	void on_pushButtonStartStaticTest_clicked();	

};

#endif // QTESTWIDGET_H
