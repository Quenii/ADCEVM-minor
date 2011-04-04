#include "qtester.h"

// QWeakPointer<QTester> QTester::_instance;
#include <QPointer>

QTester::QTester(QObject *parent)
	: QObject(parent)
	, m_bStarted(false)
{

}

QTester::~QTester()
{

}


QSharedPointer<QTester> QTester::instance()
{
	static QPointer<QTester> _instance;
	if (_instance.isNull())
		_instance = new QTester();

	return QSharedPointer<QTester>(_instance.data());
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