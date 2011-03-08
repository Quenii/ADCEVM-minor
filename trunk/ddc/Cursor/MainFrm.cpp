// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "AdcTestPlat.h"

#include "MainFrm.h"
#include "DataDisp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ID_INDICATOR_STATE (WM_USER+203)

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_TEST_ADC_BATCH, OnTestAdcBatch)
	ON_UPDATE_COMMAND_UI(ID_TEST_ADC_BATCH, OnUpdateTestAdcBatch)
	ON_COMMAND(ID_TEST_ADC, OnTestAdc)
	ON_UPDATE_COMMAND_UI(ID_TEST_ADC, OnUpdateTestAdc)
	ON_COMMAND(ID_TEST_ALG, OnTestAlg)
	ON_UPDATE_COMMAND_UI(ID_TEST_ALG, OnUpdateTestAlg)
	ON_COMMAND(ID_VIEW_ALG_RECORD, OnViewAlgRecord)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ALG_RECORD, OnUpdateViewAlgRecord)
	ON_COMMAND(ID_VIEW_ADC_RECORD, OnViewAdcRecord)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ADC_RECORD, OnUpdateViewAdcRecord)
	ON_COMMAND(ID_VIEW_ADC_BATCH_RECORD, OnViewAdcBatchRecord)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ADC_BATCH_RECORD, OnUpdateViewAdcBatchRecord)
	ON_COMMAND(ID_MY_FILE_SAVE, OnMyFileSave)
	ON_UPDATE_COMMAND_UI(ID_MY_FILE_SAVE, OnUpdateMyFileSave)
	ON_COMMAND(ID_MY_FILE_OPEN, OnMyFileOpen)
	ON_UPDATE_COMMAND_UI(ID_MY_FILE_OPEN, OnUpdateMyFileOpen)
	ON_COMMAND(ID_FFT_SAVE, OnFftSave)
	ON_COMMAND(ID_MENU_ZOOM_BOTH, OnMenuZoomBoth)
	ON_UPDATE_COMMAND_UI(ID_MENU_ZOOM_BOTH, OnUpdateMenuZoomBoth)
	ON_COMMAND(ID_MENU_ZOOM_H, OnMenuZoomH)
	ON_UPDATE_COMMAND_UI(ID_MENU_ZOOM_H, OnUpdateMenuZoomH)
	ON_COMMAND(ID_MENU_ZOOM_V, OnMenuZoomV)
	ON_UPDATE_COMMAND_UI(ID_MENU_ZOOM_V, OnUpdateMenuZoomV)
	ON_COMMAND(ID_MENU_ZOOM_IN, OnMenuZoomIn)
	ON_UPDATE_COMMAND_UI(ID_MENU_ZOOM_IN, OnUpdateMenuZoomIn)
	ON_COMMAND(ID_MENU_ZOOM_OUT, OnMenuZoomOut)
	ON_UPDATE_COMMAND_UI(ID_MENU_ZOOM_OUT, OnUpdateMenuZoomOut)
	ON_COMMAND(ID_MENU_ZOOM_RESTORE, OnMenuZoomRestore)
	ON_UPDATE_COMMAND_UI(ID_MENU_ZOOM_RESTORE, OnUpdateMenuZoomRestore)
	ON_COMMAND(ID_TOOLBAR_RESTORE, OnToolbarRestore)
	ON_UPDATE_COMMAND_UI(ID_TOOLBAR_RESTORE, OnUpdateToolbarRestore)
	ON_COMMAND(ID_TOOLBAR_ZOOM_IN, OnToolbarZoomIn)
	ON_UPDATE_COMMAND_UI(ID_TOOLBAR_ZOOM_IN, OnUpdateToolbarZoomIn)
	ON_COMMAND(ID_TOOLBAR_ZOOM_OUT, OnToolbarZoomOut)
	ON_UPDATE_COMMAND_UI(ID_TOOLBAR_ZOOM_OUT, OnUpdateToolbarZoomOut)
	ON_COMMAND(ID_MENU_FFT_ZOOM_IN, OnMenuFftZoomIn)
	ON_UPDATE_COMMAND_UI(ID_MENU_FFT_ZOOM_IN, OnUpdateMenuFftZoomIn)
	ON_COMMAND(ID_MENU_FFT_ZOOM_OUT, OnMenuFftZoomOut)
	ON_UPDATE_COMMAND_UI(ID_MENU_FFT_ZOOM_OUT, OnUpdateMenuFftZoomOut)
	ON_COMMAND(ID_MENU_FFT_ZOOM_RESTORE, OnMenuFftZoomRestore)
	ON_UPDATE_COMMAND_UI(ID_MENU_FFT_ZOOM_RESTORE, OnUpdateMenuFftZoomRestore)
	ON_UPDATE_COMMAND_UI( ID_INDICATOR_STATE, OnUpdateState )
	ON_COMMAND(ID_TOOLBAR_MULTI_VIEW, OnToolbarMultiView)
	ON_UPDATE_COMMAND_UI(ID_TOOLBAR_MULTI_VIEW, OnUpdateToolbarMultiView)
	ON_WM_TIMER()
	ON_COMMAND(ID_TOOLBAR_START, OnToolbarStart)
	ON_UPDATE_COMMAND_UI(ID_TOOLBAR_START, OnUpdateToolbarStart)
	ON_COMMAND(ID_TOOLBAR_END, OnToolbarEnd)
	ON_UPDATE_COMMAND_UI(ID_TOOLBAR_END, OnUpdateToolbarEnd)
	ON_COMMAND(ID_TOOLBAR_SINGLE_VIEW, OnToolbarSingleView)
	ON_UPDATE_COMMAND_UI(ID_TOOLBAR_SINGLE_VIEW, OnUpdateToolbarSingleView)
	ON_COMMAND(ID_TOOLBAR_MULTI_VIEW_F, OnToolbarMultiViewF)
	ON_UPDATE_COMMAND_UI(ID_TOOLBAR_MULTI_VIEW_F, OnUpdateToolbarMultiViewF)
	ON_COMMAND(ID_TOOLBAR_MULTI_VIEW_S, OnToolbarMultiViewS)
	ON_UPDATE_COMMAND_UI(ID_TOOLBAR_MULTI_VIEW_S, OnUpdateToolbarMultiViewS)
	ON_COMMAND(ID_TOOLBAR_MULTI_VIEW_FS1, OnToolbarMultiViewFs1)
	ON_UPDATE_COMMAND_UI(ID_TOOLBAR_MULTI_VIEW_FS1, OnUpdateToolbarMultiViewFs1)
	ON_COMMAND(ID_TOOLBAR_MULTI_VIEW_FS2, OnToolbarMultiViewFs2)
	ON_UPDATE_COMMAND_UI(ID_TOOLBAR_MULTI_VIEW_FS2, OnUpdateToolbarMultiViewFs2)
	ON_COMMAND(ID_TOOLBAR_POWER, OnToolbarPower)
	ON_UPDATE_COMMAND_UI(ID_TOOLBAR_POWER, OnUpdateToolbarPower)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	m_bTestAlg = TRUE;
	m_bTestADC = FALSE;
	m_bTestADCBatch = FALSE;
	m_bTestDDCBatch = FALSE;
	m_bViewAlg = FALSE;
	m_bViewADC = FALSE;
	m_bViewADCBatch = FALSE;
	m_bViewDDCBatch = FALSE;
	m_dwCurFilePos = 0;
	m_dwFileArraySize = 0;
	m_bZoomH = TRUE;
	m_bZoomV = TRUE;
	m_bZoomOut = FALSE;
	m_bZoomIn = FALSE;
	// Ĭ�϶ϵ�
	m_bPower = FALSE;
	m_strState = "����ͨ������";
	m_byMultiView = 0;
	m_bRunning = FALSE;
	m_hCursorOut = AfxGetApp()->LoadCursor( IDC_CURSOR_OUT );
	m_hCursorIn = AfxGetApp()->LoadCursor( IDC_CURSOR_IN );
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	// �õ�״̬�����ж��ٸ�����
	int nOrigSize = sizeof( indicators ) / sizeof( UINT );
	// ����
	UINT* pIndicators = new UINT[nOrigSize+1];
	memcpy( pIndicators, indicators, sizeof(indicators) );
	m_nIndexOfState = nOrigSize++;
	pIndicators[m_nIndexOfState] = ID_INDICATOR_STATE;
	m_wndStatusBar.SetIndicators( pIndicators, nOrigSize );
	delete [] pIndicators;
	
	// ��Ӷ�ʱ�������Բ�ѯ����״̬(1s)
	SetTimer( 0, 1000, NULL );

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	
	//cs.style &= ~WS_MAXIMIZEBOX;
	
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	if ( !m_wndSplitter.CreateStatic( this, 1, 2 ) )
	{
		TRACE0("Failed to CreateStaticSplitter\n");
		return FALSE;
	}

	// add the first splitter pane - which is a nested splitter with 2 rows
	if ( !m_wndSplitter2.CreateStatic(
		 &m_wndSplitter,     // our parent window is the first splitter
		 2, 1,               // the new splitter is 2 rows, 1 column
		 WS_CHILD | WS_VISIBLE | WS_BORDER,  // style, WS_BORDER is needed
		 m_wndSplitter.IdFromRowCol(0, 0)
			// new splitter is in the first row, 2nd column of first splitter
	   ))
	{
		TRACE0("Failed to create nested splitter\n");
		return FALSE;
	}

	// add the second splitter pane - the default view in column 1	
	if ( !m_wndSplitter.CreateView( 0, 1,
		RUNTIME_CLASS(CAdcTestPlatView), CSize(0, 0), pContext ) )// pContext->m_pNewViewClass
	{
		TRACE0("Failed to create second pane\n");
		return FALSE;
	}	

	// now create the two views inside the nested splitter
	if ( !m_wndSplitter2.CreateView(0, 0,
		RUNTIME_CLASS(CTestAlgView), CSize(0, 0 ), pContext) ) // CSize(0, cyText)
	{
		TRACE0("Failed to create second pane\n");
		return FALSE;
	}
	if ( !m_wndSplitter2.CreateView(1, 0,
		RUNTIME_CLASS(CTestResultView), CSize(0, 0), pContext) )
	{
		TRACE0("Failed to create third pane\n");
		return FALSE;
	}
	// ��ȡ�ͻ�����С
	CRect rc;
	GetClientRect( &rc );
	m_nWidth = rc.right - rc.left;
	m_nHeight = rc.bottom - rc.top;
	// ��ȡ���ô��ڵĴ�С
	int nMapMode;
	CSize sizeTotalView, sizePage, sizeLine;	
	((CFormView*)m_wndSplitter2.GetPane(0, 0))->GetDeviceScrollSizes(
		nMapMode, sizeTotalView, sizePage, sizeLine);
	// �������еĴ�С
	m_wndSplitter.SetColumnInfo( 0, sizeTotalView.cx, 1 );
	m_wndSplitter.SetColumnInfo( 1, 100, 1 );
	// ���������ͼ���д�С
	m_wndSplitter2.SetRowInfo( 0, sizeTotalView.cy, 1 );
	m_wndSplitter2.SetRowInfo( 1, 10, 1 );
	/*
	// �����ұ�ͼ����ʾ������ͼ�Ĵ�С
	CRect rcPic;
	rcPic.left = sizeTotalView.cx;
	rcPic.right = rc.right;
	rcPic.top = rc.top;
	rcPic.bottom = rc.bottom;
	m_wndSplitter.GetPane( 0, 1 )->MoveWindow( &rcPic );
	*/
	//return CFrameWnd::OnCreateClient(lpcs, pContext);
	return TRUE;
}

