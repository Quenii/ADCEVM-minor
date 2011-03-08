#define   WIN32_LEAN_AND_MEAN 

#include <windows.h>
#include <process.h>
#include <qmath.h>
#include <vector>
#include <Dbt.h>
#include <QDebug>
#include <QString>
#include <QEvent>
#include <QList>
#include <QTimer>
#include <QSettings>

#include "CyAPI.h"

#include "../include/pcap/pcap.h"
#include "AdcBoard.hpp"
#include "gkhy/mfcminus/Win32App.hpp"
#include "gkhy/mfcminus/AsyncHugeRingBuffer.hpp"
#include "QZebraScopeSettings.h"
#include "QZebraScopeSettings.h"

#ifdef _DEBUG
#endif // _DEBUG

#ifdef MATLAB   //defined in AdcBoardTypes.hpp
#include "libalgo_wrapper.h"
#endif // MATLAB

#pragma comment(lib, "CyAPI.lib")
#pragma comment(lib, "wpcap.lib")
#pragma comment(lib, "Ws2_32.lib")

using namespace std;

pcap_t * AdcBoard::m_fp;
DspCommand AdcBoard::m_cmdRequest, AdcBoard::m_cmdReset, AdcBoard::m_cmdPara;

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
, m_channelFifoSize(3*1024*1024)
//, m_fifoArray(m_channelFifoSize)
{
	for (int i = 0; i < (_countof(m_fifoArray) - 1); ++i)
	{
		m_fifoArray[i] = new gkhy::MfcMinus::AsyncHugeRingBuffer(m_channelFifoSize);
	}
	m_fifoArray[36] = new gkhy::MfcMinus::AsyncHugeRingBuffer(m_channelFifoSize*12);

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


	//开启读数据线程；
	//创建若干AsyncFIFO，属于AdcBoard类；
	//线程中通过this指针访问fifo；
	//timer里面读取数据、解析、显示；
	if (on && !m_timerId)
	{
		InitWinsock();
		SendCmd(m_cmdReset);
		Sleep(1000);
		SendCmd(m_cmdPara);
		Sleep(1000);
		SendCmd(m_cmdRequest);

		m_bThreadNetAccessEnabled = true;
		m_bThreadNetAccessCompleted = FALSE;
		m_bThreadParseDataEnabled = true;
		m_bThreadParseDataCompleted = FALSE;
//		AfxBeginThread(&AdcBoard::ThreadNetAccess, this, THREAD_PRIORITY_TIME_CRITICAL);
		unsigned threadID;

		// Create the second thread.
//		_beginthreadex( NULL, 0, &AdcBoard::ThreadNetAccess, this, 0, &threadID );
		_beginthread(&AdcBoard::ThreadNetAccess, 0, this);
		_beginthread(&AdcBoard::ThreadParseData, 0, this);


		m_timerId = startTimer(500);
	}

	if (!on && m_timerId)
	{
		m_bThreadNetAccessEnabled = false;
		m_bThreadParseDataEnabled = false;
		killTimer(m_timerId);
		m_timerId = 0;
	}
}

void AdcBoard::devChanged()
{
	QList<AdcBoardInfo> devList;

	pcap_if_t *alldevs;
	pcap_if_t *d;

	char errbuf[PCAP_ERRBUF_SIZE];

	/* Retrieve the device list */
	if(pcap_findalldevs(&alldevs, errbuf) != -1)
	{
		devList.clear();
	}

	int i = 0;
	for (d=alldevs; d; d=d->next)
	{
		AdcBoardInfo info;
		info.index = i++;
		info.devName = QString(d->description);
		info.infName = QString(d->name);
		devList.push_front(info);
	}

	//if (!(usbDev->DeviceCount()))
	//{
	//	devList.clear();
	//}
	//for (int i = 0; i < usbDev->DeviceCount(); ++i)
	//{
	//	if (usbDev->Open(i))
	//	{
	//		AdcBoardInfo info;
	//		info.usbAddr = i;
	//		info.devName = QString(usbDev->DeviceName);
	//		info.infName = QString(usbDev->FriendlyName);
	//		devList.push_back(info);
	//	}
	//}

	emit devListChanged(devList);
}

bool AdcBoard::open(int usbAddr)
{
	return usbDev->Open((UCHAR)usbAddr);
}

bool AdcBoard::open(QString infName)
{
	char errbuf[PCAP_ERRBUF_SIZE];
	QByteArray byteArray = infName.toAscii();

	if ((m_fp = pcap_open_live((const char *)byteArray.data(),		// name of the device
		65536,								// portion of the packet to capture. 
		// 65536 grants that the whole packet will be captured on all the MACs.
		1,									// promiscuous mode (nonzero means promiscuous)
		1000,								// read timeout
		errbuf								// error buffer
		)) == NULL)
	{
		return FALSE;
	}

	bpf_u_int32 NetMask=0xffffff;
	struct bpf_program fcode;
	const char *filter ="dst port 69";

	//compile the filter
	if(pcap_compile(m_fp, &fcode, filter, 1, NetMask) < 0)
	{
		//fprintf(stderr,"\nError compiling filter: wrong syntax.\n");
		pcap_close(m_fp);
		return false;
	}

	//set the filter
	if(pcap_setfilter(m_fp, &fcode)<0)
	{
		//fprintf(stderr,"\nError setting the filter\n");
		pcap_close(m_fp);
		return false;
	}

	m_cmdRequest.Cmd = DSPREQUEST;
	m_cmdRequest.Len = 5;

	m_cmdReset.Cmd = DSPRESET;
	m_cmdReset.Len = 5;

	m_cmdPara.Cmd = DSPPARAMETER;
	m_cmdPara.Para[0] = 0x0C00;
	m_cmdPara.Para[1] = 0x07;
	m_cmdPara.Len = 13;


	return true;
}

