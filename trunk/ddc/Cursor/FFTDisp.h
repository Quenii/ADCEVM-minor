#if !defined(AFX_FFTDISP_H__8A497384_F7CD_4AF1_9918_12CDC7627E4E__INCLUDED_)
#define AFX_FFTDISP_H__8A497384_F7CD_4AF1_9918_12CDC7627E4E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FFTDisp.h : header file
//

#include "AdcTestPlatDoc.h"

// FFT缓冲区大小
//#define FFT_DATA_SIZE 4096

#define MAX_POW 5

// 最多显示几个坐标值
#define MAX_AXIS_VALUE 8

/////////////////////////////////////////////////////////////////////////////
// CFFTDisp window

class CFFTDisp : public CWnd
{
// Construction
public:
	CFFTDisp();

// Attributes
public:
	// 使用内存DC
	CDC     m_dcGrid;
	CDC     m_dcPlot;
	CBitmap *m_pbitmapOldGrid;
	CBitmap *m_pbitmapOldPlot;
	CBitmap m_bitmapGrid;
	CBitmap m_bitmapPlot;
	// 绘图区
	CRect  m_rectPlot;
	// 图像区
	CRect m_rectPic;
	// 
	int m_nClientWidth, m_nClientHeight;
	DWORD m_dwPicWidth;
	int m_nBeginPos;
	COLORREF m_crBackColor; 
	CBrush m_brushBack;
	// 图像颜色
	COLORREF m_crImageColor;	
	// 存放计算FFT后的值
	double m_FFTData[MAX_DEPTH];// 去掉x2
	double m_daDispData[MAX_DEPTH];
	// FFT后的最大值
	double m_dMaxData;		
	double m_dMinData;		
	// 通道1，2的点数
	DWORD m_dwDot;	
	DWORD m_dwCurDot;
	// 字体
	CFont m_fntScale;
	CFont m_fntTitle;
	// 是否显示图像
	BOOL m_bDisplay;
	CPoint m_ptRightClick;
	//	
	// 第一次出现有效的值
	BOOL m_bFirstVaule;
	// 第几个fft图像
	BYTE m_byIndex;
	// 与坐标值显示有关的变量
	double m_dMaxGap, m_dGap;
	int m_nRatio;
	// 初始采样频率
	double m_dOrgSampFreq;
	// 鼠标移动时的坐标
	CPoint m_ptMove;
	// fft缓冲区的读写保护
	CCriticalSection m_csFftDataBuf;
	// 是否显示参数
	BOOL m_bShowParam;
	// 输入信号的Vpp
	double m_dVpp;
	// SNR / SFDR / SINAD / ENOB
	double m_dSNR, m_dSFDR, m_dSINAD, m_dENOB;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFFTDisp)
	public:
	//virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID=NULL);
	//}}AFX_VIRTUAL

// Implementation
public:
	//void DrawSpectrum( void );
	void DrawCurve( void );
	void InvalidateCtrl( void );
	virtual ~CFFTDisp();

	// Generated message map functions
protected:
	//{{AFX_MSG(CFFTDisp)
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);	
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
public:	
	double FindNearFloatValue( double dGap );
	void DrawMark( int x, int y, char type, COLORREF color );
	void ZoomRestore( void );
	void ZoomOut( void );
	void ZoomIn( void );
	int FindNearValue( int nValue );
	// 是否在图像区的标志
	BOOL m_bInPic;
	// 鼠标坐标
	CPoint m_pointMouse;
	CString m_strTitle;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FFTDISP_H__8A497384_F7CD_4AF1_9918_12CDC7627E4E__INCLUDED_)
