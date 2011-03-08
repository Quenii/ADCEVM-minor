#include <windows.h>
#include <qmath.h>
#include <vector>
#include <Dbt.h>
#include <QDebug>
#include <QString>
#include <QEvent>
#include <QList>
#include <QTimer>
#include <QSettings>

#include "AdcBoard.hpp"
#include "CyAPI.h"
#include "gkhy/mfcminus/Win32App.hpp"
#include "QZebraScopeSettings.h"
#include "QZebraScopeSettings.h"

#ifdef _DEBUG
#endif // _DEBUG

#ifdef MATLAB   //defined in AdcBoardTypes.hpp
#include "libalgo_wrapper.h"
#endif // MATLAB

#pragma comment(lib, "CyAPI.lib")

using namespace std;


DummyWidget::DummyWidget(QWidget* parent /*= 0*/, Qt::WindowFlags f /*= 0*/ ) : QWidget(parent, f) 
{
	bPnP_Arrival = false;
	bPnP_DevNodeChange = false;
	bPnP_Removal = false;
	QTimer::singleShot(0, this, SIGNAL(devChanged()));	
}

bool DummyWidget::winEvent(MSG * message, long * result)
{	
	if (message->message == WM_DEVICECHANGE) {
		// Tracks DBT_DEVICEARRIVAL followed by DBT_DEVNODES_CHANGED
		if (message->wParam == DBT_DEVICEARRIVAL) {
			bPnP_Arrival = true;
			bPnP_DevNodeChange = false;
		}
		// Tracks DBT_DEVNODES_CHANGED followed by DBT_DEVICEREMOVECOMPLETE
		if (message->wParam == DBT_DEVNODES_CHANGED) {
			bPnP_DevNodeChange = true;
			bPnP_Removal = false;
		}
		if (message->wParam == DBT_DEVICEREMOVECOMPLETE) {
			bPnP_Removal = true;
			PDEV_BROADCAST_HDR bcastHdr = (PDEV_BROADCAST_HDR) message->lParam;
			if (bcastHdr->dbch_devicetype == DBT_DEVTYP_HANDLE) {
				PDEV_BROADCAST_HANDLE pDev = (PDEV_BROADCAST_HANDLE) message->lParam;
				/*if (pDev->dbch_handle == USBDevice->DeviceHandle())
				USBDevice->Close();*/
			}
		}
		// If DBT_DEVNODES_CHANGED followed by DBT_DEVICEREMOVECOMPLETE
		if (bPnP_Removal && bPnP_DevNodeChange) {
			//Sleep(10);
			//DisplayDevices();
			bPnP_Removal = false;
			bPnP_DevNodeChange = false;
			//gkhy::MfcMinus::Win32App::sleep(10);
			emit devChanged();
		}
		// If DBT_DEVICEARRIVAL followed by DBT_DEVNODES_CHANGED
		if (bPnP_DevNodeChange && bPnP_Arrival) {
			//DisplayDevices();
			bPnP_Arrival = false;
			bPnP_DevNodeChange = false;
			emit devChanged();
		}
	}
	return false;
}

AdcBoard* AdcBoard::_inst = 0;
AdcBoard::AdcBoard(QObject* parent /* = 0 */) 
: QObject(parent)
, pi(3.141592653589793f)
, m_timerId(0)
{
	widget = new DummyWidget();
	bool okay = connect(widget, SIGNAL(devChanged()), this, SLOT(devChanged()));
	Q_ASSERT(okay);
	usbDev = new CCyUSBDevice((HANDLE)(widget->winId()));

	//m_settings.beginGroup("AdcBoard");

	QZebraScopeSettings settings;
	settings.adcSettings(m_adcSettings);
	settings.signalSettings(m_signalSettings);

	setAdcSettings(m_adcSettings);
	setSignalSettings(m_signalSettings);
}

AdcBoard::~AdcBoard()
{
	if (usbDev)
	{
		delete usbDev;
		usbDev = 0;
	}

	if (widget)
	{
		delete widget;
		widget = 0;
	}
}

bool AdcBoard::isRunning()
{
	return m_timerId ? true : false;
}

void AdcBoard::setDynamicOn(bool on /* = true */)
{
	if (on && !m_timerId)
	{
		m_timerId = startTimer(500);
	}

	if (!on && m_timerId)
	{
		killTimer(m_timerId);
		m_timerId = 0;
	}
}

