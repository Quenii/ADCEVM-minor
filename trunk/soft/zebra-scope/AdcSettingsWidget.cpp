#include "AdcSettingsWidget.h"
#include "AdcSettingsDialog.h"
#include "QZebraScopeSettings.h"


AdcSettingsWidget::AdcSettingsWidget(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);
}

AdcSettingsWidget::~AdcSettingsWidget()
{

}

void AdcSettingsWidget::on_pushButtonChangeSettings_clicked()
{
	AdcSettingsDialog dlg;
	dlg.setSettings(m_settings);
	if (QDialog::Accepted  == dlg.exec())
	{
		dlg.settings(m_settings);
		setSettings(m_settings);
		
		QZebraScopeSettings settings;
		settings.setAdcSettings(m_settings);

		emit settingsChanged();
	}
}

void AdcSettingsWidget::setSettings(const AdcSettings& settings)
{
	m_settings = settings;

	adcTypeLineEdit->setText(settings.adcType);

	vaDoubleLineEdit->setText(QString("%1").arg(settings.va));
	vdDoubleLineEdit->setText(QString("%1").arg(settings.vd));
	bitCountLineEdit->setText(QString("%1").arg(settings.bitcount));
	vppLineEdit->setText(QString("%1").arg(settings.vpp * 2));
	codingLineEdit->setText(conv_to_string((AdcCoding)settings.coding));
	phaseLineEdit->setText(QString("%1").arg(settings.phase));
}

void AdcSettingsWidget::settings(AdcSettings& settings)
{
	settings = m_settings;
}
