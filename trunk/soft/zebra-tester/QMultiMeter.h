#pragma once

#include "visa.h"

#include <QObject>
#include <QString>

class QTimerEvent;

class QMultiMeter : public QObject
{
	static QMultiMeter m_inst;
private:
	QMultiMeter(QObject* parent = 0);
public:
	virtual ~QMultiMeter(void);
private:
	Q_DISABLE_COPY(QMultiMeter);	

public:
	static QMultiMeter* instance() { return &m_inst; }
	bool measureVolt(int averageLevel, float& measured);

private:
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



	void timerEvent(QTimerEvent* e);


private:
	ViSession videfaultRM;	
	ViStatus errorStatus;
	ViSession vi;	
	ViChar	ReturnedData[2048];
	bool m_connected;
};
