#include "qdactypedialog.h"
#include "dacanalyzersettings.h"

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

	DacAnalyzerSettings s;
	s.setDacTypeSettings(val);

	QDialog::accept();

}