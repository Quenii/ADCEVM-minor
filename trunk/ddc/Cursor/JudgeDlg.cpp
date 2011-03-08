// JudgeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "adctestplat.h"
#include "JudgeDlg.h"
#include "PromptDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CJudgeDlg dialog


CJudgeDlg::CJudgeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CJudgeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CJudgeDlg)
	m_CHA = -1;
	m_CHB = -1;
	m_CHC = -1;
	m_CHD = -1;
	//}}AFX_DATA_INIT
}

CJudgeDlg::CJudgeDlg( int nPos, CWnd* pParent /*=NULL*/)
	: CDialog(CJudgeDlg::IDD, pParent)
{
	m_nPos = nPos;
	m_pSetBatchView = (CTestSetBatchView*)pParent;
}

void CJudgeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CJudgeDlg)
	DDX_Radio(pDX, IDC_RADIO9, m_CHA);
	DDX_Radio(pDX, IDC_RADIO11, m_CHB);
	DDX_Radio(pDX, IDC_RADIO13, m_CHC);
	DDX_Radio(pDX, IDC_RADIO15, m_CHD);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CJudgeDlg, CDialog)
	//{{AFX_MSG_MAP(CJudgeDlg)
	ON_BN_CLICKED(ID_BTN_RIGHT, OnBtnRight)
	ON_BN_CLICKED(ID_BTN_WRONG, OnBtnWrong)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_RADIO1, OnAllPass)
	ON_BN_CLICKED(IDC_RADIO8, OnAllFail)
	ON_BN_CLICKED(IDC_RADIO15, OnRadio15)
	ON_BN_CLICKED(IDC_RADIO9, OnRadio9)
	ON_BN_CLICKED(IDC_RADIO11, OnRadio11)
	ON_BN_CLICKED(IDC_RADIO13, OnRadio13)
	ON_BN_CLICKED(IDC_RADIO10, OnRadio10)
	ON_BN_CLICKED(IDC_RADIO12, OnRadio12)
	ON_BN_CLICKED(IDC_RADIO14, OnRadio14)
	ON_BN_CLICKED(IDC_RADIO16, OnRadio16)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CJudgeDlg message handlers

void CJudgeDlg::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	delete this;
	
	CDialog::PostNcDestroy();
}

void CJudgeDlg::OnBtnRight() 
{
	CString strMsg;

	
	if ( m_pSetBatchView != NULL )
	{
		// 通过关闭定时器，停止采集
		m_pSetBatchView->KillTimer(1);
		// 保存测试结果
		m_pSetBatchView->m_byaResult[m_nPos+1][0] = m_CHA;
		m_pSetBatchView->m_byaResult[m_nPos+1][1] = m_CHB;
		m_pSetBatchView->m_byaResult[m_nPos+1][2] = m_CHC;
		m_pSetBatchView->m_byaResult[m_nPos+1][3] = m_CHD;
	}

	switch ( m_nPos )
	{
		case 0:
		{
			// 在批量测试区显示
			if ( m_pSetBatchView != NULL )
			{
				m_pSetBatchView->SetStaticColor( 1, 1 );
			}
			strMsg = "ADC测试完成!";			
			CPromptDlg dlgPrompt( strMsg, 1, "测试下一项", m_pSetBatchView, this );
			//PostNcDestroy();
			dlgPrompt.DoModal();
			// 关闭本窗口
			SendMessage( WM_CLOSE );
			
			break;
		}
		case 1:
		{
			// 在批量测试区显示
			if ( m_pSetBatchView != NULL )
			{
				m_pSetBatchView->SetStaticColor( 2, 1 );
			}
			strMsg = "2M带宽测试完成!";
			CPromptDlg dlgPrompt( strMsg, 2, "测试下一项", m_pSetBatchView, this );
			dlgPrompt.DoModal();
			// 关闭本窗口
			SendMessage( WM_CLOSE );
			break;
		}
		case 2:
		{
			// 在批量测试区显示
			if ( m_pSetBatchView != NULL )
			{
				m_pSetBatchView->SetStaticColor( 3, 1 );
			}
			strMsg = "M0/START测试完成!";
			CPromptDlg dlgPrompt( strMsg, 3, "测试下一项", m_pSetBatchView, this );
			dlgPrompt.DoModal();
			// 关闭本窗口
			SendMessage( WM_CLOSE );
			break;
		}
		case 3:
		{
			// 在批量测试区显示
			if ( m_pSetBatchView != NULL )
			{
				m_pSetBatchView->SetStaticColor( 4, 1 );
			}
			strMsg = "5M带宽测试完成!";
			CPromptDlg dlgPrompt( strMsg, 4, "测试下一项", m_pSetBatchView, this );
			dlgPrompt.DoModal();
			// 关闭本窗口
			SendMessage( WM_CLOSE );
			break;
		}
		case 4:
		{
			// 在批量测试区显示
			if ( m_pSetBatchView != NULL )
			{
				m_pSetBatchView->SetStaticColor( 5, 1 );
			}
			strMsg = "20M带宽测试完成!\r\n\r\n全部测试完成";
			CPromptDlg dlgPrompt( strMsg, 5, "测试完成", m_pSetBatchView, this );
			dlgPrompt.DoModal();
			// 关闭本窗口
			SendMessage( WM_CLOSE );
			break;
		}
		default:
			break;
	}
	
	
}

