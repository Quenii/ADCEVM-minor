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

// 根据不同阶段有不同动作
void CPromptDlg::OnBtnNext() 
{
	switch ( m_nPos )
	{
		case 0:
		{
			// 关闭前一个窗口
			if ( m_pPrevJudgeDlg != NULL )
			{
				m_pPrevJudgeDlg->SendMessage( WM_CLOSE );
			}
			// 提示
			AfxMessageBox( "ADC测试：请输入正弦波信号频率1MHz，信号功率-3dBm；时钟频率80MHz，信号功率13dBm" );
			// ADC测试开始
			if ( m_pSetBatchView != NULL )
			{
				// 标识
				m_pSetBatchView->SetStaticColor( 1, 0 );
				// ADC测试
				m_pSetBatchView->TestAdc();
			}			
			
			// 让用户选择测试是否正确
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
			// 关闭本窗口
			SendMessage( WM_CLOSE );
			// 备份测试判断窗口的指针
			if ( m_pSetBatchView != NULL )
			{
				m_pSetBatchView->m_pJudgeDlgBack = m_pJudgeDlg;
			}
			break;
		}
		case 1:
		{
			// 关闭前一个窗口
			if ( m_pPrevJudgeDlg != NULL )
			{
				m_pPrevJudgeDlg->SendMessage( WM_CLOSE );
			}
			// 提示
			AfxMessageBox( "2M带宽测试：请输入正弦波信号频率51.6MHz，信号功率0dBm；时钟频率80MHz，信号功率13dBm" );
			// 2M带宽测试开始
			if ( m_pSetBatchView != NULL )
			{
				m_pSetBatchView->SetStaticColor( 2, 0 );
				// 2M带宽测试
				m_pSetBatchView->Test2M();
			}			
			
			// 让用户选择测试是否正确
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
			// 关闭本窗口
			SendMessage( WM_CLOSE );
			// 备份测试判断窗口的指针
			if ( m_pSetBatchView != NULL )
			{
				m_pSetBatchView->m_pJudgeDlgBack = m_pJudgeDlg;
			}
			break;
		}
		case 2:
		{
			// 关闭前一个窗口
			if ( m_pPrevJudgeDlg != NULL )
			{
				m_pPrevJudgeDlg->SendMessage( WM_CLOSE );
			}
			// 提示
			AfxMessageBox( "M0/START测试：信号频率和幅度不变" );
			// M0/START测试开始
			if ( m_pSetBatchView != NULL )
			{
				m_pSetBatchView->SetStaticColor( 3, 0 );
				// M0/START测试
				m_pSetBatchView->TestM0();
			}
			
			
			// 让用户选择测试是否正确
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
			// 关闭本窗口
			SendMessage( WM_CLOSE );
			// 备份测试判断窗口的指针
			if ( m_pSetBatchView != NULL )
			{
				m_pSetBatchView->m_pJudgeDlgBack = m_pJudgeDlg;
			}
			break;
		}
		case 3:
		{
			// 关闭前一个窗口
			if ( m_pPrevJudgeDlg != NULL )
			{
				m_pPrevJudgeDlg->SendMessage( WM_CLOSE );
			}
			// 提示
			AfxMessageBox( "5M带宽测试" );
			// 5M带宽测试开始
			if ( m_pSetBatchView != NULL )
			{
				m_pSetBatchView->SetStaticColor( 4, 0 );
				// 5M带宽测试
				m_pSetBatchView->Test5M();
			}
			
			
			// 让用户选择测试是否正确
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
			// 关闭本窗口
			SendMessage( WM_CLOSE );
			// 备份测试判断窗口的指针
			if ( m_pSetBatchView != NULL )
			{
				m_pSetBatchView->m_pJudgeDlgBack = m_pJudgeDlg;
			}
			break;
		}
		case 4:
		{
			// 关闭前一个窗口
			if ( m_pPrevJudgeDlg != NULL )
			{
				m_pPrevJudgeDlg->SendMessage( WM_CLOSE );
			}
			// 提示
			AfxMessageBox( "20M带宽测试：请输入正弦波信号频率61MHz，信号功率0dBm；时钟频率80MHz，信号功率13dBm" );
			// 20M带宽测试开始
			if ( m_pSetBatchView != NULL )
			{
				m_pSetBatchView->SetStaticColor( 5, 0 );
				// 20M带宽测试
				m_pSetBatchView->Test20M();
			}			
			
			// 让用户选择测试是否正确
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
			// 关闭本窗口
			SendMessage( WM_CLOSE );
			// 备份测试判断窗口的指针
			if ( m_pSetBatchView != NULL )
			{
				m_pSetBatchView->m_pJudgeDlgBack = m_pJudgeDlg;
			}
			break;
		}
		case 5:
		{
			// 关闭前一个窗口
			if ( m_pPrevJudgeDlg != NULL )
			{
				m_pPrevJudgeDlg->SendMessage( WM_CLOSE );
			}
			// 关闭本窗口
			SendMessage( WM_CLOSE );
			if ( m_pJudgeDlg != NULL )
			{
				m_pJudgeDlg->SendMessage( WM_CLOSE );
			}
			// 测试结束后自动断电
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
				// 备份测试判断窗口的指针
				m_pSetBatchView->m_pJudgeDlgBack = m_pJudgeDlg;
				// 测试完成保存为文件
				m_pSetBatchView->AutoSaveFile();
				// 跳过测试停止
				m_pSetBatchView->SendMessage( WM_COMMAND, ID_BTN_TEST );
			}
			

			break;
		}
		default:
			break;
	}
	
}

