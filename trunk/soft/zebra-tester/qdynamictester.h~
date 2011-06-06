#ifndef QSTATICTESTER_H
#define QSTATICTESTER_H

#include "types.h"

#include <QObject>
#include <QWeakPointer>
#include <QSharedPointer>
#include <QFile>

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

	void newData(float output, float measured);

public:
	bool start();
	void stop();
	bool isRunning() { return m_bStarted; }
	
protected:
	void timerEvent(QTimerEvent * event);
	
private:	
	bool m_bStarted;
	int m_timerId;
	
	DacTypeSettings m_dacTypeSettings;
	StaticTestSettings m_staticTestSettings;
	unsigned int m_currentVal;	

	QFile m_file;
};

#endif // QSTATICTESTER_H
