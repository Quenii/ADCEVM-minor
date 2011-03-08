#include "SignalSettingsWidget.h"
#include "SignalSettingsDialog.h"
#include "QZebraScopeSettings.h"

SignalSettingsWidget::SignalSettingsWidget(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);
}

SignalSettingsWidget::~SignalSettingsWidget()
{

}

void SignalSettingsWidget::on_pushButtonChangeSettings_clicked()
{
	SignalSettingsDialog dlg;
	dlg.setSettings(m_settings);
	if (QDialog::Accepted  == dlg.exec())
	{
		dlg.settings(m_settings);
		setSettings(m_settings);

		QZebraScopeSettings settings;
		settings.setSignalSettings(m_settings);

		emit settingsChanged();
	}
}

void SignalSettingsWidget::setSettings(const SignalSettings& settings)
{
	m_settings = settings;

	signalFreqLineEdit->setText(QString("%L1").arg(settings.signalFreq, 0, 'f', 1));
	signalPowerLineEdit->setText(QString("%L1").arg(settings.signalPower, 0, 'f', 1));
	clockFreqMHzLineEdit->setText(QString("%L1").arg(settings.clockFreq / 1e6, 0, 'f', 1));
}

void SignalSettingsWidget::settings(SignalSettings& settings)
{
	settings = m_settings;
}