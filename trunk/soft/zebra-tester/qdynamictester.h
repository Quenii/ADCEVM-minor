#ifndef QDYNAMICTESTER_H
#define QDYNAMICTESTER_H

#include "types.h"

#include <QObject>
#include <QWeakPointer>
#include <QSharedPointer>
#include <QFile>


class QDynamicTester : public QObject
{
	Q_OBJECT

public:
	static QDynamicTester* instance();

private:
	QDynamicTester(QObject *parent = 0);
	Q_DISABLE_COPY(QDynamicTester)

public:
	~QDynamicTester();

signals:
	void started();
	void stopped();

public:
	bool start();
	void stop();
	bool isRunning() { return m_bStarted; }
	
protected:
	
private:	
	bool m_bStarted;
	int m_timerId;
	const float pi;
	
	DacTypeSettings m_dacTypeSettings;
	DynamicTestSettings m_dynamicTestSettings;
	unsigned int m_currentVal;	

	QFile m_file;
};

#endif // QDYNAMICTESTER_H
