#ifndef QSMSSETTINGS_H
#define QSMSSETTINGS_H


#include "qsmstypes.h"

#include <QSettings>

class QSmsSettings 
{	

public:
	QSmsSettings();
	~QSmsSettings();

public:
	SmsConfig smsConfig();
	void setSmsConfig(const SmsConfig& data);

	qint16 serverPort();
	void setServerPort(qint16 port);

private:
	QSettings m_settings;
};


#endif // QSMSSETTINGS_H