void CMainFrame::OnTestAdcBatch() 
{
	m_bTestADCBatch = TRUE;
	m_bTestAlg = FALSE;
	m_bTestADC = FALSE;	
	m_bTestDDCBatch = FALSE;
	m_bViewADCBatch = FALSE;
	m_bViewAlg = FALSE;
	m_bViewADC = FALSE;	
	m_bViewDDCBatch = FALSE;
/*
	if ( m_bTestADCBatch )
	{
		// ����ɾ���������ô��ڵ���ͼ
		m_wndSplitter2.DeleteView( 0, 0 );
		// Ȼ���½���Ҫ����ͼ
		CCreateContext context;	
		context.m_pNewViewClass = RUNTIME_CLASS(CTestSetBatchView);
		CDocument* pDoc = GetActiveDocument();
		context.m_pCurrentDoc = pDoc;
		if ( !m_wndSplitter2.CreateView( 0, 0,
			RUNTIME_CLASS(CTestSetBatchView), CSize(0, 0 ), &context) ) 
		{
			TRACE0("Failed to create second pane\n");
			return;
		}
		
		// ��ȡ���ô��ڵĴ�С
		int nMapMode;
		CSize sizeTotalView, sizePage, sizeLine;	
		((CFormView*)m_wndSplitter2.GetPane(0, 0))->GetDeviceScrollSizes(
			nMapMode, sizeTotalView, sizePage, sizeLine);
		// �������еĴ�С
		m_wndSplitter.SetColumnInfo( 0, sizeTotalView.cx, 1 );
		m_wndSplitter.SetColumnInfo( 1, 100, 1 );
		// ���������ͼ���д�С
		m_wndSplitter2.SetRowInfo( 0, sizeTotalView.cy, 1 );
		m_wndSplitter2.SetRowInfo( 1, 10, 1 );
		
		// ��ִ��ڷ����仯����������ĺ�������
		m_wndSplitter2.RecalcLayout();
		m_wndSplitter.RecalcLayout();

		SetWindowText( "ADC�������" );
		// ����������ͼ
		pDoc->UpdateAllViews( NULL );		
	}
*/
	SwitchView();

}

void CMainFrame::OnUpdateTestAdcBatch(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck( m_bTestADCBatch );
}

void CMainFrame::OnTestAdc() 
{
	m_bTestADC = TRUE;
	m_bTestAlg = FALSE;	
	m_bTestADCBatch = FALSE;
	m_bTestDDCBatch = FALSE;	
	m_bViewAlg = FALSE;
	m_bViewADC = FALSE;	
	m_bViewADCBatch = FALSE;
	m_bViewDDCBatch = FALSE;

	SwitchView();

	// �����л���adc����
	CAdcTestPlatDoc* pDoc = (CAdcTestPlatDoc*)GetActiveDocument();
	if ( pDoc != NULL )
	{
		pDoc->m_nTestModeSel = 1;
		// �л���adc��fft��ͼ�Ĳ���Ƶ�ʻָ�Ϊ80M
		// ������ʾ��ͼ
		CAdcTestPlatView* pTestPlatView = NULL;
		POSITION pos = pDoc->GetFirstViewPosition();
		while ( pos != NULL )
		{
			CView* pView = pDoc->GetNextView( pos );			
			if ( pView->IsKindOf(RUNTIME_CLASS(CAdcTestPlatView)) )
			{
				pTestPlatView = (CAdcTestPlatView*)pView;
				break;
			}
		}
		// �ҵ��ˣ��޸ĳ�ʼ����Ƶ��
		if ( pTestPlatView != NULL )
		{
			pTestPlatView->m_FFTDisp[0].m_dOrgSampFreq = 80.0;
			pTestPlatView->m_FFTDisp[1].m_dOrgSampFreq = 80.0;
			pTestPlatView->m_FFTDisp[2].m_dOrgSampFreq = 80.0;
			pTestPlatView->m_FFTDisp[3].m_dOrgSampFreq = 80.0;
			pTestPlatView->m_FFTDisp[4].m_dOrgSampFreq = 80.0;
			// ��ͼ�ָ�
			pTestPlatView->m_FFTDisp[0].ZoomRestore();
			pTestPlatView->m_FFTDisp[1].ZoomRestore();
			pTestPlatView->m_FFTDisp[2].ZoomRestore();
			pTestPlatView->m_FFTDisp[3].ZoomRestore();
			pTestPlatView->m_FFTDisp[4].ZoomRestore();
		}
	}
}

void CMainFrame::OnUpdateTestAdc(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck( ( m_bTestADC && (!m_bTestADCBatch) ) );
}

