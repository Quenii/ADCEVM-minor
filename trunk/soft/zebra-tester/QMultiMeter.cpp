#include "QMultiMeter.h"

#include <QMessageBox>

#pragma comment(lib, "visa32.lib")

#define AfxMessageBox(x) \
	QMessageBox::warning(0, "", (x));

static bool check_inst_model(QString check_msg, QString msgval)
{
	// Checks correct insdtrument model number	

	return check_msg.contains(msgval, Qt::CaseInsensitive);
}

QMultiMeter::QMultiMeter(void)
{
}

QMultiMeter::~QMultiMeter(void)
{
	close();
}

/////////////////////////////////////////////////////////////////////////////
int QMultiMeter::open_port(QString addr)
{
	// This function opens a port (the communication between the instrument and 
	// computer).

	if (m_connected)
		// Close session just in case one is open
		// errorStatus = viClose(vi);
		close();

	// convert CString to char

	addr.append("::INSTR");
	char* instr_addr = addr.toLocal8Bit().data();
	
	// Open the VISA session
	errorStatus = viOpenDefaultRM(&videfaultRM);

	// Open communication to the instrument
	errorStatus = viOpen(videfaultRM, instr_addr, VI_TRUE, VI_TRUE, &vi);

	// If an error occurs, give a message
	if (errorStatus < VI_SUCCESS)
	{
		AfxMessageBox("Unable to Open port; check address");
		return -1; // exit(1);
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
		return 0;
	}

	// Check error
	// check_error("open_port");
	close();

	return 1;	
}	

void QMultiMeter::close()
{
	// Close the instrument session
	errorStatus = viClose(vi);

	// Close the interface session
	errorStatus = viClose(videfaultRM);

	m_connected = false;
}

int QMultiMeter::send_msg(char *Cmds)
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

		return -1;
		// exit(1);
	}

	return 1;

}