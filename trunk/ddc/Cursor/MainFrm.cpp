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
	// 默认断电
	m_bPower = FALSE;
	m_strState = "光纤通道正常";
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

	// 得到状态栏共有多少个区域
	int nOrigSize = sizeof( indicators ) / sizeof( UINT );
	// 构建
	UINT* pIndicators = new UINT[nOrigSize+1];
	memcpy( pIndicators, indicators, sizeof(indicators) );
	m_nIndexOfState = nOrigSize++;
	pIndicators[m_nIndexOfState] = ID_INDICATOR_STATE;
	m_wndStatusBar.SetIndicators( pIndicators, nOrigSize );
	delete [] pIndicators;
	
	// 添加定时器周期性查询光纤状态(1s)
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
	// 获取客户区大小
	CRect rc;
	GetClientRect( &rc );
	m_nWidth = rc.right - rc.left;
	m_nHeight = rc.bottom - rc.top;
	// 获取设置窗口的大小
	int nMapMode;
	CSize sizeTotalView, sizePage, sizeLine;	
	((CFormView*)m_wndSplitter2.GetPane(0, 0))->GetDeviceScrollSizes(
		nMapMode, sizeTotalView, sizePage, sizeLine);
	// 调整两列的大小
	m_wndSplitter.SetColumnInfo( 0, sizeTotalView.cx, 1 );
	m_wndSplitter.SetColumnInfo( 1, 100, 1 );
	// 调整左边视图两行大小
	m_wndSplitter2.SetRowInfo( 0, sizeTotalView.cy, 1 );
	m_wndSplitter2.SetRowInfo( 1, 10, 1 );
	/*
	// 调整右边图像显示区域视图的大小
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
		// 首先删除测试设置窗口的视图
		m_wndSplitter2.DeleteView( 0, 0 );
		// 然后新建需要的视图
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
		
		// 获取设置窗口的大小
		int nMapMode;
		CSize sizeTotalView, sizePage, sizeLine;	
		((CFormView*)m_wndSplitter2.GetPane(0, 0))->GetDeviceScrollSizes(
			nMapMode, sizeTotalView, sizePage, sizeLine);
		// 调整两列的大小
		m_wndSplitter.SetColumnInfo( 0, sizeTotalView.cx, 1 );
		m_wndSplitter.SetColumnInfo( 1, 100, 1 );
		// 调整左边视图两行大小
		m_wndSplitter2.SetRowInfo( 0, sizeTotalView.cy, 1 );
		m_wndSplitter2.SetRowInfo( 1, 10, 1 );
		
		// 拆分窗口发生变化，调用下面的函数更新
		m_wndSplitter2.RecalcLayout();
		m_wndSplitter.RecalcLayout();

		SetWindowText( "ADC测试软件" );
		// 更新所有视图
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

	// 波形切换到adc测试
	CAdcTestPlatDoc* pDoc = (CAdcTestPlatDoc*)GetActiveDocument();
	if ( pDoc != NULL )
	{
		pDoc->m_nTestModeSel = 1;
		// 切换到adc后，fft视图的采样频率恢复为80M
		// 查找显示视图
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
		// 找到了，修改初始采样频率
		if ( pTestPlatView != NULL )
		{
			pTestPlatView->m_FFTDisp[0].m_dOrgSampFreq = 80.0;
			pTestPlatView->m_FFTDisp[1].m_dOrgSampFreq = 80.0;
			pTestPlatView->m_FFTDisp[2].m_dOrgSampFreq = 80.0;
			pTestPlatView->m_FFTDisp[3].m_dOrgSampFreq = 80.0;
			pTestPlatView->m_FFTDisp[4].m_dOrgSampFreq = 80.0;
			// 视图恢复
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
	// 切换视图
	SwitchView();
/*
	// 波形切换到算法测试
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
	// 波形切换到算法测试
	CAdcTestPlatDoc* pDoc = (CAdcTestPlatDoc*)GetActiveDocument();
	if ( pDoc != NULL )
	{
		pDoc->m_nTestModeSel = 6;
		// 切换到alg后，fft视图的设置恢复
		// 查找显示视图
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
		// 找到了
		if ( pTestPlatView != NULL )
		{

			pTestPlatView->m_FFTDisp[0].m_dOrgSampFreq = 80.0 / 20;
			pTestPlatView->m_FFTDisp[1].m_dOrgSampFreq = 80.0 / 20;
			pTestPlatView->m_FFTDisp[2].m_dOrgSampFreq = 80.0 / 20;
			pTestPlatView->m_FFTDisp[3].m_dOrgSampFreq = 80.0 / 20;
			pTestPlatView->m_FFTDisp[4].m_dOrgSampFreq = 80.0 / 20;
			// 视图恢复
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

	// 查找ADC批量测试文件
	if ( !SearchAdcBatchFile() )
	{
		AfxMessageBox( "未找到批量测试文件!" );
	}
	else
	{
		// 找到的第一个批量测试文件放入电路ID文本框显示
		CDocument* pDoc = GetActiveDocument();
		POSITION pos = pDoc->GetFirstViewPosition();
		while ( pos != NULL )
		{
			CView* pView = pDoc->GetNextView( pos );
			// 找到图像显示视图
			if ( pView->IsKindOf(RUNTIME_CLASS(CAdcTestPlatView)) )
			{
				((CAdcTestPlatView*)pView)->m_strID = m_strFileArray[m_dwCurFilePos].Left(8);
				((CAdcTestPlatView*)pView)->UpdateData( FALSE );
				break;
			}
		}
		// 同时打开该文件，显示设置区/结果区/图像区内容
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
	// 没起作用?
	::SetCurrentDirectory( szCurDir );

	strDefExt = ".atp";
	strDefFileName = szCurDir;
	strDefFileName += "\\*.atp";
	// 文件类型不能加括号
	strFilter = "ADC test platform file (*.atp)|*.atp|all files (*.*)|*.*||";

	// 文件保存对话框
	CFileDialog fileDlg( FALSE, strDefExt, strDefFileName, 
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		strFilter, this );
	
	// 修改文件对话框的标题
	fileDlg.m_ofn.lpstrTitle = "保存当前测试数据";

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

	// 文件打开对话框
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
	// 初始化文件数据缓冲区, 文件头标识
	for ( i = 0; i < 16; i++ )
	{
		m_byaFileBuf[i] = 0x5A;
	}
	dwPos += 16;
	// 根据不同测试类型分类处理
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
		// 批量测试的保存，不存当时的测试数据，只保存测试结果
		// 写入文件
		fileSave.Write( m_byaFileBuf, dwPos );
		fileSave.Close();
		return;
	}
	// ADC+DDC保留
	
	// doc里面所有相关的状态、数据在此存储
	((CAdcTestPlatDoc*)pDoc)->FileSave( m_byaFileBuf+dwPos, &dwSize );
	dwPos += dwSize;
/*
	// 测试结果窗口的数据		
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
	// 4个通道的底噪声测试数据
	memcpy( m_byaFileBuf+dwPos, (BYTE*)((CAdcTestPlatDoc*)pDoc)->m_waCh1SignalNoise, MAX_DEPTH*2 );
	dwPos += MAX_DEPTH*2;
	memcpy( m_byaFileBuf+dwPos, (BYTE*)((CAdcTestPlatDoc*)pDoc)->m_waCh2SignalNoise, MAX_DEPTH*2 );
	dwPos += MAX_DEPTH*2;
	memcpy( m_byaFileBuf+dwPos, (BYTE*)((CAdcTestPlatDoc*)pDoc)->m_waCh3SignalNoise, MAX_DEPTH*2 );
	dwPos += MAX_DEPTH*2;
	memcpy( m_byaFileBuf+dwPos, (BYTE*)((CAdcTestPlatDoc*)pDoc)->m_waCh4SignalNoise, MAX_DEPTH*2 );
	dwPos += MAX_DEPTH*2;
	// 4个通道的性能测试数据
	memcpy( m_byaFileBuf+dwPos, (BYTE*)((CAdcTestPlatDoc*)pDoc)->m_waCh1SignalPerf, MAX_DEPTH*2 );
	dwPos += MAX_DEPTH*2;
	memcpy( m_byaFileBuf+dwPos, (BYTE*)((CAdcTestPlatDoc*)pDoc)->m_waCh2SignalPerf, MAX_DEPTH*2 );
	dwPos += MAX_DEPTH*2;
	memcpy( m_byaFileBuf+dwPos, (BYTE*)((CAdcTestPlatDoc*)pDoc)->m_waCh3SignalPerf, MAX_DEPTH*2 );
	dwPos += MAX_DEPTH*2;
	memcpy( m_byaFileBuf+dwPos, (BYTE*)((CAdcTestPlatDoc*)pDoc)->m_waCh4SignalPerf, MAX_DEPTH*2 );
	dwPos += MAX_DEPTH*2;
	// 4个通道的通道串音测试数据
	memcpy( m_byaFileBuf+dwPos, (BYTE*)((CAdcTestPlatDoc*)pDoc)->m_waCh1SignalDisturb, MAX_DEPTH*2 );
	dwPos += MAX_DEPTH*2;
	memcpy( m_byaFileBuf+dwPos, (BYTE*)((CAdcTestPlatDoc*)pDoc)->m_waCh2SignalDisturb, MAX_DEPTH*2 );
	dwPos += MAX_DEPTH*2;
	memcpy( m_byaFileBuf+dwPos, (BYTE*)((CAdcTestPlatDoc*)pDoc)->m_waCh3SignalDisturb, MAX_DEPTH*2 );
	dwPos += MAX_DEPTH*2;
	memcpy( m_byaFileBuf+dwPos, (BYTE*)((CAdcTestPlatDoc*)pDoc)->m_waCh4SignalDisturb, MAX_DEPTH*2 );
	dwPos += MAX_DEPTH*2;
*/
	// 写入文件
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
		// 检查是否ADC批量测试文件
		if ( fileOpen.Open(strTempFileName , CFile::modeRead | CFile::typeBinary ) )
		{
			// 批量测试文件的文件名必须为8位数字
			//if ( fileOpen.GetLength() > 4*MAX_DEPTH 
			//	&& strTempFileName.GetLength() == 12)
			if ( strTempFileName.GetLength() == 12 )
			{
				// 检查文件头标识
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
						// 保留ADC批量测试的文件名
						m_strFileArray[m_dwFileArraySize++] = strTempFileName;						
						bRet = TRUE;
					}
				}
			}
		}
		fileOpen.Close();
	}
	// 调整电路ID微调按钮的范围
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
		strMessage.Format( "打开文件 %s 失败!", strFileName );
		AfxMessageBox( strMessage );
		return;
	}
	/*
	// 获取文件大小
	dwFileSize = fileOpen.GetLength();		
	if ( dwFileSize < 4*MAX_DEPTH )
	{
		AfxMessageBox( "文件长度不符合要求!" );
		return;
	}
	*/
	// 检查文件头标识
	fileOpen.Read( m_byaFileBuf, 16 );
	for ( i = 0; i < 16; i++ )
	{
		if ( m_byaFileBuf[i] != 0x5A )
		{
			AfxMessageBox( "文件格式不符合要求!" );
			fileOpen.Close();
			return;
		}
	}		
	// 根据文件类型打开不同视图
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
			// 保留
			break;
		}
		case ADC_ID:
		{
			// 显示ADC查看模式
			OnViewAdcRecord();			
			break;
		}
		case ADC_BATCH_ID:
		{
			// 切换到ADC批量查看模式
			m_bTestADC = FALSE;
			m_bTestAlg = FALSE;	
			m_bTestADCBatch = FALSE;
			m_bTestDDCBatch = FALSE;
			m_bViewAlg = FALSE;
			m_bViewADC = FALSE;	
			m_bViewADCBatch = TRUE;
			m_bViewDDCBatch = FALSE;			
			SwitchView();
			// 读取6B的参数值
			fileOpen.Read( m_byaFileBuf, TEST_ITEM );
			POSITION pos = pDoc->GetFirstViewPosition();
			while ( pos != NULL )
			{
				CView* pView = pDoc->GetNextView( pos );				
				if ( pView->IsKindOf(RUNTIME_CLASS(CTestSetBatchView)) )
				{
					// 文件名
					((CTestSetBatchView*)pView)->m_strID = (strFileName.Right(12)).Left(8);
					((CTestSetBatchView*)pView)->FileOpen( m_byaFileBuf );						
					break;
				}
			}
			// 批量测试没有保存测试数据直接返回
			// 刷新所有视图
			((CAdcTestPlatDoc*)pDoc)->UpdateAllViews( NULL );
			return;
			break;
		}
		case DDC_BATCH_ID:
		{
			// 保留
			break;
		}
		default:
			break;
	}

	// 读取剩余数据，送doc解析，总计4B+288B+256KB
	fileOpen.Read( m_byaFileBuf, 4+288+256*1024 );			
	((CAdcTestPlatDoc*)pDoc)->FileOpen( m_byaFileBuf );
	// 刷新所有视图
	((CAdcTestPlatDoc*)pDoc)->UpdateAllViews( NULL );
}

