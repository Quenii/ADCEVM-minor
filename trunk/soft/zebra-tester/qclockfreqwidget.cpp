#include "qclockfreqwidget.h"

QClockFreqWidget::QClockFreqWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

QClockFreqWidget::~QClockFreqWidget()
{

}


void QClockFreqWidget::setClockFreq(float val)
{
	ui.lineEditClockFreq->setText(QString("%L1").arg(val));
	m_fClockFreq = val;
}
