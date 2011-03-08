// AdcTestPlat.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "AdcTestPlat.h"

#include "MainFrm.h"
#include "AdcTestPlatDoc.h"
#include "AdcTestPlatView.h"

#include "PlxApi.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAdcTestPlatApp

BEGIN_MESSAGE_MAP(CAdcTestPlatApp, CWinApp)
	//{{AFX_MSG_MAP(CAdcTestPlatApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAdcTestPlatApp construction

CAdcTestPlatApp::CAdcTestPlatApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	m_hDevice = NULL;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CAdcTestPlatApp object

CAdcTestPlatApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CAdcTestPlatApp initialization

BOOL CAdcTestPlatApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CAdcTestPlatDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CAdcTestPlatView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->SetWindowText( "SIP测试系统ver2.0" );
	m_nCmdShow = SW_MAXIMIZE;
	m_pMainWnd->ShowWindow(m_nCmdShow);//SW_SHOW
	m_pMainWnd->UpdateWindow();

	//qqqqqq 系统启动后先调用面板上的运行，否则有时设置不成功，不知道这样是否有效
// 	CAdcTestPlatDoc* pDoc = NULL;
// 	pDoc = (CAdcTestPlatDoc*)( ((CFrameWnd*)m_pMainWnd)->GetActiveDocument());
// 	if ( pDoc != NULL )
// 	{
// 		// 算法测试采集
// 		pDoc->SetTestMode(3);
// 	}

	// 查找设备
	BOOL bRet = DetectedCards();
	if ( !bRet )
	{
		int nRet = AfxMessageBox( "没有找到PCIE设备，是否工作在查看模式?", MB_YESNO | MB_ICONQUESTION );
		// 不工作在查看模式，则退出
		if ( nRet == IDNO )
		{
			::SendMessage( m_pMainWnd->m_hWnd, WM_CLOSE, 0, 0 );
		}
	}
/*	
	WORD wTest;
	short test;

	test = -100;
	test >>= 2;
*/
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CAdcTestPlatApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CAdcTestPlatApp message handlers


BOOL CAdcTestPlatApp::DetectedCards()
{
	//U32 devNumber; 
	RETURN_CODE rc;
	DEVICE_LOCATION device;	
	
	device.BusNumber = PCI_FIELD_IGNORE;// PCI_FIELD_IGNORE;
	device.SlotNumber = PCI_FIELD_IGNORE; //PCI_FIELD_IGNORE;
	device.VendorId = 0x10b5;
	device.DeviceId = 0x86e1;
	device.SerialNumber[0] = '\0';	
	rc = PlxPciDeviceOpen( &device, &m_hDevice );
	if (rc != ApiSuccess)
		return FALSE;	

	return TRUE;
}