// 切换左上方的视图
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
	// ADC+DDC保留

	// 首先删除左上窗口的视图
	m_wndSplitter2.DeleteView( 0, 0 );
	// 然后新建需要的视图
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
	
	// 获取设置窗口的大小
	int nMapMode;
	CSize sizeTotalView, sizePage, sizeLine;	
	((CFormView*)m_wndSplitter2.GetPane(0, 0))->GetDeviceScrollSizes(
		nMapMode, sizeTotalView, sizePage, sizeLine);
	// 调整两列的大小
	m_wndSplitter.SetColumnInfo( 0, sizeTotalView.cx, 1 );
	m_wndSplitter.SetColumnInfo( 1, 100, 1 );
	// 调整左边视图两行大小
	m_wndSplitter2.SetRowInfo( 0, sizeTotalView.cy, 1 );
	m_wndSplitter2.SetRowInfo( 1, 10, 1 );
	
	// 拆分窗口发生变化，调用下面的函数更新
	m_wndSplitter2.RecalcLayout();
	m_wndSplitter.RecalcLayout();

	SetWindowText( "SIP测试系统ver2.0" );// ADC测试软件
	// 更新所有视图
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
	// 没起作用?
	::SetCurrentDirectory( szCurDir );

	strDefExt = ".bmp";
	strDefFileName = szCurDir;
	strDefFileName += "\\*.bmp";
	// 文件类型不能加括号
	strFilter = "fft bmp file (*.bmp)|*.bmp||";

	// 文件保存对话框
	CFileDialog fileDlg( FALSE, strDefExt, strDefFileName, 
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		strFilter, this );
	
	// 修改文件对话框的标题
	fileDlg.m_ofn.lpstrTitle = "保存频谱波形";

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
			// 显示视图
			if ( pView->IsKindOf(RUNTIME_CLASS(CAdcTestPlatView)) )
			{			
				pTestPlatView = (CAdcTestPlatView*)pView;
				break;
			}
		}
	}
	// 通过显示视图获取文件名
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
		strMsg.Format( "文件%s和%s保存成功", strFftFileName, strDataFileName );
		AfxMessageBox( strMsg );
	}
}

