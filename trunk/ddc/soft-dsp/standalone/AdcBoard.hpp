#pragma once

#include <vector>
#include <string>
#include "../include/pcap/pcap.h"
#include "gkhy/mfcminus/AsyncHugeRingBuffer.hpp"

#define DSPREQUEST		0x1D
#define DSPRESET		0x1E
#define DSPPARAMETER	0x1F

class CCyUSBDevice;
class DummyWidget;
class QObject;
class QEvent;
#pragma pack(push)

#pragma pack(1)

typedef struct _DspCommand
{
	int Sof;
	unsigned char Cmd;
	int Para[16];
	int Len;
}DspCommand;

#pragma pack(pop)

using namespace std;
class AdcBoard
{


public:	
	virtual ~AdcBoard();
	AdcBoard();

public:
	void TaskStart(bool on = true);
	bool isRunning();

	bool InitWinsock();
	static int SendCmd(DspCommand cmd);
	void AdcBoard::Reset();

	static void ThreadNetAccess(void * lpVoid);
	static void ThreadParseData(void * lpVoid);

public:
	bool open();
	
	void SetServerAddress(string, string, short);
	void SetParameters(int * para, int len);

	
private:
	static pcap_t *m_fp;
	static DspCommand m_cmdRequest, m_cmdReset, m_cmdPara; 

	gkhy::MfcMinus::AsyncHugeRingBuffer * m_fifoArray[37];
	int m_channelFifoSize;

	const static int buffer_cnt = 4 * 1024;
	string infName;

	string serverIp;// = "192.168.10.71";
	static short serverPort;// = 70;
	static struct sockaddr_in server;

private:	
	BOOL volatile m_bThreadNetAccessEnabled;
	BOOL volatile m_bThreadNetAccessCompleted;
	BOOL volatile m_bThreadParseDataEnabled;
	BOOL volatile m_bThreadParseDataCompleted;
};


