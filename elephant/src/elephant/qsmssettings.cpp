#include "qsmssettings.h"

static const char* serverPortKey = "ServerPort";
static const char* smsConfigKey = "SmsConfig";

QSmsSettings::QSmsSettings()
{
	m_settings.beginGroup("Solid Mass Storage");
}

QSmsSettings::~QSmsSettings()
{
	m_settings.endGroup();
}

SmsConfig QSmsSettings::smsConfig()
{
	m_settings.beginGroup(smsConfigKey);
	SmsConfig data;
	data.fromSettings(m_settings);
	m_settings.endGroup();
	return data;
}

void QSmsSettings::setSmsConfig(const SmsConfig& data)
{
	data.toSettings(m_settings);
}

qint16 QSmsSettings::serverPort()
{
	return qint16(m_settings.value(serverPortKey, 3000).toInt());
}

void QSmsSettings::setServerPort(qint16 port)
{
	m_settings.setValue(serverPortKey, QString("%1").arg(port));
}