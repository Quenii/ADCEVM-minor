#include "DacAnalyzerSettings.h"

static const char* dacTypeSettingsKey = "DacTypeSettings";
static const char* clockFreqKey = "ClockFreq";
static const char* powerMonitorPoskey = "PowerMonitorPos";

DacAnalyzerSettings::DacAnalyzerSettings(void)
{
}

DacAnalyzerSettings::~DacAnalyzerSettings(void)
{
}

QPoint DacAnalyzerSettings::powerMonitorWidgetPos()
{
	return m_s.value(powerMonitorPoskey).toPoint();
}

void DacAnalyzerSettings::setPowerMonitorWidgetPos(const QPoint& val)
{
	m_s.setValue(powerMonitorPoskey, val);
}

void DacAnalyzerSettings::setDacTypeSettings(const DacTypeSettings& val)
{
	m_s.setValue(dacTypeSettingsKey, val);
}

DacTypeSettings DacAnalyzerSettings::dacTypeSettings() const
{
	return m_s.value(dacTypeSettingsKey).value<DacTypeSettings>();
}

void DacAnalyzerSettings::setClockFreq(const float& val)
{
	m_s.setValue(clockFreqKey, val);

}

float DacAnalyzerSettings::clockFreq() const
{
	return m_s.value(clockFreqKey, 0).toFloat();
}