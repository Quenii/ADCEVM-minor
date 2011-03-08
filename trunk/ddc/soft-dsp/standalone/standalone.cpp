// standalone.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "standalone.h"
#include "AdcBoard.hpp"

#include "../include/pcap/pcap.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;
string selectdevice();

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;
	string ip("192.168.10.71");
	short port = 70;

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		_tprintf(_T("Fatal Error: MFC initialization failed\n"));
		nRetCode = 1;
	}
	else
	{
		// TODO: code your application's behavior here.
		AdcBoard board;
		string infName = selectdevice();
		board.SetServerAddress(infName, ip, port);
		board.Reset();
		int para[2];
		para[0] = 0x0C00;
		para[1] = 0x07;
		board.SetParameters(para, 2);
		board.TaskStart(true);
		while(board.isRunning())
			Sleep(100);


	}

	return nRetCode;
}


string selectdevice()
{

	pcap_if_t *alldevs;
	pcap_if_t *d;
	string infName;

	char errbuf[PCAP_ERRBUF_SIZE];
	char input;

	/* Retrieve the device list */
	if(pcap_findalldevs(&alldevs, errbuf) != -1)
	{
		//return false;
	}

	int i = 0;
	do 
	{
		i = 0;
		printf("Please Select Network Device to Received ADC Sampling Data:\n");
		for (d=alldevs; d; d=d->next)
		{

			printf("No. %d\t", i++);
			printf("Name:%s\t", d->description);
			printf("Device:%s", d->name);
			printf("\n");
		}
		printf("Input [0 to %d]:", i-1);
		input = getchar();
	} while (input < 48 || input > 48+i-1);

	i = 0;
	for (d=alldevs; d; d=d->next)
	{
		if(i == input - 48)
		{
			infName = d->name;
			break;
		}
		else
			i++;
	}

	return infName;

}