HBITMAP CMainFrame::CopyScreenToBitmap(LPRECT lpRect) //lpRect 代表选定区域
{
 HDC hScrDC, hMemDC;      
 // 屏幕和内存设备描述表
 HBITMAP hBitmap,hOldBitmap;   
 // 位图句柄
 int       nX, nY, nX2, nY2;      
 // 选定区域坐标
 int       nWidth, nHeight;      
 // 位图宽度和高度
 int       xScrn, yScrn;         
 // 屏幕分辨率
 // 确保选定区域不为空矩形
 if (IsRectEmpty(lpRect))
  return NULL;
 //为屏幕创建设备描述表
 hScrDC = CreateDC("DISPLAY", NULL, NULL, NULL);
 //为屏幕设备描述表创建兼容的内存设备描述表
 hMemDC = CreateCompatibleDC(hScrDC);
 // 获得选定区域坐标
 nX = lpRect->left;
 nY = lpRect->top;
 nX2 = lpRect->right;
 nY2 = lpRect->bottom;
 // 获得屏幕分辨率
 xScrn = GetDeviceCaps(hScrDC, HORZRES);
 yScrn = GetDeviceCaps(hScrDC, VERTRES);
 //确保选定区域是可见的
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
 // 创建一个与屏幕设备描述表兼容的位图
 hBitmap=CreateCompatibleBitmap(hScrDC,nWidth,nHeight);
 // 把新位图选到内存设备描述表中
 hOldBitmap=(HBITMAP)SelectObject(hMemDC,hBitmap);
 // 把屏幕设备描述表拷贝到内存设备描述表中
 BitBlt(hMemDC,0,0, nWidth,nHeight,hScrDC, nX, nY, SRCCOPY);
 //得到屏幕位图的句柄
 hBitmap=(HBITMAP)SelectObject(hMemDC,hOldBitmap);
 //清除 
 DeleteDC(hScrDC);
 DeleteDC(hMemDC);
 // 返回位图句柄
 return hBitmap;
}