void AdcBoard::devChanged()
{
	QList<AdcBoardInfo> devList;
	if (!(usbDev->DeviceCount()))
	{
		devList.clear();
	}
	for (int i = 0; i < usbDev->DeviceCount(); ++i)
	{
		if (usbDev->Open(i))
		{
			AdcBoardInfo info;
			info.usbAddr = i;
			info.devName = QString(usbDev->DeviceName);
			info.infName = QString(usbDev->FriendlyName);
			devList.push_back(info);
		}
	}

	emit devListChanged(devList);
}

bool AdcBoard::open(int usbAddr)
{
	return usbDev->Open((UCHAR)usbAddr);
}

bool AdcBoard::read(unsigned short addr, unsigned short *buf, unsigned int len)
{	
	if (! usbDev->BulkOutEndPt)
		return false;

	long b2Read = (len * sizeof(unsigned short) + 511) / 512 * 512;
	long w2Read = b2Read / 2;
	if (bulkIOBuff.size() < w2Read) bulkIOBuff.resize(w2Read);

	if (!writeIOCmd(addr, true, w2Read))
	{
		return false;
	}

	long bRead = b2Read;
	if (!usbDev->BulkInEndPt->XferData((unsigned char*)&bulkIOBuff[0], bRead))
		return false;

	if (b2Read != bRead)
	{
		return false;
	}

	memcpy(buf, &bulkIOBuff[0], len * sizeof(unsigned short));

	return true;
}

bool AdcBoard::writeIOCmd(unsigned short addr, bool dirRead, unsigned short data)
{	
	if (! usbDev->BulkOutEndPt)
		return false;

	if (bulkIOBuff.size() < 4) bulkIOBuff.resize(4);

	bulkIOBuff[0] = 0xbc95;
	bulkIOBuff[1] = addr;
	bulkIOBuff[2] = dirRead ?  0xFF00 : 0x00FF;
	bulkIOBuff[3] = data;
	long llen = 4 * sizeof(unsigned short);
	if (!usbDev->BulkOutEndPt->XferData((UCHAR*)&bulkIOBuff[0], llen))
		return false;

	return true;
}

bool AdcBoard::readReg(unsigned short addr, unsigned short &val)
{
	return read(addr, &val, 1);
}

bool AdcBoard::writeReg(unsigned short addr, unsigned short val)
{
	if (!writeIOCmd(addr, false, val))
	{
		return false;
	}

	return true;
}

bool AdcBoard::readReg24b(unsigned short addr,unsigned short& val)
{
	unsigned short w1 = (addr & 0xFF) << 8;
	unsigned short w2 = (addr & 0xFF00) >> 8 | 0x80;
	unsigned short r;
	if (!writeReg(0x1002, w1))
		return false;

	gkhy::MfcMinus::Win32App::sleep(100);

	if (!writeReg(0x1003, w2))
		return false;

	gkhy::MfcMinus::Win32App::sleep(300);

	unsigned short temp[1024];

	memset(temp, 0, sizeof(temp));
	if ( !read(0x1002, temp, 1024)  )
	{
		return false;
	}
	val = temp[0];

	//if ( !read(0x1002, &buff[0], 1024)  )
	//{
	//	return false;
	//}

	//	val = buff[0];

	return 	true;
}

bool AdcBoard::writeReg24b(unsigned short addr,unsigned short val)
{
	unsigned short w1 = ((addr & 0xFF) << 8) | (val & 0xFF);
	unsigned short w2 = (addr & 0xFF00) >> 8;
	return (writeReg(0x1002, w1)  && writeReg(0x1003, w2));
}

void AdcBoard::changeSampleRate(uint sampleFreq)
{

}

