#include "qstatictester.h"
#include "types.h"
#include "dacanalyzersettings.h"
#include "DacBoard.h"
#include "QMultiMeter.h"

#include <cmath>
#include <QMessageBox>
#include <QPointer>
#include <QVector>
#include <QThread>

class QThreadL : public QThread
{
public:
	static void msleep (unsigned long msecs)
	{
		QThread::msleep(msecs);
	}
};

static void msleep (unsigned long msecs)
{
	QThreadL::msleep(msecs);
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


	/*QMultiMeter* meter = QMultiMeter::instance();
	meter->close();
	if (!meter->open_port())
	{
		QMessageBox::critical(0, "", QString::fromLocal8Bit("打开数字万用表失败。"));
		return false;
	}*/

	/* Board* board = Board::instance();
	board->close();
	if (!board->open())
	{
		QMessageBox::critical(0, "", QString::fromLocal8Bit("打开板卡失败。"));
		return false;
	}*/

	m_bStarted = true;
	emit started();

	DacBoard* board = DacBoard::instance();

	board->writeReg(0x1008, 0x8001); //bit 15: static/dynamic; bit 0: reset dut;
	msleep(100);

	board->writeReg(0x1008, 0x8000); //bit 15: static/dynamic; bit 0: reset dut;

	m_timerId = startTimer(1);	

	return true;
}

 
void QStaticTester::stop()
{
	if (!m_bStarted) return ;
		
	killTimer(m_timerId);
	m_bStarted = false;

	//Board::instance()->close();

	emit stopped();
}

void QStaticTester::timerEvent(QTimerEvent * event)
{	
	if (!m_bStarted) return;

	// staticOutput
	if (! DacBoard::instance()->setDacOutput(m_currentVal))
	{
		QMessageBox::critical(0, "", QString::fromLocal8Bit("操作板卡失败。"));
		stop();
		return ;
	}

	float measured;
	// measure
	//if (! QMultiMeter::instance()->measureVolt(m_settings.averageLevel, measured))
	//{
	//	QMessageBox::critical(0, "", QString::fromLocal8Bit("操作数字万用表失败。"));
	//	stop();
	//	return ;

	//}

	emit newData(m_currentVal, measured);

	m_currentVal += 1 << m_settings.step2n;

	if (m_currentVal > pow(2.0, 16))
	{
		QMessageBox::information(0, "", QString::fromLocal8Bit("测试完成。"));
		stop();
	}
	
}

