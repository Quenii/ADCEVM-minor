#include "qworkerthread.h"


#include <QThread>

using namespace gkhy::pagoda;

class  QWorkerThreadPrivate : public QThread
{
	friend QWorkerThread;

public:
	QWorkerThreadPrivate(QWorkerThread& obj, QObject* parent = 0)
		: QThread(parent)
		, m_obj(obj)
	{

	}
protected:
	void run()
	{
		m_obj.run();
	}
private:
	QWorkerThread& m_obj;
};


void QWorkerThread::sleep(unsigned long secs)
{
	QWorkerThreadPrivate::sleep(secs);
}

void QWorkerThread::msleep(unsigned long msecs)
{
	QWorkerThreadPrivate::msleep(msecs);
}

QWorkerThread::QWorkerThread()
: m_enabled(1)
, m_started(false)
, m_p(0)
{
	m_p = new QWorkerThreadPrivate(*this);
}

QWorkerThread::~QWorkerThread()
{
	stop();
	delete m_p;
}


void QWorkerThread::start(QThread::Priority priority /*= InheritPriority*/)
{
	Q_ASSERT(!m_started);

	m_enabled = 1;
	m_p->start(priority);
	m_started = true;
}

void QWorkerThread::stop()
{
	m_enabled = 0;
	if (m_started)
		m_p->wait();
}

bool QWorkerThread::shouldStop()
{
	return m_enabled ? false : true;
}

