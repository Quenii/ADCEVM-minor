#include "qdactypedialog.h"
#include "dacanalyzersettings.h"
#include "DacBoard.h"

QDacTypeDialog::QDacTypeDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	loadSettings();
}

QDacTypeDialog::~QDacTypeDialog()
{

}

void QDacTypeDialog::loadSettings()
{
	const DacTypeSettings& val = DacAnalyzerSettings().dacTypeSettings();

	/* ui.comboBoxDacType->setText(val.type);
	ui.spinBoxVa->set
	float va;
	float vd;
	int bitCount;
	float refVolt;
	float phase;	
	*/
}

void QDacTypeDialog::accept()
{
	DacTypeSettings val;

	val.type = ui.comboBoxDacType->currentText();
	val.bitCount = ui.spinBoxBitCount->text().toInt();
	val.va = ui.doubleSpinBoxVa->text().toFloat();
	val.vd = ui.doubleSpinBoxVd->text().toFloat();
	val.refVolt = ui.doubleSpinBoxVref->text().toFloat();
	val.phase = ui.comboBoxPhase->currentText().toInt();


	DacAnalyzerSettings s;
	s.setDacTypeSettings(val);

	DacBoard::instance()->setDacTypeSettings(val);

	QDialog::accept();

}