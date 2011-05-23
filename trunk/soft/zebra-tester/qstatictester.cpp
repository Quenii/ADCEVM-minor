#include "qstatictester.h"
#include "types.h"
#include "dacanalyzersettings.h"
#include "Board.h"
#include "QMultiMeter.h"

#include <QMessageBox>
#include <QPointer>
#include <QVector>

static bool measureVolt(int averageLevel, float& measured)
{
	QVector<float> vect(averageLevel + 2);
	QMultiMeter* multiMeter = QMultiMeter::instance();
	for (int i = 0; i < averageLevel + 2; ++i)
	{
	}

	return true;
}

static bool output(unsigned short)
{
	Board* board = Board::instance();

	return true;
	
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
	if (! output(m_currentVal))
	{
		QMessageBox::critical(0, "", QString::fromLocal8Bit("操作板卡失败"));
		stop();
		return ;
	}

	float measured;
	// measure
	if (! measureVolt(m_settings.averageLevel, measured))
	{
		QMessageBox::critical(0, "", QString::fromLocal8Bit("操作数字万用表失败"));
		stop();
		return ;

	}

	emit newData(m_currentVal, measured);

	m_currentVal += 1 << m_settings.step2n;
}

