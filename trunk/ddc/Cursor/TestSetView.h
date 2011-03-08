#if !defined(AFX_TESTSETVIEW_H__56023580_6BCF_4FBD_A2B2_159BF7C29101__INCLUDED_)
#define AFX_TESTSETVIEW_H__56023580_6BCF_4FBD_A2B2_159BF7C29101__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TestSetView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTestSetView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "MainFrm.h"

class CTestSetView : public CFormView
{
protected:
	CTestSetView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CTestSetView)

// Form Data
public:
	//{{AFX_DATA(CTestSetView)
	enum { IDD = IDD_TEST_SET };
	CStatic	m_imgState;
	CBitmap m_bmpGreen;
	CBitmap m_bmpRed;
	CBitmap m_bmpBack;
	int		m_nTestModeSel;
	//}}AFX_DATA

// Attributes
public:	
	int m_nCount;
	// 测试开始标志
	BOOL m_bTestBegin;

// Operations
public:
	void ChangeTestMode( void );
	void FileOpen( BYTE* pbyData );
	void FileSave( BYTE* pbyData, DWORD* pdwSize );
	void SetCheckState( void );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestSetView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CTestSetView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CTestSetView)
	afx_msg void OnCheckLowNoise();
	afx_msg void OnCheckSnr();
	afx_msg void OnCheckSfdr();
	afx_msg void OnCheckChanDisturb();
	afx_msg void OnCheckSinad();
	afx_msg void OnBtnTest();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnRadioBackNoise();
	afx_msg void OnRadioChanDisturbA();
	afx_msg void OnRadioChanDisturbB();
	afx_msg void OnRadioChanDisturbC();
	afx_msg void OnRadioChanDisturbD();
	afx_msg void OnRadioPerf();

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTSETVIEW_H__56023580_6BCF_4FBD_A2B2_159BF7C29101__INCLUDED_)
