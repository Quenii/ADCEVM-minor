#if !defined(AFX_TESTSETBATCHVIEW_H__D11D586C_37B4_4FE4_90F5_3BF783F959DC__INCLUDED_)
#define AFX_TESTSETBATCHVIEW_H__D11D586C_37B4_4FE4_90F5_3BF783F959DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TestSetBatchView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTestSetBatchView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "MainFrm.h"
#include "ColorStatic.h"
#include "ParamDialog.h"
#include "JudgeDlg.h"

// 测试项
#define TEST_ITEM 6
#define TEST_CH 4

class CParamDialog;
class CJudgeDlg;

class CTestSetBatchView : public CFormView
{
protected:
	CTestSetBatchView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CTestSetBatchView)

// Form Data
public:
	//{{AFX_DATA(CTestSetBatchView)
	enum { IDD = IDD_TEST_SET_BATCH };
	CColorStatic	m_stcRegTest2;
	CColorStatic	m_stcRegTest;
	CColorStatic	m_stcM0Test2;
	CColorStatic	m_stcM0Test;
	CColorStatic	m_stcAdcTest2;
	CColorStatic	m_stcAdcTest;
	CColorStatic	m_stc5MTest2;
	CColorStatic	m_stc5MTest;
	CColorStatic	m_stc2MTest2;
	CColorStatic	m_stc2MTest;
	CColorStatic	m_stc20MTest2;
	CColorStatic	m_stc20MTest;
	CString	m_strID;
	CString	m_strBackNoise;
	CString	m_strSNR;
	CString	m_strSFDR;
	CString	m_strChanDisturb;
	CString	m_strSINAD;
	CString	m_strPassCount;
	CString	m_strErrorCount;
	CBitmap m_bmpGreen;
	CBitmap m_bmpRed;
	CBitmap m_bmpBack;
	CBitmap m_bmpCross;
	CBitmap m_bmpOk;
	int m_nCount;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:	
	CString m_strCurFileName;
	BOOL m_bTestBegin;	
	int m_nPassCount;
	int m_nErrorCount;
	BOOL m_bFirst;
	// 参数设置对象
	CParamDialog* m_pParamDlg;
	// 判断测试是否正确的对话框
	CJudgeDlg* m_pJudgeDlgBack;
	// 测试结果
	BYTE m_byaResult[TEST_ITEM][TEST_CH];

public:
	void SaveTxtFile( void );
	void SetTestResult( CString &strResult, CString &strSrc, BYTE *byR );
	void AutoSaveFile( void );
	CString m_str20MFileName;
	CString m_str5MFileName;
	CString m_str2MFileName;
	void LoadParamFile( CString strFileName );
	void SetR( int nR );
	void Test20M( void );
	void Test5M( void );
	void TestM0( void );
	void Test2M( void );
	void TestAdc( void );
	void InitStaticColor( void );
	void SetStaticColor( int nIndex, int nType );
	BOOL SearchFile( CString strFileName );
	void FileOpen( BYTE* pbyData );
	void FileSave( BYTE* pbyData, DWORD* pdwSize );
	void SetState( void );
	void DoTestBatch( void );
	BOOL TestReg( BYTE * );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestSetBatchView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnDraw(CDC* pDC);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CTestSetBatchView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CTestSetBatchView)
	afx_msg void OnBtnTest();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnBtnRetry();
	afx_msg void OnCheckChanDisturb2();
	afx_msg void OnCheckLowNoise2();
	afx_msg void OnCheckSfdr2();
	afx_msg void OnCheckSinad2();
	afx_msg void OnCheckSnr2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTSETBATCHVIEW_H__D11D586C_37B4_4FE4_90F5_3BF783F959DC__INCLUDED_)
