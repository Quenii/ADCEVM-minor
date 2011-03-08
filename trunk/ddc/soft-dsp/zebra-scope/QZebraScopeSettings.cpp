#include "QZebraScopeSettings.h"

static const char* adcSettingsKey = "AdcBoard/AdcSettings";
static const char* signalSettingsKey = "AdcBoard/SignalSettings";

QZebraScopeSettings::QZebraScopeSettings(const QString & fileName, Format format, QObject * parent /* = 0 */) : QSettings(fileName, format, parent)
{

}

QZebraScopeSettings::QZebraScopeSettings(QObject* parent /*= 0*/) : QSettings(parent)
{
}

QZebraScopeSettings::~QZebraScopeSettings(void)
{
}

void QZebraScopeSettings::setAdcSettings(const AdcSettings& data) 
{
	beginGroup(adcSettingsKey);
	data.writeSettings(*this); 
	endGroup();
}

void QZebraScopeSettings::adcSettings(AdcSettings& data)
{ 
	beginGroup(adcSettingsKey);
	data.readSettings(*this); 
	endGroup();
}

void QZebraScopeSettings::setSignalSettings(const SignalSettings& data)
{
	beginGroup(signalSettingsKey);
	data.writeSettings(*this);
	endGroup();
}
void QZebraScopeSettings::signalSettings(SignalSettings& data)
{
	beginGroup(signalSettingsKey);
	data.readSettings(*this);
	endGroup();
}