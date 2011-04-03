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
/*	void on_tabWidget_currentChanged(int index);

	void on_pushButtonSetStaticTest_clicked();
	void on_pushButtonStartStaticTest_clicked();

	void on_pushButtonStartDynamicTest_clicked();	

	void on_pushButtonStartInstTest_clicked();	

	void on_pushButtonStartCalibration_clicked();	

private:
	void anotherTestIsRunningWarning();

private:
	union u_t
	{
		struct
		{
			unsigned int staticTestStarted : 1;
			unsigned int dynamicTestStarted : 1;
			unsigned int instTestStarted : 1;
			unsigned int calibrationStarted : 1;
		};

		unsigned int testStarted;
	} m_state;
	*/
};

#endif // QTESTWIDGET_H