void CMainFrame::OnTestAlg() 
{
	// TODO: Add your command handler code here
	m_bTestADC = FALSE;
	m_bTestAlg = TRUE;	
	m_bTestADCBatch = FALSE;
	m_bTestDDCBatch = FALSE;
	m_bViewAlg = FALSE;
	m_bViewADC = FALSE;	
	m_bViewADCBatch = FALSE;
	m_bViewDDCBatch = FALSE;
	// �л���ͼ
	SwitchView();
/*
	// �����л����㷨����
	CAdcTestPlatDoc* pDoc = (CAdcTestPlatDoc*)GetActiveDocument();
	if ( pDoc != NULL )
	{
		CView* pView = NULL;
		CAdcTestPlatView* pDispView = NULL;
		POSITION pos = pDoc->GetFirstViewPosition();
		while ( pos != NULL )
		{
			CView* pView = pDoc->GetNextView( pos );				
			if ( pView->IsKindOf(RUNTIME_CLASS(CAdcTestPlatView)) )
			{				
				pDispView = (CAdcTestPlatView*)pView;
				break;
			}
		}
		if ( pDispView != NULL )
		{
			pDispView->AlgTestSet();
		}
	}
*/
	// �����л����㷨����
	CAdcTestPlatDoc* pDoc = (CAdcTestPlatDoc*)GetActiveDocument();
	if ( pDoc != NULL )
	{
		pDoc->m_nTestModeSel = 6;
		// �л���alg��fft��ͼ�����ûָ�
		// ������ʾ��ͼ
		CAdcTestPlatView* pTestPlatView = NULL;
		POSITION pos = pDoc->GetFirstViewPosition();
		while ( pos != NULL )
		{
			CView* pView = pDoc->GetNextView( pos );			
			if ( pView->IsKindOf(RUNTIME_CLASS(CAdcTestPlatView)) )
			{
				pTestPlatView = (CAdcTestPlatView*)pView;
				break;
			}
		}
		// �ҵ���
		if ( pTestPlatView != NULL )
		{

			pTestPlatView->m_FFTDisp[0].m_dOrgSampFreq = 80.0 / 20;
			pTestPlatView->m_FFTDisp[1].m_dOrgSampFreq = 80.0 / 20;
			pTestPlatView->m_FFTDisp[2].m_dOrgSampFreq = 80.0 / 20;
			pTestPlatView->m_FFTDisp[3].m_dOrgSampFreq = 80.0 / 20;
			pTestPlatView->m_FFTDisp[4].m_dOrgSampFreq = 80.0 / 20;
			// ��ͼ�ָ�
			pTestPlatView->m_FFTDisp[0].ZoomRestore();
			pTestPlatView->m_FFTDisp[1].ZoomRestore();
			pTestPlatView->m_FFTDisp[2].ZoomRestore();
			pTestPlatView->m_FFTDisp[3].ZoomRestore();
			pTestPlatView->m_FFTDisp[4].ZoomRestore();
		}
	}
}

void CMainFrame::OnUpdateTestAlg(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck( m_bTestAlg && (!m_bTestADCBatch) );
}

void CMainFrame::OnViewAlgRecord() 
{
	// TODO: Add your command handler code here
	m_bTestADC = FALSE;
	m_bTestAlg = FALSE;	
	m_bTestADCBatch = FALSE;
	m_bTestDDCBatch = FALSE;
	m_bViewAlg = TRUE;
	m_bViewADC = FALSE;	
	m_bViewADCBatch = FALSE;
	m_bViewDDCBatch = FALSE;
	
	SwitchView();
}

void CMainFrame::OnUpdateViewAlgRecord(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck( m_bViewAlg );
}

void CMainFrame::OnViewAdcRecord() 
{
	// TODO: Add your command handler code here
	m_bTestADC = FALSE;
	m_bTestAlg = FALSE;	
	m_bTestADCBatch = FALSE;
	m_bTestDDCBatch = FALSE;
	m_bViewAlg = FALSE;
	m_bViewADC = TRUE;	
	m_bViewADCBatch = FALSE;
	m_bViewDDCBatch = FALSE;
	
	SwitchView();	
}

void CMainFrame::OnUpdateViewAdcRecord(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck( m_bViewADC );
}

void CMainFrame::OnViewAdcBatchRecord() 
{
	
//	m_bTestADC = FALSE;
//	m_bTestAlg = FALSE;	
//	m_bTestADCBatch = FALSE;
//	m_bTestDDCBatch = FALSE;
//	m_bViewAlg = FALSE;
//	m_bViewADC = FALSE;	
//	m_bViewADCBatch = TRUE;
//	m_bViewDDCBatch = FALSE;	
//	SwitchView();

	// ����ADC���������ļ�
	if ( !SearchAdcBatchFile() )
	{
		AfxMessageBox( "δ�ҵ����������ļ�!" );
	}
	else
	{
		// �ҵ��ĵ�һ�����������ļ������·ID�ı�����ʾ
		CDocument* pDoc = GetActiveDocument();
		POSITION pos = pDoc->GetFirstViewPosition();
		while ( pos != NULL )
		{
			CView* pView = pDoc->GetNextView( pos );
			// �ҵ�ͼ����ʾ��ͼ
			if ( pView->IsKindOf(RUNTIME_CLASS(CAdcTestPlatView)) )
			{
				((CAdcTestPlatView*)pView)->m_strID = m_strFileArray[m_dwCurFilePos].Left(8);
				((CAdcTestPlatView*)pView)->UpdateData( FALSE );
				break;
			}
		}
		// ͬʱ�򿪸��ļ�����ʾ������/�����/ͼ��������
		FileOpen( m_strFileArray[m_dwCurFilePos] );			
	}	
}

void CMainFrame::OnUpdateViewAdcBatchRecord(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck( m_bViewADCBatch );
}

void CMainFrame::OnMyFileSave() 
{
	CString strDefExt;
	CString strDefFileName;
	CString strFilter;		
	char szCurDir[100];

	::GetCurrentDirectory( 100, szCurDir );
	// û������?
	::SetCurrentDirectory( szCurDir );

	strDefExt = ".atp";
	strDefFileName = szCurDir;
	strDefFileName += "\\*.atp";
	// �ļ����Ͳ��ܼ�����
	strFilter = "ADC test platform file (*.atp)|*.atp|all files (*.*)|*.*||";

	// �ļ�����Ի���
	CFileDialog fileDlg( FALSE, strDefExt, strDefFileName, 
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		strFilter, this );
	
	// �޸��ļ��Ի���ı���
	fileDlg.m_ofn.lpstrTitle = "���浱ǰ��������";

	if ( fileDlg.DoModal() == IDOK )
	{
		CString strDestFileName = fileDlg.GetPathName();
		FileSave( strDestFileName );
	}
	
}

