// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__0B09ABC1_D266_4EDE_ACF6_259D019C9657__INCLUDED_)
#define AFX_MAINFRM_H__0B09ABC1_D266_4EDE_ACF6_259D019C9657__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FixedSplitterWnd.h"
#include "TestSetView.h"
#include "TestSetBatchView.h"
#include "TestResultView1.h"
#include "AdcTestPlatView.h"
#include "TestAlgView.h"

#define FILE_BUF_SIZE (800*1024)

#define ALG_ID       0xF1F1F1F1
#define ADC_ID       0xF3F3F3F3
#define ADC_BATCH_ID 0xF5F5F5F5
#define DDC_BATCH_ID 0xF7F7F7F7

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
	// ʹ�ù̶���С����ͼ
	//CFixedSplitterWnd m_wndSplitter;
	CFixedSplitterWnd m_wndSplitter2;
	CSplitterWnd m_wndSplitter;
	//CSplitterWnd m_wndSplitter2;
	// ����ģʽѡ��
	BOOL m_bTestAlg;
	BOOL m_bTestADC;
	BOOL m_bTestADCBatch;
	BOOL m_bTestDDCBatch;
	// �鿴ģʽѡ��
	BOOL m_bViewAlg;
	BOOL m_bViewADC;
	BOOL m_bViewADCBatch;
	BOOL m_bViewDDCBatch;
	// �ͻ�����С
	int m_nWidth;
	int m_nHeight;
	// �ļ�������
	BYTE m_byaFileBuf[FILE_BUF_SIZE];
	// fft����λ��
	CRect m_rcFFT;
	// ���ű���
	BOOL m_bZoomH, m_bZoomV;
	// ��������ť״̬
	BOOL m_bZoomOut, m_bZoomIn, m_bRestore;
	// �ϵ�/�ϵ�
	BOOL m_bPower;
	// CURSOR
	HCURSOR m_hCursorOut, m_hCursorIn;
	// ��ӵ�״̬��Ϣ��λ��
	int m_nIndexOfState;
	// ״̬��Ϣ
	CString m_strState;
	// ��ʾģʽ
	// 0: ��ͨ�� 1: 4��ͨ��
	// 2: 4��fft 3: 4��data
	// 4: 1/2��fft��data
	// 5: 3/4��fft��data
	BYTE m_byMultiView;
	// ���ŵ��ǵڼ���fftͼ��
	BYTE m_byFftIndex;
	// ���ŵ��ǵڼ���dataͼ��
	BYTE m_byDataIndex;
	// ����״̬
	BOOL m_bRunning;

// Operations
public:
	HBITMAP CopyScreenToBitmap(LPRECT lpRect);
	int SaveBitmapToFile(HBITMAP hBitmap, LPSTR lpFileName);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
public:
	void ChangeMultiView( void );
	CString m_strCurDir;
	void SwitchView( void );
	void FileOpen( CString strFileName );
	CString m_strFileArray[BATCH_FILE_ARRAY_SIZE];
	DWORD m_dwCurFilePos;
	DWORD m_dwFileArraySize;
	BOOL SearchAdcBatchFile( void );
	void FileSave( CString strFileName );
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTestAdcBatch();
	afx_msg void OnUpdateTestAdcBatch(CCmdUI* pCmdUI);
	afx_msg void OnTestAdc();
	afx_msg void OnUpdateTestAdc(CCmdUI* pCmdUI);
	afx_msg void OnTestAlg();
	afx_msg void OnUpdateTestAlg(CCmdUI* pCmdUI);
	afx_msg void OnViewAlgRecord();
	afx_msg void OnUpdateViewAlgRecord(CCmdUI* pCmdUI);
	afx_msg void OnViewAdcRecord();
	afx_msg void OnUpdateViewAdcRecord(CCmdUI* pCmdUI);
	afx_msg void OnViewAdcBatchRecord();
	afx_msg void OnUpdateViewAdcBatchRecord(CCmdUI* pCmdUI);
	afx_msg void OnMyFileSave();
	afx_msg void OnUpdateMyFileSave(CCmdUI* pCmdUI);
	afx_msg void OnMyFileOpen();
	afx_msg void OnUpdateMyFileOpen(CCmdUI* pCmdUI);
	afx_msg void OnFftSave();
	afx_msg void OnMenuZoomBoth();
	afx_msg void OnUpdateMenuZoomBoth(CCmdUI* pCmdUI);
	afx_msg void OnMenuZoomH();
	afx_msg void OnUpdateMenuZoomH(CCmdUI* pCmdUI);
	afx_msg void OnMenuZoomV();
	afx_msg void OnUpdateMenuZoomV(CCmdUI* pCmdUI);
	afx_msg void OnMenuZoomIn();
	afx_msg void OnUpdateMenuZoomIn(CCmdUI* pCmdUI);
	afx_msg void OnMenuZoomOut();
	afx_msg void OnUpdateMenuZoomOut(CCmdUI* pCmdUI);
	afx_msg void OnMenuZoomRestore();
	afx_msg void OnUpdateMenuZoomRestore(CCmdUI* pCmdUI);
	afx_msg void OnToolbarRestore();
	afx_msg void OnUpdateToolbarRestore(CCmdUI* pCmdUI);
	afx_msg void OnToolbarZoomIn();
	afx_msg void OnUpdateToolbarZoomIn(CCmdUI* pCmdUI);
	afx_msg void OnToolbarZoomOut();
	afx_msg void OnUpdateToolbarZoomOut(CCmdUI* pCmdUI);
	afx_msg void OnMenuFftZoomIn();
	afx_msg void OnUpdateMenuFftZoomIn(CCmdUI* pCmdUI);
	afx_msg void OnMenuFftZoomOut();
	afx_msg void OnUpdateMenuFftZoomOut(CCmdUI* pCmdUI);
	afx_msg void OnMenuFftZoomRestore();
	afx_msg void OnUpdateMenuFftZoomRestore(CCmdUI* pCmdUI);
	afx_msg void OnUpdateState( CCmdUI* pCmdUI );
	afx_msg void OnToolbarMultiView();
	afx_msg void OnUpdateToolbarMultiView(CCmdUI* pCmdUI);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnToolbarStart();
	afx_msg void OnUpdateToolbarStart(CCmdUI* pCmdUI);
	afx_msg void OnToolbarEnd();
	afx_msg void OnUpdateToolbarEnd(CCmdUI* pCmdUI);
	afx_msg void OnToolbarSingleView();
	afx_msg void OnUpdateToolbarSingleView(CCmdUI* pCmdUI);
	afx_msg void OnToolbarMultiViewF();
	afx_msg void OnUpdateToolbarMultiViewF(CCmdUI* pCmdUI);
	afx_msg void OnToolbarMultiViewS();
	afx_msg void OnUpdateToolbarMultiViewS(CCmdUI* pCmdUI);
	afx_msg void OnToolbarMultiViewFs1();
	afx_msg void OnUpdateToolbarMultiViewFs1(CCmdUI* pCmdUI);
	afx_msg void OnToolbarMultiViewFs2();
	afx_msg void OnUpdateToolbarMultiViewFs2(CCmdUI* pCmdUI);
	afx_msg void OnToolbarPower();
	afx_msg void OnUpdateToolbarPower(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__0B09ABC1_D266_4EDE_ACF6_259D019C9657__INCLUDED_)
