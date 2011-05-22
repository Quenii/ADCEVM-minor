#ifndef QSTATICTESTER_H
#define QSTATICTESTER_H

#include "types.h"

#include <QObject>
#include <QWeakPointer>
#include <QSharedPointer>

class QTimerEvent;


class QStaticTester : public QObject
{
	Q_OBJECT

public:
	static QStaticTester* instance();

private:
	QStaticTester(QObject *parent = 0);
	Q_DISABLE_COPY(QStaticTester)

public:
	~QStaticTester();

signals:
	void started();
	void stopped();

	void newData();

public:
	bool start();
	void stop();
	bool isRunning() { return m_bStarted; }
	
protected:
	void timerEvent(QTimerEvent * event);
	
private:	
	bool m_bStarted;
	int m_timerId;
	
	StaticTestSettings m_settings;
	unsigned int m_currentVal;	
};

#endif // QSTATICTESTER_H
