#include "qstatictester.h"
#include "types.h"
#include "dacanalyzersettings.h"

#include <QPointer>


QStaticTester::QStaticTester(QObject *parent)
	: QObject(parent)
	, m_bStarted(false)
{
}

QStaticTester::~QStaticTester()
{

}

QStaticTester* QStaticTester::instance()
{
	static QStaticTester _instance;
	return &_instance;
}

bool QStaticTester::start()
{
	if (m_bStarted) 
		return false;
	
	m_bStarted = true;
	
	m_settings = DacAnalyzerSettings().staticTestSettings();
	m_currentVal = 0;
	
	emit started();
	m_timerId = startTimer(1);

	return true;
}

 
void QStaticTester::stop()
{
	if (!m_bStarted) return ;
		
	killTimer(m_timerId);
	m_bStarted = false;

	emit stopped();
}

void QStaticTester::timerEvent(QTimerEvent * event)
{	
	if (!m_bStarted) return;

	
		// staticOutput

		// measure

		emit newData();
	

}