void CJudgeDlg::OnBtnWrong() 
{	
	CString strMsg;

	
	if ( m_pSetBatchView != NULL )
	{
		// 通过关闭定时器，停止采集
		m_pSetBatchView->KillTimer(1);
		// 保存测试结果
		m_pSetBatchView->m_byaResult[m_nPos+1][0] = 2;
	}

	switch ( m_nPos )
	{		
		case 0:
		{
			// 在批量测试区显示
			if ( m_pSetBatchView != NULL )
			{
				m_pSetBatchView->SetStaticColor( 1, 2 );
			}
			strMsg = "ADC测试错误!";			
			CPromptDlg dlgPrompt( strMsg, 1, "测试下一项", m_pSetBatchView, this );
			//PostNcDestroy();
			dlgPrompt.DoModal();
			// 关闭本窗口
			SendMessage( WM_CLOSE );
			
			break;
		}
		case 1:
		{
			// 在批量测试区显示
			if ( m_pSetBatchView != NULL )
			{
				m_pSetBatchView->SetStaticColor( 2, 2 );
			}
			strMsg = "2M带宽测试错误!";
			CPromptDlg dlgPrompt( strMsg, 2, "测试下一项", m_pSetBatchView, this );
			dlgPrompt.DoModal();
			// 关闭本窗口
			SendMessage( WM_CLOSE );
			break;
		}
		case 2:
		{
			// 在批量测试区显示
			if ( m_pSetBatchView != NULL )
			{
				m_pSetBatchView->SetStaticColor( 3, 2 );
			}
			strMsg = "M0/START测试错误!";
			CPromptDlg dlgPrompt( strMsg, 3, "测试下一项", m_pSetBatchView, this );
			dlgPrompt.DoModal();
			// 关闭本窗口
			SendMessage( WM_CLOSE );
			break;
		}
		case 3:
		{
			// 在批量测试区显示
			if ( m_pSetBatchView != NULL )
			{
				m_pSetBatchView->SetStaticColor( 4, 2 );
			}
			strMsg = "5M带宽测试错误!";
			CPromptDlg dlgPrompt( strMsg, 4, "测试下一项", m_pSetBatchView, this );
			dlgPrompt.DoModal();
			// 关闭本窗口
			SendMessage( WM_CLOSE );
			break;
		}
		case 4:
		{
			// 在批量测试区显示
			if ( m_pSetBatchView != NULL )
			{
				m_pSetBatchView->SetStaticColor( 5, 2 );
			}
			strMsg = "20M带宽测试错误!";
			CPromptDlg dlgPrompt( strMsg, 5, "测试完成", m_pSetBatchView, this );
			dlgPrompt.DoModal();
			// 关闭本窗口
			SendMessage( WM_CLOSE );
			break;
		}
		default:
			break;
	}
}

