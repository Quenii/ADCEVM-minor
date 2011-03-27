#ifndef QSTATICTESTER_H
#define QSTATICTESTER_H

#include <QObject>

class QTimerEvent;

class QStaticTester : public QObject
{
	Q_OBJECT

public:
	static QStaticTester& instance();

private:
	QStaticTester(QObject *parent);
	~QStaticTester();

	Q_DISABLE_COPY(QStaticTester)

signals:
	void started();
	void newData();

public slots:
	void start();
	void stop();

protected:
	void timerEvent(QTimerEvent * event);

private:	
	bool m_bStarted;
};

#endif // QSTATICTESTER_H
