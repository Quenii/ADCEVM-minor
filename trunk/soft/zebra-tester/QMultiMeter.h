#pragma once

#include "visa.h"

#include <QString>

class QMultiMeter
{
public:
	static QMultiMeter* instance() { static QMultiMeter _inst; return & _inst; }
private:
	QMultiMeter();
public:
	virtual ~QMultiMeter(void);

public:
	// Declare functions
	bool open_port(char* addr = "GPIB0::22::INSTR");
	void close();
	bool isOpen() { return m_connected; }
	bool send_msg(char *Cmds);
	bool get_data(void);


/*	int check_inst_model(CString check_msg, CString msgval);
	void setup_inst(void);
	void get_rdgs(void);
	void check_error(CString msg);
*/
private:
	ViSession videfaultRM;	
	ViStatus errorStatus;
	ViSession vi;	
	ViChar	ReturnedData[2048];
	bool m_connected;
};
