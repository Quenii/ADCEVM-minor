// TestSetView.cpp : implementation file
//

#include "stdafx.h"
#include "AdcTestPlat.h"
#include "TestSetView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestSetView

IMPLEMENT_DYNCREATE(CTestSetView, CFormView)

CTestSetView::CTestSetView()
	: CFormView(CTestSetView::IDD)
{
	//{{AFX_DATA_INIT(CTestSetView)	
	//}}AFX_DATA_INIT
	m_nTestModeSel = 1;
	m_nCount = 0;
	m_bmpGreen.LoadBitmap( IDB_GREEN );
	m_bmpRed.LoadBitmap( IDB_RED );
	m_bmpBack.LoadBitmap( IDB_BACK );
	m_bTestBegin = TRUE;
}

CTestSetView::~CTestSetView()
{
}

void CTestSetView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestSetView)
	//DDX_Control(pDX, IDC_SET_PIC_STATE, m_imgState);
	DDX_Radio(pDX, IDC_RADIO_BACK_NOISE, m_nTestModeSel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestSetView, CFormView)
	//{{AFX_MSG_MAP(CTestSetView)
	ON_BN_CLICKED(IDC_CHECK_LOW_NOISE, OnCheckLowNoise)
	ON_BN_CLICKED(IDC_CHECK_SNR, OnCheckSnr)
	ON_BN_CLICKED(IDC_CHECK_SFDR, OnCheckSfdr)
	ON_BN_CLICKED(IDC_CHECK_CHAN_DISTURB, OnCheckChanDisturb)
	ON_BN_CLICKED(IDC_CHECK_SINAD, OnCheckSinad)
	ON_BN_CLICKED(ID_BTN_TEST, OnBtnTest)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_RADIO_BACK_NOISE, OnRadioBackNoise)
	ON_BN_CLICKED(IDC_RADIO_CHAN_DISTURB_A, OnRadioChanDisturbA)
	ON_BN_CLICKED(IDC_RADIO_CHAN_DISTURB_B, OnRadioChanDisturbB)
	ON_BN_CLICKED(IDC_RADIO_CHAN_DISTURB_C, OnRadioChanDisturbC)
	ON_BN_CLICKED(IDC_RADIO_CHAN_DISTURB_D, OnRadioChanDisturbD)
	ON_BN_CLICKED(IDC_RADIO_PERF, OnRadioPerf)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestSetView diagnostics

#ifdef _DEBUG
void CTestSetView::AssertValid() const
{
	CFormView::AssertValid();
}

void CTestSetView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTestSetView message handlers

void CTestSetView::OnCheckLowNoise() 
{		
	CAdcTestPlatDoc* pDoc = (CAdcTestPlatDoc*)GetDocument();
	if ( pDoc != NULL )
	{
		CButton* pCheck = (CButton*)GetDlgItem( IDC_CHECK_LOW_NOISE );
		int nCheck = pCheck->GetCheck();
		if ( nCheck == 1 )
		{
			pDoc->m_bTestBackNoise = TRUE;
		}
		else
		{
			pDoc->m_bTestBackNoise = FALSE;
		}
		pDoc->UpdateAllViews( NULL );
	}
}

void CTestSetView::OnCheckSnr() 
{	
	CAdcTestPlatDoc* pDoc = (CAdcTestPlatDoc*)GetDocument();
	if ( pDoc != NULL )
	{
		CButton* pCheck = (CButton*)GetDlgItem( IDC_CHECK_SNR );
		int nCheck = pCheck->GetCheck();
		if ( nCheck == 1 )
		{
			pDoc->m_bTestSNR = TRUE;
		}
		else
		{
			pDoc->m_bTestSNR = FALSE;
		}
		pDoc->UpdateAllViews( NULL );
	}
}

void CTestSetView::OnCheckSfdr() 
{
	CAdcTestPlatDoc* pDoc = (CAdcTestPlatDoc*)GetDocument();
	if ( pDoc != NULL )
	{
		CButton* pCheck = (CButton*)GetDlgItem( IDC_CHECK_SFDR );
		int nCheck = pCheck->GetCheck();
		if ( nCheck == 1 )
		{
			pDoc->m_bTestSFDR = TRUE;
		}
		else
		{
			pDoc->m_bTestSFDR = FALSE;
		}
		pDoc->UpdateAllViews( NULL );
	}	
}

