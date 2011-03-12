#include "qdactypedialog.h"
#include "dacanalyzersettings.h"

QDacTypeDialog::QDacTypeDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	DacAnalyzerSettings settings;
	setSettings(settings.dacTypeSettings());
}

QDacTypeDialog::~QDacTypeDialog()
{

}

void QDacTypeDialog::setSettings(const DacTypeSettings& val)
{
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

	DacAnalyzerSettings s;
	s.setDacTypeSettings(m_settings);

}