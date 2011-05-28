#include "QMultiMeter.h"

#include <QMessageBox>
#include <Windows.h>

#pragma comment(lib, "visa32.lib")
#pragma warning(disable:4996)

#define AfxMessageBox(x) \
	QMessageBox::warning(0, "", (x));

static bool check_inst_model(QString check_msg, QString msgval)
{
	// Checks correct insdtrument model number	

	return check_msg.contains(msgval, Qt::CaseInsensitive);
}


QMultiMeter::QMultiMeter(QObject* parent) 
: QObject(parent)
, m_connected(false)
{
	open_port();
	startTimer(500);

}

QMultiMeter::~QMultiMeter(void)
{
	close();
}

void QMultiMeter::timerEvent(QTimerEvent* e)
{
	if (!isOpen())
	{
		open_port();
	}
}

/////////////////////////////////////////////////////////////////////////////
bool QMultiMeter::open_port(char* addr)
{
	// This function opens a port (the communication between the instrument and 
	// computer).

	if (m_connected)
		// Close session just in case one is open
		// errorStatus = viClose(vi);
		close();

	// convert CString to char
	char* instr_addr = addr; // .toLocal8Bit().data();

	// convert CString to char
// 	LPTSTR instr_addr = new TCHAR[addr.GetLength()+1];
// 	_tcscpy(instr_addr, addr);
// 	_tcscat(instr_addr, "::INSTR");

	
	// Open the VISA session
	errorStatus = viOpenDefaultRM(&videfaultRM);

	// Open communication to the instrument
	errorStatus = viOpen(videfaultRM, instr_addr, VI_TRUE, VI_TRUE, &vi);

	// If an error occurs, give a message
	if (errorStatus < VI_SUCCESS)
	{
		AfxMessageBox("Unable to Open port; check address");
		return false; // exit(1);
	}

	// Set timeout to 5 seconds
	errorStatus = viSetAttribute(vi, VI_ATTR_TMO_VALUE, 5000); 

	// Set the termination character to carriage return (i.e., 13);
	// the 3458A uses this character
	errorStatus = viSetAttribute(vi, VI_ATTR_TERMCHAR, 13);

	// Set the flag to terminate when receiving a termination character
	errorStatus = viSetAttribute(vi, VI_ATTR_TERMCHAR_EN, 1);

	// Query instrument ID string
	send_msg("ID?");
	get_data();

	// Check and make sure the correct instrument is addressed
	if (!check_inst_model(ReturnedData, "3458A"))
	{
		AfxMessageBox("Incorrect instrument selected; use the correct address.");

		// Close the session
		errorStatus = viClose(vi);
		return false;
	}

	if (!setup_inst())
		return false;


	// Check error
	// check_error("open_port");
	// close();

	m_connected = true;

	return true;	
}	

void QMultiMeter::close()
{
	if (m_connected)
	{
		// Close the instrument session
		errorStatus = viClose(vi);

		// Close the interface session
		errorStatus = viClose(videfaultRM);

		m_connected = false;

	}
}

bool QMultiMeter::setup_inst()
{
	// Performs the instrument setup.

	char	*cmds;

	// Setup the 3458A
	cmds =
		"PRESET DIG;"		// Preset to the designated state (Digitizing)
		"MFORMAT DINT;"		// Set the memory storage format (double integer)
		"OFORMAT ASCII;"	// Set the output format (ASCI)
		"APER 6E-6;"		// Set the arperature time (
		"MEM FIFO;"			// Set the meomory staorage type (First In, Fist Out)
		"TRIG AUTO;"		// Set the trigger source (Auto)
		//"NRDGS 4100,AUTO;"	// Set the number of readings (4100 readings)
		"NRDGS 10,AUTO;"	// Set the number of readings (4100 readings)
		"END ON;"			// Enable EOI function
		"TARM HOLD";		// Hold the trigger until triggered

	// Execute the commands
	return send_msg(cmds);

	//Check for errors
	// check_error("setup");
}

bool QMultiMeter::send_msg(char *Cmds)
{
	// This function will send a  command string to the GPIB
	// port.

	unsigned long	actual;  // Number of characters sent/returned
	// char			commandstr[1024];

	// Write the command to the instrument (terminated by a linefeed)
// 	strcpy(commandstr, Cmds);
// 	strcat(commandstr, "\n");
	QString commandstr = QString(Cmds).append("\n");
	errorStatus = viWrite(vi, (ViBuf)qPrintable(commandstr), commandstr.length(), &actual);

	// Check I/O error
	if (errorStatus < VI_SUCCESS)
	{
		AfxMessageBox("I/O error!\n\n");

		// Close instrument session
		errorStatus = viClose(vi);

		// Close the session
		errorStatus = viClose(videfaultRM);

		return false;
		// exit(1);
	}

	return true;

}


//////////////////////////////////////////////////////////////////////////////////////
bool QMultiMeter::get_data()
{	
	// This function reads the string returned by the instrument
	unsigned long	actual; // Number of characters sent/returned

	// Read the response string
	errorStatus = viRead(vi, (ViBuf)ReturnedData, 2048, &actual);

	// NULL terminate the string and remove carriage return
	ReturnedData[actual-1]=0;

	// Check I/O error
	if (errorStatus < VI_SUCCESS)
	{
		/* printf("I/O error!\n\n"); 

		// Close instrument session
		errorStatus = viClose(vi);

		// Close the session
		errorStatus = viClose(videfaultRM);

		exit(1);*/

		close();
		return false;
	}

	return true;
}

bool QMultiMeter::get_rdgs(int n)
{
	// This function triggers the instrument and takes readings.

	ViUInt16	rdcnt;
	char		cmd_str[50], cmd_str1[50];

	
	// Trigger the 3458A
	send_msg("TARM SGL");

	// char* cmd = const_cast<char*>(qPrintable(QString("NRDGS %,AUTO; TARM SGL").arg(n)));
	// send_msg(cmd);

	// Read status byte to determine when measurements are complete
	do
		errorStatus = viReadSTB(vi, &rdcnt);
	while ((rdcnt & 128) != 128);

	// Get number of readings taken
	send_msg("MCOUNT?");
	get_data();
	int num_rdgs = atoi(ReturnedData);

	/*strcat(ReturnedData," mesurements made; takes some time to return them.");
	AfxMessageBox(ReturnedData);
	*/	

	// Setup 'viQueryf' to: viQueryf(vi, "REM 1,4100\n", "%,4100lf", rdgs)'
	// to return readings
	sprintf(cmd_str, "%s %d\n", "RMEM 1,", num_rdgs);
	sprintf(cmd_str1, "%%,%dlf", num_rdgs);

	// Return the readings
	errorStatus=viQueryf(vi, cmd_str,cmd_str1,rdgs);
	
	return true;
	//Check for errors
	// check_error("get_rdgs");
}

bool QMultiMeter::measureVolt(int averageLevel, float& measured)
{
	const int nMeasures = averageLevel + 2;
	QVector<float> vect(nMeasures);
	QMultiMeter* multiMeter = QMultiMeter::instance();

	if (!get_rdgs(nMeasures))
	{
		return false;
	}
	
	float f = 0;
	for (int i = 0; i < 10; ++i)
	{		
		f += rdgs[i];
	}

	measured = float(f / 10);

	return true;
}