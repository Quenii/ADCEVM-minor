#include "qclockfreqdialog.h"
#include "dacanalyzersettings.h"

QClockFreqDialog::QClockFreqDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	setClockFreq(DacAnalyzerSettings().clockFreq());
}

QClockFreqDialog::~QClockFreqDialog()
{

}

void QClockFreqDialog::setClockFreq(const float& val)
{
	ui.lineEditClockFreq->setText(QString::number(val));
}

void QClockFreqDialog::accept()
{
	float f = ui.lineEditClockFreq->text().toFloat();

	DacAnalyzerSettings s;
	s.setClockFreq(f);

	QDialog::accept();
}