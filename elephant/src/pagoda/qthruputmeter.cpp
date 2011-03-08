#include "QThruputMeter.h"

#include <QTimer>
#include <QMutexLocker>

using namespace gkhy::pagoda;


QThruputMeter::QThruputMeter(qint64 avgInteral_ms, bool threadSafe /* = false */, QObject* parent /* = 0 */)
: QObject(parent)
, m_mutex(threadSafe ? new QMutex : 0)
{
	QTimer* timer = new QTimer(this);
	timer->setObjectName("timer");

	QMetaObject::connectSlotsByName(this);

	timer->start(avgInteral_ms);

	m_instTimer.start();
	m_avgTimer.start();

	reset();
}

QThruputMeter::~QThruputMeter(void)
{
	if (m_mutex)
		delete m_mutex;
}

ThruputMeterValue QThruputMeter::value() const
{
	QMutexLocker lock(m_mutex);
	return m_value;
}

void QThruputMeter::on_timer_timeout()
{
	QMutexLocker lock(m_mutex);

	m_value.nInstThruput = (m_value.nTotal - m_lastTotal) / m_instTimer.restart();
	m_value.nAvgThruput = m_value.nTotal / m_avgTimer.restart();
	m_lastTotal = m_value.nTotal;		 
}

void QThruputMeter::reset()
{
	QMutexLocker lock(m_mutex);

	m_value.nTotal = 0;
	m_value.nAvgThruput = 0;
	m_value.nInstThruput = 0;

	m_avgTimer.restart();
	m_instTimer.restart();
}

void QThruputMeter::flow(qint64 nCount)
{
	QMutexLocker lock(m_mutex);

	m_value.nTotal += nCount;
}