void CTestSetView::OnCheckChanDisturb() 
{
	CAdcTestPlatDoc* pDoc = (CAdcTestPlatDoc*)GetDocument();
	if ( pDoc != NULL )
	{
		CButton* pCheck = (CButton*)GetDlgItem( IDC_CHECK_CHAN_DISTURB );
		int nCheck = pCheck->GetCheck();
		if ( nCheck == 1 )
		{
			pDoc->m_bTestChanDisturb = TRUE;
		}
		else
		{
			pDoc->m_bTestChanDisturb = FALSE;
		}
		pDoc->UpdateAllViews( NULL );
	}	
}

void CTestSetView::OnCheckSinad() 
{
	CAdcTestPlatDoc* pDoc = (CAdcTestPlatDoc*)GetDocument();
	if ( pDoc != NULL )
	{
		CButton* pCheck = (CButton*)GetDlgItem( IDC_CHECK_SINAD );
		int nCheck = pCheck->GetCheck();
		if ( nCheck == 1 )
		{
			pDoc->m_bTestSINAD = TRUE;
		}
		else
		{
			pDoc->m_bTestSINAD = FALSE;
		}
		pDoc->UpdateAllViews( NULL );
	}
}

void CTestSetView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	SetCheckState();	
}

void CTestSetView::SetCheckState()
{
/*
	CAdcTestPlatDoc* pDoc = (CAdcTestPlatDoc*)GetDocument();
	if ( pDoc != NULL )
	{
		// 设置复选框状态
		if ( pDoc->m_bTestBackNoise )
		{
			((CButton*)GetDlgItem( IDC_CHECK_LOW_NOISE ))->SetCheck(1);
		}
		else
		{
			((CButton*)GetDlgItem( IDC_CHECK_LOW_NOISE ))->SetCheck(0);
		}
		if ( pDoc->m_bTestSNR )
		{
			((CButton*)GetDlgItem( IDC_CHECK_SNR ))->SetCheck(1);
		}
		else
		{
			((CButton*)GetDlgItem( IDC_CHECK_SNR ))->SetCheck(0);
		}
		if ( pDoc->m_bTestSFDR )
		{
			((CButton*)GetDlgItem( IDC_CHECK_SFDR ))->SetCheck(1);
		}
		else
		{
			((CButton*)GetDlgItem( IDC_CHECK_SFDR ))->SetCheck(0);
		}
		if ( pDoc->m_bTestChanDisturb )
		{
			((CButton*)GetDlgItem( IDC_CHECK_CHAN_DISTURB ))->SetCheck(1);
		}
		else
		{
			((CButton*)GetDlgItem( IDC_CHECK_CHAN_DISTURB ))->SetCheck(0);
		}
		if ( pDoc->m_bTestSINAD )
		{
			((CButton*)GetDlgItem( IDC_CHECK_SINAD ))->SetCheck(1);
		}
		else
		{
			((CButton*)GetDlgItem( IDC_CHECK_SINAD ))->SetCheck(0);
		}
	}
	
	// ADC查看模式，设置按钮都设置为无效
	if ( ((CMainFrame*)GetParentFrame())->m_bViewADC )
	{
		GetDlgItem( IDC_CHECK_LOW_NOISE )->EnableWindow( FALSE );
		GetDlgItem( IDC_CHECK_SNR )->EnableWindow( FALSE );
		GetDlgItem( IDC_CHECK_SFDR )->EnableWindow( FALSE );
		GetDlgItem( IDC_CHECK_CHAN_DISTURB )->EnableWindow( FALSE );
		GetDlgItem( IDC_CHECK_SINAD )->EnableWindow( FALSE );
		GetDlgItem( ID_BTN_TEST )->EnableWindow( FALSE );
		GetDlgItem( IDC_STATIC_STATE )->EnableWindow( FALSE );
	}
	else
	{
		GetDlgItem( IDC_CHECK_LOW_NOISE )->EnableWindow( TRUE );
		GetDlgItem( IDC_CHECK_SNR )->EnableWindow( TRUE );
		GetDlgItem( IDC_CHECK_SFDR )->EnableWindow( TRUE );
		GetDlgItem( IDC_CHECK_CHAN_DISTURB )->EnableWindow( TRUE );
		GetDlgItem( IDC_CHECK_SINAD )->EnableWindow( TRUE );
		GetDlgItem( ID_BTN_TEST )->EnableWindow( TRUE );
		GetDlgItem( IDC_STATIC_STATE )->EnableWindow( TRUE );
	}
*/
	CAdcTestPlatDoc* pDoc = (CAdcTestPlatDoc*)GetDocument();
	if ( pDoc != NULL )
	{
		// 设置按钮状态		
		switch ( pDoc->m_nTestModeSel )
		{
			case 0:
			{
				((CButton*)GetDlgItem( IDC_RADIO_BACK_NOISE ))->SetCheck(1);
				break;
			}
			case 1:
			{
				((CButton*)GetDlgItem( IDC_RADIO_PERF ))->SetCheck(1);
				break;
			}
			case 2:
			{
				((CButton*)GetDlgItem( IDC_RADIO_CHAN_DISTURB_A ))->SetCheck(1);
				break;
			}
			case 3:
			{
				((CButton*)GetDlgItem( IDC_RADIO_CHAN_DISTURB_B ))->SetCheck(1);
				break;
			}
			case 4:
			{
				((CButton*)GetDlgItem( IDC_RADIO_CHAN_DISTURB_C ))->SetCheck(1);
				break;
			}
			case 5:
			{
				((CButton*)GetDlgItem( IDC_RADIO_CHAN_DISTURB_D ))->SetCheck(1);
				break;
			}
			default:
				break;
		}
	}
	// ADC查看模式，设置按钮都设置为无效
	if ( ((CMainFrame*)GetParentFrame())->m_bViewADC )
	{
		GetDlgItem( IDC_RADIO_BACK_NOISE )->EnableWindow( FALSE );
		GetDlgItem( IDC_RADIO_PERF )->EnableWindow( FALSE );
		GetDlgItem( IDC_RADIO_CHAN_DISTURB_A )->EnableWindow( FALSE );
		GetDlgItem( IDC_RADIO_CHAN_DISTURB_B )->EnableWindow( FALSE );
		GetDlgItem( IDC_RADIO_CHAN_DISTURB_C )->EnableWindow( FALSE );
		GetDlgItem( IDC_RADIO_CHAN_DISTURB_D )->EnableWindow( FALSE );
		GetDlgItem( ID_BTN_TEST )->EnableWindow( FALSE );
		GetDlgItem( IDC_STATIC_STATE )->EnableWindow( FALSE );
	}
	else
	{
		GetDlgItem( IDC_RADIO_BACK_NOISE )->EnableWindow( TRUE );
		GetDlgItem( IDC_RADIO_PERF )->EnableWindow( TRUE );
		GetDlgItem( IDC_RADIO_CHAN_DISTURB_A )->EnableWindow( TRUE );
		GetDlgItem( IDC_RADIO_CHAN_DISTURB_B )->EnableWindow( TRUE );
		GetDlgItem( IDC_RADIO_CHAN_DISTURB_C )->EnableWindow( TRUE );
		GetDlgItem( IDC_RADIO_CHAN_DISTURB_D )->EnableWindow( TRUE );
		GetDlgItem( ID_BTN_TEST )->EnableWindow( TRUE );
		GetDlgItem( IDC_STATIC_STATE )->EnableWindow( TRUE );
	}
}