BOOL CJudgeDlg::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	//cs.x = 100;
	//cs.y = 100;
	
	return CDialog::PreCreateWindow(cs);
}

void CJudgeDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	CRect rc, rcFrame;
	GetWindowRect( &rc );
	int nWidth = rc.right - rc.left;
	int nHeight = rc.bottom - rc.top;
	( (CMainFrame*)AfxGetMainWnd() )->GetWindowRect( &rcFrame );
	int nFrameWidth = rcFrame.right - rcFrame.left;
	int nFrameHeight = rcFrame.bottom - rcFrame.top;

	rc.left = (nFrameWidth - nWidth) / 2;
	rc.top = (nFrameHeight - nHeight) / 2;
	rc.right = rc.left + nWidth;
	rc.bottom = rc.top + nHeight;
	// 居中
	MoveWindow( &rc );
	OnAllPass();
}

void CJudgeDlg::OnAllPass() 
{
	// TODO: Add your control notification handler code here
	((CButton *)GetDlgItem(IDC_RADIO9))->SetCheck(TRUE);//
	((CButton *)GetDlgItem(IDC_RADIO11))->SetCheck(TRUE);//
	((CButton *)GetDlgItem(IDC_RADIO13))->SetCheck(TRUE);//
	((CButton *)GetDlgItem(IDC_RADIO15))->SetCheck(TRUE);//

	((CButton *)GetDlgItem(IDC_RADIO10))->SetCheck(FALSE);//
	((CButton *)GetDlgItem(IDC_RADIO12))->SetCheck(FALSE);//
	((CButton *)GetDlgItem(IDC_RADIO14))->SetCheck(FALSE);//
	((CButton *)GetDlgItem(IDC_RADIO16))->SetCheck(FALSE);//
	
	m_CHA = 1;
	m_CHB = 1;
	m_CHC = 1;
	m_CHD = 1;
}

void CJudgeDlg::OnAllFail() 
{
	// TODO: Add your control notification handler code here
	((CButton *)GetDlgItem(IDC_RADIO10))->SetCheck(TRUE);//
	((CButton *)GetDlgItem(IDC_RADIO12))->SetCheck(TRUE);//
	((CButton *)GetDlgItem(IDC_RADIO14))->SetCheck(TRUE);//
	((CButton *)GetDlgItem(IDC_RADIO16))->SetCheck(TRUE);//	

	((CButton *)GetDlgItem(IDC_RADIO9))->SetCheck(FALSE);//
	((CButton *)GetDlgItem(IDC_RADIO11))->SetCheck(FALSE);//
	((CButton *)GetDlgItem(IDC_RADIO13))->SetCheck(FALSE);//
	((CButton *)GetDlgItem(IDC_RADIO15))->SetCheck(FALSE);//
	
	m_CHA = 2;
	m_CHB = 2;
	m_CHC = 2;
	m_CHD = 2;
}

void CJudgeDlg::OnRadio15() 
{
	// TODO: Add your control notification handler code here
	m_CHD = 1;
}

void CJudgeDlg::OnRadio9() 
{
	// TODO: Add your control notification handler code here
	m_CHA = 1;
}

void CJudgeDlg::OnRadio11() 
{
	// TODO: Add your control notification handler code here
	m_CHB = 1;

}

void CJudgeDlg::OnRadio13() 
{
	// TODO: Add your control notification handler code here
	m_CHC = 1;
}

void CJudgeDlg::OnRadio10() 
{
	// TODO: Add your control notification handler code here
	m_CHA = 2;
}

void CJudgeDlg::OnRadio12() 
{
	// TODO: Add your control notification handler code here
	m_CHB = 2;
}

void CJudgeDlg::OnRadio14() 
{
	// TODO: Add your control notification handler code here
	m_CHC = 2;
}

void CJudgeDlg::OnRadio16() 
{
	// TODO: Add your control notification handler code here
	m_CHD = 2;
}