void AdcBoard::timerEvent(QTimerEvent* event)
{
	//return ;

	PowerStatus& powerStatus = report.powerStatus;
	this->powerStatus(powerStatus);

	TimeDomainReport& tdReport = report.tdReport;
	tdReport.samples.resize(buffer_cnt);

	float vpp = m_adcSettings.vpp;
	float max = (1 << (m_adcSettings.bitcount - 1));
	if (m_adcSettings.coding == AdcCodingOffset)
	{
	}
	else if (m_adcSettings.coding == AdcCodingComplement)
	{
	}
	else
	{
		Q_ASSERT(false);
	}

	if (usbDev->IsOpen() && (usbDev->DeviceCount()))
	{
		buff.resize(buffer_cnt);
		writeReg(0xFFFF, 0x0001);  //reset
		writeReg(0xFFFF, 0x0000);  //dereset
		//buff[512] = {0x0032};
		writeReg(0x1004, 0xEFFF);  //stor 1M
		//read(0x04, buff, 256);
		Sleep(200);	

		unsigned short* p = &buff[0];
		bool okay = read(0x1005, &buff[0], buffer_cnt);
		Q_ASSERT(okay);

		if (tdReport.rawSamples.size() != buff.size())
		{
			tdReport.rawSamples.resize(buff.size());
		}
		for (int i = 0; i < tdReport.samples.size(); i+=4)
		{
			tdReport.rawSamples[i+0] = buff[i+3];
			tdReport.rawSamples[i+1] = buff[i+2];
			tdReport.rawSamples[i+2] = buff[i+1];
			tdReport.rawSamples[i+3] = buff[i+0];

			tdReport.samples[i+0] = (buff[i+3]/max-1)*vpp;
			tdReport.samples[i+1] = (buff[i+2]/max-1)*vpp;
			tdReport.samples[i+2] = (buff[i+1]/max-1)*vpp;
			tdReport.samples[i+3] = (buff[i+0]/max-1)*vpp;	
		}
	}
	else
	{
#ifdef _DEBUG

		int offset = rand();
		tdReport.rawSamples.resize(tdReport.samples.size());
		for (int i = 0; i < tdReport.samples.size(); ++i)
		{
			//tdReport.samples[i] = ((int)((i+offset)));
			//tdReport.rawSamples[i] = ((int)((i+offset)));

			tdReport.samples[i] = ((int)(qSin(pi/29*i+offset)*8192))*vpp/8192;
			tdReport.rawSamples[i] = ((int)(qSin(pi/29*i+offset)*8192));
		}
#endif //_DEBUG
	}

	float fmin = vpp;
	float fmax = -vpp;
	for (int i = 0; i < tdReport.samples.size(); ++i )
	{
		float f = tdReport.samples[i];
		fmin = min(fmin, f);
		fmax = max(fmax, f);
	}

	tdReport.max = fmax;
	tdReport.min = fmin;

	FreqDomainReport& fdReport = report.fdReport;

	fdReport.Spectrum.resize(buffer_cnt/2);

#ifdef MATLAB
	calc_dynam_params(tdReport.samples, 16, fdReport);

#else
	memcpy( &fdReport.Spectrum[0], &tdReport.samples[0], buffer_cnt/2);

#endif // MATLAB

	emit boardReport(report);
}


unsigned short AdcBoard::CalcReg(float v)
{
	//todo: 1, 
	float min = 1.41f;
	float max = 3.60f;
	float step = 65536/(max - min);
	//calibrite from vio@2s60;
	//unsigned int reg = (int)((max-v)*step);

	//
	unsigned int reg = (int)((3.00f-v)*31000);
	unsigned short temp = reg;
	return temp;
}

bool AdcBoard::setAdcSettings(const AdcSettings& adcSettings)
{	
	float vio = adcSettings.vd;

	//配置2656，控制板卡电压
	if (!writeReg(5, CalcReg(vio)) ) //控制VIO电压到1.8V
		return false;

	if (!writeReg(6, 0x0004))  //执行 通道E
		return false;

	//writeReg(5, 0x8000);  //控制VD电压到1.8V
	if (!writeReg(5, CalcReg(adcSettings.vd)))
		return false;
	if (!writeReg(6, 0x0000))  //执行 通道A
		return false;

	//writeReg(5, 0x77FF);  //控制VA电压到1.8V
	if (!writeReg(5, CalcReg(adcSettings.va)))
		return false;
	if (!writeReg(6, 0x0002))  //执行 通道C
		return false;


	if (!writeReg(0xFFFF, 0xFFFF))  //reset
		return false;
	gkhy::MfcMinus::Win32App::sleep(10);

	if (!writeReg(0xFFFF, 0x0000))  //dereset
		return false;
	gkhy::MfcMinus::Win32App::sleep(200);

	//writeReg(0x1000, 0x000C);  //jad14p1 reset
	//gkhy::MfcMinus::Win32App::sleep(200);

	//writeReg(0x1000, 0x0003);

	if (!writeReg(0x1000, 0x000D)) return false;
	if (!writeReg(0x1000, 0x000C)) return false;  //jad14p1  reset
	gkhy::MfcMinus::Win32App::sleep(2);

	if (!writeReg(0x1000, 0x0001)) return false;
	gkhy::MfcMinus::Win32App::sleep(600);
	if (!writeReg(0x1000, 0x0003)) return false;
	gkhy::MfcMinus::Win32App::sleep(100);
	if (!writeReg(0x1000, 0x000B)) return false;

	m_adcSettings = adcSettings;
	//m_adcSettings.writeSettings(m_settings);
	QZebraScopeSettings settings;
	settings.setAdcSettings(m_adcSettings);

	return true;

}