void CTestSetView::OnDraw(CDC* pDC) 
{
	// TODO: Add your specialized code here and/or call the base class
	SetCheckState();	
}

// 
void CTestSetView::OnBtnTest() 
{
	CMainFrame* pFrame = (CMainFrame*)GetParentFrame();

#ifndef SELF_TEST

	// 检查有无pcie板卡
	if ( !((CAdcTestPlatApp*)AfxGetApp())->DetectedCards() )
	{
		// 更新到工具栏
		if ( pFrame != NULL )
		{
			pFrame->m_bRunning = FALSE;
		}
		AfxMessageBox( "未找到PCIE设备!" );
		return;
	}
	else
#endif
	
	{
		CAdcTestPlatDoc* pDoc = (CAdcTestPlatDoc*)GetDocument();
		if ( pDoc != NULL )
		{
			DWORD dwCmd = (CMD_MODE << 16) 
				+ (0 << 8) //m_nStart
				+ (1 << 6) //m_nM0
				+ (1 << 5) //m_nChanConfigCtrl  
				+ (1 << 4) //m_nDataOutModelSel  lvds
				+ (1 << 3) //m_nParaSerSel
				+ (1 << 1) //m_nLvdsAck
				+ 1; //m_nTest
			pDoc->SendCommand( dwCmd ); 
			Sleep(1);
			dwCmd = 0x40000039;
			pDoc->SendCommand( dwCmd ); 
			Sleep(1);
			dwCmd = 0x40000079;
			pDoc->SendCommand( dwCmd ); 
			Sleep(1);
			dwCmd = 0x40000179;
			pDoc->SendCommand( dwCmd ); 

		}



		// 用于刷新视图
		SetTimer( 2, 500, NULL );
		// 能够开始测试
		if ( m_bTestBegin )
		{
			// 更新到工具栏
			if ( pFrame != NULL )
			{
				pFrame->m_bRunning = TRUE;
			}
			m_bTestBegin = FALSE;
			GetDlgItem( ID_BTN_TEST )->SetWindowText( "停止测试" );
			GetDlgItem( IDC_STATIC_STATE )->SetWindowText( "测试中..." );	
			((CStatic*)GetDlgItem( IDC_SET_PIC_STATE ))->SetBitmap( m_bmpGreen );
			// 设置定时器，用于指示灯的闪烁
			m_nCount = 0;
			SetTimer( 1, 500, NULL );

			// 设置测试模式，开始测试
			CAdcTestPlatDoc* pDoc = (CAdcTestPlatDoc*)GetDocument();
			if ( pDoc != NULL )
			{
				pDoc->SetTestMode( 1 );
			}
		}
		// 停止测试
		else
		{
			// 更新到工具栏
			if ( pFrame != NULL )
			{
				pFrame->m_bRunning = FALSE;
			}
			m_bTestBegin = TRUE;
			m_nCount = 0;
			KillTimer(1);
			GetDlgItem( ID_BTN_TEST )->SetWindowText( "开始测试" );
			GetDlgItem( IDC_STATIC_STATE )->SetWindowText( "测试停止" );
			((CStatic*)GetDlgItem( IDC_SET_PIC_STATE ))->SetBitmap( m_bmpRed );
		}
	}
	
}

