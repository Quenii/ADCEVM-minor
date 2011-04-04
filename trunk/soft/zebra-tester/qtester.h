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
	static QSharedPointer<QTester> instance();

private:
	QTester(QObject *parent = 0);
	Q_DISABLE_COPY(QTester)

public:
	~QTester();

signals:
	void started();
	void stopped();

	void newData();

public slots:
	void start();
	void stop();

protected:
	void timerEvent(QTimerEvent * event);

private:	
	bool m_bStarted;
	int m_timerId;

	//static QWeakPointer<QTester> _instance;
};

#endif // QSTATICTESTER_H
