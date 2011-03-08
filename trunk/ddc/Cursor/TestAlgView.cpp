// TestAlgView.cpp : implementation file
//

#include "stdafx.h"
#include "adctestplat.h"
#include "TestAlgView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestAlgView

IMPLEMENT_DYNCREATE(CTestAlgView, CFormView)

CTestAlgView::CTestAlgView()
	: CFormView(CTestAlgView::IDD)
{
	//{{AFX_DATA_INIT(CTestAlgView)
		// NOTE: the ClassWizard will add member initialization here	
	//}}AFX_DATA_INIT
	m_nCount = 0;
	m_bmpGreen.LoadBitmap( IDB_GREEN );
	m_bmpRed.LoadBitmap( IDB_RED );
	m_bmpBack.LoadBitmap( IDB_BACK );
	m_pParamDlg = NULL;
	// 
	m_nChanSel = 0;
	m_nChanConfigCtrl = 1;
	m_nDataOutModelSel = 1;
	m_nLvdsAck = 0;
	m_nParaSerSel = 1;
	m_nTest = 0;
	m_nDepth = MAX_DEPTH / 1024;	
	m_nM0 = 0;
	m_nStart = 0;
	m_strAPath = "";
	m_strBPath = "";
	m_strCPath = "";
	m_strDPath = "";
	memset( m_dwaAParam, 0, DMA_SIZE*sizeof(DWORD) );
	memset( m_dwaBParam, 0, DMA_SIZE*sizeof(DWORD) );
	memset( m_dwaCParam, 0, DMA_SIZE*sizeof(DWORD) );
	memset( m_dwaDParam, 0, DMA_SIZE*sizeof(DWORD) );
	m_nSampFreq = 80;
	m_nR[1] = 20;
	m_nR[2] = 20;
	m_nR[3] = 20;
	m_nR[4] = 20;
	//
	m_bTestBegin = TRUE;
	m_bIsFirstTime = TRUE;
}

CTestAlgView::~CTestAlgView()
{
}

void CTestAlgView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestAlgView)
	DDX_Control(pDX, IDC_PIC_STATE, m_imgState);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestAlgView, CFormView)
	//{{AFX_MSG_MAP(CTestAlgView)
	ON_BN_CLICKED(ID_BTN_TEST, OnBtnTest)
	ON_BN_CLICKED(ID_BTN_PARAM, OnBtnParam)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestAlgView diagnostics

#ifdef _DEBUG
void CTestAlgView::AssertValid() const
{
	CFormView::AssertValid();
}

void CTestAlgView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTestAlgView message handlers

void CTestAlgView::OnBtnTest() 
{

	CMainFrame* pFrame = (CMainFrame*)GetParentFrame();

	if ( pFrame != NULL )
	{
		CAdcTestPlatDoc* pDoc = (CAdcTestPlatDoc*)GetDocument();
//		if ( pDoc != NULL && pFrame->m_bPower == 0 && !m_bIsFirstTime )
		if ( pDoc != NULL )
		{
			pDoc->PowerOn();
		}
		pFrame->m_bPower = 1;
	}

#ifndef SELF_TEST

	// �������pcie�忨
	if ( !((CAdcTestPlatApp*)AfxGetApp())->DetectedCards() )
	{
		// ���µ�������
		if ( pFrame != NULL )
		{
			pFrame->m_bRunning = FALSE;
		}
		AfxMessageBox( "δ�ҵ�PCIE�豸!" );
		return;
	}
	else

#endif
	{
		// ����ˢ����ͼ  0.5s
		SetTimer( 2, 700, NULL );
		// �ܹ���ʼ����
		if ( m_bTestBegin )
		{
			// ���µ�������
			if ( pFrame != NULL )
			{
				pFrame->m_bRunning = TRUE;
			}
			m_bTestBegin = FALSE;
			GetDlgItem( ID_BTN_TEST )->SetWindowText( "ֹͣ����" );
			GetDlgItem( IDC_STATIC_STATE )->SetWindowText( "������..." );	
			((CStatic*)GetDlgItem( IDC_PIC_STATE ))->SetBitmap( m_bmpGreen );
			// ���ö�ʱ��������ָʾ�Ƶ���˸
			m_nCount = 0;
			SetTimer( 1, 500, NULL );
			// ���ò���ģʽ����ʼ����
			CAdcTestPlatDoc* pDoc = (CAdcTestPlatDoc*)GetDocument();
			if ( pDoc != NULL )
			{
				pDoc->SetTestMode( 3 );
			}
		}
		// ֹͣ����
		else
		{
			// ���µ�������
			if ( pFrame != NULL )
			{
				pFrame->m_bRunning = FALSE;
			}
			m_bTestBegin = TRUE;
			m_nCount = 0;
			KillTimer(1);
			GetDlgItem( ID_BTN_TEST )->SetWindowText( "��ʼ����" );
			GetDlgItem( IDC_STATIC_STATE )->SetWindowText( "����ֹͣ" );
			((CStatic*)GetDlgItem( IDC_PIC_STATE ))->SetBitmap( m_bmpRed );

/*			CAdcTestPlatDoc* pDoc = (CAdcTestPlatDoc*)GetDocument();
			if ( pDoc != NULL )
			{
				pDoc->PowerOff();
			}
			pFrame->m_bPower = 0;
*/
		}
	}
}