void CMainFrame::OnUpdateMyFileSave(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CMainFrame::OnMyFileOpen() 
{
	CString strDefExt;
	CString strDefFileName;
	CString strFilter;	
	char szCurDir[100];
	CString strSrcFileName;	

	::GetCurrentDirectory( 100, szCurDir );
	// 
	m_strCurDir.Format( "%s", szCurDir );

	strDefExt = ".atp";
	strDefFileName = szCurDir;
	strDefFileName += "\\*.atp";	
	strFilter = "ADC test platform file (*.atp)|*.atp|all files (*.*)|*.*||";	

	// �ļ��򿪶Ի���
	CFileDialog fileDlg( TRUE, strDefExt, strDefFileName, 
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		strFilter, this );
	
	if ( fileDlg.DoModal() == IDOK )
	{
		strSrcFileName = fileDlg.GetPathName();
		FileOpen( strSrcFileName );
	}
	
}

void CMainFrame::OnUpdateMyFileOpen(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CMainFrame::FileSave(CString strFileName)
{
	int i;
	CFile fileSave;

	if ( !fileSave.Open(strFileName, 
		CFile::modeCreate | CFile::modeWrite | CFile::typeBinary) )
	{
		return;
	}

	DWORD dwPos = 0;
	DWORD dwSize = 0;
	// ��ʼ���ļ����ݻ�����, �ļ�ͷ��ʶ
	for ( i = 0; i < 16; i++ )
	{
		m_byaFileBuf[i] = 0x5A;
	}
	dwPos += 16;
	// ���ݲ�ͬ�������ͷ��ദ��
	CDocument* pDoc = GetActiveDocument();
	if ( pDoc == NULL )
	{
		return;
	}
	if ( m_bTestAlg && (!m_bTestADCBatch) )
	{
		*(DWORD*)&m_byaFileBuf[dwPos] = ALG_ID;
		dwPos += 4;			
		POSITION pos = pDoc->GetFirstViewPosition();
		while ( pos != NULL )
		{
			CView* pView = pDoc->GetNextView( pos );				
			if ( pView->IsKindOf(RUNTIME_CLASS(CTestAlgView)) )
			{
				((CTestAlgView*)pView)->FileSave( m_byaFileBuf+dwPos, &dwSize );
				dwPos += dwSize;
				break;
			}
		}
	}
	else if ( m_bTestADC && (!m_bTestADCBatch) )
	{
		*(DWORD*)&m_byaFileBuf[dwPos] = ADC_ID;
		dwPos += 4;			
	}
	else if ( m_bTestADCBatch )
	{
		*(DWORD*)&m_byaFileBuf[dwPos] = ADC_BATCH_ID;
		dwPos += 4;			
		POSITION pos = pDoc->GetFirstViewPosition();
		while ( pos != NULL )
		{
			CView* pView = pDoc->GetNextView( pos );				
			if ( pView->IsKindOf(RUNTIME_CLASS(CTestSetBatchView)) )
			{
				((CTestSetBatchView*)pView)->FileSave( m_byaFileBuf+dwPos, &dwSize );
				dwPos += dwSize;
				break;
			}
		}
		// �������Եı��棬���浱ʱ�Ĳ������ݣ�ֻ������Խ��
		// д���ļ�
		fileSave.Write( m_byaFileBuf, dwPos );
		fileSave.Close();
		return;
	}
	// ADC+DDC����
	
	// doc����������ص�״̬�������ڴ˴洢
	((CAdcTestPlatDoc*)pDoc)->FileSave( m_byaFileBuf+dwPos, &dwSize );
	dwPos += dwSize;
/*
	// ���Խ�����ڵ�����		
	memcpy( m_byaFileBuf+dwPos, ((CAdcTestPlatDoc*)pDoc)->m_daResultBackNoise, CHANNEL_NUM*sizeof(double) );
	dwPos += CHANNEL_NUM*sizeof(double);
	memcpy( m_byaFileBuf+dwPos, ((CAdcTestPlatDoc*)pDoc)->m_daResultSNR, CHANNEL_NUM*sizeof(double) );
	dwPos += CHANNEL_NUM*sizeof(double);
	memcpy( m_byaFileBuf+dwPos, ((CAdcTestPlatDoc*)pDoc)->m_daResultSFDR, CHANNEL_NUM*sizeof(double) );
	dwPos += CHANNEL_NUM*sizeof(double);
	memcpy( m_byaFileBuf+dwPos, ((CAdcTestPlatDoc*)pDoc)->m_daResultChanDisturb, CHANNEL_NUM*sizeof(double) );
	dwPos += CHANNEL_NUM*sizeof(double);
	memcpy( m_byaFileBuf+dwPos, ((CAdcTestPlatDoc*)pDoc)->m_daResultSINAD, CHANNEL_NUM*sizeof(double) );
	dwPos += CHANNEL_NUM*sizeof(double);
	// 4��ͨ���ĵ�������������
	memcpy( m_byaFileBuf+dwPos, (BYTE*)((CAdcTestPlatDoc*)pDoc)->m_waCh1SignalNoise, MAX_DEPTH*2 );
	dwPos += MAX_DEPTH*2;
	memcpy( m_byaFileBuf+dwPos, (BYTE*)((CAdcTestPlatDoc*)pDoc)->m_waCh2SignalNoise, MAX_DEPTH*2 );
	dwPos += MAX_DEPTH*2;
	memcpy( m_byaFileBuf+dwPos, (BYTE*)((CAdcTestPlatDoc*)pDoc)->m_waCh3SignalNoise, MAX_DEPTH*2 );
	dwPos += MAX_DEPTH*2;
	memcpy( m_byaFileBuf+dwPos, (BYTE*)((CAdcTestPlatDoc*)pDoc)->m_waCh4SignalNoise, MAX_DEPTH*2 );
	dwPos += MAX_DEPTH*2;
	// 4��ͨ�������ܲ�������
	memcpy( m_byaFileBuf+dwPos, (BYTE*)((CAdcTestPlatDoc*)pDoc)->m_waCh1SignalPerf, MAX_DEPTH*2 );
	dwPos += MAX_DEPTH*2;
	memcpy( m_byaFileBuf+dwPos, (BYTE*)((CAdcTestPlatDoc*)pDoc)->m_waCh2SignalPerf, MAX_DEPTH*2 );
	dwPos += MAX_DEPTH*2;
	memcpy( m_byaFileBuf+dwPos, (BYTE*)((CAdcTestPlatDoc*)pDoc)->m_waCh3SignalPerf, MAX_DEPTH*2 );
	dwPos += MAX_DEPTH*2;
	memcpy( m_byaFileBuf+dwPos, (BYTE*)((CAdcTestPlatDoc*)pDoc)->m_waCh4SignalPerf, MAX_DEPTH*2 );
	dwPos += MAX_DEPTH*2;
	// 4��ͨ����ͨ��������������
	memcpy( m_byaFileBuf+dwPos, (BYTE*)((CAdcTestPlatDoc*)pDoc)->m_waCh1SignalDisturb, MAX_DEPTH*2 );
	dwPos += MAX_DEPTH*2;
	memcpy( m_byaFileBuf+dwPos, (BYTE*)((CAdcTestPlatDoc*)pDoc)->m_waCh2SignalDisturb, MAX_DEPTH*2 );
	dwPos += MAX_DEPTH*2;
	memcpy( m_byaFileBuf+dwPos, (BYTE*)((CAdcTestPlatDoc*)pDoc)->m_waCh3SignalDisturb, MAX_DEPTH*2 );
	dwPos += MAX_DEPTH*2;
	memcpy( m_byaFileBuf+dwPos, (BYTE*)((CAdcTestPlatDoc*)pDoc)->m_waCh4SignalDisturb, MAX_DEPTH*2 );
	dwPos += MAX_DEPTH*2;
*/
	// д���ļ�
	fileSave.Write( m_byaFileBuf, dwPos );
	fileSave.Close();
}

BOOL CMainFrame::SearchAdcBatchFile()
{
	int i;
	CFileFind finder;
	CString strTempFileName;
	CFile fileOpen;
	BYTE DataBuf[100];
	BOOL bRet = FALSE;

	//
	//::SetCurrentDirectory( m_strCurDir );

	BOOL bWorking = finder.FindFile("*.atp");	
	while ( bWorking )
	{
		bWorking = finder.FindNextFile();
		strTempFileName = finder.GetFileName();
		// ����Ƿ�ADC���������ļ�
		if ( fileOpen.Open(strTempFileName , CFile::modeRead | CFile::typeBinary ) )
		{
			// ���������ļ����ļ�������Ϊ8λ����
			//if ( fileOpen.GetLength() > 4*MAX_DEPTH 
			//	&& strTempFileName.GetLength() == 12)
			if ( strTempFileName.GetLength() == 12 )
			{
				// ����ļ�ͷ��ʶ
				fileOpen.Read( DataBuf, 16 );
				for ( i = 0; i < 16; i++ )
				{
					if ( DataBuf[i] != 0x5A )
					{
						break;
					}
				}
				if ( i == 16 )
				{
					fileOpen.Read( DataBuf, 4 );
					if ( *(DWORD*)DataBuf == ADC_BATCH_ID )
					{
						// ����ADC�������Ե��ļ���
						m_strFileArray[m_dwFileArraySize++] = strTempFileName;						
						bRet = TRUE;
					}
				}
			}
		}
		fileOpen.Close();
	}
	// ������·ID΢����ť�ķ�Χ
	CDocument* pDoc = GetActiveDocument();
	POSITION pos = pDoc->GetFirstViewPosition();
	while ( pos != NULL )
	{
		CView* pView = pDoc->GetNextView( pos );				
		if ( pView->IsKindOf(RUNTIME_CLASS(CAdcTestPlatView)) )
		{
			(((CAdcTestPlatView*)pView)->m_spinID).SetRange( 0, m_dwFileArraySize-1 );						
			break;
		}
	}
	return bRet;
}

void CMainFrame::FileOpen(CString strFileName)
{
	int i;
	CFile fileOpen;			
	CString strMessage;		
	//DWORD dwFileSize;

	if ( !fileOpen.Open(strFileName , CFile::modeRead | CFile::typeBinary ) )
	{						
		strMessage.Format( "���ļ� %s ʧ��!", strFileName );
		AfxMessageBox( strMessage );
		return;
	}
	/*
	// ��ȡ�ļ���С
	dwFileSize = fileOpen.GetLength();		
	if ( dwFileSize < 4*MAX_DEPTH )
	{
		AfxMessageBox( "�ļ����Ȳ�����Ҫ��!" );
		return;
	}
	*/
	// ����ļ�ͷ��ʶ
	fileOpen.Read( m_byaFileBuf, 16 );
	for ( i = 0; i < 16; i++ )
	{
		if ( m_byaFileBuf[i] != 0x5A )
		{
			AfxMessageBox( "�ļ���ʽ������Ҫ��!" );
			fileOpen.Close();
			return;
		}
	}		
	// �����ļ����ʹ򿪲�ͬ��ͼ
	fileOpen.Read( m_byaFileBuf, 4 );
	CDocument* pDoc = GetActiveDocument();
	if ( pDoc == NULL )
	{
		return;
	}
	switch ( *(DWORD*)m_byaFileBuf )
	{
		case ALG_ID:
		{
			// ����
			break;
		}
		case ADC_ID:
		{
			// ��ʾADC�鿴ģʽ
			OnViewAdcRecord();			
			break;
		}
		case ADC_BATCH_ID:
		{
			// �л���ADC�����鿴ģʽ
			m_bTestADC = FALSE;
			m_bTestAlg = FALSE;	
			m_bTestADCBatch = FALSE;
			m_bTestDDCBatch = FALSE;
			m_bViewAlg = FALSE;
			m_bViewADC = FALSE;	
			m_bViewADCBatch = TRUE;
			m_bViewDDCBatch = FALSE;			
			SwitchView();
			// ��ȡ6B�Ĳ���ֵ
			fileOpen.Read( m_byaFileBuf, TEST_ITEM );
			POSITION pos = pDoc->GetFirstViewPosition();
			while ( pos != NULL )
			{
				CView* pView = pDoc->GetNextView( pos );				
				if ( pView->IsKindOf(RUNTIME_CLASS(CTestSetBatchView)) )
				{
					// �ļ���
					((CTestSetBatchView*)pView)->m_strID = (strFileName.Right(12)).Left(8);
					((CTestSetBatchView*)pView)->FileOpen( m_byaFileBuf );						
					break;
				}
			}
			// ��������û�б����������ֱ�ӷ���
			// ˢ��������ͼ
			((CAdcTestPlatDoc*)pDoc)->UpdateAllViews( NULL );
			return;
			break;
		}
		case DDC_BATCH_ID:
		{
			// ����
			break;
		}
		default:
			break;
	}

	// ��ȡʣ�����ݣ���doc�������ܼ�4B+288B+256KB
	fileOpen.Read( m_byaFileBuf, 4+288+256*1024 );			
	((CAdcTestPlatDoc*)pDoc)->FileOpen( m_byaFileBuf );
	// ˢ��������ͼ
	((CAdcTestPlatDoc*)pDoc)->UpdateAllViews( NULL );
}

// �л����Ϸ�����ͼ
void CMainFrame::SwitchView()
{
	CRuntimeClass* pViewClass;
	if ( m_bViewAlg || m_bTestAlg )
	{
		pViewClass = RUNTIME_CLASS(CTestAlgView);
	}
	else if ( m_bViewADC || m_bTestADC )
	{
		pViewClass = RUNTIME_CLASS(CTestSetView);
	}
	else if ( m_bViewADCBatch || m_bTestADCBatch )
	{
		pViewClass = RUNTIME_CLASS(CTestSetBatchView);
	}
	// ADC+DDC����

	// ����ɾ�����ϴ��ڵ���ͼ
	m_wndSplitter2.DeleteView( 0, 0 );
	// Ȼ���½���Ҫ����ͼ
	CCreateContext context;	
	context.m_pNewViewClass = pViewClass;
	CDocument* pDoc = GetActiveDocument();
	context.m_pCurrentDoc = pDoc;
	if ( !m_wndSplitter2.CreateView( 0, 0,
		pViewClass, CSize(0, 0 ), &context) ) 
	{
		TRACE0("Failed to create second pane\n");
		return;
	}	
	
	// ��ȡ���ô��ڵĴ�С
	int nMapMode;
	CSize sizeTotalView, sizePage, sizeLine;	
	((CFormView*)m_wndSplitter2.GetPane(0, 0))->GetDeviceScrollSizes(
		nMapMode, sizeTotalView, sizePage, sizeLine);
	// �������еĴ�С
	m_wndSplitter.SetColumnInfo( 0, sizeTotalView.cx, 1 );
	m_wndSplitter.SetColumnInfo( 1, 100, 1 );
	// ���������ͼ���д�С
	m_wndSplitter2.SetRowInfo( 0, sizeTotalView.cy, 1 );
	m_wndSplitter2.SetRowInfo( 1, 10, 1 );
	
	// ��ִ��ڷ����仯����������ĺ�������
	m_wndSplitter2.RecalcLayout();
	m_wndSplitter.RecalcLayout();

	SetWindowText( "SIP����ϵͳver2.0" );// ADC�������
	// ����������ͼ
	pDoc->UpdateAllViews( NULL );
	// 
	CView* pView = GetActiveView();	
	if ( pView->IsKindOf(RUNTIME_CLASS(CTestResultView)) )
	{
		((CEdit*)((CTestResultView*)pView)->GetDlgItem( IDC_EDIT_TEST_RESULT ))
			->SetSel( -1, 0, TRUE );
	}
}

void CMainFrame::OnFftSave() 
{
/*
	CString strDefExt;
	CString strDefFileName;
	CString strFilter;		
	char szCurDir[100];

	::GetCurrentDirectory( 100, szCurDir );
	// û������?
	::SetCurrentDirectory( szCurDir );

	strDefExt = ".bmp";
	strDefFileName = szCurDir;
	strDefFileName += "\\*.bmp";
	// �ļ����Ͳ��ܼ�����
	strFilter = "fft bmp file (*.bmp)|*.bmp||";

	// �ļ�����Ի���
	CFileDialog fileDlg( FALSE, strDefExt, strDefFileName, 
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		strFilter, this );
	
	// �޸��ļ��Ի���ı���
	fileDlg.m_ofn.lpstrTitle = "����Ƶ�ײ���";

	if ( fileDlg.DoModal() == IDOK )
	{
		CString strDestFileName = fileDlg.GetPathName();		
		CRect rect;
		LPTSTR lpFileName;
		GetWindowRect(&rect);
		rect.CopyRect( &m_rcFFT );
		HBITMAP hMap =  CopyScreenToBitmap(rect); 
		lpFileName = strDestFileName.GetBuffer(1000);
		SaveBitmapToFile(hMap,lpFileName); 
	}
*/
	CAdcTestPlatView* pTestPlatView;
	pTestPlatView = NULL;
	CString strFileName;
	CString strDataFileName;
	CString strFftFileName;
	CAdcTestPlatDoc* pDoc = (CAdcTestPlatDoc*)GetActiveDocument();
	if ( pDoc != NULL )
	{				
		POSITION pos = pDoc->GetFirstViewPosition();
		while ( pos != NULL )
		{
			CView* pView = pDoc->GetNextView( pos );			
			// ��ʾ��ͼ
			if ( pView->IsKindOf(RUNTIME_CLASS(CAdcTestPlatView)) )
			{			
				pTestPlatView = (CAdcTestPlatView*)pView;
				break;
			}
		}
	}
	// ͨ����ʾ��ͼ��ȡ�ļ���
	if ( pTestPlatView != NULL )
	{
		strFileName = pTestPlatView->DataSave();
		strDataFileName = strFileName + ".txt";
		strFftFileName = strFileName + ".bmp";
		CRect rect;
		LPTSTR lpFileName;
		CString strMsg;
		GetWindowRect(&rect);
		rect.CopyRect( &m_rcFFT );
		HBITMAP hMap =  CopyScreenToBitmap(rect); 
		lpFileName = strFftFileName.GetBuffer(1000);
		SaveBitmapToFile(hMap,lpFileName);
		strMsg.Format( "�ļ�%s��%s����ɹ�", strFftFileName, strDataFileName );
		AfxMessageBox( strMsg );
	}
}

HBITMAP CMainFrame::CopyScreenToBitmap(LPRECT lpRect) //lpRect ����ѡ������
{
 HDC hScrDC, hMemDC;      
 // ��Ļ���ڴ��豸������
 HBITMAP hBitmap,hOldBitmap;   
 // λͼ���
 int       nX, nY, nX2, nY2;      
 // ѡ����������
 int       nWidth, nHeight;      
 // λͼ��Ⱥ͸߶�
 int       xScrn, yScrn;         
 // ��Ļ�ֱ���
 // ȷ��ѡ������Ϊ�վ���
 if (IsRectEmpty(lpRect))
  return NULL;
 //Ϊ��Ļ�����豸������
 hScrDC = CreateDC("DISPLAY", NULL, NULL, NULL);
 //Ϊ��Ļ�豸�����������ݵ��ڴ��豸������
 hMemDC = CreateCompatibleDC(hScrDC);
 // ���ѡ����������
 nX = lpRect->left;
 nY = lpRect->top;
 nX2 = lpRect->right;
 nY2 = lpRect->bottom;
 // �����Ļ�ֱ���
 xScrn = GetDeviceCaps(hScrDC, HORZRES);
 yScrn = GetDeviceCaps(hScrDC, VERTRES);
 //ȷ��ѡ�������ǿɼ���
 if (nX < 0)
  nX = 0;
 if (nY < 0)
  nY = 0;
 if (nX2 > xScrn)
  nX2 = xScrn;
 if (nY2 > yScrn)
  nY2 = yScrn;
 nWidth = nX2 - nX;
 nHeight = nY2 - nY;
 // ����һ������Ļ�豸��������ݵ�λͼ
 hBitmap=CreateCompatibleBitmap(hScrDC,nWidth,nHeight);
 // ����λͼѡ���ڴ��豸��������
 hOldBitmap=(HBITMAP)SelectObject(hMemDC,hBitmap);
 // ����Ļ�豸�����������ڴ��豸��������
 BitBlt(hMemDC,0,0, nWidth,nHeight,hScrDC, nX, nY, SRCCOPY);
 //�õ���Ļλͼ�ľ��
 hBitmap=(HBITMAP)SelectObject(hMemDC,hOldBitmap);
 //��� 
 DeleteDC(hScrDC);
 DeleteDC(hMemDC);
 // ����λͼ���
 return hBitmap;
}

int CMainFrame::SaveBitmapToFile(HBITMAP hBitmap, LPSTR lpFileName) //hBitmap Ϊ�ղŵ���Ļλͼ���
{      //lpFileName Ϊλͼ�ļ���
 HDC     hDC;         
    //�豸������
 int     iBits;      
 //��ǰ��ʾ�ֱ�����ÿ��������ռ�ֽ���
 WORD    wBitCount;   
    //λͼ��ÿ��������ռ�ֽ���
 //�����ɫ���С�� λͼ�������ֽڴ�С ��  λͼ�ļ���С �� д���ļ��ֽ���
 DWORD           dwPaletteSize=0,dwBmBitsSize,dwDIBSize, dwWritten;
 BITMAP          Bitmap;        
 //λͼ���Խṹ
 BITMAPFILEHEADER   bmfHdr;        
 //λͼ�ļ�ͷ�ṹ
 BITMAPINFOHEADER   bi;            
 //λͼ��Ϣͷ�ṹ 
 LPBITMAPINFOHEADER lpbi;          
 //ָ��λͼ��Ϣͷ�ṹ
    HANDLE          fh, hDib, hPal;
 HPALETTE     hOldPal=NULL;
 //�����ļ��������ڴ�������ɫ����
 
 //����λͼ�ļ�ÿ��������ռ�ֽ���
 hDC = CreateDC("DISPLAY",NULL,NULL,NULL);
 iBits = GetDeviceCaps(hDC, BITSPIXEL) * 
  GetDeviceCaps(hDC, PLANES);
 DeleteDC(hDC);
 if (iBits <= 1)
  wBitCount = 1;
 else if (iBits <= 4)
  wBitCount = 4;
 else if (iBits <= 8)
  wBitCount = 8;
 else if (iBits <= 24)
  wBitCount = 24;
else
  wBitCount = 32;
 //�����ɫ���С
 if (wBitCount <= 8)
  dwPaletteSize=(1<<wBitCount)*sizeof(RGBQUAD);
 
 //����λͼ��Ϣͷ�ṹ
 GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&Bitmap);
 bi.biSize            = sizeof(BITMAPINFOHEADER);
 bi.biWidth           = Bitmap.bmWidth;
 bi.biHeight          = Bitmap.bmHeight;
 bi.biPlanes          = 1;
 bi.biBitCount         = wBitCount;
 bi.biCompression      = BI_RGB;
 bi.biSizeImage        = 0;
 bi.biXPelsPerMeter     = 0;
 bi.biYPelsPerMeter     = 0;
 bi.biClrUsed         = 0;
 bi.biClrImportant      = 0;
 
 dwBmBitsSize = ((Bitmap.bmWidth*wBitCount+31)/32)*4*Bitmap.bmHeight;
 //Ϊλͼ���ݷ����ڴ�

/*xxxxxxxx����λͼ��С�ֽ�һ��(����һ����������)xxxxxxxxxxxxxxxxxxxx 
//ÿ��ɨ������ռ���ֽ���Ӧ��Ϊ4���������������㷨Ϊ:
 int biWidth = (Bitmap.bmWidth*wBitCount) / 32;
 if((Bitmap.bmWidth*wBitCount) % 32)
  biWidth++; //�����������ļ�1
 biWidth *= 4;//���������õ���Ϊÿ��ɨ���е��ֽ�����
 dwBmBitsSize = biWidth * Bitmap.bmHeight;//�õ���С
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx*/


 hDib  = GlobalAlloc(GHND,dwBmBitsSize+dwPaletteSize+sizeof(BITMAPINFOHEADER));
 lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);
 *lpbi = bi;
 // �����ɫ��   
 hPal = GetStockObject(DEFAULT_PALETTE);
 if (hPal)
 {
  hDC = ::GetDC(NULL);
  hOldPal=SelectPalette(hDC,(HPALETTE)hPal,FALSE);
  RealizePalette(hDC);
 }
 // ��ȡ�õ�ɫ�����µ�����ֵ
 GetDIBits(hDC,hBitmap,0,(UINT)Bitmap.bmHeight,(LPSTR)lpbi+sizeof(BITMAPINFOHEADER)+dwPaletteSize, (BITMAPINFO *)lpbi,DIB_RGB_COLORS);
 //�ָ���ɫ��   
 if (hOldPal)
 {
  SelectPalette(hDC, hOldPal, TRUE);
  RealizePalette(hDC);
  ::ReleaseDC(NULL, hDC);
 }
 //����λͼ�ļ�    
 fh=CreateFile(lpFileName, GENERIC_WRITE,0, NULL, CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);
 if (fh==INVALID_HANDLE_VALUE)
  return FALSE;
 // ����λͼ�ļ�ͷ
 bmfHdr.bfType = 0x4D42;  // "BM"
 dwDIBSize=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+dwPaletteSize+dwBmBitsSize;  
 bmfHdr.bfSize = dwDIBSize;
 bmfHdr.bfReserved1 = 0;
 bmfHdr.bfReserved2 = 0;
 bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER)+(DWORD)sizeof(BITMAPINFOHEADER)+dwPaletteSize;
 // д��λͼ�ļ�ͷ
 WriteFile(fh, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);
 // д��λͼ�ļ���������
  WriteFile(fh, (LPSTR)lpbi, sizeof(BITMAPINFOHEADER)+dwPaletteSize+dwBmBitsSize , &dwWritten, NULL); 
 //���   
 GlobalUnlock(hDib);
 GlobalFree(hDib);
 CloseHandle(fh);
 return TRUE;
}

