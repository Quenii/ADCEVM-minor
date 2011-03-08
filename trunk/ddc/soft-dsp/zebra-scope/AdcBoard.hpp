#pragma once

#include <QObject>
#include <QString>
#include <QList>
#include <QWidget>
#include <vector>
#include <QSettings>

#include "AdcBoardTypes.hpp"
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

class AdcBoard : public QObject
{
	Q_OBJECT

private:
	static AdcBoard* _inst;

public:
	static AdcBoard* instance() 
	{
		if (!_inst)
		{
			_inst = new AdcBoard(0);
		}

		return _inst;
	}

public:	
	virtual ~AdcBoard();

private:
	AdcBoard(QObject* parent = 0);
	Q_DISABLE_COPY(AdcBoard);

public:
	bool readReg(unsigned short addr,unsigned short& val);
	bool writeReg(unsigned short addr,unsigned short val);

	bool readReg24b(unsigned short addr,unsigned short& val);
	bool writeReg24b(unsigned short addr,unsigned short val);

	void changeSampleRate(uint sampleFreq);	

	bool setAdcSettings(const AdcSettings& adcSettings);
	bool setSignalSettings(const SignalSettings& signalSettings);	

	void adcSettings(AdcSettings& adcSettings) { adcSettings = m_adcSettings; }
	void signalSettings(SignalSettings& signalSettings) { signalSettings = m_signalSettings; }	
	void powerStatus(PowerStatus& powerStatus);

	void setDynamicOn(bool on = true);
	bool isRunning();
	const AdcBoardReport& reportRef() { return report; }

	bool InitWinsock();
	static int SendCmd(DspCommand cmd);
//	UINT ThreadNetAccess(LPVOID lpVoid);
	static void ThreadNetAccess(void * lpVoid);
	static void ThreadParseData(void * lpVoid);



protected:
	void timerEvent (QTimerEvent * event);
	// len - number of unsigned-short's
	bool read(unsigned short addr, unsigned short* buf, unsigned int len);
	// len - number of unsigned-short's
	//bool write(unsigned int addr, const unsigned short* buf, int len);
	

private:
	bool writeIOCmd(unsigned short addr, bool dirRead, unsigned short data);

	unsigned short CalcReg(float v);

signals:
	void devListChanged(const QList<AdcBoardInfo>& lst);
	void boardReport(const AdcBoardReport& report);

public slots:
	bool open(int usbAddr);
	bool open(QString infName);
	
private slots:
	void devChanged();
	
private:
	static pcap_t *m_fp;
	static DspCommand m_cmdRequest, m_cmdReset, m_cmdPara; 

	CCyUSBDevice* usbDev;

	AdcBoardReport report;
	DummyWidget* widget;
	std::vector<unsigned short> bulkIOBuff;
	std::vector<unsigned short> buff;

	gkhy::MfcMinus::AsyncHugeRingBuffer * m_fifoArray[37];
	int m_channelFifoSize;

	const static int buffer_cnt = 4 * 1024;
	const float pi;

private:	
	AdcSettings m_adcSettings;
	SignalSettings m_signalSettings;
	int m_timerId;
	BOOL volatile m_bThreadNetAccessEnabled;
	BOOL volatile m_bThreadNetAccessCompleted;
	BOOL volatile m_bThreadParseDataEnabled;
	BOOL volatile m_bThreadParseDataCompleted;
};


///// 
class DummyWidget : public QWidget
{
	Q_OBJECT

public:
	DummyWidget(QWidget* parent = 0, Qt::WindowFlags f = 0 );

protected:
	bool winEvent(MSG * message, long * result);

signals:
	void devChanged();

private:
	bool bPnP_Arrival;
	bool bPnP_DevNodeChange;
	bool bPnP_Removal;
};
