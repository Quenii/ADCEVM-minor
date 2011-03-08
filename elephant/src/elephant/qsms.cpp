#include "qsms.h"
#include "gkhy/PcieDab2/PcieDab0718.h"
#include "gkhy/PcieDab2/PcieDabEmulator.h"
#include "gkhy/pagoda/qworkerthread.h"
#include "qsmssettings.h"
#include "gkhy/pagoda/FixedSizeArchive.h"
#include "gkhy/pagoda/qsessionalrepository.h"
#include "gkhy/pagoda/HugeRingBuffer.h"

#include <QCoreApplication>
#include <QThread>
#include <QDir>
#include <vector>

using namespace gkhy::PcieDab2;
using namespace gkhy::pagoda;

QSms::QSms(QObject* parent /* = 0 */)
: QDev(parent)
{	
	tryLoadRealDev<PcieDab0718, 0>();
	
	QSmsSettings s;
	SmsConfig m_smsConfig = s.smsConfig();	
}

QSms::~QSms()
{
	stop();
}

bool QSms::start()
{
	if (! m_pcieDab->open())
	{
		return false;
	}

	QWorkerThread::start();

	return true;	
}

void QSms::stop()
{
	QWorkerThread::stop();
	m_pcieDab->close();

}

bool QSms::set(const SmsConfig& settings)
{
	return true;
}

bool QSms::get(const SmsConfig& settings) const
{
	return true;
}

bool QSms::get(SmsStatus& status)
{
	return true;
}

bool QSms::set(const SmsCommand& command)
{

	return true;
}

void QSms::run()
{
	qDebug("SMS Emulator is now started. \r\nBegin receiving data...");

	QSessionalRepositoryDW repos(
		QDir(qApp->applicationDirPath()).absoluteFilePath("../repos"),  
		2LL * 1024 * 1024 * 1024,
		512 * 1024,
		-1, 
		false);

	repos.open();

	while (!shouldStop())
	{
		int read = m_pcieDab->readData(repos.nextWriteBlock(), repos.nextWriteBlockSize());
		if (read > 0)
		{
			repos.commit(read);
		}
		else if (read < 0)
		{
			Q_ASSERT(false);
			break;
		}
	}

	qDebug("SMS Emulator is stopped.");
}