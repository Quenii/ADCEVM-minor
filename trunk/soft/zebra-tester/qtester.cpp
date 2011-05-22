#include "qtester.h"
#include "types.h"

#include <QPointer>


QTester::QTester(QObject *parent)
	: QObject(parent)
	, m_bStarted(false)
	, m_mode(StaticTest)
{
}

QTester::~QTester()
{

}

QTester* QTester::instance()
{
	static QTester _instance;
	return &_instance;
}

bool QTester::start(TestMode mode)
{
	if (m_bStarted) 
		return false;

	m_timerId = startTimer(1);
	
	m_bStarted = true;
	emit started();

	return true;
}

 
void QTester::stop()
{
	if (!m_bStarted) return ;
		
	killTimer(m_timerId);
	m_bStarted = false;

	emit stopped();
}

void QTester::timerEvent(QTimerEvent * event)
{	
	if (!m_bStarted) return;

	emit newData();

	// staticOutput

	// measure
}

