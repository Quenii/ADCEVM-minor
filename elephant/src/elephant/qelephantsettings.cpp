#include "qelephantsettings.h"

static const char* sarIpKey = "/SAR/IP";
static const char* smsIpKey = "/SMS/IP";

QElephantSettings::QElephantSettings()
{
}

QElephantSettings::~QElephantSettings()
{
}

QString QElephantSettings::sarIp()
{
	return m_settings.value(sarIpKey, "127.0.0.1").toString();
}

void QElephantSettings::setSarIp(QString ip)
{
	m_settings.setValue(sarIpKey, ip);
}

QString QElephantSettings::smsIp()
{
	return m_settings.value(smsIpKey, "127.0.0.1").toString();
}

void QElephantSettings::setsmsIp(QString ip) 
{
	m_settings.setValue(smsIpKey, ip);
}