void CTestSetView::OnTimer(UINT nIDEvent) 
{
	static DWORD dwLastTick, dwTickCnt;
	// TODO: Add your message handler code here and/or call default
	if ( nIDEvent == 2 )
	{
		// 用于刷新视图
		CAdcTestPlatDoc* pDoc = (CAdcTestPlatDoc*)GetDocument();
		if ( pDoc != NULL )
		{
			if ( pDoc->m_bTestComp )
			{
				// 使用this，可以避免本视图被刷新
				pDoc->UpdateAllViews( this );
			}
		}
		// 
		if ( m_bTestBegin )
		{
			KillTimer(2);
		}
	}
	else if ( nIDEvent == 1 )
	{
		m_nCount++; 
		// 闪烁
		if ( m_nCount % 2 != 0 )
		{
			((CStatic*)GetDlgItem( IDC_SET_PIC_STATE ))->SetBitmap( m_bmpBack );
		}
		else
		{
			((CStatic*)GetDlgItem( IDC_SET_PIC_STATE ))->SetBitmap( m_bmpGreen );
		}

		// 连续测试(每隔2s，触发一次测试)
		if ( m_nCount % 2 == 0 )
		{
			dwTickCnt = GetTickCount() - dwLastTick;
			TRACE("\nRefresh: %d", dwTickCnt);
			CAdcTestPlatDoc* pDoc = (CAdcTestPlatDoc*)GetDocument();
			if ( pDoc != NULL )
			{
				pDoc->SetTestMode( 1 );
			}
		}
	}
	
	dwLastTick = GetTickCount();

	

	CFormView::OnTimer(nIDEvent);
}

void CTestSetView::OnRadioBackNoise() 
{
	ChangeTestMode();
}

void CTestSetView::OnRadioChanDisturbA() 
{
	// TODO: Add your control notification handler code here
	ChangeTestMode();
}

void CTestSetView::OnRadioChanDisturbB() 
{
	// TODO: Add your control notification handler code here
	ChangeTestMode();
}

void CTestSetView::OnRadioChanDisturbC() 
{
	// TODO: Add your control notification handler code here
	ChangeTestMode();
}

void CTestSetView::OnRadioChanDisturbD() 
{
	// TODO: Add your control notification handler code here
	ChangeTestMode();
}

void CTestSetView::OnRadioPerf() 
{
	// TODO: Add your control notification handler code here
	ChangeTestMode();
}

void CTestSetView::ChangeTestMode()
{
	UpdateData( TRUE );
	CAdcTestPlatDoc* pDoc = (CAdcTestPlatDoc*)GetDocument();
	if ( pDoc != NULL )
	{
		pDoc->m_nTestModeSel = m_nTestModeSel;
		pDoc->UpdateAllViews( NULL );
	}
}

