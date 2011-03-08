// mfcminus.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "mfcminus.h"
#include <afxsock.h>
#include "gkhy/mfcplus/WorkerThread.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

class CMfcMinusApp : public CWinApp
{
public:
	 BOOL InitInstance()
	 {
		 _CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
		 return CWinApp::InitInstance();
	 }
};

CMfcMinusApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

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
	}

	return nRetCode;
}

