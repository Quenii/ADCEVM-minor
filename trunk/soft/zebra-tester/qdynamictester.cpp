#include "qdynamictester.h"
#include "types.h"
#include "dacanalyzersettings.h"
#include "DacBoard.h"
#include "QMultiMeter.h"

#include <cmath>
#include <QMessageBox>
#include <QThread>
#include <QPointer>
#include <QVector>
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

QDynamicTester::QDynamicTester(QObject *parent)
	: QObject(parent)
	, pi(3.141592653589793f)
	, m_bStarted(false)
{

}

QDynamicTester::~QDynamicTester()
{

}

QDynamicTester* QDynamicTester::instance()
{
	static QDynamicTester _instance;
	return &_instance;
}

bool QDynamicTester::start()
{
	//if (m_bStarted) 
	//	return false;

	DacAnalyzerSettings s;
	
	m_dynamicTestSettings = s.dynamicTestSettings();
	m_dacTypeSettings = s.dacTypeSettings();

	DacBoard* board = DacBoard::instance();

	board->close();
	if (!board->open())
	{
		QMessageBox::critical(0, "", QString::fromLocal8Bit("´ò¿ª°å¿¨Ê§°Ü¡£"));
		return false;
	}
	std::vector<unsigned short> buff;
	const int buffer_cnt = 20000;

	board->writeReg(0x1008, 0x0001); //bit 15: static/dynamic; bit 0: reset dut;
	msleep(100);

	board->writeReg(0x1008, 0x0000); //bit 15: static/dynamic; bit 0: reset dut;

	board->writeReg(0x1004, buffer_cnt);
	if (buff.size() < buffer_cnt)
		buff.resize(buffer_cnt);

	float max = (1 << (m_dacTypeSettings.bitCount - 1)) - 1;

	float fs = m_dynamicTestSettings.clockFreq;
	float fc = m_dynamicTestSettings.signalFreq;


	for (int i=0; i<buffer_cnt; ++i)
	{
		buff[i] = ((short)((sin(2*pi*i*fc/fs)+1)*(max+0.5)));
	}

	bool okay = board->write(0x1005, &buff[0], buffer_cnt);
	board->writeReg(0x1006, 0);
	board->writeReg(0x1007, 1);

	//m_bStarted = true;
	//emit started();

	
	return true;
}

 
void QDynamicTester::stop()
{
	if (!m_bStarted) return ;

	m_bStarted = false;

	//Board::instance()->close();

	emit stopped();
}

