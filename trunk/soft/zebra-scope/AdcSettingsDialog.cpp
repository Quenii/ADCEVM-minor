#include "AdcSettingsDialog.h"

AdcSettingsDialog::AdcSettingsDialog(QWidget *parent)
	: QDialog(parent)
{
	setupUi(this);
	
	codingComboBox->addItems(QStringList() << tr("Offset") << tr("Complement") << tr("Gray"));

}

AdcSettingsDialog::~AdcSettingsDialog()
{

}



void AdcSettingsDialog::setSettings(const AdcSettings& settings)
{
	adcTypeLineEdit->setText(settings.adcType);

	vaDoubleSpinBox->setValue(settings.va);
	vdDoubleSpinBox->setValue(settings.vd);
	bitCountSpinBox->setValue(settings.bitcount);
	vppLineEdit->setText(QString("%1").arg(settings.vpp * 2));
	codingComboBox->setCurrentIndex(settings.coding);
	phaseLineEdit->setText(QString("%1").arg(settings.phase));
}

void AdcSettingsDialog::settings(AdcSettings& settings)
{
	QLocale c(QLocale::C);

	settings.adcType = adcTypeLineEdit->text();
	settings.va = vaDoubleSpinBox->value();
	settings.vd = vdDoubleSpinBox->value();
	settings.bitcount = bitCountSpinBox->value();
	settings.vpp = c.toFloat( vppLineEdit->text() ) / 2;
	settings.coding = (AdcCoding) codingComboBox->currentIndex();
	settings.phase = c.toFloat( phaseLineEdit->text() );
}


