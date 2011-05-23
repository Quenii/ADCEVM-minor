#include "qstatictester.h"
#include "types.h"
#include "dacanalyzersettings.h"
#include "Board.h"
#include "QMultiMeter.h"

#include <QPointer>
#include <QVector>

static bool measureVolt(int averageLevel, float& measured)
{
	QVector<float> vect(averageLevel + 2);
	QMultiMeter* multiMeter = QMultiMeter::instance();
	for (int i = 0; i < averageLevel + 2; ++i)
	{

	}
}


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
	
	m_settings = DacAnalyzerSettings().staticTestSettings();
	m_currentVal = 0;

	Board* board = Board::instance();
	board->close();
	if (!board->open())
		return false;

	QMultiMeter* meter = QMultiMeter::instance();
	meter->close();
	if (!meter->open_port())
	{
		return false;
	}
	
	m_bStarted = true;
	emit started();
	m_timerId = startTimer(1);	

	return true;
}

 
void QStaticTester::stop()
{
	if (!m_bStarted) return ;
		
	killTimer(m_timerId);
	m_bStarted = false;

	Board::instance()->close();

	emit stopped();
}

void QStaticTester::timerEvent(QTimerEvent * event)
{	
	if (!m_bStarted) return;

	// staticOutput


	float measured;
	// measure
	if (measureVolt(m_settings.averageLevel, measured))
	{
	}

	emit newData();
}

