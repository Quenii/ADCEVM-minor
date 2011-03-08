// TestSetBatchView.cpp : implementation file
//

#include "stdafx.h"
#include "adctestplat.h"
#include "TestSetBatchView.h"
#include "PromptDlg.h"
#include "ParamDialog.h"
#include "Shlwapi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include <math.h>

// ��û��Ӳ���豸������´򿪴˿������ڵ���
//#define SELF_TEST

// Ĭ�ϵ�ַ
DWORD g_dwAddr[ADDR_PARAM_SIZE] = {
	0x00,
	0x01,
	0x10,
	0x11,
	0x12,
	0x13,
	0x20,
	0x30,
	0x31,
	0x32,
	0x33,
	0x40,
	0x50,
	0x51,
	0x52,
	0x53,
	0x54,
	0x55,
	0x56,
	0x57,
	0x58,
	0x59,
	0x5A,
	0x5B,
	0x5C,
	0x5D,
	0x5E,
	0x5F,
	0x60,
	0x61,
	0x62,
	0x63,
	0x64,
	0x65,
	0x66,
	0x67,
	0x68,
	0x69,
	0x6A,
	0x6B,
	0x6C,
	0x6D,
	0x6E,
	0x6F,
	0x70,
	0x71,
	0x72,
	0x73
};


// �����ԵĶ�ʱ������(ms)
#define TIMER_PERIOD 500
// �����Խ���һ����Ҫ��ʱ��(s)
#define BATCH_PERIOD 3
/////////////////////////////////////////////////////////////////////////////
// CTestSetBatchView

IMPLEMENT_DYNCREATE(CTestSetBatchView, CFormView)

CTestSetBatchView::CTestSetBatchView()
	: CFormView(CTestSetBatchView::IDD)
{
	//{{AFX_DATA_INIT(CTestSetBatchView)
	m_strID = _T("");
	m_strBackNoise = _T("0");
	m_strSNR = _T("0");
	m_strSFDR = _T("0");
	m_strChanDisturb = _T("0");
	m_strSINAD = _T("0");
	m_strPassCount = _T("0");
	m_strErrorCount = _T("0");
	m_bTestBegin = TRUE;
	m_nPassCount = 0;
	m_nErrorCount = 0;
	//}}AFX_DATA_INIT
	m_nCount = 0;
	m_bmpGreen.LoadBitmap( IDB_GREEN );
	m_bmpRed.LoadBitmap( IDB_RED );
	m_bmpBack.LoadBitmap( IDB_BACK );
	m_bmpCross.LoadBitmap( IDB_CROSS );
	m_bmpOk.LoadBitmap( IDB_OK );
//	OnInitialUpdate();
	m_bFirst = TRUE;
	// �����������ԵĲ�������
	m_pParamDlg = NULL;
	m_str2MFileName = "param_2m.dat";
	m_str5MFileName = "param_5m.dat";
	m_str20MFileName = "param_20m.dat";
	memset( m_byaResult, 0, TEST_ITEM );
}

CTestSetBatchView::~CTestSetBatchView()
{
	if ( m_pParamDlg != NULL )
	{
		delete m_pParamDlg;
	}
}

void CTestSetBatchView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestSetBatchView)
	DDX_Control(pDX, IDC_STATIC_REG_TEST2, m_stcRegTest2);
	DDX_Control(pDX, IDC_STATIC_REG_TEST, m_stcRegTest);
	DDX_Control(pDX, IDC_STATIC_M0_TEST2, m_stcM0Test2);
	DDX_Control(pDX, IDC_STATIC_M0_TEST, m_stcM0Test);
	DDX_Control(pDX, IDC_STATIC_ADC_TEST2, m_stcAdcTest2);
	DDX_Control(pDX, IDC_STATIC_ADC_TEST, m_stcAdcTest);
	DDX_Control(pDX, IDC_STATIC_5M_TEST2, m_stc5MTest2);
	DDX_Control(pDX, IDC_STATIC_5M_TEST, m_stc5MTest);
	DDX_Control(pDX, IDC_STATIC_2M_TEST2, m_stc2MTest2);
	DDX_Control(pDX, IDC_STATIC_2M_TEST, m_stc2MTest);
	DDX_Control(pDX, IDC_STATIC_20M_TEST2, m_stc20MTest2);
	DDX_Control(pDX, IDC_STATIC_20M_TEST, m_stc20MTest);
	DDX_Text(pDX, IDC_EDIT_ID, m_strID);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestSetBatchView, CFormView)
	//{{AFX_MSG_MAP(CTestSetBatchView)
	ON_BN_CLICKED(ID_BTN_TEST, OnBtnTest)
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(ID_BTN_RETRY, OnBtnRetry)
	ON_BN_CLICKED(IDC_CHECK_CHAN_DISTURB2, OnCheckChanDisturb2)
	ON_BN_CLICKED(IDC_CHECK_LOW_NOISE2, OnCheckLowNoise2)
	ON_BN_CLICKED(IDC_CHECK_SFDR2, OnCheckSfdr2)
	ON_BN_CLICKED(IDC_CHECK_SINAD2, OnCheckSinad2)
	ON_BN_CLICKED(IDC_CHECK_SNR2, OnCheckSnr2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestSetBatchView diagnostics

#ifdef _DEBUG
void CTestSetBatchView::AssertValid() const
{
	CFormView::AssertValid();
}

void CTestSetBatchView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTestSetBatchView message handlers

void CTestSetBatchView::OnDraw(CDC* pDC) 
{
	// TODO: Add your specialized code here and/or call the base class	
	SetState();
}

void CTestSetBatchView::OnBtnTest() 
{
	CMainFrame* pFrame = (CMainFrame*)GetParentFrame();

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
		
		// �ܹ���ʼ����
		if ( m_bTestBegin )
		{			
			
			// ��ȡ�ؼ�����
			UpdateData( TRUE );
			// ��·ID���
			if ( m_strID.GetLength() == 0 )
			{
				AfxMessageBox( "��������оƬ����(8λ����),���ܿ�ʼ����!" );
				GetDlgItem( IDC_EDIT_ID )->SetFocus();
				//m_bTestBegin = !m_bTestBegin;
				// ���µ�������
				if ( pFrame != NULL )
				{
					pFrame->m_bRunning = FALSE;
				}
				return;
			}
			else if ( m_strID.GetLength() != 8 )
			{
				AfxMessageBox( "оƬ����Ϊ8λ����!" );
				//GetDlgItem( IDC_EDIT_ID )->SetWindowText( "" );
				GetDlgItem( IDC_EDIT_ID )->SetFocus();
				//m_bTestBegin = !m_bTestBegin;
				// ���µ�������
				if ( pFrame != NULL )
				{
					pFrame->m_bRunning = FALSE;
				}
				return;
			}
			// ���������ͬID���ļ�����
			CString strFileName = m_strID + ".atp";
			if ( SearchFile( strFileName ) )
			{
				int nRet = AfxMessageBox( "��оƬ�����Ѿ����Թ�,�Ƿ񸲸�?", 
					MB_YESNO | MB_ICONQUESTION );
				// ��������Ҫ�û���������
				if ( nRet == IDNO )
				{
					//GetDlgItem( IDC_EDIT_ID )->SetWindowText( "" );
					GetDlgItem( IDC_EDIT_ID )->SetFocus();
					//m_bTestBegin = !m_bTestBegin;
					// ���µ�������
					if ( pFrame != NULL )
					{
						pFrame->m_bRunning = FALSE;
					}
					return;
				}
			}
			
			// �����ļ���
			m_strCurFileName = strFileName;
			// ���µ�������
			if ( pFrame != NULL )
			{
				pFrame->m_bRunning = TRUE;
			}
			// ״̬�ı�
			m_bTestBegin = FALSE;
			GetDlgItem( ID_BTN_TEST )->SetWindowText( "����ֹͣ" );
			InitStaticColor();			
			// ����ˢ����ͼ
			SetTimer( 2, 500, NULL );
			// ��������
			CAdcTestPlatDoc* pDoc = (CAdcTestPlatDoc*)GetDocument();
			if ( pDoc != NULL )
			{
				//  ���Կ�ʼʱ�Զ��ϵ�
				pDoc->PowerOn();
				Sleep(400);
			}

			DoTestBatch();

		}
		else
		{
			// ���Թ����е�����Խ������ر��Ѿ��򿪵Ĵ���
			if ( m_pJudgeDlgBack != NULL )
			{
				m_pJudgeDlgBack->SendMessage( WM_CLOSE );
			}
			// ���µ�������
			if ( pFrame != NULL )
			{
				pFrame->m_bRunning = FALSE;
			}
			// ״̬�ı�
			m_bTestBegin = TRUE;
			GetDlgItem( ID_BTN_TEST )->SetWindowText( "���Կ�ʼ" );
			// ����ֹͣ���رն�ʱ��
			KillTimer( 1 );

		}
	}	
}

