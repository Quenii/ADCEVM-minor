#if !defined(AFX_PARAMDIALOG_H__896AA89E_7725_4DB4_AFCB_09F99428BB54__INCLUDED_)
#define AFX_PARAMDIALOG_H__896AA89E_7725_4DB4_AFCB_09F99428BB54__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ParamDialog.h : header file
//

#include "ColorStatic.h"
#include "TestAlgView.h"
#include "AdcTestPlatDoc.h"


/////////////////////////////////////////////////////////////////////////////
// CParamDialog dialog


class CTestAlgView;

class CParamDialog : public CDialog
{
// Construction
public:
	CParamDialog(CWnd* pParent = NULL);   // standard constructor	
	CParamDialog( int nChanSel, int nChanCogfigCtrl, int nDataOutModeSel,
		int nLvdsAck, int nParaSerSel, int nTest, int nDepth, int nM0, int nStart, 
		CString strAPath, CString strBPath, CString strCPath, CString strDPath,
		DWORD* pdwAParam, DWORD* pdwBParam, DWORD* pdwCParam, DWORD* pdwDParam,
		int nSampFreq, int nR[5]/*1, int nR2, int nR3, int nR4*/,
		CWnd* pParent = NULL );

// Dialog Data
	//{{AFX_DATA(CParamDialog)
	enum { IDD = IDD_DDC_PARAM };
	CEdit	m_edtR;
	CColorStatic	m_stcParamReg;
	CColorStatic	m_stcParamControl;
	CColorStatic	m_stcParamInput;
	int		m_nChanSel;
	int		m_nChanConfigCtrl;
	int		m_nDataOutModelSel;
	int		m_nLvdsAck;
	int		m_nParaSerSel;
	int		m_nTest;
	int		m_nDepth;
	CTestAlgView* m_pParent;
	int		m_nM0;
	int		m_nStart;
	CString	m_strAPath;
	CString	m_strBPath;
	CString	m_strCPath;
	CString	m_strDPath;
	int		m_nSampFreq;
	//}}AFX_DATA
public:
	CString FileOpen( DWORD* pdwDataBuf );
	DWORD m_dwaAAddr[DMA_SIZE];
	DWORD m_dwaBAddr[DMA_SIZE];
	DWORD m_dwaCAddr[DMA_SIZE];
	DWORD m_dwaDAddr[DMA_SIZE];
	DWORD m_dwaAParam[DMA_SIZE];
	DWORD m_dwaBParam[DMA_SIZE];
	DWORD m_dwaCParam[DMA_SIZE];
	DWORD m_dwaDParam[DMA_SIZE];
	DWORD m_dwaAllAddrParam[DMA_SIZE*4];
	
	int		m_nR[5];//1, m_nR2, m_nR3, m_nR4;
	CString	m_strR;
	
public:
	void ReadByChannel( BYTE byChannel );
	void SendByChannel( BYTE byChannel );
	void CheckData( void );
	void ChangeMode( void );
	void DmaWrite( HANDLE hDevice, BYTE *pbyData, DWORD dwLocalAddr, DWORD dwSize);
	void SendCommand(DWORD dwCmd);
	void IoRead( DWORD dwLocalAddr, DWORD* pdwData );
	void IoWrite( DWORD dwLocalAddr, DWORD* pdwData );
	void DmaRead( HANDLE hDevice, BYTE *pbyData, DWORD dwLocalAddr, DWORD dwSize);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CParamDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CParamDialog)
	afx_msg void OnBTNRead1();
	afx_msg void OnBTNRead2();
	afx_msg void OnBTNRead3();
	afx_msg void OnBTNRead4();
	afx_msg void OnRadioChanSel();
	afx_msg void OnRadioChanSel2();
	afx_msg void OnRadioChanSel3();
	afx_msg void OnRadioChanSel4();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSend();
	afx_msg void OnRadioChannelConfigCtrl();
	afx_msg void OnRadioDataoutModelSel();
	afx_msg void OnRadioLvdsAck();
	afx_msg void OnRadioParaSerSel();
	afx_msg void OnRadioTest();
	afx_msg void OnRadioChannelConfigCtrl1();
	afx_msg void OnRadioDataoutModelSel1();
	afx_msg void OnRadioLvdsAck1();
	afx_msg void OnRadioLvdsAck2();
	afx_msg void OnRadioParaSerSel1();
	afx_msg void OnM0_0();
	afx_msg void OnM0_1();
	afx_msg void OnM0_a();
	afx_msg void OnStart0();
	afx_msg void OnStart1();
	afx_msg void OnStarta();
	afx_msg void OnRadioTest1();
	afx_msg void OnButtonCollect();
	afx_msg void OnClose();
	afx_msg void OnBtnSave();
	afx_msg void OnBtnReset();
	afx_msg void OnBtnReply();
	afx_msg void OnChangeEditR();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARAMDIALOG_H__896AA89E_7725_4DB4_AFCB_09F99428BB54__INCLUDED_)
