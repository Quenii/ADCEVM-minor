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
#include <Qdir>
#include <QTime>
#include <QDate>
#include <QCoreApplication>
#include <QTextStream>


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

	DacAnalyzerSettings s;
	
	m_staticTestSettings = s.staticTestSettings();
	m_dacTypeSettings = s.dacTypeSettings();

	if (m_staticTestSettings.left != 0)
	{
		m_currentVal = m_staticTestSettings.left;
	}
	else
	{
		m_currentVal = 0;
	}
	if (m_staticTestSettings.right == 0)
	{
		m_fullScale = 1 << m_dacTypeSettings.bitCount - 1;
	}
	else 
	{
		m_fullScale = m_staticTestSettings.right;
	}


	m_bStarted = true;
	emit started();

	DacBoard* board = DacBoard::instance();

	board->writeReg(0x1008, 0x8001); //bit 15: static/dynamic; bit 0: reset dut;
	msleep(100);

	board->writeReg(0x1008, 0x8000); //bit 15: static/dynamic; bit 0: reset dut;

	
	QString fileName = QString("%1-%2.txt").arg(
		QDate::currentDate().toString("yyMMdd"),
		QTime::currentTime().toString("hhmmss"));

	QString filePath = QDir(qApp->applicationDirPath()).filePath(fileName);

	m_file.setFileName(filePath);
	if (!m_file.open(QIODevice::WriteOnly | QIODevice::Text))
		return false;

	m_timerId = startTimer(1);	

	return true;
}

 
void QStaticTester::stop()
{
	if (!m_bStarted) return ;

	m_file.close();
		
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
		QMessageBox::critical(0, "", QString::fromLocal8Bit("�����忨ʧ�ܡ�"));
		stop();
		return ;
	}
	msleep(1);
	float measured;
	// measure
	if (! QMultiMeter::instance()->measureVolt(m_staticTestSettings.averageLevel, measured, m_staticTestSettings.nplc, true))
	{
		QMessageBox::critical(0, "", QString::fromLocal8Bit("�����������ñ�ʧ�ܡ�"));
		stop();
		return ;
	}

	float ideal = float(m_currentVal) * m_dacTypeSettings.refVolt / (1 << m_dacTypeSettings.bitCount);

	emit newData(ideal, measured);

	QTextStream out(&m_file);
	out << QString("%1\n").arg(measured, 0, 'f', 10);

	m_currentVal += 1;

	if (m_currentVal > m_fullScale)
	{
		QMessageBox::information(0, "", QString::fromLocal8Bit("������ɡ�"));
		stop();
	}
	
}