void CTestSetBatchView::SetState()
{
	/*
	CAdcTestPlatDoc* pDoc = (CAdcTestPlatDoc*)GetDocument();
	if ( pDoc != NULL )
	{
		// ���ø�ѡ��״̬
		if ( pDoc->m_bTestBackNoise )
		{
			((CButton*)GetDlgItem( IDC_CHECK_LOW_NOISE2 ))->SetCheck(1);
		}
		else
		{
			((CButton*)GetDlgItem( IDC_CHECK_LOW_NOISE2 ))->SetCheck(0);
		}
		if ( pDoc->m_bTestSNR )
		{
			((CButton*)GetDlgItem( IDC_CHECK_SNR2 ))->SetCheck(1);
		}
		else
		{
			((CButton*)GetDlgItem( IDC_CHECK_SNR2 ))->SetCheck(0);
		}
		if ( pDoc->m_bTestSFDR )
		{
			((CButton*)GetDlgItem( IDC_CHECK_SFDR2 ))->SetCheck(1);
		}
		else
		{
			((CButton*)GetDlgItem( IDC_CHECK_SFDR2 ))->SetCheck(0);
		}
		if ( pDoc->m_bTestChanDisturb )
		{
			((CButton*)GetDlgItem( IDC_CHECK_CHAN_DISTURB2 ))->SetCheck(1);
		}
		else
		{
			((CButton*)GetDlgItem( IDC_CHECK_CHAN_DISTURB2 ))->SetCheck(0);
		}
		if ( pDoc->m_bTestSINAD )
		{
			((CButton*)GetDlgItem( IDC_CHECK_SINAD2 ))->SetCheck(1);
		}
		else
		{
			((CButton*)GetDlgItem( IDC_CHECK_SINAD2 ))->SetCheck(0);
		}
	}
	*/
	/*
	// ADC�鿴ģʽ�����ð�ť������Ϊ��Ч
	if ( ((CMainFrame*)GetParentFrame())->m_bViewADCBatch )
	{
		GetDlgItem( IDC_EDIT_LOW_NOISE )->EnableWindow( FALSE );
		GetDlgItem( IDC_EDIT_SNR )->EnableWindow( FALSE );
		GetDlgItem( IDC_EDIT_SFDR )->EnableWindow( FALSE );
		GetDlgItem( IDC_EDIT_CHAN_DISTURB )->EnableWindow( FALSE );
		GetDlgItem( IDC_EDIT_SINAD )->EnableWindow( FALSE );
		GetDlgItem( IDC_EDIT_ID )->EnableWindow( FALSE );
		GetDlgItem( IDC_EDIT_PASS_COUNT )->EnableWindow( FALSE );
		GetDlgItem( IDC_EDIT_ERROR_COUNT )->EnableWindow( FALSE );
		GetDlgItem( ID_BTN_TEST )->EnableWindow( FALSE );
		GetDlgItem( ID_BTN_RETRY )->EnableWindow( FALSE );
		GetDlgItem( IDC_CHECK_LOW_NOISE2 )->EnableWindow( FALSE );
		GetDlgItem( IDC_CHECK_SNR2 )->EnableWindow( FALSE );
		GetDlgItem( IDC_CHECK_SINAD2 )->EnableWindow( FALSE );
		GetDlgItem( IDC_CHECK_CHAN_DISTURB2 )->EnableWindow( FALSE );
		GetDlgItem( IDC_CHECK_SFDR2 )->EnableWindow( FALSE );
	}
	else
	{
		GetDlgItem( IDC_EDIT_LOW_NOISE )->EnableWindow( TRUE );
		GetDlgItem( IDC_EDIT_SNR )->EnableWindow( TRUE );
		GetDlgItem( IDC_EDIT_SFDR )->EnableWindow( TRUE );
		GetDlgItem( IDC_EDIT_CHAN_DISTURB )->EnableWindow( TRUE );
		GetDlgItem( IDC_EDIT_SINAD )->EnableWindow( TRUE );
		GetDlgItem( IDC_EDIT_ID )->EnableWindow( TRUE );
		GetDlgItem( IDC_EDIT_PASS_COUNT )->EnableWindow( TRUE );
		GetDlgItem( IDC_EDIT_ERROR_COUNT )->EnableWindow( TRUE );
		GetDlgItem( ID_BTN_TEST )->EnableWindow( TRUE );
		GetDlgItem( ID_BTN_RETRY )->EnableWindow( TRUE );
		GetDlgItem( IDC_CHECK_LOW_NOISE2 )->EnableWindow( TRUE );
		GetDlgItem( IDC_CHECK_SNR2 )->EnableWindow( TRUE );
		GetDlgItem( IDC_CHECK_SINAD2 )->EnableWindow( TRUE );
		GetDlgItem( IDC_CHECK_CHAN_DISTURB2 )->EnableWindow( TRUE );
		GetDlgItem( IDC_CHECK_SFDR2 )->EnableWindow( TRUE );
	}
	*/
	// ADC�鿴ģʽ�����ð�ť������Ϊ��Ч
	if ( ((CMainFrame*)GetParentFrame())->m_bViewADCBatch )
	{		
		GetDlgItem( IDC_EDIT_ID )->EnableWindow( FALSE );
		GetDlgItem( ID_BTN_TEST )->EnableWindow( FALSE );
	}
	else
	{
		GetDlgItem( IDC_EDIT_ID )->EnableWindow( TRUE );
		GetDlgItem( ID_BTN_TEST )->EnableWindow( TRUE );
	}
}

