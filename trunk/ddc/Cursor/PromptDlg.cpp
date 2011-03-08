// PromptDlg.cpp : implementation file
//

#include "stdafx.h"
#include "adctestplat.h"
#include "PromptDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPromptDlg dialog


CPromptDlg::CPromptDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPromptDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPromptDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pJudgeDlg = NULL;
	m_pSetBatchView = (CTestSetBatchView*)pParent;
}

CPromptDlg::CPromptDlg( CString strMsg, int nPos, CString strBtnText, CWnd* pParent /*=NULL*/, CJudgeDlg* pJudgeDlg /*=NULL*/ )
	: CDialog(CPromptDlg::IDD, pParent)
{
	m_strMsg = strMsg;
	m_nPos = nPos;
	m_strBtnText = strBtnText;
	m_pJudgeDlg = NULL;
	m_pSetBatchView = (CTestSetBatchView*)pParent;
	m_pPrevJudgeDlg = pJudgeDlg;
}

void CPromptDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPromptDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPromptDlg, CDialog)
	//{{AFX_MSG_MAP(CPromptDlg)
	ON_BN_CLICKED(ID_BTN_NEXT, OnBtnNext)
	ON_BN_CLICKED(ID_BTN_RETRY, OnBtnRetry)
	ON_BN_CLICKED(ID_BTN_ABORT, OnBtnAbort)
	ON_BN_CLICKED(ID_BTN_RETRY2, OnBtnRetry2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPromptDlg message handlers

BOOL CPromptDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	GetDlgItem( IDC_STATIC_MSG )->SetWindowText( m_strMsg );
	GetDlgItem( ID_BTN_NEXT )->SetWindowText( m_strBtnText );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

// ���ݲ�ͬ�׶��в�ͬ����
void CPromptDlg::OnBtnNext() 
{
	switch ( m_nPos )
	{
		case 0:
		{
			// �ر�ǰһ������
			if ( m_pPrevJudgeDlg != NULL )
			{
				m_pPrevJudgeDlg->SendMessage( WM_CLOSE );
			}
			// ��ʾ
			AfxMessageBox( "ADC���ԣ����������Ҳ��ź�Ƶ��1MHz���źŹ���-3dBm��ʱ��Ƶ��80MHz���źŹ���13dBm" );
			// ADC���Կ�ʼ
			if ( m_pSetBatchView != NULL )
			{
				// ��ʶ
				m_pSetBatchView->SetStaticColor( 1, 0 );
				// ADC����
				m_pSetBatchView->TestAdc();
			}			
			
			// ���û�ѡ������Ƿ���ȷ
			if ( m_pJudgeDlg != NULL )
			{
				m_pJudgeDlg->SetActiveWindow();
			}
			else
			{
				m_pJudgeDlg = new CJudgeDlg( 0, m_pSetBatchView );
				m_pJudgeDlg->Create( IDD_JUDGE, NULL );// NULL
				m_pJudgeDlg->ShowWindow( SW_SHOW );
			}
			// �رձ�����
			SendMessage( WM_CLOSE );
			// ���ݲ����жϴ��ڵ�ָ��
			if ( m_pSetBatchView != NULL )
			{
				m_pSetBatchView->m_pJudgeDlgBack = m_pJudgeDlg;
			}
			break;
		}
		case 1:
		{
			// �ر�ǰһ������
			if ( m_pPrevJudgeDlg != NULL )
			{
				m_pPrevJudgeDlg->SendMessage( WM_CLOSE );
			}
			// ��ʾ
			AfxMessageBox( "2M������ԣ����������Ҳ��ź�Ƶ��51.6MHz���źŹ���0dBm��ʱ��Ƶ��80MHz���źŹ���13dBm" );
			// 2M������Կ�ʼ
			if ( m_pSetBatchView != NULL )
			{
				m_pSetBatchView->SetStaticColor( 2, 0 );
				// 2M�������
				m_pSetBatchView->Test2M();
			}			
			
			// ���û�ѡ������Ƿ���ȷ
			if ( m_pJudgeDlg != NULL )
			{
				m_pJudgeDlg->m_nPos = 1;
				m_pJudgeDlg->SetActiveWindow();
			}
			else
			{
				m_pJudgeDlg = new CJudgeDlg( 1, m_pSetBatchView );
				m_pJudgeDlg->Create( IDD_JUDGE, NULL );// NULL
				m_pJudgeDlg->ShowWindow( SW_SHOW );
			}
			// �رձ�����
			SendMessage( WM_CLOSE );
			// ���ݲ����жϴ��ڵ�ָ��
			if ( m_pSetBatchView != NULL )
			{
				m_pSetBatchView->m_pJudgeDlgBack = m_pJudgeDlg;
			}
			break;
		}
		case 2:
		{
			// �ر�ǰһ������
			if ( m_pPrevJudgeDlg != NULL )
			{
				m_pPrevJudgeDlg->SendMessage( WM_CLOSE );
			}
			// ��ʾ
			AfxMessageBox( "M0/START���ԣ��ź�Ƶ�ʺͷ��Ȳ���" );
			// M0/START���Կ�ʼ
			if ( m_pSetBatchView != NULL )
			{
				m_pSetBatchView->SetStaticColor( 3, 0 );
				// M0/START����
				m_pSetBatchView->TestM0();
			}
			
			
			// ���û�ѡ������Ƿ���ȷ
			if ( m_pJudgeDlg != NULL )
			{
				m_pJudgeDlg->m_nPos = 2;
				m_pJudgeDlg->SetActiveWindow();
			}
			else
			{
				m_pJudgeDlg = new CJudgeDlg( 2, m_pSetBatchView );
				m_pJudgeDlg->Create( IDD_JUDGE, NULL );// NULL
				m_pJudgeDlg->ShowWindow( SW_SHOW );
			}
			// �رձ�����
			SendMessage( WM_CLOSE );
			// ���ݲ����жϴ��ڵ�ָ��
			if ( m_pSetBatchView != NULL )
			{
				m_pSetBatchView->m_pJudgeDlgBack = m_pJudgeDlg;
			}
			break;
		}
		case 3:
		{
			// �ر�ǰһ������
			if ( m_pPrevJudgeDlg != NULL )
			{
				m_pPrevJudgeDlg->SendMessage( WM_CLOSE );
			}
			// ��ʾ
			AfxMessageBox( "5M�������" );
			// 5M������Կ�ʼ
			if ( m_pSetBatchView != NULL )
			{
				m_pSetBatchView->SetStaticColor( 4, 0 );
				// 5M�������
				m_pSetBatchView->Test5M();
			}
			
			
			// ���û�ѡ������Ƿ���ȷ
			if ( m_pJudgeDlg != NULL )
			{
				m_pJudgeDlg->m_nPos = 3;
				m_pJudgeDlg->SetActiveWindow();
			}
			else
			{
				m_pJudgeDlg = new CJudgeDlg( 3, m_pSetBatchView );
				m_pJudgeDlg->Create( IDD_JUDGE, NULL );
				m_pJudgeDlg->ShowWindow( SW_SHOW );
			}
			// �رձ�����
			SendMessage( WM_CLOSE );
			// ���ݲ����жϴ��ڵ�ָ��
			if ( m_pSetBatchView != NULL )
			{
				m_pSetBatchView->m_pJudgeDlgBack = m_pJudgeDlg;
			}
			break;
		}
		case 4:
		{
			// �ر�ǰһ������
			if ( m_pPrevJudgeDlg != NULL )
			{
				m_pPrevJudgeDlg->SendMessage( WM_CLOSE );
			}
			// ��ʾ
			AfxMessageBox( "20M������ԣ����������Ҳ��ź�Ƶ��61MHz���źŹ���0dBm��ʱ��Ƶ��80MHz���źŹ���13dBm" );
			// 20M������Կ�ʼ
			if ( m_pSetBatchView != NULL )
			{
				m_pSetBatchView->SetStaticColor( 5, 0 );
				// 20M�������
				m_pSetBatchView->Test20M();
			}			
			
			// ���û�ѡ������Ƿ���ȷ
			if ( m_pJudgeDlg != NULL )
			{
				m_pJudgeDlg->m_nPos = 4;
				m_pJudgeDlg->SetActiveWindow();
			}
			else
			{
				m_pJudgeDlg = new CJudgeDlg( 4, m_pSetBatchView );
				m_pJudgeDlg->Create( IDD_JUDGE, NULL );
				m_pJudgeDlg->ShowWindow( SW_SHOW );
			}
			// �رձ�����
			SendMessage( WM_CLOSE );
			// ���ݲ����жϴ��ڵ�ָ��
			if ( m_pSetBatchView != NULL )
			{
				m_pSetBatchView->m_pJudgeDlgBack = m_pJudgeDlg;
			}
			break;
		}
		case 5:
		{
			// �ر�ǰһ������
			if ( m_pPrevJudgeDlg != NULL )
			{
				m_pPrevJudgeDlg->SendMessage( WM_CLOSE );
			}
			// �رձ�����
			SendMessage( WM_CLOSE );
			if ( m_pJudgeDlg != NULL )
			{
				m_pJudgeDlg->SendMessage( WM_CLOSE );
			}
			// ���Խ������Զ��ϵ�
			if ( m_pSetBatchView != NULL )
			{
				CAdcTestPlatDoc* pDoc = (CAdcTestPlatDoc*)(m_pSetBatchView->GetDocument());
				if ( pDoc != NULL )
				{
					pDoc->PowerOff();
				}
				CMainFrame* pFrame = (CMainFrame*)GetParentFrame();
				if ( pFrame != NULL )
				{
					pFrame->m_bPower = 0;
				}
			}
			
			if ( m_pSetBatchView != NULL )
			{
				// ���ݲ����жϴ��ڵ�ָ��
				m_pSetBatchView->m_pJudgeDlgBack = m_pJudgeDlg;
				// ������ɱ���Ϊ�ļ�
				m_pSetBatchView->AutoSaveFile();
				// ��������ֹͣ
				m_pSetBatchView->SendMessage( WM_COMMAND, ID_BTN_TEST );
			}
			

			break;
		}
		default:
			break;
	}
	
}

// ����
void CPromptDlg::OnBtnRetry() 
{
	// �رձ�����
	SendMessage( WM_CLOSE );
	// �ر��жϴ���
	if ( m_pPrevJudgeDlg != NULL )
	{
		m_pPrevJudgeDlg->SendMessage( WM_CLOSE );
	}
	// �ر��жϴ���
	if ( m_pJudgeDlg != NULL )
	{
		m_pJudgeDlg->SendMessage( WM_CLOSE );
	}
	// ����
	if ( m_pSetBatchView != NULL )
	{
		//m_pSetBatchView->m_bTestBegin = TRUE;
		//m_pSetBatchView->SendMessage( WM_COMMAND, ID_BTN_TEST );

		// ���²��Ե�ǰ��
		if ( m_nPos > 0 )
		{
			m_nPos--;
			SetStaticColor();
			OnBtnNext();
		}
		// ����տ�ʼ���ԣ���ӵ�һ�ʼ
		else
		{
			(m_pSetBatchView->GetDlgItem( ID_BTN_TEST ))->SetWindowText( "���Կ�ʼ" );
			m_pSetBatchView->m_bTestBegin = TRUE;
			m_pSetBatchView->InitStaticColor();
			CMainFrame* pFrame = (CMainFrame*)(m_pSetBatchView->GetParentFrame());
			// ���µ�������
			if ( pFrame != NULL )
			{
				pFrame->m_bRunning = FALSE;
			}
			m_pSetBatchView->SendMessage( WM_COMMAND, ID_BTN_TEST );
		}
		
	}
	
}

// ��������
void CPromptDlg::OnBtnAbort() 
{
	
	// �ر��жϴ���
	if ( m_pPrevJudgeDlg != NULL )
	{
		m_pPrevJudgeDlg->SendMessage( WM_CLOSE );
	}
	// �ر��жϴ���
	if ( m_pJudgeDlg != NULL )
	{
		m_pJudgeDlg->SendMessage( WM_CLOSE );
	}
	// ����
	if ( m_pSetBatchView != NULL )
	{
	//	(m_pSetBatchView->GetDlgItem( IDC_EDIT_ID ))->SetWindowText( "" );
		(m_pSetBatchView->GetDlgItem( IDC_EDIT_ID ))->SetFocus();
		(m_pSetBatchView->GetDlgItem( ID_BTN_TEST ))->SetWindowText( "���Կ�ʼ" );
		m_pSetBatchView->m_bTestBegin = TRUE;
		m_pSetBatchView->InitStaticColor();
		CMainFrame* pFrame = (CMainFrame*)(m_pSetBatchView->GetParentFrame());
		// ���µ�������
		if ( pFrame != NULL )
		{
			pFrame->m_bRunning = FALSE;
		}
		//m_pSetBatchView->SendMessage( WM_COMMAND, ID_BTN_TEST );
	}
	// �رձ�����
	SendMessage( WM_CLOSE );
}

void CPromptDlg::SetStaticColor()
{
	switch ( m_nPos )
	{
		case 0:
		{
			if ( m_pSetBatchView != NULL )
			{
				// ��ʶ���Կ�ʼ
				m_pSetBatchView->SetStaticColor( 1, 0 );				
			}
			break;
		}
		case 1:
		{
			if ( m_pSetBatchView != NULL )
			{
				// ��ʶ���Կ�ʼ
				m_pSetBatchView->SetStaticColor( 2, 0 );				
			}
			break;
		}
		case 2:
		{
			if ( m_pSetBatchView != NULL )
			{
				// ��ʶ���Կ�ʼ
				m_pSetBatchView->SetStaticColor( 3, 0 );				
			}
			break;
		}
		case 3:
		{
			if ( m_pSetBatchView != NULL )
			{
				// ��ʶ���Կ�ʼ
				m_pSetBatchView->SetStaticColor( 4, 0 );				
			}
			break;
		}
		case 4:
		{
			if ( m_pSetBatchView != NULL )
			{
				// ��ʶ���Կ�ʼ
				m_pSetBatchView->SetStaticColor( 5, 0 );				
			}
			break;
		}
		default:
			break;
	}
}

void CPromptDlg::OnBtnRetry2() 
{
	// TODO: Add your control notification handler code here
	// �رձ�����
	SendMessage( WM_CLOSE );
	// �ر��жϴ���
	if ( m_pPrevJudgeDlg != NULL )
	{
		m_pPrevJudgeDlg->SendMessage( WM_CLOSE );
	}
	// �ر��жϴ���
	if ( m_pJudgeDlg != NULL )
	{
		m_pJudgeDlg->SendMessage( WM_CLOSE );
	}
	// ����
	if ( m_pSetBatchView != NULL )
	{
		//m_pSetBatchView->m_bTestBegin = TRUE;
		//m_pSetBatchView->SendMessage( WM_COMMAND, ID_BTN_TEST );

//		// ���²��Ե�ǰ��
//		if ( m_nPos > 0 )
//		{
//			m_nPos--;
//			SetStaticColor();
//			OnBtnNext();
//		}
//		// ����տ�ʼ���ԣ���ӵ�һ�ʼ
//		else
		{
			(m_pSetBatchView->GetDlgItem( ID_BTN_TEST ))->SetWindowText( "���Կ�ʼ" );
			m_pSetBatchView->m_bTestBegin = TRUE;
			m_pSetBatchView->InitStaticColor();
			CMainFrame* pFrame = (CMainFrame*)(m_pSetBatchView->GetParentFrame());
			// ���µ�������
			if ( pFrame != NULL )
			{
				pFrame->m_bRunning = FALSE;
			}
			m_pSetBatchView->SendMessage( WM_COMMAND, ID_BTN_TEST );
		}
		
	}
	
}
