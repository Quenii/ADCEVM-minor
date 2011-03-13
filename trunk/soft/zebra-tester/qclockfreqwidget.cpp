#include "qclockfreqwidget.h"

#include "dacanalyzersettings.h"

QClockFreqWidget::QClockFreqWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	setClockFreq(DacAnalyzerSettings().clockFreq());
}

QClockFreqWidget::~QClockFreqWidget()
{

}


void QClockFreqWidget::setClockFreq(float val)
{
	ui.lineEditClockFreq->setText(QString("%L1").arg(val));
	// m_fClockFreq = val;
}
