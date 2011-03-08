// AdcTestPlatView.h : interface of the CAdcTestPlatView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ADCTESTPLATVIEW_H__EB392703_CD45_4027_A4EB_B6D735E8C1B5__INCLUDED_)
#define AFX_ADCTESTPLATVIEW_H__EB392703_CD45_4027_A4EB_B6D735E8C1B5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FFTDisp.h"
#include "DataDisp.h"
#include "ColorStatic.h"
#include "fft.h"

//#include "libfft.h"
//#include "libplot.h"
//#include "libcomplexfft.h"
//#include "libtriplot.h"
//#include "libdualplot.h"

#define BATCH_FILE_ARRAY_SIZE 1000

class CAdcTestPlatView : public CFormView
{
protected: // create from serialization only
	CAdcTestPlatView();
	DECLARE_DYNCREATE(CAdcTestPlatView)

public:
	//{{AFX_DATA(CAdcTestPlatView)
	enum { IDD = IDD_ADCTESTPLAT_FORM };
	CTabCtrl	m_tcTestMode;
	CColorStatic	m_stcMode;
	CScrollBar	m_scrlPic;
	CSpinButtonCtrl	m_spinID;
	CString	m_strID;
	int		m_nPos;
	BOOL	m_bMatlab;
	BOOL	m_bIData;
	BOOL	m_bQData;
	BOOL	m_bAlgAutoSave;
	//}}AFX_DATA

// Attributes
public:
	CAdcTestPlatDoc* GetDocument();

// Operations
public:
	// fft相关的变量
/*	mxArray* mxIn;
	mxArray* mxOut;
	mxArray* mxDotnum;
	// plot相关变量
	mxArray* mxX;
	mxArray* mxY;
	// complex fft相关的变量
	mxArray* mxI;
	mxArray* mxQ;
	mxArray* mxNum;
	mxArray* mxC;
	mxArray* mxT;
	*/

// 	CFFTDisp m_FFTDisp;
// 	CDataDisp m_DataDisp;	

	double daI[MAX_DEPTH];
	double daQ[MAX_DEPTH];
	double daC[MAX_DEPTH];
	
	double daIn[MAX_DEPTH];
	double daOut[MAX_DEPTH];

	double daX[MAX_DEPTH/2];
	double daY[MAX_DEPTH/2];
	double daT[MAX_DEPTH];
	
	// 算法测试开始标志
	//BOOL m_bAlgStart;

	// 记录几个视图的大小
	CRect /*m_rcFFT, m_rcData, */m_rcScroll;
	CRect m_rcFFT[5];
	CRect m_rcData[5];
	CRect m_rcFFT_F[5];//, m_rcFFT2_F, m_rcFFT3_F, m_rcFFT4_F;
	CRect m_rcData_S[5];//, m_rcData2_S, m_rcData3_S, m_rcData4_S;
	CRect m_rcFFT1_FS, m_rcFFT2_FS, m_rcData1_FS, m_rcData2_FS;
	CRect m_rcFFT3_FS, m_rcFFT4_FS, m_rcData3_FS, m_rcData4_FS;
	
	// 4个通道视图
	CFFTDisp m_FFTDisp[5];	
	CDataDisp m_DataDisp[5];

public:
	//void DrawSpectrum( void );
	void SetState( void );
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAdcTestPlatView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:	
	void AlgDispFourChannel( void );
	void AdcDispFourChannel( void );
	void ChangeWindow( void );
	void Display( void );
	void AdcTestSet( void );
	void AlgDisp( void );
	void AlgTestSet( void );
	void AdcDisp( void );
	CString DataSave( void );
	virtual ~CAdcTestPlatView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAdcTestPlatView)
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnCheckMatlab();
	afx_msg void OnCheckIData();
	afx_msg void OnCheckQData();
	afx_msg void OnCheckAlgAutoSave();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in AdcTestPlatView.cpp
inline CAdcTestPlatDoc* CAdcTestPlatView::GetDocument()
   { return (CAdcTestPlatDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADCTESTPLATVIEW_H__EB392703_CD45_4027_A4EB_B6D735E8C1B5__INCLUDED_)
