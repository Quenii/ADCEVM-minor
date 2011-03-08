#if !defined(AFX_PROMPTDLG_H__DCA1FDDA_8F5B_4E42_ABFF_461BD1EFB705__INCLUDED_)
#define AFX_PROMPTDLG_H__DCA1FDDA_8F5B_4E42_ABFF_461BD1EFB705__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PromptDlg.h : header file
//

#include "TestSetBatchView.h"
#include "JudgeDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CPromptDlg dialog

class CJudgeDlg;
class CTestSetBatchView;

class CPromptDlg : public CDialog
{
// Construction
public:
	CPromptDlg(CWnd* pParent = NULL);   // standard constructor
	CPromptDlg( CString strMsg, int nPos, CString strBtnText, 
		CWnd* pParent = NULL, CJudgeDlg* pJudgeDlg = NULL );

// Dialog Data
	//{{AFX_DATA(CPromptDlg)
	enum { IDD = IDD_PROMPT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

public:
	void SetStaticColor( void );
	CString m_strMsg;
	int m_nPos;
	CString m_strBtnText;
	CJudgeDlg* m_pJudgeDlg;
	CTestSetBatchView* m_pSetBatchView;
	CJudgeDlg* m_pPrevJudgeDlg;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPromptDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPromptDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnNext();
	afx_msg void OnBtnRetry();
	afx_msg void OnBtnAbort();
	afx_msg void OnBtnRetry2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROMPTDLG_H__DCA1FDDA_8F5B_4E42_ABFF_461BD1EFB705__INCLUDED_)