void CMainFrame::OnMenuZoomBoth() 
{
	// TODO: Add your command handler code here
	m_bZoomH = TRUE;
	m_bZoomV = TRUE;
}

void CMainFrame::OnUpdateMenuZoomBoth(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck( (m_bZoomH && m_bZoomV) );
}

void CMainFrame::OnMenuZoomH() 
{
	// TODO: Add your command handler code here
	m_bZoomH = TRUE;
	m_bZoomV = FALSE;
}

void CMainFrame::OnUpdateMenuZoomH(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck( (m_bZoomH && !m_bZoomV) );
}

void CMainFrame::OnMenuZoomV() 
{
	// TODO: Add your command handler code here
	m_bZoomH = FALSE;
	m_bZoomV = TRUE;
}

void CMainFrame::OnUpdateMenuZoomV(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck( (!m_bZoomH && m_bZoomV) );
}

void CMainFrame::OnMenuZoomIn() 
{
	CDataDisp* pDataDisp = NULL;
	CAdcTestPlatDoc* pDoc = (CAdcTestPlatDoc*)GetActiveDocument();
	if ( pDoc != NULL )
	{
		CAdcTestPlatView* pTestPlatView = NULL;
		POSITION pos = pDoc->GetFirstViewPosition();
		while ( pos != NULL )
		{
			CView* pView = pDoc->GetNextView( pos );			
			if ( pView->IsKindOf(RUNTIME_CLASS(CAdcTestPlatView)) )
			{
				pTestPlatView = (CAdcTestPlatView*)pView;
				break;
			}
		}
		// �ҵ�AdcTestPlatView
		if ( pTestPlatView != NULL )
		{
			//pTestPlatView->m_DataDisp.ZoomIn();
			// �ҵ��ǵڼ���data��ͼ

			pDataDisp = &(pTestPlatView->m_DataDisp[m_byDataIndex]);
			if ( pDataDisp != NULL )
			{
				pDataDisp->ZoomIn();
			}			
		}
	}
}

