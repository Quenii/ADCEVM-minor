#include "qtester.h"

QTester::QTester(QObject *parent)
	: QObject(parent)
	, m_bStarted(false)
{

}

QTester::~QTester()
{

}

QTester& QTester::instance()
{
	static QTester tester(0);
	return tester;
}

void QTester::start()
{
	if (m_bStarted) return;

	m_timerId = startTimer(100);
	
	m_bStarted = true;
	emit started();
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

}