void AdcBoard::ThreadNetAccess(void * lpVoid)
{
	AdcBoard * obj = (AdcBoard *)lpVoid;
	struct pcap_pkthdr *header;
	const u_char *pkt_data;
	int res;
	int pkgcnt = 0;
	bool overflow = false;
	bool timeout = false;

	while (obj->m_bThreadNetAccessEnabled && ((res = pcap_next_ex( m_fp, &header, &pkt_data)) >= 0))
	{	
		//if ()
		//{
		//	timeout = true;
		//}
		if(res == 0)
		{
			continue;
		}
		int len = header->caplen - 44;
		const char * src = (const char *)(pkt_data + 44);
		const int pkt_len = 1024;

		if (len > 0)
		{
			pkgcnt ++;
			if (len == pkt_len && obj->m_fifoArray[36]->totalWritableSize() >= pkt_len)
			{
				if ( obj->m_fifoArray[36]->write(src, pkt_len) < pkt_len)
				{
					overflow = true;
				}
			}
			else
			{
				overflow = true;
			}
		}
		if (pkgcnt == 3 * 1024)
		{
//			int t = obj->m_fifoArray[36]->count();
			Sleep(50);
			SendCmd(m_cmdRequest);
			pkgcnt = 0;
		}

	}

	//////////////////////////////////////////////////////////////////////////
	obj->m_bThreadNetAccessCompleted = TRUE;
//	return 0;

}

void AdcBoard::ThreadParseData(void * lpVoid)
{
	AdcBoard * obj = (AdcBoard *)lpVoid;
	int res;
	int pkgcnt = 0;
	const int block_size = 128;
	short temp[block_size];
	short *p = &temp[0];
	short chan_buff[6][20];
	int count_fifo[36] = { 0 };
	int count_packet[7] = { 0 };

	unsigned int ad_num = 0;

	int t = 0;
	while (obj->m_bThreadParseDataEnabled)
	{	
		if (obj->m_fifoArray[36]->count() >= block_size)
		{
			obj->m_fifoArray[36]->read((char *)temp, block_size);
			p = &temp[0];
			ad_num = (*((char *)p + 3)) & 0x0F;
			p += 4;
			if (ad_num < 6)
			{
				count_packet[ad_num] ++;
				int j = 0;
				while (p-temp < block_size/2)
				{
					for (int i=0; i<6; ++i)
					{
						chan_buff[i][j] = *p;
						count_fifo[(ad_num) * 6 + i] += 2;
						p += 1;
					}
					j++;
				}
				for (int i=0; i<6; ++i)
				{
					obj->m_fifoArray[(ad_num) * 6 + i]->write((char *)chan_buff[i], 20);
				}

			}
			else
			{
				count_packet[6]++;
			}
		}
		//for (int i=0; i<36; ++i)
		//{
		//	count_fifo[i] = obj->m_fifoArray[i]->count();
		//}
		t = obj->m_fifoArray[36]->count();
	}

	//////////////////////////////////////////////////////////////////////////
	obj->m_bThreadParseDataCompleted = TRUE;
	//	return 0;

}
bool AdcBoard::InitWinsock()
{
	int Error;
	WORD VersionRequested;
	WSADATA WsaData;
	VersionRequested = MAKEWORD(2, 2);
	Error = WSAStartup(VersionRequested, &WsaData); //启动WinSock2
	if(Error != 0)
	{
		return FALSE;
	}
	else
	{
		if(LOBYTE(WsaData.wVersion) != 2 
			|| HIBYTE(WsaData.wHighVersion) != 2)
		{
			WSACleanup();
			return FALSE;
		}

	}
	return TRUE;
}

int AdcBoard::SendCmd(DspCommand cmd)
{
	const char * serverIp = "192.168.10.71";
	static short serverPort = 70;

	static struct sockaddr_in server;

	server.sin_family = AF_INET;
	server.sin_port = htons(serverPort);                      ///server的监听端口
	server.sin_addr.s_addr = inet_addr(serverIp); ///server的地址 
	cmd.Sof  = 0xFCCF1A00;

	SOCKET skt = socket(AF_INET, SOCK_DGRAM, 0);

	return sendto(skt, (char *)&cmd, cmd.Len, 0, (struct sockaddr*)&server, sizeof(server));
}

bool AdcBoard::read(unsigned short addr, unsigned short *buf, unsigned int len)
{	
	return true;
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
	return true;
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
	return true;
	return read(addr, &val, 1);
}

bool AdcBoard::writeReg(unsigned short addr, unsigned short val)
{
	return true;

	if (!writeIOCmd(addr, false, val))
	{
		return false;
	}

	return true;
}

bool AdcBoard::readReg24b(unsigned short addr,unsigned short& val)
{
	return true;

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

	return 	true;
}

bool AdcBoard::writeReg24b(unsigned short addr,unsigned short val)
{
	return true;
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

	TimeDomainReport& tdReport = report.tdReport;
	tdReport.samples.resize(buffer_cnt);
	char temp[buffer_cnt];
	int channel = 12;

	if (m_fifoArray[channel]->count() >= buffer_cnt)
	{
		m_fifoArray[channel]->read(temp, buffer_cnt);
		memcpy(&tdReport.samples[0], temp, buffer_cnt);
	}


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
	return true;

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
	return true;
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

	return;

	if (buff.size() < 1024)
	{
		buff.resize(1024);
	}
	unsigned short* p = &buff[0];
	writeReg(9, 0xA400);  //select 3548, work at default mode
	writeReg(9, 0xA400);  //select 3548, work at default mode

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