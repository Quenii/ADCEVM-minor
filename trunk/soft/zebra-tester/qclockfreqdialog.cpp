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
	ui.lineEditClockFreq->setText(QString::number(val));
}

void QClockFreqDialog::accepted()
{
	m_clockFreq = ui.lineEditClockFreq->text().toFloat();

	DacAnalyzerSettings s;
	s.setClockFreq(m_clockFreq);
}