void CTestSetBatchView::FileSave(BYTE *pbyData, DWORD *pdwSize)
{
	// ����������
	if ( pbyData == NULL || pdwSize == NULL )
	{
		return;
	}
	/*
	// ADC�������ԵĲ�������32B	
	UpdateData( TRUE );
	*(DWORD*)(pbyData+0) = atoi( m_strBackNoise );
	*(DWORD*)(pbyData+4) = atoi( m_strSNR );
	*(DWORD*)(pbyData+8) = atoi( m_strSFDR );
	*(DWORD*)(pbyData+12) = atoi( m_strChanDisturb );
	*(DWORD*)(pbyData+16) = atoi( m_strSINAD );
	*(DWORD*)(pbyData+20) = atoi( m_strID );
	*(DWORD*)(pbyData+24) = atoi( m_strPassCount );
	*(DWORD*)(pbyData+28) = atoi( m_strErrorCount );
	*pdwSize = 32;
	*/
	memcpy( pbyData, m_byaResult, TEST_ITEM );
	*pdwSize = 6;
}

void CTestSetBatchView::FileOpen(BYTE *pbyData)
{
	// ������
	if ( pbyData == NULL )
	{
		return;
	}
	/*
	// ADC�������ԵĲ�������32B	
	m_strBackNoise.Format( "%d", *(DWORD*)(pbyData+0) );
	m_strSNR.Format( "%d", *(DWORD*)(pbyData+4) );
	m_strSFDR.Format( "%d", *(DWORD*)(pbyData+8) );
	m_strChanDisturb.Format( "%d", *(DWORD*)(pbyData+12) );
	m_strSINAD.Format( "%d", *(DWORD*)(pbyData+16) );
	m_strID.Format( "%d", *(DWORD*)(pbyData+20) );
	m_strPassCount.Format( "%d", *(DWORD*)(pbyData+24) );
	m_strErrorCount.Format( "%d", *(DWORD*)(pbyData+28) );
	*/
	memcpy( m_byaResult, pbyData, TEST_ITEM );
	for ( int i = 0; i < TEST_ITEM; i++ )
	{
		SetStaticColor( i, m_byaResult[i][0] );
	}
	UpdateData( FALSE );
}

BOOL CTestSetBatchView::SearchFile(CString strFileName)
{
	CFileFind finder;
	CString strTempFileName;

	BOOL bWorking = finder.FindFile("*.*");
	while ( bWorking )
	{
		bWorking = finder.FindNextFile();
		strTempFileName = finder.GetFileName();
		// ���ҵ��ļ�����ͬ�ķ���true, ���򷵻�false
		if ( strTempFileName.Compare( strFileName ) == 0 )
		{
			return TRUE;
		}
	}
	return FALSE;
}

void CTestSetBatchView::OnTimer(UINT nIDEvent) 
{
	/*
	// ��ʱ��1��������˸
	if ( nIDEvent == 1 )
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
		// ��ѯ��һ����·ID�������(ĿǰΪ�̶�3s)�����Զ������ļ�
		if ( m_nCount % ( BATCH_PERIOD * 1000 / TIMER_PERIOD ) == 0 )
		{
			((CMainFrame*)GetParentFrame())->FileSave( m_strCurFileName );
			// �ļ�����ԭ����·ID����������1
			UpdateData( TRUE );
			m_strID.Format( "%08d", atoi(m_strID) + 1 );
			m_strCurFileName = m_strID + ".atp";
			UpdateData( FALSE );
			// ��ʼ��һ����������
			CAdcTestPlatDoc* pDoc = (CAdcTestPlatDoc*)GetDocument();
			if ( pDoc != NULL )
			{
				pDoc->SetTestMode(2);
			}	
		}
	}
	*/
	/*
	// ��ʱ��2��ʱ2s��Ϊ�����Ѿ��ɼ�����������
	if ( nIDEvent == 2 )
	{
		((CMainFrame*)GetParentFrame())->FileSave( m_strCurFileName );
		KillTimer( 2 );
		GetDlgItem( ID_BTN_TEST )->SetWindowText( "���Կ�ʼ" );		
		((CStatic*)GetDlgItem( IDC_PIC_STATE ))->SetBitmap( m_bmpRed );
		m_nCount = 0;
	}
	*/
	
	// ��ʱ��1����������βɼ�
	if ( nIDEvent == 1 )
	{
		CAdcTestPlatDoc* pDoc = (CAdcTestPlatDoc*)GetDocument();
		if ( pDoc != NULL )
		{
			// �ϴεĲɼ���ɺ󣬿��Խ������̣߳��ɼ��ͼ���
			if ( pDoc->m_bTestComp )
			{			
				// �ڶ�������������doc����ֱ��ʹ��this, �м�
				AfxBeginThread( pDoc->TestAndCalc, pDoc );
			}
		}
	}
	// ��ʱ��2����ˢ����ͼ
	if ( nIDEvent == 2 )
	{		
		CAdcTestPlatDoc* pDoc = (CAdcTestPlatDoc*)GetDocument();
		if ( pDoc != NULL )
		{
			// ����
			CSingleLock slDataBuf( &(pDoc->m_csDataBuf) );
			if ( pDoc->m_bTestComp )
			{				
				slDataBuf.Lock();
				// ʹ��this�����Ա��Ȿ��ͼ��ˢ��
				pDoc->UpdateAllViews( this );
				slDataBuf.Unlock();
			}	
			// 
			if ( m_bTestBegin )
			{
				KillTimer(2);
			}
		}
		
	}

	CFormView::OnTimer(nIDEvent);
}

