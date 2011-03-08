#include "qsarsettings.h"

static const char* serverPortKey = "ServerPort";
static const char* sarConfigKey = "SarConfig";

QSarSettings::QSarSettings()
{
	m_settings.beginGroup("SAR");
}

QSarSettings::~QSarSettings()
{
	m_settings.endGroup();
}

SarConfig QSarSettings::sarConfig()
{
	m_settings.beginGroup(sarConfigKey);
	SarConfig data;
	data.fromSettings(m_settings);
	m_settings.endGroup();
	return data;
}

void QSarSettings::setSarConfig(const SarConfig& data)
{
	data.toSettings(m_settings);
}

qint16 QSarSettings::serverPort()
{
	return qint16(m_settings.value(serverPortKey, 3000).toInt());
}

void QSarSettings::setServerPort(qint16 port)
{
	m_settings.setValue(serverPortKey, QString("%1").arg(port));
}