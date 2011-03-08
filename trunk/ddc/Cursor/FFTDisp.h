#if !defined(AFX_FFTDISP_H__8A497384_F7CD_4AF1_9918_12CDC7627E4E__INCLUDED_)
#define AFX_FFTDISP_H__8A497384_F7CD_4AF1_9918_12CDC7627E4E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FFTDisp.h : header file
//

#include "AdcTestPlatDoc.h"

// FFT��������С
//#define FFT_DATA_SIZE 4096

#define MAX_POW 5

// �����ʾ��������ֵ
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
	// ʹ���ڴ�DC
	CDC     m_dcGrid;
	CDC     m_dcPlot;
	CBitmap *m_pbitmapOldGrid;
	CBitmap *m_pbitmapOldPlot;
	CBitmap m_bitmapGrid;
	CBitmap m_bitmapPlot;
	// ��ͼ��
	CRect  m_rectPlot;
	// ͼ����
	CRect m_rectPic;
	// 
	int m_nClientWidth, m_nClientHeight;
	DWORD m_dwPicWidth;
	int m_nBeginPos;
	COLORREF m_crBackColor; 
	CBrush m_brushBack;
	// ͼ����ɫ
	COLORREF m_crImageColor;	
	// ��ż���FFT���ֵ
	double m_FFTData[MAX_DEPTH];// ȥ��x2
	double m_daDispData[MAX_DEPTH];
	// FFT������ֵ
	double m_dMaxData;		
	double m_dMinData;		
	// ͨ��1��2�ĵ���
	DWORD m_dwDot;	
	DWORD m_dwCurDot;
	// ����
	CFont m_fntScale;
	CFont m_fntTitle;
	// �Ƿ���ʾͼ��
	BOOL m_bDisplay;
	CPoint m_ptRightClick;
	//	
	// ��һ�γ�����Ч��ֵ
	BOOL m_bFirstVaule;
	// �ڼ���fftͼ��
	BYTE m_byIndex;
	// ������ֵ��ʾ�йصı���
	double m_dMaxGap, m_dGap;
	int m_nRatio;
	// ��ʼ����Ƶ��
	double m_dOrgSampFreq;
	// ����ƶ�ʱ������
	CPoint m_ptMove;
	// fft�������Ķ�д����
	CCriticalSection m_csFftDataBuf;
	// �Ƿ���ʾ����
	BOOL m_bShowParam;
	// �����źŵ�Vpp
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
	// �Ƿ���ͼ�����ı�־
	BOOL m_bInPic;
	// �������
	CPoint m_pointMouse;
	CString m_strTitle;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FFTDISP_H__8A497384_F7CD_4AF1_9918_12CDC7627E4E__INCLUDED_)
