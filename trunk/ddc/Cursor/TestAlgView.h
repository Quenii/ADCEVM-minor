#if !defined(AFX_TESTALGVIEW_H__FA61C535_0BF4_44D6_BCF4_2DB52A9C5728__INCLUDED_)
#define AFX_TESTALGVIEW_H__FA61C535_0BF4_44D6_BCF4_2DB52A9C5728__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TestAlgView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTestAlgView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "MainFrm.h"
#include "ParamDialog.h"
#include "AdcTestPlatDoc.h"


class CParamDialog;

class CTestAlgView : public CFormView
{
protected:
	CTestAlgView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CTestAlgView)

// Form Data
public:
	//{{AFX_DATA(CTestAlgView)
	enum { IDD = IDD_TEST_ALG };
	CStatic	m_imgState;
	CBitmap m_bmpGreen;
	CBitmap m_bmpRed;
	CBitmap m_bmpBack;
	int m_nCount;
	CParamDialog* m_pParamDlg;
	//}}AFX_DATA

// Attributes
public:
	// 与参数设置窗口相关的变量
	int		m_nChanSel;
	int		m_nChanConfigCtrl;
	int		m_nDataOutModelSel;
	int		m_nLvdsAck;
	int		m_nParaSerSel;
	int		m_nTest;
	int		m_nDepth;	
	int		m_nM0;
	int		m_nStart;
	CString m_strAPath;
	CString m_strBPath;
	CString m_strCPath;
	CString m_strDPath;
	DWORD m_dwaAParam[DMA_SIZE];
	DWORD m_dwaBParam[DMA_SIZE];
	DWORD m_dwaCParam[DMA_SIZE];
	DWORD m_dwaDParam[DMA_SIZE];
	int m_nSampFreq;
	int m_nR[5];//1, m_nR2, m_nR3, m_nR4;
	// 
	BOOL m_bTestBegin;
	BOOL m_bIsFirstTime;

// Operations
public:
	void FileSave( BYTE* pbyData, DWORD* pdwSize );
	void SetState( void );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestAlgView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CTestAlgView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CTestAlgView)
	afx_msg void OnBtnTest();
	afx_msg void OnBtnParam();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTALGVIEW_H__FA61C535_0BF4_44D6_BCF4_2DB52A9C5728__INCLUDED_)
