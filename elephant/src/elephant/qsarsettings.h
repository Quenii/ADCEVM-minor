#ifndef QSARSETTINGS_H
#define QSARSETTINGS_H

#include "qsartypes.h"

#include <QSettings>

class QSarSettings 
{	
public:
	QSarSettings();
	~QSarSettings();

public:
	SarConfig sarConfig();
	void setSarConfig(const SarConfig& data);

	qint16 serverPort();
	void setServerPort(qint16 port);

private:
	QSettings m_settings;
};

#endif // QSARSETTINGS_H