int CMainFrame::SaveBitmapToFile(HBITMAP hBitmap, LPSTR lpFileName) //hBitmap 为刚才的屏幕位图句柄
{      //lpFileName 为位图文件名
 HDC     hDC;         
    //设备描述表
 int     iBits;      
 //当前显示分辨率下每个像素所占字节数
 WORD    wBitCount;   
    //位图中每个像素所占字节数
 //定义调色板大小， 位图中像素字节大小 ，  位图文件大小 ， 写入文件字节数
 DWORD           dwPaletteSize=0,dwBmBitsSize,dwDIBSize, dwWritten;
 BITMAP          Bitmap;        
 //位图属性结构
 BITMAPFILEHEADER   bmfHdr;        
 //位图文件头结构
 BITMAPINFOHEADER   bi;            
 //位图信息头结构 
 LPBITMAPINFOHEADER lpbi;          
 //指向位图信息头结构
    HANDLE          fh, hDib, hPal;
 HPALETTE     hOldPal=NULL;
 //定义文件，分配内存句柄，调色板句柄
 
 //计算位图文件每个像素所占字节数
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
 //计算调色板大小
 if (wBitCount <= 8)
  dwPaletteSize=(1<<wBitCount)*sizeof(RGBQUAD);
 
 //设置位图信息头结构
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
 //为位图内容分配内存

/*xxxxxxxx计算位图大小分解一下(解释一下上面的语句)xxxxxxxxxxxxxxxxxxxx 
//每个扫描行所占的字节数应该为4的整数倍，具体算法为:
 int biWidth = (Bitmap.bmWidth*wBitCount) / 32;
 if((Bitmap.bmWidth*wBitCount) % 32)
  biWidth++; //不是整数倍的加1
 biWidth *= 4;//到这里，计算得到的为每个扫描行的字节数。
 dwBmBitsSize = biWidth * Bitmap.bmHeight;//得到大小
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx*/


 hDib  = GlobalAlloc(GHND,dwBmBitsSize+dwPaletteSize+sizeof(BITMAPINFOHEADER));
 lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);
 *lpbi = bi;
 // 处理调色板   
 hPal = GetStockObject(DEFAULT_PALETTE);
 if (hPal)
 {
  hDC = ::GetDC(NULL);
  hOldPal=SelectPalette(hDC,(HPALETTE)hPal,FALSE);
  RealizePalette(hDC);
 }
 // 获取该调色板下新的像素值
 GetDIBits(hDC,hBitmap,0,(UINT)Bitmap.bmHeight,(LPSTR)lpbi+sizeof(BITMAPINFOHEADER)+dwPaletteSize, (BITMAPINFO *)lpbi,DIB_RGB_COLORS);
 //恢复调色板   
 if (hOldPal)
 {
  SelectPalette(hDC, hOldPal, TRUE);
  RealizePalette(hDC);
  ::ReleaseDC(NULL, hDC);
 }
 //创建位图文件    
 fh=CreateFile(lpFileName, GENERIC_WRITE,0, NULL, CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);
 if (fh==INVALID_HANDLE_VALUE)
  return FALSE;
 // 设置位图文件头
 bmfHdr.bfType = 0x4D42;  // "BM"
 dwDIBSize=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+dwPaletteSize+dwBmBitsSize;  
 bmfHdr.bfSize = dwDIBSize;
 bmfHdr.bfReserved1 = 0;
 bmfHdr.bfReserved2 = 0;
 bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER)+(DWORD)sizeof(BITMAPINFOHEADER)+dwPaletteSize;
 // 写入位图文件头
 WriteFile(fh, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);
 // 写入位图文件其余内容
  WriteFile(fh, (LPSTR)lpbi, sizeof(BITMAPINFOHEADER)+dwPaletteSize+dwBmBitsSize , &dwWritten, NULL); 
 //清除   
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
		// 找到AdcTestPlatView
		if ( pTestPlatView != NULL )
		{
			//pTestPlatView->m_DataDisp.ZoomIn();
			// 找到是第几个data视图

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
		// 找到AdcTestPlatView
		if ( pTestPlatView != NULL )
		{
			//pTestPlatView->m_DataDisp.ZoomOut();
			// 找到是第几个data视图
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
		// 找到AdcTestPlatView
		if ( pTestPlatView != NULL )
		{
			//pTestPlatView->m_DataDisp.ZoomRestore();
			// 找到是第几个data视图
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
		// 找到AdcTestPlatView
		if ( pTestPlatView != NULL )
		{
			//pTestPlatView->m_FFTDisp[0].ZoomIn();
			// 找到是第几个fft视图
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
		// 找到AdcTestPlatView
		if ( pTestPlatView != NULL )
		{
			// 找到是第几个fft视图
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
		// 找到AdcTestPlatView
		if ( pTestPlatView != NULL )
		{
			//pTestPlatView->m_FFTDisp[0].ZoomRestore();
			// 找到是第几个fft视图
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

	// 得到当前状态栏的字体
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
	// 修改状态栏
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

// 周期检查光纤状态
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
// 		// 发送光纤通道检测命令
// 		dwSend &= 0x0000FFFF;
// 		dwCmd = (CMD_FIBER_CHECK << 16) + dwSend;
// 		pDoc->IoWrite( LOCAL_ADDR_CMD, dwCmd );
// 		Sleep(10);
// 		// 取回数据
// 		pDoc->IoRead( LOCAL_ADDR_CHECK, &dwRecv );
// 		dwRecv &= 0x0000FFFF;
// 		if ( dwRecv != dwSend && dwRecv != 0 )
// 		{
// 			m_strState = "光纤传输出错";
// 		}
// 		else
// 		{
// 			m_strState = "光纤通道正常";
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
			// 根据当前处于什么模式，调用不同的“运行”程序
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
			// 根据当前处于什么模式，调用不同的“运行”程序
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
	// 刷新视图
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
		// 找到AdcTestPlatView
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
		// 上板电源上电
		if ( m_bPower )
		{			
			pDoc->PowerOn();
		}
		// 上板电源断电
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
