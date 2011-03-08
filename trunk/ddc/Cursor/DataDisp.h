/*
#if !defined(AFX_FFTDISP_H__8A497384_F7CD_4AF1_9918_12CDC7627E4E__INCLUDED_)
#define AFX_FFTDISP_H__8A497384_F7CD_4AF1_9918_12CDC7627E4E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
*/



// DataDisp.h : header file
//

#ifndef _DATA_DISP_H_
#define _DATA_DISP_H_

#include "AdcTestPlatDoc.h"



// FFT缓冲区大小
//#define FFT_DATA_SIZE 4096

// 边界留量
#define LEFT_MARGIN 25
#define TOP_MARGIN  25
// 垂直方向和水平方向的小格数
#define NUM_VERT 8
#define NUM_HORZ 4

/////////////////////////////////////////////////////////////////////////////
// CDataDisp window

class CDataDisp : public CWnd
{
// Construction
public:
	CDataDisp();

// Attributes
public:	
	// 使用内存DC
	CDC     m_dcGrid;
	CDC     m_dcPlot;
	CBitmap *m_pbitmapOldGrid;
	CBitmap *m_pbitmapOldPlot;
	CBitmap m_bitmapGrid;
	CBitmap m_bitmapPlot;
	// 颜色
	COLORREF m_crImageBack;
	COLORREF m_crImageFore;
	COLORREF m_crYellow;
	// 字体
	CFont m_fntScale;
	CFont m_fntTitle;
	// 显示缓冲区
	//WORD m_waDataDisp[MAX_DEPTH];
	short m_waDataDisp[MAX_DEPTH];
	short m_waDataDisp2[MAX_DEPTH];
	int m_nDot;
	int m_nSaveDot;
	// 是否显示图像
	BOOL m_bDisplay;
	// 一个周期的点数
	int m_nDotPerPeriod;
	// 最大值
	double m_dMaxValue;
	// 显示的路数
	int m_nDisplaySel;
	// 初始幅值
	double m_dAmp;
	int m_nClientWidth, m_nClientHeight;
	// 第几个data图像
	BYTE m_byIndex;
	// mv显示
	BOOL m_bMv;
	

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDataDisp)
	public:
	//virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID=NULL);
	//}}AFX_VIRTUAL

// Implementation
public:
	void DrawData( void );
	void InitDC( void );
	virtual ~CDataDisp();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDataDisp)
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);	
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
public:
	void ZoomRestore( void );
	void ZoomOut( void );
	void ZoomIn( void );
	int FindNearValue(int nValue);
	CString m_strTitle;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif

/*
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FFTDISP_H__8A497384_F7CD_4AF1_9918_12CDC7627E4E__INCLUDED_)
*/
