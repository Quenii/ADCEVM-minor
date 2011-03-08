#include "qclockfreqdialog.h"
#include "dacanalyzersettings.h"

QClockFreqDialog::QClockFreqDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	DacAnalyzerSettings s;
	setClockFreq(s.clockFreq());
}

QClockFreqDialog::~QClockFreqDialog()
{

}

void QClockFreqDialog::setClockFreq(const float& val)
{

}