#include "qdynamictestsettingsdialog.h"
#include "dacanalyzersettings.h"
#include "global.h"

#include <QMessageBox>

QDynamicTestSettingsDialog::QDynamicTestSettingsDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	//ui.doubleSpinBoxVpp->setRange();
	//ui.spinBoxBitCount->setRange();
	//ui.doubleSpinBoxClockFreq->setRange();
	//ui.doubleSpinBoxSignalFreq.setRange();
	
	DynamicTestSettings val =  DacAnalyzerSettings().dynamicTestSettings();
	ui.doubleSpinBoxVpp->setValue(val.vpp);
	ui.spinBoxBitCount->setValue(val.bitCount);
	ui.doubleSpinBoxClockFreq->setValue(val.clockFreq);
	ui.doubleSpinBoxSignalFreq->setValue(val.signalFreq);

}

QDynamicTestSettingsDialog::~QDynamicTestSettingsDialog()
{

}

bool QDynamicTestSettingsDialog::validate(QDoubleSpinBox * doubleSpinBox)
{
//	return checkInputValidity(doubleSpinBox);
	return true;
}

bool QDynamicTestSettingsDialog::validate(QSpinBox * spinBox)
{
	//	return checkInputValidity(spinBox);
	return true;
}

void QDynamicTestSettingsDialog::accept()
{
	DynamicTestSettings val;

	if (! validate(ui.doubleSpinBoxVpp)) return ;
	val.vpp = ui.doubleSpinBoxVpp->value();

	if (! validate(ui.doubleSpinBoxClockFreq)) return ;
	val.clockFreq = ui.doubleSpinBoxClockFreq->value();

	if (! validate(ui.doubleSpinBoxSignalFreq)) return ;
	val.signalFreq = ui.doubleSpinBoxSignalFreq->value();

	if (! validate(ui.spinBoxBitCount)) return ;
	val.bitCount = ui.spinBoxBitCount->value();

	//if (! validate(ui.lineEditAverageLevel)) return ;
	//val.averageLevel = ui.lineEditAverageLevel->text().toInt();

	//if (! validate(ui.lineEditStep2n)) return ;
	//val.step2n = ui.lineEditStep2n->text().toInt();

	//if (! validate(ui.lineEditLeft)) return;
	//val.left = ui.lineEditLeft->text().toInt();
	//
	//if (! validate(ui.lineEditRight)) return;
	//val.right = ui.lineEditRight->text().toInt();

	DacAnalyzerSettings().setDynamicTestSettings(val);
	QDialog::accept();
}