// 重试
void CPromptDlg::OnBtnRetry() 
{
	// 关闭本窗口
	SendMessage( WM_CLOSE );
	// 关闭判断窗口
	if ( m_pPrevJudgeDlg != NULL )
	{
		m_pPrevJudgeDlg->SendMessage( WM_CLOSE );
	}
	// 关闭判断窗口
	if ( m_pJudgeDlg != NULL )
	{
		m_pJudgeDlg->SendMessage( WM_CLOSE );
	}
	// 重试
	if ( m_pSetBatchView != NULL )
	{
		//m_pSetBatchView->m_bTestBegin = TRUE;
		//m_pSetBatchView->SendMessage( WM_COMMAND, ID_BTN_TEST );

		// 重新测试当前项
		if ( m_nPos > 0 )
		{
			m_nPos--;
			SetStaticColor();
			OnBtnNext();
		}
		// 如果刚开始测试，则从第一项开始
		else
		{
			(m_pSetBatchView->GetDlgItem( ID_BTN_TEST ))->SetWindowText( "测试开始" );
			m_pSetBatchView->m_bTestBegin = TRUE;
			m_pSetBatchView->InitStaticColor();
			CMainFrame* pFrame = (CMainFrame*)(m_pSetBatchView->GetParentFrame());
			// 更新到工具栏
			if ( pFrame != NULL )
			{
				pFrame->m_bRunning = FALSE;
			}
			m_pSetBatchView->SendMessage( WM_COMMAND, ID_BTN_TEST );
		}
		
	}
	
}

// 放弃测试
void CPromptDlg::OnBtnAbort() 
{
	
	// 关闭判断窗口
	if ( m_pPrevJudgeDlg != NULL )
	{
		m_pPrevJudgeDlg->SendMessage( WM_CLOSE );
	}
	// 关闭判断窗口
	if ( m_pJudgeDlg != NULL )
	{
		m_pJudgeDlg->SendMessage( WM_CLOSE );
	}
	// 重试
	if ( m_pSetBatchView != NULL )
	{
	//	(m_pSetBatchView->GetDlgItem( IDC_EDIT_ID ))->SetWindowText( "" );
		(m_pSetBatchView->GetDlgItem( IDC_EDIT_ID ))->SetFocus();
		(m_pSetBatchView->GetDlgItem( ID_BTN_TEST ))->SetWindowText( "测试开始" );
		m_pSetBatchView->m_bTestBegin = TRUE;
		m_pSetBatchView->InitStaticColor();
		CMainFrame* pFrame = (CMainFrame*)(m_pSetBatchView->GetParentFrame());
		// 更新到工具栏
		if ( pFrame != NULL )
		{
			pFrame->m_bRunning = FALSE;
		}
		//m_pSetBatchView->SendMessage( WM_COMMAND, ID_BTN_TEST );
	}
	// 关闭本窗口
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
				// 标识测试开始
				m_pSetBatchView->SetStaticColor( 1, 0 );				
			}
			break;
		}
		case 1:
		{
			if ( m_pSetBatchView != NULL )
			{
				// 标识测试开始
				m_pSetBatchView->SetStaticColor( 2, 0 );				
			}
			break;
		}
		case 2:
		{
			if ( m_pSetBatchView != NULL )
			{
				// 标识测试开始
				m_pSetBatchView->SetStaticColor( 3, 0 );				
			}
			break;
		}
		case 3:
		{
			if ( m_pSetBatchView != NULL )
			{
				// 标识测试开始
				m_pSetBatchView->SetStaticColor( 4, 0 );				
			}
			break;
		}
		case 4:
		{
			if ( m_pSetBatchView != NULL )
			{
				// 标识测试开始
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
	// 关闭本窗口
	SendMessage( WM_CLOSE );
	// 关闭判断窗口
	if ( m_pPrevJudgeDlg != NULL )
	{
		m_pPrevJudgeDlg->SendMessage( WM_CLOSE );
	}
	// 关闭判断窗口
	if ( m_pJudgeDlg != NULL )
	{
		m_pJudgeDlg->SendMessage( WM_CLOSE );
	}
	// 重试
	if ( m_pSetBatchView != NULL )
	{
		//m_pSetBatchView->m_bTestBegin = TRUE;
		//m_pSetBatchView->SendMessage( WM_COMMAND, ID_BTN_TEST );

//		// 重新测试当前项
//		if ( m_nPos > 0 )
//		{
//			m_nPos--;
//			SetStaticColor();
//			OnBtnNext();
//		}
//		// 如果刚开始测试，则从第一项开始
//		else
		{
			(m_pSetBatchView->GetDlgItem( ID_BTN_TEST ))->SetWindowText( "测试开始" );
			m_pSetBatchView->m_bTestBegin = TRUE;
			m_pSetBatchView->InitStaticColor();
			CMainFrame* pFrame = (CMainFrame*)(m_pSetBatchView->GetParentFrame());
			// 更新到工具栏
			if ( pFrame != NULL )
			{
				pFrame->m_bRunning = FALSE;
			}
			m_pSetBatchView->SendMessage( WM_COMMAND, ID_BTN_TEST );
		}
		
	}
	
}