void CTestSetBatchView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{	
	// ��ʼ����ǰ�����԰�ť��Ч
	//GetDlgItem( ID_BTN_RETRY )->EnableWindow( FALSE );
	
	// ֻ�ܳ�ʼ��һ��
	if ( m_bFirst )
	{
		m_bFirst = FALSE;
		OnInitialUpdate();
	}
	
	return;	
}

void CTestSetBatchView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CFormView::OnMouseMove(nFlags, point);
}


// ����
void CTestSetBatchView::OnBtnRetry() 
{
	// ��ǰ������ֹͣ
	KillTimer( 1 );
	// ��ȡ�ؼ�����
	UpdateData( TRUE );
	// ��·ID���
	if ( m_strID.GetLength() == 0 )
	{
		AfxMessageBox( "���������·ID(8λ����),���ܿ�ʼ����!" );
		GetDlgItem( IDC_EDIT_ID )->SetFocus();		
		return;
	}
	else if ( m_strID.GetLength() != 8 )
	{
		AfxMessageBox( "��·IDΪ8λ����!" );
		GetDlgItem( IDC_EDIT_ID )->SetWindowText( "" );
		GetDlgItem( IDC_EDIT_ID )->SetFocus();		
		return;
	}	
	
	// �ɼ�����
	CAdcTestPlatDoc* pDoc = (CAdcTestPlatDoc*)GetDocument();
	if ( pDoc != NULL )
	{
		pDoc->SetTestMode(2);
	}
	// ���ö�ʱ��2
	SetTimer( 2, 2000, NULL );
}

void CTestSetBatchView::OnInitialUpdate() 
{
	// ͨ������������԰ѿؼ��Ͷ�Ӧ����������ϵ����������
	CFormView::OnInitialUpdate();
	
	// ��ʼ����ǰ�����԰�ť��Ч
	//GetDlgItem( ID_BTN_RETRY )->EnableWindow( FALSE );
	
	//m_stcRegTest2.SetTextColor( RGB(0,0,0) );
	
	//SetState();

	// ��ʼ�����������õĲ�������
	m_pParamDlg = new CParamDialog();
	m_pJudgeDlgBack = NULL;
}

