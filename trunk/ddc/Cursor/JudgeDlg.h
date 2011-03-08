#if !defined(AFX_JUDGEDLG_H__3C124362_C49E_401D_A3F0_B8CD03BF0B58__INCLUDED_)
#define AFX_JUDGEDLG_H__3C124362_C49E_401D_A3F0_B8CD03BF0B58__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// JudgeDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CJudgeDlg dialog

#include "TestSetBatchView.h"

class CTestSetBatchView;

class CJudgeDlg : public CDialog
{
// Construction
public:
	CJudgeDlg(CWnd* pParent = NULL);   // standard constructor
	CJudgeDlg( int nPos, CWnd* pParent = NULL);

// Dialog Data
	//{{AFX_DATA(CJudgeDlg)
	enum { IDD = IDD_JUDGE };
	int		m_CHA;
	int		m_CHB;
	int		m_CHC;
	int		m_CHD;
	//}}AFX_DATA
public:
	int m_nPos;
	CTestSetBatchView* m_pSetBatchView;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJudgeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CJudgeDlg)
	afx_msg void OnBtnRight();
	afx_msg void OnBtnWrong();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnAllPass();
	afx_msg void OnAllFail();
	afx_msg void OnRadio15();
	afx_msg void OnRadio9();
	afx_msg void OnRadio11();
	afx_msg void OnRadio13();
	afx_msg void OnRadio10();
	afx_msg void OnRadio12();
	afx_msg void OnRadio14();
	afx_msg void OnRadio16();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JUDGEDLG_H__3C124362_C49E_401D_A3F0_B8CD03BF0B58__INCLUDED_)
