#pragma once

#include "visa.h"

#include <QString>

class QMultiMeter
{
public:
	QMultiMeter(void);
	virtual ~QMultiMeter(void);

public:
	// Declare functions
	int open_port(QString addr);
	void close();
	int send_msg(char *Cmds);
	void get_data(void);


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
