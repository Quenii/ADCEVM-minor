#include "qsar.h"
#include "gkhy/PcieDab2/PcieDab0718.h"
#include "gkhy/pagoda/qworkerthread.h"
#include "qsarsettings.h"
#include "gkhy/pagoda/QRebufferedTcpSocket.h"

#include <QThread>
#include <vector>

using namespace gkhy::PcieDab2;

QSar::QSar(QObject* parent) 
: QDev(parent)
, m_thruputMeter_mt(0)
{
	m_thruputMeter_mt = new QThruputMeter(1000, true, this);

	tryLoadRealDev<PcieDab0718, 1>();

	QSarSettings s;
	SarConfig m_sarConfig = s.sarConfig();	
}

QSar::~QSar()
{
	stop();
}

bool QSar::start()
{
	m_elapsedTimer.restart();

	if (! m_pcieDab->open())
	{
		return false;
	}
		
	QWorkerThread::start();
	
	return true;	
}

void QSar::stop()
{
	QWorkerThread::stop();
	m_pcieDab->close();
}

bool QSar::set(const SarConfig& settings, int& ret)
{
	return true;
}

bool QSar::get(const SarConfig& settings, int& ret) const
{
	return true;
}

bool QSar::get(SarStatus& status, int& ret)
{	
	SarStatus _status;
	_status.isRunning = started();
	_status.secondElapsed = m_elapsedTimer.elapsed() / 1000;
	_status.thruput = m_thruputMeter_mt->value();

	status = _status;

	ret = 1;

	return true;
}

bool QSar::set(const SarCommand& command, int& ret)
{
	return true;
}

void QSar::run()
{	
	while (!shouldStop())
	{
		 run_session();
	}
}

void QSar::run_session()
{
	m_thruputMeter_mt->reset();

	qDebug("SAR Emulator is now started. \r\nBegin sending data...");

	m_pcieDab->writeReg(15 * 4, 1);
	while (m_pcieDab->readReg(15 * 4) != 1 && !shouldStop())
		msleep(10);

    m_pcieDab->writeReg(15 * 4, 0);
	unsigned int cmd[4]={0x0001,0x0002,0x0003,0x0004};
	m_pcieDab->writeSglDma(13 * 4, cmd, sizeof(cmd) / sizeof(cmd[0]));

	std::vector<unsigned int> buf(1024 * 1024);
	int count = 0;
	while (!shouldStop())
	{	
		unsigned int space = m_pcieDab->readReg(0 * 4);
		int toWrite = qMin(buf.size(), space);
		for (int i = 0; i < toWrite; ++i)
		{
			buf[i] = count + i;
		}

		m_pcieDab->writeSglDma(1 * 4, &buf[0], toWrite);

		m_thruputMeter_mt->flow(toWrite);

		sleep(1);
	}

	qDebug("SAR Emulator is stopped.");
}