void CMainFrame::OnUpdateMenuZoomIn(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CMainFrame::OnMenuZoomOut() 
{	
	CDataDisp* pDataDisp = NULL;
	CAdcTestPlatDoc* pDoc = (CAdcTestPlatDoc*)GetActiveDocument();
	if ( pDoc != NULL )
	{
		CAdcTestPlatView* pTestPlatView = NULL;
		POSITION pos = pDoc->GetFirstViewPosition();
		while ( pos != NULL )
		{
			CView* pView = pDoc->GetNextView( pos );			
			if ( pView->IsKindOf(RUNTIME_CLASS(CAdcTestPlatView)) )
			{
				pTestPlatView = (CAdcTestPlatView*)pView;
				break;
			}
		}
		// �ҵ�AdcTestPlatView
		if ( pTestPlatView != NULL )
		{
			//pTestPlatView->m_DataDisp.ZoomOut();
			// �ҵ��ǵڼ���data��ͼ
			pDataDisp = &(pTestPlatView->m_DataDisp[m_byDataIndex]);
			if ( pDataDisp != NULL )
			{
				pDataDisp->ZoomOut();
			}			
		}
	}
}

void CMainFrame::OnUpdateMenuZoomOut(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CMainFrame::OnMenuZoomRestore() 
{
	// TODO: Add your command handler code here
	CDataDisp* pDataDisp = NULL;
	CAdcTestPlatDoc* pDoc = (CAdcTestPlatDoc*)GetActiveDocument();
	if ( pDoc != NULL )
	{
		CAdcTestPlatView* pTestPlatView = NULL;
		POSITION pos = pDoc->GetFirstViewPosition();
		while ( pos != NULL )
		{
			CView* pView = pDoc->GetNextView( pos );			
			if ( pView->IsKindOf(RUNTIME_CLASS(CAdcTestPlatView)) )
			{
				pTestPlatView = (CAdcTestPlatView*)pView;
				break;
			}
		}
		// �ҵ�AdcTestPlatView
		if ( pTestPlatView != NULL )
		{
			//pTestPlatView->m_DataDisp.ZoomRestore();
			// �ҵ��ǵڼ���data��ͼ
			pDataDisp = &(pTestPlatView->m_DataDisp[m_byDataIndex]);
			if ( pDataDisp != NULL )
			{
				pDataDisp->ZoomRestore();
			}			
		}
	}
}

void CMainFrame::OnUpdateMenuZoomRestore(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CMainFrame::OnToolbarRestore() 
{
	// TODO: Add your command handler code here
	m_bZoomOut = FALSE;
	m_bZoomIn = FALSE;
}

void CMainFrame::OnUpdateToolbarRestore(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CMainFrame::OnToolbarZoomIn() 
{
	// TODO: Add your command handler code here
	m_bZoomIn = !m_bZoomIn;
	if ( m_bZoomIn )
	{
		m_bZoomOut = FALSE;
	}
}

void CMainFrame::OnUpdateToolbarZoomIn(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck( m_bZoomIn );
}

void CMainFrame::OnToolbarZoomOut() 
{
	// TODO: Add your command handler code here
	m_bZoomOut = !m_bZoomOut;
	if ( m_bZoomOut )
	{
		m_bZoomIn = FALSE;
	}
}

void CMainFrame::OnUpdateToolbarZoomOut(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck( m_bZoomOut );
}



void CMainFrame::OnMenuFftZoomIn() 
{
	// TODO: Add your command handler code here
	CFFTDisp* pFftDisp = NULL;
	CAdcTestPlatDoc* pDoc = (CAdcTestPlatDoc*)GetActiveDocument();
	if ( pDoc != NULL )
	{
		CAdcTestPlatView* pTestPlatView = NULL;
		POSITION pos = pDoc->GetFirstViewPosition();
		while ( pos != NULL )
		{
			CView* pView = pDoc->GetNextView( pos );			
			if ( pView->IsKindOf(RUNTIME_CLASS(CAdcTestPlatView)) )
			{
				pTestPlatView = (CAdcTestPlatView*)pView;
				break;
			}
		}
		// �ҵ�AdcTestPlatView
		if ( pTestPlatView != NULL )
		{
			//pTestPlatView->m_FFTDisp[0].ZoomIn();
			// �ҵ��ǵڼ���fft��ͼ
			pFftDisp = &(pTestPlatView->m_FFTDisp[m_byFftIndex]);
			if ( pFftDisp != NULL )
			{
				pFftDisp->ZoomIn();
			}			
		}
	}
}

void CMainFrame::OnUpdateMenuFftZoomIn(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CMainFrame::OnMenuFftZoomOut() 
{
	// TODO: Add your command handler code here
	CFFTDisp* pFftDisp = NULL;
	CAdcTestPlatDoc* pDoc = (CAdcTestPlatDoc*)GetActiveDocument();
	if ( pDoc != NULL )
	{
		CAdcTestPlatView* pTestPlatView = NULL;
		POSITION pos = pDoc->GetFirstViewPosition();
		while ( pos != NULL )
		{
			CView* pView = pDoc->GetNextView( pos );			
			if ( pView->IsKindOf(RUNTIME_CLASS(CAdcTestPlatView)) )
			{
				pTestPlatView = (CAdcTestPlatView*)pView;
				break;
			}
		}
		// �ҵ�AdcTestPlatView
		if ( pTestPlatView != NULL )
		{
			// �ҵ��ǵڼ���fft��ͼ
			pFftDisp = &(pTestPlatView->m_FFTDisp[m_byFftIndex]);
			if ( pFftDisp != NULL )
			{
				pFftDisp->ZoomOut();
			}			
		}
	}
}

void CMainFrame::OnUpdateMenuFftZoomOut(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CMainFrame::OnMenuFftZoomRestore() 
{
	// TODO: Add your command handler code here
	CFFTDisp* pFftDisp = NULL;
	CAdcTestPlatDoc* pDoc = (CAdcTestPlatDoc*)GetActiveDocument();
	if ( pDoc != NULL )
	{
		CAdcTestPlatView* pTestPlatView = NULL;
		POSITION pos = pDoc->GetFirstViewPosition();
		while ( pos != NULL )
		{
			CView* pView = pDoc->GetNextView( pos );			
			if ( pView->IsKindOf(RUNTIME_CLASS(CAdcTestPlatView)) )
			{
				pTestPlatView = (CAdcTestPlatView*)pView;
				break;
			}
		}
		// �ҵ�AdcTestPlatView
		if ( pTestPlatView != NULL )
		{
			//pTestPlatView->m_FFTDisp[0].ZoomRestore();
			// �ҵ��ǵڼ���fft��ͼ
			pFftDisp = &(pTestPlatView->m_FFTDisp[m_byFftIndex]);
			if ( pFftDisp != NULL )
			{
				pFftDisp->ZoomRestore();
			}
		}
	}
}

void CMainFrame::OnUpdateMenuFftZoomRestore(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CMainFrame::OnUpdateState( CCmdUI* pCmdUI )
{
	//pCmdUI->SetText( "Welcome" );
	CSize size;
	HGDIOBJ hOldFont = NULL;

	// �õ���ǰ״̬��������
	HFONT hFont = (HFONT)m_wndStatusBar.SendMessage( WM_GETFONT );
	CClientDC dc(NULL);
	if ( hFont != NULL )
	{
		hOldFont = dc.SelectObject( hFont );
	}
	size =dc.GetTextExtent( m_strState );
	if ( hOldFont != NULL )
	{
		dc.SelectObject( hOldFont );
	}
	// �޸�״̬��
	m_wndStatusBar.SetPaneInfo( m_nIndexOfState, ID_INDICATOR_STATE, 0, size.cx );	
	pCmdUI->SetText( m_strState );
	pCmdUI->Enable( TRUE );
}

void CMainFrame::OnToolbarMultiView() 
{
	
	//m_bMultiView = !m_bMultiView;
	m_byMultiView = 1;
	ChangeMultiView();
}

void CMainFrame::OnUpdateToolbarMultiView(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck( (m_byMultiView == 1) );
}

// ���ڼ�����״̬
void CMainFrame::OnTimer(UINT nIDEvent) 
{
// 	DWORD dwSend, dwRecv, dwCmd;
// 
// 	dwCmd = 0;
// 	dwRecv = 0;
// 	srand( (unsigned)time( NULL ) );
// 	dwSend = abs( rand() );
// 
// 	CAdcTestPlatDoc* pDoc = (CAdcTestPlatDoc*)GetActiveDocument();
// 	if ( pDoc != NULL )
// 	{
// 		// ���͹���ͨ���������
// 		dwSend &= 0x0000FFFF;
// 		dwCmd = (CMD_FIBER_CHECK << 16) + dwSend;
// 		pDoc->IoWrite( LOCAL_ADDR_CMD, dwCmd );
// 		Sleep(10);
// 		// ȡ������
// 		pDoc->IoRead( LOCAL_ADDR_CHECK, &dwRecv );
// 		dwRecv &= 0x0000FFFF;
// 		if ( dwRecv != dwSend && dwRecv != 0 )
// 		{
// 			m_strState = "���˴������";
// 		}
// 		else
// 		{
// 			m_strState = "����ͨ������";
// 		}
// 	}

	CFrameWnd::OnTimer(nIDEvent);
}



void CMainFrame::OnToolbarStart() 
{
	CAdcTestPlatDoc* pDoc = (CAdcTestPlatDoc*)GetActiveDocument();
	if ( pDoc != NULL )
	{
		CView* pView = NULL;
		POSITION pos = pDoc->GetFirstViewPosition();
		while ( pos != NULL )
		{
			pView = pDoc->GetNextView( pos );
			// ���ݵ�ǰ����ʲôģʽ�����ò�ͬ�ġ����С�����
			if ( m_bTestAlg )
			{
				if ( pView->IsKindOf(RUNTIME_CLASS(CTestAlgView)) )
				{
					m_bRunning = TRUE;
					((CTestAlgView*)pView)->SendMessage( WM_COMMAND, ID_BTN_TEST, 0 );
					break;
				}
			}
			if ( m_bTestADC )
			{
				if ( pView->IsKindOf(RUNTIME_CLASS(CTestSetView)) )
				{
					m_bRunning = TRUE;
					((CTestSetView*)pView)->SendMessage( WM_COMMAND, ID_BTN_TEST, 0 );
					break;
				}
			}
			if ( m_bTestADCBatch )
			{
				if ( pView->IsKindOf(RUNTIME_CLASS(CTestSetBatchView)) )
				{
					m_bRunning = TRUE;
					((CTestSetBatchView*)pView)->SendMessage( WM_COMMAND, ID_BTN_TEST, 0 );
					break;
				}
			}
		}
		
	}
	
}

void CMainFrame::OnUpdateToolbarStart(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( !m_bRunning );
}

void CMainFrame::OnToolbarEnd() 
{
	CAdcTestPlatDoc* pDoc = (CAdcTestPlatDoc*)GetActiveDocument();
	if ( pDoc != NULL )
	{
		CView* pView = NULL;
		POSITION pos = pDoc->GetFirstViewPosition();
		while ( pos != NULL )
		{
			pView = pDoc->GetNextView( pos );
			// ���ݵ�ǰ����ʲôģʽ�����ò�ͬ�ġ����С�����
			if ( m_bTestAlg )
			{
				if ( pView->IsKindOf(RUNTIME_CLASS(CTestAlgView)) )
				{
					m_bRunning = FALSE;
					((CTestAlgView*)pView)->SendMessage( WM_COMMAND, ID_BTN_TEST, 0 );
					break;
				}
			}
			if ( m_bTestADC )
			{
				if ( pView->IsKindOf(RUNTIME_CLASS(CTestSetView)) )
				{
					m_bRunning = FALSE;
					((CTestSetView*)pView)->SendMessage( WM_COMMAND, ID_BTN_TEST, 0 );
					break;
				}
			}
			if ( m_bTestADCBatch )
			{
				if ( pView->IsKindOf(RUNTIME_CLASS(CTestSetBatchView)) )
				{
					m_bRunning = FALSE;
					((CTestSetBatchView*)pView)->SendMessage( WM_COMMAND, ID_BTN_TEST, 0 );
					break;
				}
			}
		}
		
	}
	
}

void CMainFrame::OnUpdateToolbarEnd(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( m_bRunning );
}

void CMainFrame::OnToolbarSingleView() 
{
	m_byMultiView = 0;
	ChangeMultiView();	
}

void CMainFrame::OnUpdateToolbarSingleView(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck( (m_byMultiView == 0) );
}

void CMainFrame::OnToolbarMultiViewF() 
{
	m_byMultiView = 2;
	ChangeMultiView();	
}

void CMainFrame::OnUpdateToolbarMultiViewF(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck( (m_byMultiView == 2) );
}

void CMainFrame::OnToolbarMultiViewS() 
{
	m_byMultiView = 3;
	ChangeMultiView();	
}

void CMainFrame::OnUpdateToolbarMultiViewS(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck( (m_byMultiView == 3) );
}

void CMainFrame::OnToolbarMultiViewFs1() 
{
	m_byMultiView = 4;
	ChangeMultiView();	
}

void CMainFrame::OnUpdateToolbarMultiViewFs1(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck( (m_byMultiView == 4) );
}

void CMainFrame::OnToolbarMultiViewFs2() 
{
	m_byMultiView = 5;
	ChangeMultiView();	
}

void CMainFrame::OnUpdateToolbarMultiViewFs2(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck( (m_byMultiView == 5) );
}

void CMainFrame::ChangeMultiView()
{
	// ˢ����ͼ
	CAdcTestPlatDoc* pDoc = (CAdcTestPlatDoc*)GetActiveDocument();
	if ( pDoc != NULL )
	{
		CAdcTestPlatView* pTestPlatView = NULL;
		POSITION pos = pDoc->GetFirstViewPosition();
		while ( pos != NULL )
		{
			CView* pView = pDoc->GetNextView( pos );			
			if ( pView->IsKindOf(RUNTIME_CLASS(CAdcTestPlatView)) )
			{
				pTestPlatView = (CAdcTestPlatView*)pView;
				break;
			}
		}
		// �ҵ�AdcTestPlatView
		if ( pTestPlatView != NULL )
		{
			pTestPlatView->Display();
		}
	}
}

void CMainFrame::OnToolbarPower() 
{	
	m_bPower = !m_bPower;
	CAdcTestPlatDoc* pDoc = (CAdcTestPlatDoc*)GetActiveDocument();
	if ( pDoc != NULL )
	{
		// �ϰ��Դ�ϵ�
		if ( m_bPower )
		{			
			pDoc->PowerOn();
		}
		// �ϰ��Դ�ϵ�
		else
		{
			pDoc->PowerOff();
		}
	}
	
}

void CMainFrame::OnUpdateToolbarPower(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck( m_bPower );
}
