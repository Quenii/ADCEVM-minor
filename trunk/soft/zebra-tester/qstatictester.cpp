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

static bool output(unsigned short val)
{
	Board* board = Board::instance();

//	board->writeReg(addr, val);
	return true;
	
}

static bool readPowerMonitorData(PowerMonitorData & powerStatus)
{
	Board* board = Board::instance();

	unsigned short reg = 0;
	board->writeReg(9, 0xA400);  //select 3548, work at default mode
	board->writeReg(9, 0xA400);  //select 3548, work at default mode

	board->writeReg(9, 0x7FFF);  //select 3548, select 7th channel
	board->writeReg(9, 0x7FFF);  //select 3548, select 7th channel
	board->writeReg(9, 0xeFFF);  //select 3548, read out 7th channel volage
	board->writeReg(9, 0xeFFF);  //select 3548, read out 7th channel volage
	board->readReg(0x0009, reg);
	powerStatus.va = (float(reg>>2)) * 4 / 16384;

	board->writeReg(9, 0x3FFF);  //select 3548, select 7th channel
	board->writeReg(9, 0x3FFF);  //select 3548, select 7th channel
	board->writeReg(9, 0xeFFF);  //select 3548, read out 7th channel volage
	board->writeReg(9, 0xeFFF);  //select 3548, read out 7th channel volage
	board->readReg(0x0009, reg);
	powerStatus.vd = (float(reg>>2)) * 4 / 16384;

	board->writeReg(9, 0x4FFF);  //select 3548, select 7th channel
	board->writeReg(9, 0x4FFF);  //select 3548, select 7th channel
	board->writeReg(9, 0xeFFF);  //select 3548, read out 7th channel volage
	board->writeReg(9, 0xeFFF);  //select 3548, read out 7th channel volage
	board->readReg(0x0009, reg);
	powerStatus.ia = (float(reg>>2)) * 500 * 4 / 16384;

	board->writeReg(9, 0x1FFF);  //select 3548, select 7th channel
	board->writeReg(9, 0x1FFF);  //select 3548, select 7th channel
	board->writeReg(9, 0xeFFF);  //select 3548, read out 7th channel volage
	board->writeReg(9, 0xeFFF);  //select 3548, read out 7th channel volage
	board->readReg(0x0009, reg);
	powerStatus.id = (float(reg>>2)) * 500 * 4 / 16384;

	powerStatus.p = powerStatus.va * powerStatus.ia + powerStatus.vd * powerStatus.id;


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


	QMultiMeter* meter = QMultiMeter::instance();
	meter->close();
	if (!meter->open_port())
	{
		QMessageBox::critical(0, "", QString::fromLocal8Bit("打开数字万用表失败。"));
		return false;
	}


	Board* board = Board::instance();
	board->close();
	if (!board->open())
	{
		QMessageBox::critical(0, "", QString::fromLocal8Bit("打开板卡失败。"));
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

