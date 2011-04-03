#include "qclockfreqwidget.h"

#include "dacanalyzersettings.h"

QClockFreqWidget::QClockFreqWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	
}

QClockFreqWidget::~QClockFreqWidget()
{

}

void QClockFreqWidget::reloadSettings()
{
	float val = DacAnalyzerSettings().clockFreq();
	ui.clockFreq->setText(QString("%L1").arg(val));
}