void CTestAlgView::SetState()
{
	// �㷨�鿴ģʽ, ���ð�ť��Ϊ��Ч
	if ( ((CMainFrame*)GetParentFrame())->m_bViewAlg )
	{
		GetDlgItem( ID_BTN_PARAM )->EnableWindow( FALSE );
		GetDlgItem( ID_BTN_TEST )->EnableWindow( FALSE );
		GetDlgItem( IDC_STATIC_STATE )->EnableWindow( FALSE );
	}
	else
	{
		GetDlgItem( ID_BTN_PARAM )->EnableWindow( TRUE );
		GetDlgItem( ID_BTN_TEST )->EnableWindow( TRUE );
		GetDlgItem( IDC_STATIC_STATE )->EnableWindow( TRUE );
	}
}

void CTestAlgView::OnDraw(CDC* pDC) 
{
	// TODO: Add your specialized code here and/or call the base class

	if (m_bIsFirstTime)
	{
		SetState();	
		// ��������Ͳ���ȥ ??
		OnBtnTest();
		OnBtnTest();

		CAdcTestPlatDoc* pDoc = (CAdcTestPlatDoc*)GetDocument();
		if ( pDoc != NULL )
		{
			pDoc->PowerOff();
		}
		CMainFrame* pFrame = (CMainFrame*)GetParentFrame();
		if ( pFrame != NULL )
		{
			pFrame->m_bPower = 0;
		}
		m_bIsFirstTime = FALSE;
	}
}

void CTestAlgView::FileSave(BYTE *pbyData, DWORD *pdwSize)
{
	// ����������
	if ( pbyData == NULL || pdwSize == NULL )
	{
		return;
	}
	// �㷨���ԵĲ�������

	*pdwSize = 0;
}

void CTestAlgView::OnBtnParam() 
{
	CMainFrame* pFrame = (CMainFrame*)GetParentFrame();
	bool bStop = FALSE;

	if ( pFrame != NULL )
	{
		if(pFrame->m_bPower == 0)
		{
			CAdcTestPlatDoc* pDoc = (CAdcTestPlatDoc*)GetDocument();
			if ( pDoc != NULL )
			{
				pDoc->PowerOn();
			}
			if ( pFrame != NULL )
			{
				pFrame->m_bPower = 1;
			}
		}

		if (pFrame->m_bRunning == TRUE)
		{
			OnBtnTest();
			bStop = TRUE;
		}
		
	}

	// ʹ�ô������Ĺ��캯��
	CParamDialog dlgParam( m_nChanSel, m_nChanConfigCtrl, m_nDataOutModelSel, 
		m_nLvdsAck, m_nParaSerSel, m_nTest, m_nDepth, m_nM0, m_nStart,
		m_strAPath, m_strBPath, m_strCPath, m_strDPath,
		m_dwaAParam, m_dwaBParam, m_dwaCParam, m_dwaDParam, m_nSampFreq, 
		m_nR/*1, m_nR2, m_nR3, m_nR4*/, this );
	if ( dlgParam.DoModal() == IDOK )
	{
		;
	}
	if (bStop)
	{
		OnBtnTest();
		bStop = FALSE;
	}
/*
	if ( m_pParamDlg != NULL )
	{
		// ����Ի����Ѿ�������ֱ�Ӽ���
		m_pParamDlg->SetActiveWindow();
		m_pParamDlg->ShowWindow( SW_SHOW );
	}
	else
	{
		m_pParamDlg = new CParamDialog( this );		
		m_pParamDlg->Create( IDD_DDC_PARAM, this );
		m_pParamDlg->ShowWindow( SW_SHOW );
	}
*/
}

void CTestAlgView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class	
	//m_imgState.SetBitmap( m_bmpBack );
}

void CTestAlgView::OnTimer(UINT nIDEvent) 
{
	static DWORD dwLastTick, dwTickCnt;

	CAdcTestPlatDoc* pDoc = (CAdcTestPlatDoc*)GetDocument();
	if ( pDoc != NULL )
	{
		// ����
		CSingleLock slDataBuf( &(pDoc->m_csDataBuf) );	
		// ����ˢ����ͼ
		if ( nIDEvent == 2 )
		{		
			if ( pDoc->m_bTestComp )
			{				
				slDataBuf.Lock();
				// ʹ��this�����Ա��Ȿ��ͼ��ˢ��
				pDoc->UpdateAllViews( this );
				TRACE("pDoc->UpdateAllViews( this );\r\n");
				slDataBuf.Unlock();
			}	
			// 
			if ( m_bTestBegin )
			{
				KillTimer(2);
			}
		}
		// ��˸�Ͳɼ�
		else
		{
			m_nCount++; 
			// ��˸
			if ( m_nCount % 2 != 0 )
			{
				((CStatic*)GetDlgItem( IDC_PIC_STATE ))->SetBitmap( m_bmpBack );
			}
			else
			{
				((CStatic*)GetDlgItem( IDC_PIC_STATE ))->SetBitmap( m_bmpGreen );
			}

			// ��������(ÿ��2s������һ�β���)
			if ( m_nCount % 2 == 0 )
			{			
				dwTickCnt = GetTickCount() - dwLastTick;
				TRACE("\nTestAlgView::Timer: %d", dwTickCnt);

				pDoc->SetTestMode( 3 );			
			}
		}
	}
	
	dwLastTick = GetTickCount();

	CFormView::OnTimer(nIDEvent);
}
