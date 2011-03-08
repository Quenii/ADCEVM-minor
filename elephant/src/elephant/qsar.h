#pragma once 

#include "gkhy/pagoda/qrdmpacket.h"
#include "gkhy/pagoda/qworkerthread.h"
#include "gkhy/pagoda/qthruputmeter.h"
#include "qsartypes.h"
#include "qdev.h"

#include <qobject>
#include <memory>

class QMutex;

class QSar : public QDev ,  private gkhy::pagoda::QWorkerThread
{
	Q_OBJECT

public:
	QSar(QObject* parent = 0);
	virtual ~QSar();

public:
	bool start();
	void stop();

public slots:
	bool set(const SarConfig& settings, int& ret);
	bool get(const SarConfig& settings, int& ret) const;

	bool get(SarStatus& status, int& ret);
	bool set(const SarCommand& command, int& ret);

public:
	void run();
	void run_session();

private:
	gkhy::pagoda::QThruputMeter* m_thruputMeter_mt;
	SarConfig m_sarConfig;
	QElapsedTimer m_elapsedTimer;
};
