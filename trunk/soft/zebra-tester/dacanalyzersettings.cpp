#include "DacAnalyzerSettings.h"

#include <QPoint>

static const char* dacTypeSettingsKey = "DacTypeSettings";
static const char* staticTestSettingsKey = "StaticTestSettings";
static const char* dynamicTestSettingsKey = "DynamicTestSettings";

static const char* clockFreqKey = "ClockFreq";
static const char* powerMonitorPoskey = "PowerMonitorPos";
static const char* powerMonitorVisibleKey = "PowerMonitorVisible";

DacAnalyzerSettings::DacAnalyzerSettings(void)
{
}

DacAnalyzerSettings::~DacAnalyzerSettings(void)
{
}

bool DacAnalyzerSettings::powerMonitorWidgetVisible() const
{
	return m_s.value(powerMonitorVisibleKey).toBool();
}

void DacAnalyzerSettings::setPowerMonitorWidgetVisible(const bool& val)
{
	m_s.setValue(powerMonitorVisibleKey, val);

}


QPoint DacAnalyzerSettings::powerMonitorWidgetPos() const
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

void DacAnalyzerSettings::setStaticTestSettings(const StaticTestSettings& val)
{
	m_s.setValue(staticTestSettingsKey, val);
}

StaticTestSettings DacAnalyzerSettings::staticTestSettings() const
{
	return m_s.value(staticTestSettingsKey).value<StaticTestSettings>();
}

void DacAnalyzerSettings::setDynamicTestSettings(const DynamicTestSettings& val)
{
	m_s.setValue(dynamicTestSettingsKey, val);
}

DynamicTestSettings DacAnalyzerSettings::dynamicTestSettings() const
{
	return m_s.value(dynamicTestSettingsKey).value<DynamicTestSettings>();
}

void DacAnalyzerSettings::setClockFreq(const float& val)
{
	m_s.setValue(clockFreqKey, val);

}

float DacAnalyzerSettings::clockFreq() const
{
	return m_s.value(clockFreqKey, 0).toFloat();
}