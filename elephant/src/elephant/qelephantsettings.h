#ifndef QELEPHANTSETTINGS_H
#define QELEPHANTSETTINGS_H

#include <QSettings>

class QElephantSettings
{
public:
	QElephantSettings();
	~QElephantSettings();

public:
	QString sarIp();
	void setSarIp(QString ip);

	QString smsIp();
	void setsmsIp(QString ip);


private:
	QSettings m_settings;
	
};

#endif // QELEPHANTSETTINGS_H