void CTestSetBatchView::OnCheckChanDisturb2() 
{	
	CAdcTestPlatDoc* pDoc = (CAdcTestPlatDoc*)GetDocument();
	if ( pDoc != NULL )
	{
		CButton* pCheck = (CButton*)GetDlgItem( IDC_CHECK_CHAN_DISTURB2 );
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

void CTestSetBatchView::OnCheckLowNoise2() 
{
	CAdcTestPlatDoc* pDoc = (CAdcTestPlatDoc*)GetDocument();
	if ( pDoc != NULL )
	{
		CButton* pCheck = (CButton*)GetDlgItem( IDC_CHECK_LOW_NOISE2 );
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

void CTestSetBatchView::OnCheckSfdr2() 
{	
	CAdcTestPlatDoc* pDoc = (CAdcTestPlatDoc*)GetDocument();
	if ( pDoc != NULL )
	{
		CButton* pCheck = (CButton*)GetDlgItem( IDC_CHECK_SFDR2 );
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

void CTestSetBatchView::OnCheckSinad2() 
{
	CAdcTestPlatDoc* pDoc = (CAdcTestPlatDoc*)GetDocument();
	if ( pDoc != NULL )
	{
		CButton* pCheck = (CButton*)GetDlgItem( IDC_CHECK_SINAD2 );
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

void CTestSetBatchView::OnCheckSnr2() 
{
	CAdcTestPlatDoc* pDoc = (CAdcTestPlatDoc*)GetDocument();
	if ( pDoc != NULL )
	{
		CButton* pCheck = (CButton*)GetDlgItem( IDC_CHECK_SNR2 );
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

void CTestSetBatchView::DoTestBatch( void )
{
//	int iRegResult[4];
	BOOL bRet;
	CString strMsg;

	CAdcTestPlatDoc* pDoc = (CAdcTestPlatDoc*)GetDocument();
	if ( pDoc != NULL )
	{
		//  ���Կ�ʼʱ�Զ��ϵ�
		pDoc->PowerOn();
		Sleep(400);


		SetStaticColor( 0, 0 );
		// �Ĵ�������
/*@@@*/
		bRet = TestReg(m_byaResult[0]);
		if ( bRet )
		{
			strMsg = "�Ĵ���������ȷ!";
			SetStaticColor( 0, 1 );
		}
		else
		{
			strMsg = "�Ĵ������Դ���!";
			SetStaticColor( 0, 2 );
		}
		
		
		//AfxMessageBox( strMsg, MB_YESNOCANCEL );
		CPromptDlg dlgPrompt( strMsg, 0, "������һ��", this, NULL );
		dlgPrompt.DoModal();
		//SetStaticColor( 1, 0 );

		// ���Խ������Զ��ϵ�
		//pDoc->PowerOff();
	}
	
}

void CTestSetBatchView::SetStaticColor(int nIndex, int nType)
{
	switch ( nIndex )
	{
		case 0:
		{
			m_stcRegTest.SetTextColor( RGB(0,0,255) );
			if ( nType == 0 )
			{
				m_stcRegTest2.SetWindowText( "δ����" );
				m_stcRegTest2.SetTextColor( RGB(0,0,0) );
			}
			else if ( nType == 1 )
			{
				m_stcRegTest2.SetWindowText( "��ȷ" );
				m_stcRegTest2.SetTextColor( RGB(0,0,255) );
			}
			else if ( nType == 2 )
			{
				m_stcRegTest2.SetWindowText( "����" );
				m_stcRegTest2.SetTextColor( RGB(255,0,0) );
			}
			break;
		}
		case 1:
		{
			m_stcAdcTest.SetTextColor( RGB(0,0,255) );
			if ( nType == 0 )
			{
				m_stcAdcTest2.SetWindowText( "δ����" );
				m_stcAdcTest2.SetTextColor( RGB(0,0,0) );
			}
			else if ( nType == 1 )
			{
				m_stcAdcTest2.SetWindowText( "���" );
				m_stcAdcTest2.SetTextColor( RGB(0,0,255) );
			}
			else if ( nType == 2 )
			{
				m_stcAdcTest2.SetWindowText( "����" );
				m_stcAdcTest2.SetTextColor( RGB(255,0,0) );
			}
			break;
		}
		case 2:
		{
			m_stc2MTest.SetTextColor( RGB(0,0,255) );
			if ( nType == 0 )
			{
				m_stc2MTest2.SetWindowText( "δ����" );
				m_stc2MTest2.SetTextColor( RGB(0,0,0) );
			}
			else if ( nType == 1 )
			{
				m_stc2MTest2.SetWindowText( "���" );
				m_stc2MTest2.SetTextColor( RGB(0,0,255) );
			}
			else if ( nType == 2 )
			{
				m_stc2MTest2.SetWindowText( "����" );
				m_stc2MTest2.SetTextColor( RGB(255,0,0) );
			}
			break;
		}
		case 3:
		{
			m_stcM0Test.SetTextColor( RGB(0,0,255) );
			if ( nType == 0 )
			{
				m_stcM0Test2.SetWindowText( "δ����" );
				m_stcM0Test2.SetTextColor( RGB(0,0,0) );
			}
			else if ( nType == 1 )
			{
				m_stcM0Test2.SetWindowText( "���" );
				m_stcM0Test2.SetTextColor( RGB(0,0,255) );
			}
			else if ( nType == 2 )
			{
				m_stcM0Test2.SetWindowText( "����" );
				m_stcM0Test2.SetTextColor( RGB(255,0,0) );
			}
			break;
		}
		case 4:
		{
			m_stc5MTest.SetTextColor( RGB(0,0,255) );
			if ( nType == 0 )
			{
				m_stc5MTest2.SetWindowText( "δ����" );
				m_stc5MTest2.SetTextColor( RGB(0,0,0) );
			}
			else if ( nType == 1 )
			{
				m_stc5MTest2.SetWindowText( "���" );
				m_stc5MTest2.SetTextColor( RGB(0,0,255) );
			}
			else if ( nType == 2 )
			{
				m_stc5MTest2.SetWindowText( "����" );
				m_stc5MTest2.SetTextColor( RGB(255,0,0) );
			}
			break;
		}
		case 5:
		{
			m_stc20MTest.SetTextColor( RGB(0,0,255) );
			if ( nType == 0 )
			{
				m_stc20MTest2.SetWindowText( "δ����" );
				m_stc20MTest2.SetTextColor( RGB(0,0,0) );
			}
			else if ( nType == 1 )
			{
				m_stc20MTest2.SetWindowText( "���" );
				m_stc20MTest2.SetTextColor( RGB(0,0,255) );
			}
			else if ( nType == 2 )
			{
				m_stc20MTest2.SetWindowText( "����" );
				m_stc20MTest2.SetTextColor( RGB(255,0,0) );
			}
			break;
		}
		default:
			break;
	}
}

BOOL CTestSetBatchView::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	//OnInitialUpdate();

	return CFormView::PreCreateWindow(cs);
}

void CTestSetBatchView::InitStaticColor()
{
	m_stcRegTest.SetTextColor( RGB(0,0,0) );			
	m_stcRegTest2.SetWindowText( "δ����" );
	m_stcRegTest2.SetTextColor( RGB(0,0,0) );

	m_stcAdcTest.SetTextColor( RGB(0,0,0) );			
	m_stcAdcTest2.SetWindowText( "δ����" );
	m_stcAdcTest2.SetTextColor( RGB(0,0,0) );

	m_stc2MTest.SetTextColor( RGB(0,0,0) );			
	m_stc2MTest2.SetWindowText( "δ����" );
	m_stc2MTest2.SetTextColor( RGB(0,0,0) );

	m_stcM0Test.SetTextColor( RGB(0,0,0) );			
	m_stcM0Test2.SetWindowText( "δ����" );
	m_stcM0Test2.SetTextColor( RGB(0,0,0) );

	m_stc5MTest.SetTextColor( RGB(0,0,0) );			
	m_stc5MTest2.SetWindowText( "δ����" );
	m_stc5MTest2.SetTextColor( RGB(0,0,0) );

	m_stc20MTest.SetTextColor( RGB(0,0,0) );			
	m_stc20MTest2.SetWindowText( "δ����" );
	m_stc20MTest2.SetTextColor( RGB(0,0,0) );
}

BOOL CTestSetBatchView::TestReg(BYTE iRegResult[4])
{
#define REG_DATA 0x5A5A

	BOOL bRet;
	DWORD* pdwData;

	pdwData = NULL;
	bRet = TRUE;

	if ( m_pParamDlg == NULL )
	{
		bRet = FALSE;
		return bRet;
	}

// 	CAdcTestPlatDoc* pDoc = (CAdcTestPlatDoc*)GetDocument();
// 	DWORD dwCmd = (CMD_RESET << 16); 
// 	pDoc->SendCommand( dwCmd );

	// ����֮ǰ�Ȱѵ�ַ����
	for ( int i = 0; i < ADDR_PARAM_SIZE; i++ )
	{
		m_pParamDlg->m_dwaAAddr[i] = g_dwAddr[i];
		m_pParamDlg->m_dwaBAddr[i] = g_dwAddr[i]+0x100;
		m_pParamDlg->m_dwaCAddr[i] = g_dwAddr[i]+0x200;
		m_pParamDlg->m_dwaDAddr[i] = g_dwAddr[i]+0x300;
	}
	// 4��ͨ�����η��ͺͻض�
	if ( m_pParamDlg != NULL )
	{
		for ( int i = 0; i < 4; i++ )
		{
			iRegResult[i] = 1;
			switch ( i )
			{
				case 0:
				{
					pdwData = m_pParamDlg->m_dwaAParam;
					break;
				}
				case 1:
				{
					pdwData = m_pParamDlg->m_dwaBParam;
					break;
				}
				case 2:
				{
					pdwData = m_pParamDlg->m_dwaCParam;
					break;
				}
				case 3:
				{
					pdwData = m_pParamDlg->m_dwaDParam;
					break;
				}
				default:
				{
					pdwData = m_pParamDlg->m_dwaAParam;
					break;
				}
			}
			//memset( pdwData, REG_DATA, DMA_SIZE * sizeof( DWORD ) );
			int aa= 0x5555;
			for ( int j = 0; j < ADDR_PARAM_SIZE; j++ )
			{
				pdwData[j] = j;
			}
			// д�Ĵ���
			m_pParamDlg->SendByChannel( i );
			// �ض�ǰ����ջ���������ֹ�жϴ���
			memset( pdwData, 0, DMA_SIZE * sizeof( DWORD ) );
			// ���Ĵ���
			m_pParamDlg->ReadByChannel( i );
			// �ж�
			for ( j = 0; j < ADDR_PARAM_SIZE; j++ )
			{
				//if (  pdwData[j] != REG_DATA )
				if (  pdwData[j] != j )
				{
					bRet = FALSE;
					iRegResult[i] = 2;
					break;
				}
			}
			// ���ĳ��ͨ������δͨ��, �˳�
//			if ( !bRet )
//			{
//				break;
//			}
		}
	}
	
	return bRet; 
}

void CTestSetBatchView::TestAdc()
{

	CAdcTestPlatDoc* pDoc = (CAdcTestPlatDoc*)GetDocument();
	if ( pDoc != NULL )
	{				
		DWORD dwCmd = (CMD_RESET << 16); 
		pDoc->SendCommand( dwCmd );

		// rֵ������
		SetR( 1 );
		// ����adc��ʾ
		CMainFrame* pFrame = (CMainFrame*)GetParentFrame();
		if ( pFrame != NULL )
		{
			pFrame->m_bTestADCBatch = TRUE;
			pFrame->m_bTestADC = TRUE;
			pFrame->m_bTestAlg = FALSE;
		}
		pDoc->SetTestMode(1);
		// �򿪶�ʱ��1, ÿ��2s�ɼ�һ��
		SetTimer( 1, 2000, NULL );
	}
}

// 2M�������
void CTestSetBatchView::Test2M()
{

	CAdcTestPlatDoc* pDoc = (CAdcTestPlatDoc*)GetDocument();


	if ( pDoc != NULL )
	{				
		
		DWORD dwCmd = (CMD_RESET << 16); 
		pDoc->SendCommand( dwCmd ); 
		
		dwCmd = (CMD_MODE << 16) 
				+ (0 << 8) //m_nStart
				+ (0 << 6) //m_nM0
				+ (1 << 5) //m_nChanConfigCtrl  
				+ (0 << 4) //m_nDataOutModelSel  lvds
				+ (1 << 3) //m_nParaSerSel
				+ (1 << 1) //m_nLvdsAck
				+ 0; //m_nTest
		pDoc->SendCommand( dwCmd ); 

		// �Զ����������ļ�param_2m.dat, ?????
		LoadParamFile( m_str2MFileName );
/*		// ��Ҫȷ������Ĳ��� ?? 
		DWORD dwCmd = (CMD_MODE << 16) + 0;
		pDoc->SendCommand( dwCmd );
*/

	
		dwCmd = (CMD_MODE << 16) 
				+ (1 << 8) //m_nStart
				+ (1 << 6) //m_nM0
				+ (1 << 5) //m_nChanConfigCtrl  
				+ (0 << 4) //m_nDataOutModelSel  lvds
				+ (1 << 3) //m_nParaSerSel
				+ (1 << 1) //m_nLvdsAck
				+ 0; //m_nTest
		pDoc->SendCommand( dwCmd ); 
		// rֵ������
		SetR( 20 );

		// ����alg��ʾ
		CMainFrame* pFrame = (CMainFrame*)GetParentFrame();
		if ( pFrame != NULL )
		{
			pFrame->m_bTestADCBatch = TRUE;
			pFrame->m_bTestADC = FALSE;
			pFrame->m_bTestAlg = TRUE;
		}

		// ѡ��algģʽ
		pDoc->m_nTestModeSel = 6;
		// �ϴεĲɼ���ɺ󣬿��Խ������̣߳��ɼ��ͼ���
		if ( pDoc->m_bTestComp )
		{			
			// �ڶ�������������doc����ֱ��ʹ��this, �м�
			AfxBeginThread( pDoc->TestAndCalc, pDoc );
		}
		// �򿪶�ʱ��1, ÿ��2s�ɼ�һ��
		SetTimer( 1, 2000, NULL );
		//pDoc->SetTestMode( 3 );
	}
}

void CTestSetBatchView::TestM0()
{

	CAdcTestPlatDoc* pDoc = (CAdcTestPlatDoc*)GetDocument();
	if ( pDoc != NULL )
	{				
		DWORD dwCmd = (CMD_RESET << 16); 
		pDoc->SendCommand( dwCmd );

		// M0������Ϊauto 
		dwCmd = (CMD_MODE << 16) + ( 2<<6 );
		pDoc->SendCommand( dwCmd );
		// M0����Ϊ1, start����Ϊauto 
		dwCmd = (CMD_MODE << 16) + ( 2<<8 ) + ( 1<<6 ) ;
		pDoc->SendCommand( dwCmd );

		// ����alg��ʾ
		CMainFrame* pFrame = (CMainFrame*)GetParentFrame();
		if ( pFrame != NULL )
		{
			pFrame->m_bTestADCBatch = TRUE;
			pFrame->m_bTestADC = FALSE;
			pFrame->m_bTestAlg = TRUE;
		}
		
		// ѡ��algģʽ
		pDoc->m_nTestModeSel = 6;
		// �ϴεĲɼ���ɺ󣬿��Խ������̣߳��ɼ��ͼ���
		if ( pDoc->m_bTestComp )
		{			
			// �ڶ�������������doc����ֱ��ʹ��this, �м�
			AfxBeginThread( pDoc->TestAndCalc, pDoc );
		}
		// �򿪶�ʱ��1, ÿ��2s�ɼ�һ��
		SetTimer( 1, 2000, NULL );
	}
}

void CTestSetBatchView::Test5M()
{

	CAdcTestPlatDoc* pDoc = (CAdcTestPlatDoc*)GetDocument();
	if ( pDoc != NULL )
	{				
		DWORD dwCmd = (CMD_RESET << 16); 
		pDoc->SendCommand( dwCmd );

		// ��Ҫȷ������Ĳ��� ?? 
		dwCmd = (CMD_MODE << 16) 
				+ (0 << 8) //m_nStart
				+ (0 << 6) //m_nM0
				+ (1 << 5) //m_nChanConfigCtrl  
				+ (0 << 4) //m_nDataOutModelSel  lvds
				+ (1 << 3) //m_nParaSerSel
				+ (1 << 1) //m_nLvdsAck
				+ 0; //m_nTest
		pDoc->SendCommand( dwCmd ); 
		// �Զ����������ļ�param_5m.dat, ?????
		LoadParamFile( m_str5MFileName );
		dwCmd = (CMD_MODE << 16) 
				+ (1 << 8) //m_nStart
				+ (1 << 6) //m_nM0
				+ (1 << 5) //m_nChanConfigCtrl  
				+ (0 << 4) //m_nDataOutModelSel  lvds
				+ (1 << 3) //m_nParaSerSel
				+ (1 << 1) //m_nLvdsAck
				+ 0; //m_nTest
		pDoc->SendCommand( dwCmd ); 
		// rֵ������ 80/5/2
		SetR( 8 );

		// ����alg��ʾ
		CMainFrame* pFrame = (CMainFrame*)GetParentFrame();
		if ( pFrame != NULL )
		{
			pFrame->m_bTestADCBatch = TRUE;
			pFrame->m_bTestADC = FALSE;
			pFrame->m_bTestAlg = TRUE;
		}

		// ѡ��algģʽ
		pDoc->m_nTestModeSel = 6;
		// �ϴεĲɼ���ɺ󣬿��Խ������̣߳��ɼ��ͼ���
		if ( pDoc->m_bTestComp )
		{			
			// �ڶ�������������doc����ֱ��ʹ��this, �м�
			AfxBeginThread( pDoc->TestAndCalc, pDoc );
		}
		// �򿪶�ʱ��1, ÿ��2s�ɼ�һ��
		SetTimer( 1, 2000, NULL );
	}
}

void CTestSetBatchView::Test20M()
{

	CAdcTestPlatDoc* pDoc = (CAdcTestPlatDoc*)GetDocument();
	if ( pDoc != NULL )
	{				

		DWORD dwCmd = (CMD_RESET << 16); 
		pDoc->SendCommand( dwCmd ); 
		
		dwCmd = (CMD_MODE << 16) 
				+ (0 << 8) //m_nStart
				+ (0 << 6) //m_nM0
				+ (1 << 5) //m_nChanConfigCtrl  
				+ (0 << 4) //m_nDataOutModelSel  lvds
				+ (1 << 3) //m_nParaSerSel
				+ (1 << 1) //m_nLvdsAck
				+ 0; //m_nTest
		pDoc->SendCommand( dwCmd ); 
		// �Զ����������ļ�param_20m.dat, ?????
		LoadParamFile( m_str20MFileName );
		dwCmd = (CMD_MODE << 16) 
				+ (1 << 8) //m_nStart
				+ (1 << 6) //m_nM0
				+ (1 << 5) //m_nChanConfigCtrl  
				+ (0 << 4) //m_nDataOutModelSel  lvds
				+ (1 << 3) //m_nParaSerSel
				+ (1 << 1) //m_nLvdsAck
				+ 0; //m_nTest
		pDoc->SendCommand( dwCmd ); 

		// rֵ������80/20/2
		SetR( 2 );

		// ����alg��ʾ
		CMainFrame* pFrame = (CMainFrame*)GetParentFrame();
		if ( pFrame != NULL )
		{
			pFrame->m_bTestADCBatch = TRUE;
			pFrame->m_bTestADC = FALSE;
			pFrame->m_bTestAlg = TRUE;
		}

		// ѡ��algģʽ
		pDoc->m_nTestModeSel = 6;
		// �ϴεĲɼ���ɺ󣬿��Խ������̣߳��ɼ��ͼ���
		if ( pDoc->m_bTestComp )
		{			
			// �ڶ�������������doc����ֱ��ʹ��this, �м�
			AfxBeginThread( pDoc->TestAndCalc, pDoc );
		}
		// �򿪶�ʱ��1, ÿ��2s�ɼ�һ��
		SetTimer( 1, 2000, NULL );
	}
}

void CTestSetBatchView::SetR(int nR)
{
	CAdcTestPlatDoc* pDoc = (CAdcTestPlatDoc*)GetDocument();
	if ( pDoc != NULL )
	{
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
			int nSampFreq = 80;					
			// ͨ��rֵ������ͼ��ʾ��Ƶ��
			pTestPlatView->m_FFTDisp[0].m_dOrgSampFreq = nSampFreq / nR;
			pTestPlatView->m_FFTDisp[1].m_dOrgSampFreq = nSampFreq / nR;
			pTestPlatView->m_FFTDisp[2].m_dOrgSampFreq = nSampFreq / nR;
			pTestPlatView->m_FFTDisp[3].m_dOrgSampFreq = nSampFreq / nR;
			pTestPlatView->m_FFTDisp[4].m_dOrgSampFreq = nSampFreq / nR;
			// ͨ��������ͼ�ָ�ͬ������
			pTestPlatView->m_FFTDisp[0].ZoomRestore();
			pTestPlatView->m_FFTDisp[1].ZoomRestore();
			pTestPlatView->m_FFTDisp[2].ZoomRestore();
			pTestPlatView->m_FFTDisp[3].ZoomRestore();
			pTestPlatView->m_FFTDisp[4].ZoomRestore();			
		}
	}
	
}

void CTestSetBatchView::LoadParamFile(CString strFileName)
{
	CStdioFile fileOpen;
	CString strMsg;
	DWORD dwData;
	CString strTemp;
	char c;
	int i;

	// ��ֹ����
	if ( m_pParamDlg == NULL )
	{
		return;
	}

	if ( fileOpen.Open(strFileName , CFile::modeRead | CFile::typeText ) )
	{			
		// ���ٰ���48�� 
		for ( i = 0; i < ADDR_PARAM_SIZE; i++ )
		{
			if ( fileOpen.ReadString( strTemp ) )
			{
				if ( strTemp.GetLength() == 4 )
				{
					dwData = 0;
					for ( int j = 0; j < 4; j++ )
					{
						c = strTemp.GetAt(j);
						if ( c >= '0' && c <= '9' )
						{
							dwData += (c - '0') << (12-4*j);
						}
						else if ( c >= 'a' && c <= 'f' )
						{
							dwData += (c - 'a' + 10) << (12-4*j);
						}
						else if ( c >= 'A' && c <= 'F' )
						{
							dwData += (c - 'A' + 10) << (12-4*j);
						}
					}
					//
					m_pParamDlg->m_dwaAParam[i] = dwData;
				}
			}
		}
		fileOpen.Close();
		// ʹ��ͬһ�������ļ�
		memcpy( m_pParamDlg->m_dwaBParam, m_pParamDlg->m_dwaAParam, ADDR_PARAM_SIZE * sizeof(DWORD) );
		memcpy( m_pParamDlg->m_dwaCParam, m_pParamDlg->m_dwaAParam, ADDR_PARAM_SIZE * sizeof(DWORD) );
		memcpy( m_pParamDlg->m_dwaDParam, m_pParamDlg->m_dwaAParam, ADDR_PARAM_SIZE * sizeof(DWORD) );


		for ( i = 0; i < ADDR_PARAM_SIZE; i++ )
		{
			m_pParamDlg->m_dwaAAddr[i] = g_dwAddr[i];
			m_pParamDlg->m_dwaBAddr[i] = g_dwAddr[i]+0x100;
			m_pParamDlg->m_dwaCAddr[i] = g_dwAddr[i]+0x200;
			m_pParamDlg->m_dwaDAddr[i] = g_dwAddr[i]+0x300;
		}
			// 4����������
		for ( i = 0; i < 4; i++ )
		{
			m_pParamDlg->SendByChannel( i );
		}
	}
	else
	{
		strMsg.Format( "δ�ҵ������ļ�%s!", strFileName ); 
		AfxMessageBox( strMsg );
	}	
}

void CTestSetBatchView::AutoSaveFile()
{
	((CMainFrame*)GetParentFrame())->FileSave( m_strCurFileName );
	// ����Ϊ�ı��ļ�
	SaveTxtFile();
	// �ļ�����ԭ����·ID����������1
	UpdateData( TRUE );
	m_strID.Format( "%08d", atoi(m_strID) + 1 );
	m_strCurFileName = m_strID + ".atp";
	UpdateData( FALSE );
}

void CTestSetBatchView::SetTestResult( CString &strResult, CString &strSrc, BYTE * byR)
{
	/*@@@*/
	strResult += strSrc;
	for (int i = 0; i < 4; ++i) 
	{
		if ( byR[i] == 1 )
		{
			strResult += ("\t��ȷ");
		}
		else
		{
			strResult += ("\t����");
		}
	}
	strResult += "\r\n";

}

void CTestSetBatchView::SaveTxtFile()
{
	// ������ϱ���Ϊ�ļ�
	CString strData;
	CString strTemp;
	CStdioFile file;
	SYSTEMTIME CurrentTime;
	GetLocalTime( &CurrentTime );
	CString strPath;
	strPath.Format( "%04d%02d%02d", CurrentTime.wYear, CurrentTime.wMonth, CurrentTime.wDay );

	if (!::PathIsDirectory(strPath) )
	{
		::CreateDirectory( strPath, NULL );
	}

	BOOL bRet = file.Open( ".\\"+strPath+"\\"+m_strID+".txt", CFile::modeCreate | CFile::modeWrite | CFile::typeText  );
	if ( bRet )
	{
		// ����ʱ��
		CString strTime;
		GetLocalTime( &CurrentTime );	
		strTime.Format( "����ʱ��:%04d��%02d��%02d��%02dʱ%02d��%02d��\t", CurrentTime.wYear, CurrentTime.wMonth,
			CurrentTime.wDay, CurrentTime.wHour, CurrentTime.wMinute,CurrentTime.wSecond );
		strData += strTime;
		// ����ID
		strTemp.Format( "����ID:%s\r\n", m_strID );
		strData += strTemp;
		strTemp.Format("\t\tCH A\tCH B\tCH C\tCH D\r\n");
		strData += strTemp;
		// ���Խ��
		for ( int i = 0; i < TEST_ITEM; i++ )
		{
			switch ( i )
			{
				case 0:
				{
					strTemp = "�Ĵ�������";
					break;
				}
				case 1:
				{
					strTemp = "ADC��������";
					break;
				}
				case 2:
				{
					strTemp = "2M�������";
					break;
				}
				case 3:
				{
					strTemp = "M0/START����";
					break;
				}
				case 4:
				{
					strTemp = "5M�������";
					break;
				}
				case 5:
				{
					strTemp = "20M�������";
					break;
				}
				default:
					break;
			}
			SetTestResult( strData, strTemp, m_byaResult[i] );
		}
		// д���ļ�
		file.WriteString( strData );
		file.Close();
	}

}
