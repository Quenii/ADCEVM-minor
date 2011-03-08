#define   WIN32_LEAN_AND_MEAN 
#include "stdafx.h"

#include <vector>
#include <string>
#include <process.h>
#include "../include/pcap/pcap.h"
#include "AdcBoard.hpp"
#include "gkhy/mfcminus/Win32App.hpp"
#include "gkhy/mfcminus/AsyncHugeRingBuffer.hpp"

#ifdef _DEBUG
#endif // _DEBUG


#pragma comment(lib, "wpcap.lib")
#pragma comment(lib, "Ws2_32.lib")

using namespace std;

pcap_t * AdcBoard::m_fp;
DspCommand AdcBoard::m_cmdRequest, AdcBoard::m_cmdReset, AdcBoard::m_cmdPara;
short AdcBoard::serverPort;
struct sockaddr_in AdcBoard::server;


AdcBoard::AdcBoard() 
{
	size_t m_channelFifoSize = 3*1024*1024;
	for (int i = 0; i < (_countof(m_fifoArray) - 1); ++i)
	{
		m_fifoArray[i] = new gkhy::MfcMinus::AsyncHugeRingBuffer(m_channelFifoSize);
	}
	m_fifoArray[36] = new gkhy::MfcMinus::AsyncHugeRingBuffer(m_channelFifoSize*12);
}

AdcBoard::~AdcBoard()
{

}

bool AdcBoard::isRunning()
{
//	return m_timerId ? true : false;
	return !(m_bThreadParseDataCompleted && m_bThreadNetAccessCompleted);
}

void AdcBoard::TaskStart(bool on /* = true */)
{


	if (on/* && !m_timerId */)
	{

		m_bThreadNetAccessEnabled = true;
		m_bThreadNetAccessCompleted = FALSE;
		m_bThreadParseDataEnabled = true;
		m_bThreadParseDataCompleted = FALSE;
		_beginthread(&AdcBoard::ThreadNetAccess, 0, this);
		_beginthread(&AdcBoard::ThreadParseData, 0, this);

	}

	if (!on/* && m_timerId */)
	{
		m_bThreadNetAccessEnabled = false;
		m_bThreadParseDataEnabled = false;
	}
}



bool AdcBoard::open()
{
	char errbuf[PCAP_ERRBUF_SIZE];

	if ((m_fp = pcap_open_live(infName.c_str(),		// name of the device
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
//UINT AdcBoard::ThreadNetAccess(LPVOID lpVoid)
void AdcBoard::ThreadNetAccess(void * lpVoid)
{
	AdcBoard * obj = (AdcBoard *)lpVoid;
	struct pcap_pkthdr *header;
	const u_char *pkt_data;
	int res;
	int pkgcnt = 0;
	bool overflow = false;
	bool timeout = false;
	DWORD tickCnt = 0, tickStart = 0;

	SendCmd(m_cmdRequest);

	tickStart = GetTickCount();

	while (obj->m_bThreadNetAccessEnabled && ((res = pcap_next_ex( m_fp, &header, &pkt_data)) >= 0))
	{	
		if (GetTickCount() - tickStart > 3000)
		{
			timeout = true;
/*			SendCmd(m_cmdRequest);
			tickStart = GetTickCount();
			pkgcnt = 0;
			continue;
*/
			break;
		}
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
/*			Sleep(50);
			SendCmd(m_cmdRequest);
			tickStart = GetTickCount();
			pkgcnt = 0;
*/

			break;
		}

	}

	//////////////////////////////////////////////////////////////////////////
	obj->m_bThreadNetAccessCompleted = TRUE;
//	return 0;

}

//UINT AdcBoard::ThreadParseData(LPVOID lpVoid)
void AdcBoard::ThreadParseData(void * lpVoid)
{
	AdcBoard * obj = (AdcBoard *)lpVoid;
	int pkgcnt = 0;
	const int block_size = 128;
	short temp[block_size];
	short *p = &temp[0];
	short chan_buff[6][20];
	int count_fifo[36] = { 0 };
	int count_packet[7] = { 0 };

	unsigned int ad_num = 0;

	int t = 0;
	while (obj->m_bThreadParseDataEnabled && 
		(!obj->m_bThreadNetAccessCompleted || obj->m_fifoArray[36]->count() > 0))
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
	Error = WSAStartup(VersionRequested, &WsaData); //Æô¶¯WinSock2
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

	server.sin_family = AF_INET;
	server.sin_port = htons(serverPort);     
	server.sin_addr.s_addr = inet_addr(serverIp.c_str()); ///serverµÄµØÖ· 

	return TRUE;
}

int AdcBoard::SendCmd(DspCommand cmd)
{
	cmd.Sof  = 0xFCCF1A00;
	SOCKET skt = socket(AF_INET, SOCK_DGRAM, 0);

	return sendto(skt, (char *)&cmd, cmd.Len, 0, (struct sockaddr*)&server, sizeof(server));
}


void AdcBoard::Reset()
{
	m_bThreadNetAccessEnabled = false;
	m_bThreadParseDataEnabled = false;
	while (!m_bThreadNetAccessCompleted || !m_bThreadParseDataCompleted);
	for (int i = 0; i < (_countof(m_fifoArray) - 1); ++i)
	{
		m_fifoArray[i]->syncClear();
	}
	SendCmd(m_cmdReset);
}
 
void AdcBoard::SetServerAddress(string name, string ip, short port)
{
	infName = name;
	serverIp = ip;
	serverPort = port;

	InitWinsock();

	open();
}

void AdcBoard::SetParameters(int * para, int len)
{
	DspCommand cmd;
	cmd.Cmd = DSPPARAMETER;
	cmd.Len = len*sizeof(int) + 5;
	memcpy(cmd.Para, para, len*sizeof(int));

	SendCmd(cmd);
}