bool AdcBoard::setSignalSettings(const SignalSettings& signalSettings)
{
	// change sampling frequency
	changeSampleRate(signalSettings.clockFreq);

	//todo: 1, add gpib code to specify the input signal/clock;

	float fs = signalSettings.clockFreq;
	TimeDomainReport &tdReport = report.tdReport;
	
	tdReport.xaxis.resize(buffer_cnt);

	for (int i = 0; i < tdReport.xaxis.size(); ++i)
	{
		tdReport.xaxis[i] = (float)i * (1e9 / fs);  //ns
	}

	FreqDomainReport& fdReport = report.fdReport;

	fdReport.xaxis.resize(buffer_cnt/2);
	float k = fs / 2 / (fdReport.xaxis.size()) / 1e6;

	for (int i = 0; i < fdReport.xaxis.size(); ++i)
	{
		fdReport.xaxis[i] = (float)i * k;
	}

	m_signalSettings = signalSettings;
	// m_signalSettings.writeSettings(m_settings);

	QZebraScopeSettings settings;
	settings.setSignalSettings(m_signalSettings);

	return true;
}

void AdcBoard::powerStatus(PowerStatus& powerStatus)
{

	if (buff.size() < 1024)
	{
		buff.resize(1024);
	}
	unsigned short* p = &buff[0];
	writeReg(9, 0xA400);  //select 3548, work at default mode
	writeReg(9, 0xA400);  //select 3548, work at default mode
	//writeReg(9, 0xFFFF);  //select 3548, work at default mode
	//writeReg(9, 0xFFFF);  //select 3548, work at default mode

	//writeReg(9, 0xA740);  //select 3548, work at sweep mode

	//for (int i=0; i<=7; ++i)
	//{
	//	writeReg(9, i*0x1000);
	//}

	//writeReg(9, 0xE000);

	writeReg(9, 0x7FFF);  //select 3548, select 7th channel
	writeReg(9, 0x7FFF);  //select 3548, select 7th channel
	writeReg(9, 0xeFFF);  //select 3548, read out 7th channel volage
	writeReg(9, 0xeFFF);  //select 3548, read out 7th channel volage
	read(0x0009, &buff[0], 1024);
	powerStatus.va = (float(buff[0]>>2)) * 4 / 16384;
	
	writeReg(9, 0x3FFF);  //select 3548, select 7th channel
	writeReg(9, 0x3FFF);  //select 3548, select 7th channel
	writeReg(9, 0xeFFF);  //select 3548, read out 7th channel volage
	writeReg(9, 0xeFFF);  //select 3548, read out 7th channel volage
	read(0x0009, &buff[0], 1024);
	powerStatus.vd = (float(buff[0]>>2)) * 4 / 16384;

	writeReg(9, 0x4FFF);  //select 3548, select 7th channel
	writeReg(9, 0x4FFF);  //select 3548, select 7th channel
	writeReg(9, 0xeFFF);  //select 3548, read out 7th channel volage
	writeReg(9, 0xeFFF);  //select 3548, read out 7th channel volage
	read(0x0009, &buff[0], 1024);
	powerStatus.ia = (float(buff[0]>>2)) * 1000 * 4 / 16384;

	writeReg(9, 0x1FFF);  //select 3548, select 7th channel
	writeReg(9, 0x1FFF);  //select 3548, select 7th channel
	writeReg(9, 0xeFFF);  //select 3548, read out 7th channel volage
	writeReg(9, 0xeFFF);  //select 3548, read out 7th channel volage
	read(0x0009, &buff[0], 1024);
	powerStatus.id = (float(buff[0]>>2)) * 1000 * 4 / 16384;

	powerStatus.power = powerStatus.va * powerStatus.ia + powerStatus.vd * powerStatus.id;


}