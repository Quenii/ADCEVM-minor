#ifndef QTESTWIDGET_H
#define QTESTWIDGET_H

#include <QWidget>
#include "ui_qtestwidget.h"

class QTestWidget : public QWidget, private Ui::QTestWidgetClass
{
	enum Mode 
	{
		StaticTest,
		DynamicTest,
		InstantTest,
		Calibration,	
	};

	Q_OBJECT

public:
	QTestWidget(QWidget *parent = 0);
	~QTestWidget();

signals:
	void activated(Mode mode);

private slots:
	void on_tabWidget_currentChanged(int index);

};

#endif // QTESTWIDGET_H
