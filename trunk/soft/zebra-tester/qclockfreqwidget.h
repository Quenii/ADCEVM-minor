#ifndef QCLOCKFREQWIDGET_H
#define QCLOCKFREQWIDGET_H

#include <QWidget>

#include "ui_qclockfreqwidget.h"

class QClockFreqWidget : public QWidget
{
	Q_OBJECT

public:
	QClockFreqWidget(QWidget *parent = 0);
	~QClockFreqWidget();

public:
	void reloadSettings();

private:
	Ui::QClockFreqWidgetClass ui;
	// float m_fClockFreq;
};

#endif // QCLOCKFREQWIDGET_H
