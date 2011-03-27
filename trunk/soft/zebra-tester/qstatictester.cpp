#include "qstatictester.h"

QStaticTester::QStaticTester(QObject *parent)
	: QObject(parent)
	, m_bStarted(false)
{

}

QStaticTester::~QStaticTester()
{

}

QStaticTester& QStaticTester::instance()
{
	static QStaticTester tester(0);
	return tester;
}

void QStaticTester::start()
{
	if (m_bStarted) return;

	
	m_bStarted = true;
	emit started();
}

 
void QStaticTester::stop()
{
	if (!m_bStarted) return ;
		
	m_bStarted = false;

}

void QStaticTester::timerEvent(QTimerEvent * event)
{	
	if (!m_bStarted) return;

	emit newData();

}