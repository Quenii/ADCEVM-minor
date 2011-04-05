#include "qtester.h"

#include "sicl.h"
#include <QPointer>

#pragma comment(lib, "sicl32.lib")

#define DEVICE_ADDRESS "gpib0,22"   // Modify this line to match your setup

static INST id;  

QTester::QTester(QObject *parent)
	: QObject(parent)
	, m_bStarted(false)
{
	
	// device session id
	char buf[256] = { 0 };   	// read buffer for idn string

	// Install a default SICL error handler that logs an error message and
	// exits.  On Windows 95 view messages with the SICL Message Viewer,
	// and on Windows NT use the Windows NT Event Viewer.
//	ionerror(I_ERROR_EXIT);	

	// Open a device session using the DEVICE_ADDRESS
	id = iopen(DEVICE_ADDRESS);

	// Set the I/O timeout value for this session to 1 second
	itimeout(id, 1000);

	// Write the *RST string (and send an EOI indicator) to put the instrument
	// in a known state.
	iprintf(id, "*RST\n");

	// Write the *IDN? string and send an EOI indicator, then read
	// the response into buf.  
	// For WIN16 programs, this will only work with the Large memory model 
	// since ipromptf expects to receive far pointers to the format strings.

	ipromptf(id, "*IDN?\n", "%t", buf);
	
	double res;
	/* Take a measurement */
	ipromptf(id, "MEAS:VOLT:DC?\n", "%lf", &res);
	}

QTester::~QTester()
{
	iclose(id);

	// For WIN16 programs, call _siclcleanup before exiting to release 
	// resources allocated by SICL for this application.  This call is a
	// no-op for WIN32 programs.
	_siclcleanup();

}


QSharedPointer<QTester> QTester::instance()
{
	static QPointer<QTester> _instance;
	if (_instance.isNull())
		_instance = new QTester();

	return QSharedPointer<QTester>(_instance.data());
}

void QTester::start()
{
	if (m_bStarted) return;

	m_timerId = startTimer(100);
	
	m_bStarted = true;
	emit started();
}

 
void QTester::stop()
{
	if (!m_bStarted) return ;
		
	killTimer(m_timerId);
	m_bStarted = false;

	emit stopped();
}

void QTester::timerEvent(QTimerEvent * event)
{	
	if (!m_bStarted) return;

	emit newData();

}

