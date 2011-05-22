#ifndef QSTATICTESTER_H
#define QSTATICTESTER_H

#include "types.h"

#include <QObject>
#include <QWeakPointer>
#include <QSharedPointer>

class QTimerEvent;


class  QTester : public QObject
{
	Q_OBJECT

public:
	static QTester* instance();

private:
	QTester(QObject *parent = 0);
	Q_DISABLE_COPY(QTester)

public:
	~QTester();

signals:
	void started();
	void stopped();

	void newData();

public:
	bool start(TestMode mode);
	void stop();
	bool isRunning() { return m_bStarted; }
	TestMode currentMode() { return m_mode; }

protected:
	void timerEvent(QTimerEvent * event);
	
private:	
	bool m_bStarted;
	int m_timerId;
	TestMode m_mode;
};

#endif // QSTATICTESTER_H
