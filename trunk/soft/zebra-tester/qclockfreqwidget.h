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
	void setClockFreq(float val);
	// float clockFreq() const { return m_fClockFreq; }

private:
	Ui::QClockFreqWidgetClass ui;
	// float m_fClockFreq;
};

#endif // QCLOCKFREQWIDGET_H
