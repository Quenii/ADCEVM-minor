#include "SignalSettingsDialog.h"
#include <QLocale>

SignalSettingsDialog::SignalSettingsDialog(QWidget *parent)
	: QDialog(parent)
{
	setupUi(this);
}

SignalSettingsDialog::~SignalSettingsDialog()
{

}

void SignalSettingsDialog::settings(SignalSettings& settings)
{
	bool ok;
	QLocale c(QLocale::C);

	settings.signalFreq = c.toFloat(signalFreqLineEdit->text());
	settings.signalPower = c.toFloat(signalPowerLineEdit->text());
	settings.clockFreq  = c.toFloat(clockFreqMHzLineEdit->text()) * 1e6;
}

void SignalSettingsDialog::setSettings(const SignalSettings& settings)
{

	signalFreqLineEdit->setText(QString("%L1").arg(settings.signalFreq, 0, 'f', 1));
	signalPowerLineEdit->setText(QString("%1").arg(settings.signalPower, 0, 'f', 1));
	clockFreqMHzLineEdit->setText(QString("%L1").arg(settings.clockFreq / 1e6, 0, 'f', 1));
}
