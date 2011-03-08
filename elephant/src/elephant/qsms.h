#pragma once

#include "qdev.h"
#include "gkhy/pagoda/qrdmpacket.h"
#include "gkhy/pagoda/qworkerthread.h"
#include "qsmstypes.h"

#include <qobject>



class QSms : public QDev, private gkhy::pagoda::QWorkerThread 
{
	Q_OBJECT

public:
	QSms(QObject* parent = 0);
	virtual ~QSms();

private:
	Q_DISABLE_COPY(QSms)

public:
	bool start();
	void stop();

	bool set(const SmsConfig& settings);
	bool get(const SmsConfig& settings) const;

	bool get(SmsStatus& status);
	bool set(const SmsCommand& command);

protected:
	void run();

private:
	SmsConfig m_smsConfig;
	SmsStatus m_smsStatus;
};
