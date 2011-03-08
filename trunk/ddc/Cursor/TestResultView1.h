#if !defined(AFX_TESTRESULTVIEW1_H__110237EE_D7C0_4FE2_ACDE_5C19A861699F__INCLUDED_)
#define AFX_TESTRESULTVIEW1_H__110237EE_D7C0_4FE2_ACDE_5C19A861699F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TestResultView1.h : header file
//

#include "TestSetView.h"
#include "TestSetBatchView.h"
#include "AdcTestPlatDoc.h"

/////////////////////////////////////////////////////////////////////////////
// CTestResultView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CTestResultView : public CFormView
{
protected:
	CTestResultView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CTestResultView)

// Form Data
public:
	//{{AFX_DATA(CTestResultView)
	enum { IDD = IDD_TEST_RESULT };
	CEdit	m_edtTestResult;
	CString	m_strTestResult;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:
	void DrawResult( void );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestResultView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnDraw(CDC* pDC);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CTestResultView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CTestResultView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTRESULTVIEW1_H__110237EE_D7C0_4FE2_ACDE_5C19A861699F__INCLUDED_)
