#ifndef QSTATICTESTER_H
#define QSTATICTESTER_H

#include <QObject>

class QTimerEvent;

class class QTester : public QObject
{
	Q_OBJECT

public:
	static QTester& instance();

private:
	QTester(QObject *parent);
	~QTester();

	Q_DISABLE_COPY(QTester)

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
};

#endif // QSTATICTESTER_H
