// AdcTestPlatView.cpp : implementation of the CAdcTestPlatView class
//

#include "stdafx.h"
#include "AdcTestPlat.h"

#include "AdcTestPlatDoc.h"
#include "AdcTestPlatView.h"
#include "MainFrm.h"
#include "m2c.h"
#include "GlobalData.h"

#include <math.h>

//#include "libadc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TEST_DATA

static GlobalData * pGB = 0;
/////////////////////////////////////////////////////////////////////////////
// CAdcTestPlatView

IMPLEMENT_DYNCREATE(CAdcTestPlatView, CFormView)

BEGIN_MESSAGE_MAP(CAdcTestPlatView, CFormView)
	//{{AFX_MSG_MAP(CAdcTestPlatView)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_VSCROLL()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_CHECK_MATLAB, OnCheckMatlab)
	ON_BN_CLICKED(IDC_CHECK_I_DATA, OnCheckIData)
	ON_BN_CLICKED(IDC_CHECK_Q_DATA, OnCheckQData)
	ON_BN_CLICKED(IDC_CHECK_ALG_AUTO_SAVE, OnCheckAlgAutoSave)	
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

#define DOUBLE_PI   6.283185307179586476925286766559

/* 输入数据为data，data是一组复数，偶数位存储的是复数的实数部分，奇数位存储的是复数的虚数部分。
    data的长度与n相匹配。注意：这里的n并非是data的长度，data的实际长度为(2 * 2^n),存储了N = 2^n个复数。

    输出也存放在data中。

    以正向傅里叶变换为例，作为输入data中存储的是以delta为时间间隔时域函数的振幅抽样值。
	经过函数计算后data中存放输出，存储的是以1/(N * delta)为频率间隔频域像函数值。
	频率范围为0Hz,1/(N * delta),2/(N * delta) ... (N / 2 - 1) / N * delta, +/- 1 / delta, -(N / 2 - 1) / N * delta ... -2/(N * delta), -1/(N * delta)。注意这是一个中间大两边小的排列。

    如果将isInverse设置为true则计算逆傅里叶变换。
*/



/////////////////////////////////////////////////////////////////////////////
// CAdcTestPlatView construction/destruction

CAdcTestPlatView::CAdcTestPlatView()
	: CFormView(CAdcTestPlatView::IDD)
{
	//{{AFX_DATA_INIT(CAdcTestPlatView)
	m_strID = _T("");
	m_nPos = 0;
	m_bMatlab = FALSE;
	m_bIData = TRUE;
	m_bQData = TRUE;
		
	m_bAlgAutoSave = FALSE;
	
	//}}AFX_DATA_INIT
	// TODO: add construction code here
	
	
}

CAdcTestPlatView::~CAdcTestPlatView()
{
}

void CAdcTestPlatView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAdcTestPlatView)
	DDX_Control(pDX, IDC_STATIC_MODE, m_stcMode);
	DDX_Control(pDX, IDC_SCROLLBAR_PIC, m_scrlPic);
	DDX_Control(pDX, IDC_SPIN_ID, m_spinID);
	DDX_Text(pDX, IDC_EDIT_ID, m_strID);
	DDX_Scroll(pDX, IDC_SCROLLBAR_PIC, m_nPos);
	DDX_Check(pDX, IDC_CHECK_MATLAB, m_bMatlab);
	DDX_Check(pDX, IDC_CHECK_I_DATA, m_bIData);
	DDX_Check(pDX, IDC_CHECK_Q_DATA, m_bQData);
	DDX_Check(pDX, IDC_CHECK_ALG_AUTO_SAVE, m_bAlgAutoSave);
	//}}AFX_DATA_MAP
}

BOOL CAdcTestPlatView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	
	return CFormView::PreCreateWindow(cs);
}

void CAdcTestPlatView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	//ResizeParentToFit();
	// 电路ID微调按钮初始化
	m_spinID.SetRange( 0, 100 );
	m_spinID.SetPos( 0 );
	// 初始化滚动条
	m_scrlPic.SetScrollRange( 0, CHANNEL_NUM-1 );
	m_scrlPic.SetScrollPos( 0 );
	// 静态文本工作模式
	m_stcMode.SetTextColor( RGB(0,0,255) );
	
	
	// FFT窗口绘制
	CRect rc, rcFFT, rcWnd;
	GetClientRect( &rc );
	GetWindowRect( &rcWnd );
	rcFFT.left = 2;
	rcFFT.top = 50;
	rcFFT.right = rc.right;
	int nHeight = ((CMainFrame*)GetParentFrame())->m_nHeight;
	rcFFT.bottom = ( nHeight - rcFFT.top ) / 2 + rcFFT.top;
	m_FFTDisp[0].Create( WS_VISIBLE | WS_CHILD, rcFFT, this) ;	
	m_FFTDisp[0].m_byIndex = 0;

	// 数据窗口绘制
	m_DataDisp[0].Create( WS_VISIBLE | WS_CHILD, rcFFT, this );
	m_DataDisp[0].m_byIndex = 0;


	// 四个通道的对象
	CRect rc1( 0, 0, 100, 100 );
	for (int i=1; i<5; ++i)
	{
		m_FFTDisp[i].Create( WS_VISIBLE | WS_CHILD, rc1, this);
		m_DataDisp[i].Create( WS_VISIBLE | WS_CHILD, rc1, this );
		m_FFTDisp[i].ShowWindow( SW_HIDE );
		m_DataDisp[i].ShowWindow( SW_HIDE );
		m_FFTDisp[i].m_byIndex = i;
		m_DataDisp[i].m_byIndex = i;
	}
	
	// adc显示
//	AdcDisp();
	
}

/////////////////////////////////////////////////////////////////////////////
// CAdcTestPlatView diagnostics

#ifdef _DEBUG
void CAdcTestPlatView::AssertValid() const
{
	CFormView::AssertValid();
}

void CAdcTestPlatView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CAdcTestPlatDoc* CAdcTestPlatView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAdcTestPlatDoc)));
	return (CAdcTestPlatDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAdcTestPlatView message handlers

void CAdcTestPlatView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	Display();
	
	// TODO: Add your message handler code here
	
	// Do not call CFormView::OnPaint() for painting messages
}

void CAdcTestPlatView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	CMainFrame* pFrame = (CMainFrame*)GetParentFrame();
	if ( cx > 0 && cy > 0 && pFrame != NULL )
	{		
		// 0. 单通道的区域
		// FFT窗口
		CRect rcFFT( 2, 20, cx-20, 20+(cy-20)*4/7 );
		m_rcFFT[0].CopyRect( &rcFFT );
		// 保存fft窗口位置		
		(pFrame->m_rcFFT).CopyRect( &rcFFT );
		ClientToScreen( &(pFrame->m_rcFFT) );		
		// 数据窗口
		CRect rcData( 2, rcFFT.bottom+5, cx-20, cy );
		m_rcData[0].CopyRect( &rcData );
		// 滚动条
		CRect rcScroll( cx-20, 20, cx, cy );
		m_rcScroll.CopyRect( &rcScroll );

		// 四个通道的显示区域
		int nWidth = cx;
		int nHeight = cy-20;
		
		// 1. 四个通道视图
		for (int i=1; i<5; ++i)
		{
			m_rcFFT[i].left = (i%2) ? 2 : nWidth / 2;
			m_rcFFT[i].top = (i<3) ? 20 : 20 + nHeight / 2;
			m_rcFFT[i].right = (i%2) ? nWidth / 2 : nWidth;
			m_rcFFT[i].bottom = m_rcFFT[i].top + nHeight / 4;
			
			m_rcData[i].left = (i%2) ? 2 : nWidth / 2;
			m_rcData[i].top = (i<3) ? 20 + nHeight / 4 : 20 + nHeight * 3 / 4;
			m_rcData[i].right = (i%2) ? nWidth / 2 : nWidth;
			m_rcData[i].bottom = (i<3) ? 20 + nHeight / 2 : 20 + nHeight;

			m_rcFFT_F[i].left = (i%2) ? 2 : nWidth / 2;
			m_rcFFT_F[i].top = (i<3) ? 20 : 20 + nHeight / 2;
			m_rcFFT_F[i].right = (i%2) ? nWidth / 2 : nWidth;
			m_rcFFT_F[i].bottom = (i<3) ? m_rcFFT_F[i].top + nHeight / 2 : 20 + nHeight;				

			m_rcData_S[i].left = (i%2) ? 2 : nWidth / 2;
			m_rcData_S[i].top = (i<3) ? 20 : 20 + nHeight / 2;
			m_rcData_S[i].right = (i%2) ? nWidth / 2 : nWidth;
			m_rcData_S[i].bottom = (i<3) ? m_rcFFT_F[i].top + nHeight / 2 : 20 + nHeight;			

		}
		
		// 4. 第1/2通道的fft和data
		m_rcFFT1_FS.left = 2;
		m_rcFFT1_FS.top = 20;
		m_rcFFT1_FS.right = nWidth / 2;
		m_rcFFT1_FS.bottom = m_rcFFT1_FS.top + nHeight / 2;

		m_rcData1_FS.left = 2;
		m_rcData1_FS.top = 20 + nHeight / 2;
		m_rcData1_FS.right = nWidth / 2;
		m_rcData1_FS.bottom = 20 + nHeight;

		m_rcFFT2_FS.left = nWidth / 2;
		m_rcFFT2_FS.top = 20;
		m_rcFFT2_FS.right = nWidth;
		m_rcFFT2_FS.bottom = m_rcFFT2_FS.top + nHeight / 2;

		m_rcData2_FS.left = nWidth / 2;
		m_rcData2_FS.top = 20 + nHeight / 2;
		m_rcData2_FS.right = nWidth;
		m_rcData2_FS.bottom = 20 + nHeight;
				
				
		// 5. 第3/4通道的fft和data
		m_rcFFT3_FS.left = 2;
		m_rcFFT3_FS.top = 20;
		m_rcFFT3_FS.right = nWidth / 2;
		m_rcFFT3_FS.bottom = m_rcFFT3_FS.top + nHeight / 2;

		m_rcData3_FS.left = 2;
		m_rcData3_FS.top = 20 + nHeight / 2;
		m_rcData3_FS.right = nWidth / 2;
		m_rcData3_FS.bottom = 20 + nHeight;

		m_rcFFT4_FS.left = nWidth / 2;
		m_rcFFT4_FS.top = 20;
		m_rcFFT4_FS.right = nWidth;
		m_rcFFT4_FS.bottom = m_rcFFT4_FS.top + nHeight / 2;

		m_rcData4_FS.left = nWidth / 2;
		m_rcData4_FS.top = 20 + nHeight / 2;
		m_rcData4_FS.right = nWidth;
		m_rcData4_FS.bottom = 20 + nHeight;


		// 根据区域，显示不同内容
		ChangeWindow();
	}
}

void CAdcTestPlatView::SetState( void )
{
	CDocument* pDoc = GetDocument();
	// 查找设置窗口
	POSITION pos = pDoc->GetFirstViewPosition();
	while ( pos != NULL )
	{
		CView* pView = pDoc->GetNextView( pos );
		// ADC测试
		if ( pView->IsKindOf(RUNTIME_CLASS(CTestSetView)) )
		{
		}
		// ADC批量测试
		if ( pView->IsKindOf(RUNTIME_CLASS(CTestSetBatchView)) )
		{
		}
	}
	// 设置当前的工作模式
	CString strMode;
	// ADC测试模式
	if ( ((CMainFrame*)GetParentFrame())->m_bTestADC)
	{
		strMode = "ADC测试模式";
	}
	if ( ((CMainFrame*)GetParentFrame())->m_bTestAlg )
	{
		strMode = "算法测试模式";
	}
	if ( ((CMainFrame*)GetParentFrame())->m_bTestADCBatch )
	{
		strMode = "批量测试模式";
	}
	if ( ((CMainFrame*)GetParentFrame())->m_bTestDDCBatch )
	{
		strMode = "ADC+DDC批量测试模式";
	}
	if ( ((CMainFrame*)GetParentFrame())->m_bViewAlg )
	{
		strMode = "算法查看模式";
	}
	if ( ((CMainFrame*)GetParentFrame())->m_bViewADC )
	{
		strMode = "ADC查看模式";
	}
	if ( ((CMainFrame*)GetParentFrame())->m_bViewADCBatch )
	{
		strMode = "批量查看模式";
	}
	if ( ((CMainFrame*)GetParentFrame())->m_bViewDDCBatch )
	{
		strMode = "ADC+DDC批量查看模式";
	}
	
	// 设置到界面上
	if ( GetDlgItem( IDC_STATIC_MODE ) != NULL )
	{
		GetDlgItem( IDC_STATIC_MODE )->SetWindowText( strMode );
	}
	// ADC批量查看模式显示电路ID	
	if ( ((CMainFrame*)GetParentFrame())->m_bViewADCBatch )
	{
		GetDlgItem( IDC_STATIC_ID )->ShowWindow( SW_SHOW );
		GetDlgItem( IDC_EDIT_ID )->ShowWindow( SW_SHOW );
		GetDlgItem( IDC_SPIN_ID )->ShowWindow( SW_SHOW );
	}
	else
	{
		GetDlgItem( IDC_STATIC_ID )->ShowWindow( SW_HIDE );
		GetDlgItem( IDC_EDIT_ID )->ShowWindow( SW_HIDE );
		GetDlgItem( IDC_SPIN_ID )->ShowWindow( SW_HIDE );
	}
	
}

BOOL CAdcTestPlatView::OnEraseBkgnd(CDC* pDC) 
{
	// 直接返回,效果是不会闪动
	//return TRUE;
	return CFormView::OnEraseBkgnd( pDC );
}

void CAdcTestPlatView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	// 如果到微调按钮的终点，直接退出
	if ( nSBCode == SB_ENDSCROLL )
	{
		return;
	}
	
	// 单击电路ID的微调按钮
	if ( pScrollBar->GetDlgCtrlID() == IDC_SPIN_ID )
	{
		CMainFrame* pFrame = (CMainFrame*)GetParentFrame();
		if ( pFrame == NULL )
		{
			return;
		}
		// 根据微调按钮的位置确定当前应该显示的电路ID
		pFrame->m_dwCurFilePos = nPos;
		m_strID = pFrame->m_strFileArray[pFrame->m_dwCurFilePos].Left(8);
		UpdateData( FALSE );		
		// 调用主框架的文件打开功能，显示当前的批量测试
		pFrame->FileOpen( pFrame->m_strFileArray[pFrame->m_dwCurFilePos] );
	}

	CMainFrame* pFrame = (CMainFrame*)GetParentFrame();
	if ( pFrame == NULL )
	{
		return;
	}
	// 单击垂直滚动条(ADC测试)
	//if ( (pScrollBar->GetDlgCtrlID() == IDC_SCROLLBAR_PIC) && (pFrame->m_bTestADC) )
	if ( (pScrollBar->GetDlgCtrlID() == IDC_SCROLLBAR_PIC) )
	{
		switch ( nSBCode )
		{
			//case SB_THUMBPOSITION:
			case SB_THUMBTRACK:
			{
				m_scrlPic.SetScrollPos(nPos);
				break;
			}
			case SB_LINEUP:
			case SB_PAGEUP:
			{
				int nPosition = m_scrlPic.GetScrollPos();
				if ( nPosition > 0 )
				{
					nPosition--; 
				}
				m_scrlPic.SetScrollPos(nPosition);
				break;
			}
			case SB_LINEDOWN:
			case SB_PAGEDOWN:
			{
				int nPosition = m_scrlPic.GetScrollPos();
				if ( nPosition < CHANNEL_NUM-1 )
				{
					nPosition++; 
				}
				m_scrlPic.SetScrollPos(nPosition);
				break;
			}
			default:
				break;
		}
		// 刷新视图会引起整个右边屏幕的闪动
		//Invalidate();
		//DrawData();
		//DrawSpectrum();		
		//AdcDisp();
		//SetState();
		Display();
	}
	CFormView::OnVScroll(nSBCode, nPos, pScrollBar);
}


void CAdcTestPlatView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	Display();	
}


void CAdcTestPlatView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CFormView::OnMouseMove(nFlags, point);
}


// 保存当前的原始数据，并返回文件名(不带后缀)
CString CAdcTestPlatView::DataSave()
{
	CString strFileName;
	//WORD* pwTemp;
	short* pwTemp;
	short* pwTemp2;
	CString strDataFileName;
	int j;

	// 根据设置视图选择的测试项，生产文件名
	CAdcTestPlatDoc* pDoc = (CAdcTestPlatDoc*)GetDocument();
	if ( pDoc != NULL )
	{
		switch ( pDoc->m_nTestModeSel )
		{
			case 0:
			{
				strFileName = "底噪声测试_";
				break;
			}
			case 1:
			{
				strFileName = "SNR_SFDR_SINAD_ENOB测试_";
				break;
			}
			case 2:
			{
				strFileName = "A通道串音测试_";
				break;
			}
			case 3:
			{
				strFileName = "B通道串音测试_";
				break;
			}
			case 4:
			{
				strFileName = "C通道串音测试_";
				break;
			}
			case 5:
			{
				strFileName = "D通道串音测试_";
				break;
			}
			case 6:
			{
				strFileName = "DDC_";
				break;
			}	
			default:
				break;
		}
		// 根据滚动条的位置，选择某个通道的数据存储
		UpdateData( TRUE );
		// adc测试
		if ( pDoc->m_nTestModeSel >= 0 && pDoc->m_nTestModeSel <= 5 )
		{		
			switch ( m_nPos )
			{
				case 0:
				{
					pwTemp = pDoc->m_waCh1Signal;
					strFileName += "A通道_";
					break;
				}
				case 1:
				{
					pwTemp = pDoc->m_waCh2Signal;
					strFileName += "B通道_";
					break;
				}
				case 2:
				{
					pwTemp = pDoc->m_waCh3Signal;
					strFileName += "C通道_";
					break;
				}
				case 3:
				{
					pwTemp = pDoc->m_waCh4Signal;
					strFileName += "D通道_";
					break;
				}
				default:
					break;
			}
		}
		// 算法测试
		if ( pDoc->m_nTestModeSel == 6 )
		{
			switch ( m_nPos )
			{
				case 0:
				{
					pwTemp = pDoc->m_waAiData;
					pwTemp2 = pDoc->m_waAqData;
					strFileName += "A通道_";
					break;
				}
				case 1:
				{
					pwTemp = pDoc->m_waBiData;
					pwTemp2 = pDoc->m_waBqData;
					strFileName += "B通道_";
					break;
				}
				case 2:
				{
					pwTemp = pDoc->m_waCiData;
					pwTemp2 = pDoc->m_waCqData;
					strFileName += "C通道_";
					break;
				}
				case 3:
				{
					pwTemp = pDoc->m_waDiData;
					pwTemp2 = pDoc->m_waDqData;
					strFileName += "D通道_";
					break;
				}
				default:
					break;
			}
		}
		// 获取系统时间，生成文件名
		SYSTEMTIME CurrentTime;
		CString strTime;
		GetSystemTime( &CurrentTime );	
		//CurrentTime.wHour += 8;
		strTime.Format( "%04d%02d%02d%02d%02d%02d", CurrentTime.wYear, CurrentTime.wMonth,
			CurrentTime.wDay, CurrentTime.wHour, CurrentTime.wMinute,CurrentTime.wSecond );
		strFileName += strTime;
		// 原始数据保存为文本文件
		strDataFileName = strFileName + ".txt";
		CString strData;
		CStdioFile file;
		file.Open( strDataFileName, CFile::modeWrite | CFile::modeCreate | CFile::typeText  );
		// adc测试
		if ( pDoc->m_nTestModeSel >= 0 && pDoc->m_nTestModeSel <= 5 )
		{
			for ( j = 0; j < MAX_DEPTH; j++ )
			{
				strData.Format( "%d\n", pwTemp[j] );
				file.WriteString( strData );
			}
		}
		// 算法测试
		if ( pDoc->m_nTestModeSel == 6 )
		{
			for ( j = 0; j < pDoc->m_nAlgDepth; j++ )
			{
				strData.Format( "%d\n", pwTemp[j] );
				file.WriteString( strData );
			}
			for ( j = 0; j < pDoc->m_nAlgDepth; j++ )
			{
				strData.Format( "%d\n", pwTemp2[j] );
				file.WriteString( strData );
			}
		}
		file.Close();
		
	}	
	// 返回文件名
	return strFileName;
}

// 计算FFT显示和原始数据显示需要的参数
// 包括FFT视图上的Ain和数据视图上的一个周期几个点
void CAdcTestPlatView::AdcDisp()
{
	int i;	
	double dSnrThreshold = 0;
	double dSfdrThreshold = 0;
	double dSinadThreshold = 0;
	double dBackNoiseThreshold = 0;
	double dChanDisturbThreshold = 0;
	
	double dDotnum;

	short* pwTemp = NULL;
	double dActualMax;
	double dActualMin;
	TRACE("\nAdcDisp() Calling...\n");

	UpdateData( TRUE );
	CAdcTestPlatDoc* pDoc = (CAdcTestPlatDoc*)GetDocument();
	if ( pDoc != NULL )
	{
		// 根据不同位置选择不同通道
		switch ( m_nPos )
		{
			case 0:
			{
				pwTemp = pDoc->m_waCh1Signal;
				m_DataDisp[0].m_strTitle = "A通道";
				m_FFTDisp[0].m_strTitle = "A通道";
				break;
			}
			case 1:
			{
				pwTemp = pDoc->m_waCh2Signal;
				m_DataDisp[0].m_strTitle = "B通道";
				m_FFTDisp[0].m_strTitle = "B通道";
				break;
			}
			case 2:
			{
				pwTemp = pDoc->m_waCh3Signal;
				m_DataDisp[0].m_strTitle = "C通道";
				m_FFTDisp[0].m_strTitle = "C通道";
				break;
			}
			case 3:
			{
				pwTemp = pDoc->m_waCh4Signal;
				m_DataDisp[0].m_strTitle = "D通道";
				m_FFTDisp[0].m_strTitle = "D通道";
				break;
			}
			default:
			{
				pwTemp = pDoc->m_waCh1Signal;
				m_DataDisp[0].m_strTitle = "A通道";
				m_FFTDisp[0].m_strTitle = "A通道";
				break;
			}
				
		}

		////////////////////////////////////////////////////////////////
		// 调用matlab计算fft
// 		for ( i = 0; i < MAX_DEPTH; i++ )
// 		{
// 			daIn[i] = pwTemp[i];
// 		}
// 		FFT(daIn, MAX_DEPTH, daY, MAX_DEPTH / 2);		

		dDotnum = MAX_DEPTH;

		
		// plot
		for ( i = 0; i < MAX_DEPTH/2; i++ )
		{
			//daX[i] = i; 
			// 注意数据的溢出
			daX[i] = (double)i * SAMP_FREQ / MAX_DEPTH; 
		}
		for ( i = 0; i < MAX_DEPTH; i++ )
		{			
			daT[i] = (double)i; 
		}

		// ADC测试显示参数
		m_FFTDisp[0].m_bShowParam = TRUE;
		// 使用matlab的fft结果
		// 互斥
// 		CSingleLock slDataBuf( &(m_FFTDisp[0].m_csFftDataBuf) );
// 		slDataBuf.Lock();
// 		memcpy( m_FFTDisp[0].m_FFTData, daY, (MAX_DEPTH / 2) * sizeof(double) );
		ASSERT(m_nPos < 4);
		memcpy( m_FFTDisp[0].m_FFTData, &(pGB->dataSet[m_nPos].y[0]), (MAX_DEPTH) * sizeof(double) );

		// 保存SNR/SFDR/SINAD/ENOB
// 		m_FFTDisp[0].m_dSNR = pDoc->m_daResultSNR[m_nPos];
// 		m_FFTDisp[0].m_dSFDR = pDoc->m_daResultSFDR[m_nPos];
// 		m_FFTDisp[0].m_dSINAD = pDoc->m_daResultSINAD[m_nPos];
// 		m_FFTDisp[0].m_dENOB = pDoc->m_daResultENOB[m_nPos];
	
		m_FFTDisp[0].m_dSNR = pGB->dataSet[m_nPos].SNR;
		m_FFTDisp[0].m_dSFDR = pGB->dataSet[m_nPos].SFDR;
		m_FFTDisp[0].m_dSINAD = pGB->dataSet[m_nPos].SINAD;
		m_FFTDisp[0].m_dENOB = pGB->dataSet[m_nPos].ENOB;

		// 查找最大值，算频率
		int nPos;
		double dMaxData;
		dMaxData = -10000;
		for ( i = 0; i < MAX_DEPTH / 2; i++ )
		{
			if ( m_FFTDisp[0].m_FFTData[i] > dMaxData )
			{
				nPos = i;
				dMaxData = m_FFTDisp[0].m_FFTData[i];
			}
		}
		// 计算时间显示一个周期的点数
		if ( nPos > 0 )
		{
			m_DataDisp[0].m_nDotPerPeriod = MAX_DEPTH / nPos;
		}
		
		// 2.根据原始数据计算Ain
		memcpy( m_DataDisp[0].m_waDataDisp, pwTemp, MAX_DEPTH*2 );				
		dActualMax = -MAX_VALUE;
		dActualMin = MAX_VALUE;
		// 查找最大值和最小值
		for ( i = 0; i < MAX_DEPTH; i++ )
		{
			if ( m_DataDisp[0].m_waDataDisp[i] > dActualMax )
			{				
				dActualMax = m_DataDisp[0].m_waDataDisp[i];
			}
			if ( m_DataDisp[0].m_waDataDisp[i] < dActualMin )
			{			
				dActualMin = m_DataDisp[0].m_waDataDisp[i];
			}
		}
		// 计算Vpp(Ain由Vpp计算得出)
		m_FFTDisp[0].m_dVpp = (dActualMax - dActualMin) / MAX_VALUE;

		// 显示一个波形
		m_DataDisp[0].m_nDisplaySel = 1;
		// 3.更新图形显示
		//m_FFTDisp[0].DrawSpectrum();		
		m_FFTDisp[0].DrawCurve();
		m_DataDisp[0].DrawData();
//		slDataBuf.Unlock();

	}

	TRACE("\nAdcDisp() Called...\n");

}

void CAdcTestPlatView::AlgTestSet()
{
	// 初始化滚动条
	if ( m_scrlPic )
	{
		m_scrlPic.SetScrollRange( 0, 7 );
		m_scrlPic.SetScrollPos( 0 );
	}
	// 显示
	AlgDisp();
}

void CAdcTestPlatView::AlgDisp()
{
	//WORD* pwTemp = NULL;
	short* pwTemp = NULL;
	short* pwTemp2 = NULL;
	int nAlgDepth = 32*1024;
	int nSampFreq = 80;
	
	double dNum;
	TRACE("\nAlgDisp() Calling...\n");

	UpdateData( TRUE );
	CAdcTestPlatDoc* pDoc = (CAdcTestPlatDoc*)GetDocument();
	if ( pDoc != NULL )
	{
		// 查找算法视图
		CTestAlgView* pTestAlgView = NULL;
		POSITION pos = pDoc->GetFirstViewPosition();
		while ( pos != NULL )
		{
			CView* pView = pDoc->GetNextView( pos );			
			if ( pView->IsKindOf(RUNTIME_CLASS(CTestAlgView)) )
			{
				pTestAlgView = (CTestAlgView*)pView;
				break;
			}
		}
		// 获取深度
		nAlgDepth = pDoc->m_nAlgDepth;
		// 根据不同位置选择不同通道

		if ( pTestAlgView != NULL )
		{
			m_FFTDisp[0].m_dOrgSampFreq = nSampFreq / pTestAlgView->m_nR[m_nPos+1];
			m_FFTDisp[0].m_dMaxGap = m_FFTDisp[0].m_dOrgSampFreq / 2;
			m_FFTDisp[0].m_dGap = m_FFTDisp[0].m_dMaxGap / MAX_AXIS_VALUE;
			m_FFTDisp[0].m_nRatio = 1;
		}

		switch ( m_nPos )
		{
			case 0:
			{
				pwTemp = pDoc->m_waAiData;
				pwTemp2 = pDoc->m_waAqData;
				m_DataDisp[0].m_strTitle = "A通道";
				m_FFTDisp[0].m_strTitle = "A通道";
				// 更新横轴坐标
				break;
			}
			case 1:
			{
				pwTemp = pDoc->m_waBiData;
				pwTemp2 = pDoc->m_waBqData;
				m_DataDisp[0].m_strTitle = "B通道";
				m_FFTDisp[0].m_strTitle = "B通道";
				// 更新横轴坐标
				break;
			}
			case 2:
			{
				pwTemp = pDoc->m_waCiData;
				pwTemp2 = pDoc->m_waCqData;
				m_DataDisp[0].m_strTitle = "C通道";
				m_FFTDisp[0].m_strTitle = "C通道";
				// 更新横轴坐标
				break;
			}
			case 3:
			{
				pwTemp = pDoc->m_waDiData;
				pwTemp2 = pDoc->m_waDqData;
				m_DataDisp[0].m_strTitle = "D通道";
				m_FFTDisp[0].m_strTitle = "D通道";
				// 更新横轴坐标
				break;
			}			
			default:
			{
				pwTemp = pDoc->m_waAiData;
				pwTemp2 = pDoc->m_waAqData;
				m_DataDisp[0].m_strTitle = "A通道";
				m_FFTDisp[0].m_strTitle = "A通道";
				// 更新横轴坐标
				break;
			}
				
		}
	}

	////////////////////////////////////////////////////////////////
	dNum = nAlgDepth;
	int i = 0;
	// 调用matlab计算complex fft
// 	for ( int i = 0; i < nAlgDepth; i++ )
// 	{	
// 		daI[i] = pwTemp[i];
// 		daQ[i] = pwTemp2[i];
// 	}
// 
// 	FFT_complex(daI, daQ, nAlgDepth, daY, nAlgDepth / 2);

	// plot
	for ( i = 0; i < nAlgDepth/2; i++ )
	{
		//daX[i] = i; 
		// 注意数据的溢出
		daX[i] = (double)i * SAMP_FREQ / nAlgDepth; 
	}
// 	for ( i = 0; i < nAlgDepth; i++ )
// 	{
// 		daT[i] = (double)i;
// 	}
	// 算法测试不显示参数
	m_FFTDisp[0].m_bShowParam = FALSE;

	// 使用matlab的fft结果
// 	CSingleLock slDataBuf( &(m_FFTDisp[0].m_csFftDataBuf) );
// 	slDataBuf.Lock();
//	memcpy( m_FFTDisp[0].m_FFTData, daY, (nAlgDepth / 2) * sizeof(double) );
	ASSERT(m_nPos < 4);
	memcpy( m_FFTDisp[0].m_FFTData, &(pGB->dataSet[m_nPos].y[0]), nAlgDepth * sizeof(double) );
	int k = 0;
	// 分3种情况考虑
	if ( m_bIData && !m_bQData )
	{
//		memcpy( m_DataDisp[0].m_waDataDisp, pwTemp, nAlgDepth*sizeof(short) );
		for (k = 0; k < nAlgDepth; ++k)
		{
			m_DataDisp[0].m_waDataDisp[k] = pGB->dataSet[m_nPos].i[k];
		}
		m_DataDisp[0].m_nDisplaySel = 1;
	}
	else if ( !m_bIData && m_bQData )
	{
//		memcpy( m_DataDisp[0].m_waDataDisp2, pwTemp2, nAlgDepth*sizeof(short) );
		for (k = 0; k < nAlgDepth; ++k)
		{
			m_DataDisp[0].m_waDataDisp2[k] = pGB->dataSet[m_nPos].q[k];
		}
		m_DataDisp[0].m_nDisplaySel = 2;
	}
	else if ( m_bIData && m_bQData )
	{
		// 拷贝数据(注意数据的大小!!)
//		memcpy( m_DataDisp[0].m_waDataDisp, pwTemp, nAlgDepth*sizeof(short) );
//		memcpy( m_DataDisp[0].m_waDataDisp2, pwTemp2, nAlgDepth*sizeof(short) );
		for (k = 0; k < nAlgDepth; ++k)
		{
			m_DataDisp[0].m_waDataDisp[k] = pGB->dataSet[m_nPos].i[k];
			m_DataDisp[0].m_waDataDisp2[k] = pGB->dataSet[m_nPos].q[k];
		}
		// 显示两个波形
		m_DataDisp[0].m_nDisplaySel = 3;
	}
	else
	{
		m_DataDisp[0].m_nDisplaySel = 0;
	}
	
	// 保存SNR/SFDR/SINAD/ENOB
// 	m_FFTDisp[0].m_dSNR = pDoc->m_daResultSNR[m_nPos];
// 	m_FFTDisp[0].m_dSFDR = pDoc->m_daResultSFDR[m_nPos];
// 	m_FFTDisp[0].m_dSINAD = pDoc->m_daResultSINAD[m_nPos];
// 	m_FFTDisp[0].m_dENOB = pDoc->m_daResultENOB[m_nPos];

	m_FFTDisp[0].m_dSNR = pGB->dataSet[m_nPos].SNR;
	m_FFTDisp[0].m_dSFDR = pGB->dataSet[m_nPos].SFDR;
	m_FFTDisp[0].m_dSINAD = pGB->dataSet[m_nPos].SINAD;
	m_FFTDisp[0].m_dENOB = pGB->dataSet[m_nPos].ENOB;

	// 查找最大值，算频率
	int nPos;
	double dMaxData;
	nPos = 0;
	dMaxData = -10000;
	for ( i = 0; i < nAlgDepth / 2; i++ )
	{
		if ( m_FFTDisp[0].m_FFTData[i] > dMaxData )
		{
			nPos = i;
			dMaxData = m_FFTDisp[0].m_FFTData[i];
		}
	}
	// 计算时间显示一个周期的点数
	if ( nPos > 0 )
	{
		m_DataDisp[0].m_nDotPerPeriod = nAlgDepth / nPos;
	}
	
	// 2.根据原始数据计算Ain
	//memcpy( m_DataDisp[0].m_waDataDisp, pwTemp, MAX_DEPTH*2 );				
	double dActualMax = -MAX_VALUE;
	double dActualMin = MAX_VALUE;
	// 查找最大值和最小值
	for ( i = 0; i < nAlgDepth; i++ )
	{
		if ( m_DataDisp[0].m_waDataDisp[i] > dActualMax )
		{				
			dActualMax = m_DataDisp[0].m_waDataDisp[i];
		}
		if ( m_DataDisp[0].m_waDataDisp[i] < dActualMin )
		{			
			dActualMin = m_DataDisp[0].m_waDataDisp[i];
		}
	}
	// 计算Vpp(Ain由Vpp计算得出)
	m_FFTDisp[0].m_dVpp = (dActualMax - dActualMin) / MAX_VALUE;

	// 显示
	//m_FFTDisp[0].DrawSpectrum();		
	m_FFTDisp[0].DrawCurve();
	m_DataDisp[0].DrawData();
	TRACE("\nAlgDisp() Called...\n");
//	slDataBuf.Unlock();
}

void CAdcTestPlatView::AdcTestSet()
{
	// 初始化滚动条
	if ( m_scrlPic )
	{
		m_scrlPic.SetScrollRange( 0, CHANNEL_NUM-1 );
		m_scrlPic.SetScrollPos( 0 );
	}
	// 显示
	AdcDisp();
}

void CAdcTestPlatView::OnCheckMatlab() 
{
	// TODO: Add your control notification handler code here
	m_bMatlab = !m_bMatlab;
	//Invalidate();
	if ( !m_bMatlab )
	{
		// 使用窗口名字"Figure 1"来查找显示的matlab窗口，有风险
		CWnd* pTempWnd = CWnd::FindWindow( NULL, "Figure 1" );
		if ( pTempWnd != NULL )
		{
			pTempWnd->SendMessage( WM_CLOSE );
		}
	}
	Display();
}

void CAdcTestPlatView::Display()
{
	CMainFrame* pFrame = (CMainFrame*)GetParentFrame();
	if ( pFrame == NULL )
	{
		return;
	}
	// 先调整窗口的大小
	ChangeWindow();
	// 单通道显示
	if ( pFrame->m_byMultiView == 0 )
	{
		pGB = GlobalData::lockInstance();
		// ADC测试
		if ( pFrame->m_bTestADC )
		{
			AdcDisp();		
		}
		// 算法测试
		if ( pFrame->m_bTestAlg )
		{
			AlgDisp();		
		}
		// 默认
		if ( !pFrame->m_bTestADC && !pFrame->m_bTestAlg )
		{
			AlgDisp();
		}
		pGB->unlock();
		pGB = 0;
	}
	// 多通道
	else
	{
		pGB = GlobalData::lockInstance();
		// ADC测试
		if ( pFrame->m_bTestADC )
		{
			AdcDispFourChannel();		
		}
		// 算法测试
		if ( pFrame->m_bTestAlg )
		{
			AlgDispFourChannel();		
		}
		// 默认
		if ( !pFrame->m_bTestADC && !pFrame->m_bTestAlg )
		{
			AlgDispFourChannel();
		}
		pGB->unlock();
		pGB = 0;
	}
	
	SetState();
}

void CAdcTestPlatView::OnCheckIData() 
{
	m_bIData = !m_bIData;
	Display();
}

void CAdcTestPlatView::OnCheckQData() 
{
	m_bQData = !m_bQData;
	Display();	
}

void CAdcTestPlatView::OnCheckAlgAutoSave() 
{
	m_bAlgAutoSave = !m_bAlgAutoSave;
	CAdcTestPlatDoc* pDoc = (CAdcTestPlatDoc*)GetDocument();
	if ( pDoc != NULL )
	{
		pDoc->m_bAlgAutoSave = m_bAlgAutoSave;
	}
}


void CAdcTestPlatView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	CFormView::OnTimer(nIDEvent);
}

void CAdcTestPlatView::ChangeWindow()
{
	CMainFrame* pFrame = (CMainFrame*)GetParentFrame();
	if ( pFrame != NULL )
	{		
		switch ( pFrame->m_byMultiView )
		{
			// 单通道显示
			case 0:
			{
				// FFT窗口			
				if ( m_FFTDisp[0] )
				{
					m_FFTDisp[0].MoveWindow( &m_rcFFT[0] );
				}			
				// 数据窗口			
				if ( m_DataDisp[0] )
				{
					m_DataDisp[0].MoveWindow( &m_rcData[0] );
				}
				// 滚动条			
				if ( m_scrlPic )
				{
					m_scrlPic.MoveWindow( &m_rcScroll );
				}
				// 窗口的显示和隐藏
				if ( m_FFTDisp[1] && m_FFTDisp[0] )
				{
					m_FFTDisp[1].ShowWindow( SW_HIDE );
					m_FFTDisp[2].ShowWindow( SW_HIDE );
					m_FFTDisp[3].ShowWindow( SW_HIDE );
					m_FFTDisp[4].ShowWindow( SW_HIDE );
					m_DataDisp[1].ShowWindow( SW_HIDE );
					m_DataDisp[2].ShowWindow( SW_HIDE );
					m_DataDisp[3].ShowWindow( SW_HIDE );
					m_DataDisp[4].ShowWindow( SW_HIDE );

					m_FFTDisp[0].ShowWindow( SW_SHOW );
					m_DataDisp[0].ShowWindow( SW_SHOW );
				}
				break;
			}
			// 四个通道同时显示
			case 1:
			{
				// FFT窗口			
				if ( m_FFTDisp[1] )
				{
					m_FFTDisp[1].MoveWindow( &m_rcFFT[1] );
					m_FFTDisp[2].MoveWindow( &m_rcFFT[2] );
					m_FFTDisp[3].MoveWindow( &m_rcFFT[3] );
					m_FFTDisp[4].MoveWindow( &m_rcFFT[4] );
				}			
				// 数据窗口			
				if ( m_DataDisp[1] )
				{
					m_DataDisp[1].MoveWindow( &m_rcData[1] );
					m_DataDisp[2].MoveWindow( &m_rcData[2] );
					m_DataDisp[3].MoveWindow( &m_rcData[3] );
					m_DataDisp[4].MoveWindow( &m_rcData[4] );
				}
				// 窗口的显示和隐藏
				if ( m_FFTDisp[1] && m_FFTDisp[0] )
				{
					m_FFTDisp[1].ShowWindow( SW_SHOW );
					m_FFTDisp[2].ShowWindow( SW_SHOW );
					m_FFTDisp[3].ShowWindow( SW_SHOW );
					m_FFTDisp[4].ShowWindow( SW_SHOW );
					m_DataDisp[1].ShowWindow( SW_SHOW );
					m_DataDisp[2].ShowWindow( SW_SHOW );
					m_DataDisp[3].ShowWindow( SW_SHOW );
					m_DataDisp[4].ShowWindow( SW_SHOW );

					m_FFTDisp[0].ShowWindow( SW_HIDE );
					m_DataDisp[0].ShowWindow( SW_HIDE );
				}			
				break;
			}
			// 四个fft
			case 2:
			{
				// FFT窗口			
				if ( m_FFTDisp[1] )
				{
					m_FFTDisp[1].MoveWindow( &m_rcFFT_F[1] );
					m_FFTDisp[2].MoveWindow( &m_rcFFT_F[2] );
					m_FFTDisp[3].MoveWindow( &m_rcFFT_F[3] );
					m_FFTDisp[4].MoveWindow( &m_rcFFT_F[4] );
				}				
				// 窗口的显示和隐藏
				if ( m_FFTDisp[1] && m_FFTDisp )
				{
					m_FFTDisp[1].ShowWindow( SW_SHOW );
					m_FFTDisp[2].ShowWindow( SW_SHOW );
					m_FFTDisp[3].ShowWindow( SW_SHOW );
					m_FFTDisp[4].ShowWindow( SW_SHOW );
					m_DataDisp[1].ShowWindow( SW_HIDE );
					m_DataDisp[2].ShowWindow( SW_HIDE );
					m_DataDisp[3].ShowWindow( SW_HIDE );
					m_DataDisp[4].ShowWindow( SW_HIDE );

					m_FFTDisp[0].ShowWindow( SW_HIDE );
					m_DataDisp[0].ShowWindow( SW_HIDE );
				}			
				break;
			}
			// 四个data
			case 3:
			{
				// data窗口			
				if ( m_DataDisp[1] )
				{
					m_DataDisp[1].MoveWindow( &m_rcData_S[1] );
					m_DataDisp[2].MoveWindow( &m_rcData_S[2] );
					m_DataDisp[3].MoveWindow( &m_rcData_S[3] );
					m_DataDisp[4].MoveWindow( &m_rcData_S[4] );
				}				
				// 窗口的显示和隐藏
				if ( m_FFTDisp[1] && m_FFTDisp )
				{
					m_DataDisp[1].ShowWindow( SW_SHOW );
					m_DataDisp[2].ShowWindow( SW_SHOW );
					m_DataDisp[3].ShowWindow( SW_SHOW );
					m_DataDisp[4].ShowWindow( SW_SHOW );
					m_FFTDisp[1].ShowWindow( SW_HIDE );
					m_FFTDisp[2].ShowWindow( SW_HIDE );
					m_FFTDisp[3].ShowWindow( SW_HIDE );
					m_FFTDisp[4].ShowWindow( SW_HIDE );

					m_FFTDisp[0].ShowWindow( SW_HIDE );
					m_DataDisp[0].ShowWindow( SW_HIDE );
				}			
				break;
			}
			// 第1/2通道的fft/data
			case 4:
			{
				// fft/data
				if ( m_FFTDisp[1] && m_DataDisp[1] )
				{
					m_FFTDisp[1].MoveWindow( &m_rcFFT1_FS );
					m_FFTDisp[2].MoveWindow( &m_rcFFT2_FS );
					m_DataDisp[1].MoveWindow( &m_rcData1_FS );
					m_DataDisp[2].MoveWindow( &m_rcData2_FS );					
				}				
				// 窗口的显示和隐藏
				if ( m_FFTDisp[1] && m_FFTDisp[0] )
				{					
					m_FFTDisp[1].ShowWindow( SW_SHOW );
					m_FFTDisp[2].ShowWindow( SW_SHOW );
					m_FFTDisp[3].ShowWindow( SW_HIDE );
					m_FFTDisp[4].ShowWindow( SW_HIDE );
					m_DataDisp[1].ShowWindow( SW_SHOW );
					m_DataDisp[2].ShowWindow( SW_SHOW );
					m_DataDisp[3].ShowWindow( SW_HIDE );
					m_DataDisp[4].ShowWindow( SW_HIDE );

					m_FFTDisp[0].ShowWindow( SW_HIDE );
					m_DataDisp[0].ShowWindow( SW_HIDE );
				}			
				break;
			}
			// 第3/4通道的fft/data
			case 5:
			{
				// fft/data
				if ( m_FFTDisp[3] && m_DataDisp[3] )
				{
					m_FFTDisp[3].MoveWindow( &m_rcFFT3_FS );
					m_FFTDisp[4].MoveWindow( &m_rcFFT4_FS );
					m_DataDisp[3].MoveWindow( &m_rcData3_FS );
					m_DataDisp[4].MoveWindow( &m_rcData4_FS );					
				}				
				// 窗口的显示和隐藏
				if ( m_FFTDisp[1] && m_FFTDisp[0] )
				{					
					m_FFTDisp[1].ShowWindow( SW_HIDE );
					m_FFTDisp[2].ShowWindow( SW_HIDE );
					m_FFTDisp[3].ShowWindow( SW_SHOW );
					m_FFTDisp[4].ShowWindow( SW_SHOW );
					m_DataDisp[1].ShowWindow( SW_HIDE );
					m_DataDisp[2].ShowWindow( SW_HIDE );
					m_DataDisp[3].ShowWindow( SW_SHOW );
					m_DataDisp[4].ShowWindow( SW_SHOW );

					m_FFTDisp[0].ShowWindow( SW_HIDE );
					m_DataDisp[0].ShowWindow( SW_HIDE );
				}			
				break;
			}
			default:
				break;
		}// end of switch		
		
	}
}

void CAdcTestPlatView::AdcDispFourChannel()
{
	int i,j;	
	double dDotnum;		
	short* pwTemp = NULL;
	double dActualMax;
	double dActualMin;
	CFFTDisp* pFFTDisp = NULL;
	CDataDisp* pDataDisp = NULL;

	UpdateData( TRUE );
	CAdcTestPlatDoc* pDoc = (CAdcTestPlatDoc*)GetDocument();
	
	if ( pDoc != NULL )
	{
		for ( j = 0; j < 4; j++ )
		{
			switch ( j )
			{
				case 0:
				{
					pwTemp = pDoc->m_waCh1Signal;
					pFFTDisp = &m_FFTDisp[1];
					pDataDisp = &m_DataDisp[1];
					pDataDisp->m_strTitle = "A通道";
					pFFTDisp->m_strTitle = "A通道";
					break;
				}
				case 1:
				{
					pwTemp = pDoc->m_waCh2Signal;
					pFFTDisp = &m_FFTDisp[2];
					pDataDisp = &m_DataDisp[2];
					pDataDisp->m_strTitle = "B通道";
					pFFTDisp->m_strTitle = "B通道";
					break;
				}
				case 2:
				{
					pwTemp = pDoc->m_waCh3Signal;
					pFFTDisp = &m_FFTDisp[3];
					pDataDisp = &m_DataDisp[3];
					pDataDisp->m_strTitle = "C通道";
					pFFTDisp->m_strTitle = "C通道";
					break;
				}
				case 3:
				{
					pwTemp = pDoc->m_waCh4Signal;
					pFFTDisp = &m_FFTDisp[4];
					pDataDisp = &m_DataDisp[4];
					pDataDisp->m_strTitle = "D通道";
					pFFTDisp->m_strTitle = "D通道";
					break;
				}
				default:
				{
					pwTemp = pDoc->m_waCh1Signal;
					pFFTDisp = &m_FFTDisp[1];
					pDataDisp = &m_DataDisp[1];
					pDataDisp->m_strTitle = "A通道";
					pFFTDisp->m_strTitle = "A通道";
					break;
				}
					
			}			
// 			// 调用matlab计算fft
// 			for ( i = 0; i < MAX_DEPTH; i++ )
// 			{
// 				daIn[i] = pwTemp[i];
// 			}
// 			FFT(daIn, MAX_VALUE, daY, MAX_DEPTH);

			dDotnum = MAX_DEPTH;

			// ADC测试显示参数
			pFFTDisp->m_bShowParam = TRUE;

			// 使用matlab的fft结果
			// 互斥保护
// 			CSingleLock slDataBuf( &(pFFTDisp->m_csFftDataBuf) );
// 			slDataBuf.Lock();
// 			memcpy( pFFTDisp->m_FFTData, daY, (MAX_DEPTH / 2) * sizeof(double) );

			memcpy(pFFTDisp->m_FFTData, &(pGB->dataSet[j].y[0]), (MAX_DEPTH) * sizeof(double));
			// 保存SNR/SFDR/SINAD/ENOB
// 			pFFTDisp->m_dSNR = pDoc->m_daResultSNR[m_nPos];
// 			pFFTDisp->m_dSFDR = pDoc->m_daResultSFDR[m_nPos];
// 			pFFTDisp->m_dSINAD = pDoc->m_daResultSINAD[m_nPos];
// 			pFFTDisp->m_dENOB = pDoc->m_daResultENOB[m_nPos];

			pFFTDisp->m_dSNR = pGB->dataSet[j].SNR;
			pFFTDisp->m_dSFDR = pGB->dataSet[j].SFDR;
			pFFTDisp->m_dSINAD = pGB->dataSet[j].SINAD;
			pFFTDisp->m_dENOB = pGB->dataSet[j].ENOB;


			// 查找最大值，算频率
			int nPos;
			double dMaxData;
			dMaxData = -10000;
			for ( i = 0; i < MAX_DEPTH / 2; i++ )
			{
				if ( pFFTDisp->m_FFTData[i] > dMaxData )
				{
					nPos = i;
					dMaxData = pFFTDisp->m_FFTData[i];
				}
			}
			// 计算时间显示一个周期的点数
			if ( nPos > 0 )
			{
				pDataDisp->m_nDotPerPeriod = MAX_DEPTH / nPos;
			}
			
			
			// 2.根据原始数据计算Ain
			memcpy( pDataDisp->m_waDataDisp, pwTemp, MAX_DEPTH*2 );				
			dActualMax = -MAX_VALUE;
			dActualMin = MAX_VALUE;
			// 查找最大值和最小值
			for ( i = 0; i < MAX_DEPTH; i++ )
			{
				if ( pDataDisp->m_waDataDisp[i] > dActualMax )
				{				
					dActualMax = pDataDisp->m_waDataDisp[i];
				}
				if ( pDataDisp->m_waDataDisp[i] < dActualMin )
				{			
					dActualMin = pDataDisp->m_waDataDisp[i];
				}
			}
			// 计算Vpp(Ain由Vpp计算得出)
			pFFTDisp->m_dVpp = (dActualMax - dActualMin) / MAX_VALUE;

			// 显示一个波形
			pDataDisp->m_nDisplaySel = 1;
			// 3.更新图形显示			
			pFFTDisp->DrawCurve();
			pDataDisp->DrawData();
// 			slDataBuf.Unlock();			
		}		
	}
}

void CAdcTestPlatView::AlgDispFourChannel()
{
	int j;
	short* pwTemp = NULL;
	short* pwTemp2 = NULL;
	CFFTDisp* pFFTDisp = NULL;
	CDataDisp* pDataDisp = NULL;
	int nAlgDepth = 32*1024;
	int nSampFreq = 80;
	
	double dNum;
	
	UpdateData( TRUE );
	CAdcTestPlatDoc* pDoc = (CAdcTestPlatDoc*)GetDocument();
	if ( pDoc != NULL )
	{
	
		CTestAlgView* pTestAlgView = NULL;
		POSITION pos = pDoc->GetFirstViewPosition();
		while ( pos != NULL )
		{
			CView* pView = pDoc->GetNextView( pos );			
			if ( pView->IsKindOf(RUNTIME_CLASS(CTestAlgView)) )
			{
				pTestAlgView = (CTestAlgView*)pView;
				break;
			}
		}

		// 获取深度
		nAlgDepth = pDoc->m_nAlgDepth;
		for ( j = 0; j < 4; j++ )
		{
			pFFTDisp = &m_FFTDisp[j+1];
			pDataDisp = &m_DataDisp[j+1];
			pFFTDisp->m_dOrgSampFreq = nSampFreq / pTestAlgView->m_nR[j+1];
			switch ( j )
			{
				case 0:
				{
					pwTemp = pDoc->m_waAiData;
					pwTemp2 = pDoc->m_waAqData;
					pDataDisp->m_strTitle = "A通道";
					pFFTDisp->m_strTitle = "A通道";
					break;
				}
				case 1:
				{
					pwTemp = pDoc->m_waBiData;
					pwTemp2 = pDoc->m_waBqData;
					pDataDisp->m_strTitle = "B通道";
					pFFTDisp->m_strTitle = "B通道";
					break;
				}
				case 2:
				{
					pwTemp = pDoc->m_waCiData;
					pwTemp2 = pDoc->m_waCqData;
					pDataDisp->m_strTitle = "C通道";
					pFFTDisp->m_strTitle = "C通道";
					break;
				}
				case 3:
				{
					pwTemp = pDoc->m_waDiData;
					pwTemp2 = pDoc->m_waDqData;
					pDataDisp->m_strTitle = "D通道";
					pFFTDisp->m_strTitle = "D通道";
					break;
				}			
				default:
				{
					pwTemp = pDoc->m_waAiData;
					pwTemp2 = pDoc->m_waAqData;
					pDataDisp->m_strTitle = "A通道";
					pFFTDisp->m_strTitle = "A通道";
					break;
				}
					
			}

			pFFTDisp->m_dMaxGap = pFFTDisp->m_dOrgSampFreq / 2;
			pFFTDisp->m_dGap = pFFTDisp->m_dMaxGap / MAX_AXIS_VALUE;
			pFFTDisp->m_nRatio = 1;

			int i = 0;
			////////////////////////////////////////////////////////////////
			// 调用matlab计算complex fft
// 			for ( i = 0; i < nAlgDepth; i++ )
// 			{	
// 				daI[i] = pwTemp[i];
// 				daQ[i] = pwTemp2[i];
// 			}
// 			dNum = nAlgDepth;
// 
// 			FFT_complex(daI, daQ, nAlgDepth, daY, MAX_DEPTH / 2);

			/////////////////////////////////////////////////////////////////

			pFFTDisp->m_bShowParam = FALSE;
			ASSERT( j<4 && pGB);
			memcpy( pFFTDisp->m_FFTData, &(pGB->dataSet[j].y[0]), nAlgDepth * sizeof(double) );
			// 使用matlab的fft结果
			// 互斥保护
// 			CSingleLock slDataBuf( &(pFFTDisp->m_csFftDataBuf) );
// 			slDataBuf.Lock();
//			memcpy( pFFTDisp->m_FFTData, daY, (nAlgDepth / 2) * sizeof(double) );

			// 保存SNR/SFDR/SINAD/ENOB
// 			pFFTDisp->m_dSNR = pDoc->m_daResultSNR[m_nPos];
// 			pFFTDisp->m_dSFDR = pDoc->m_daResultSFDR[m_nPos];
// 			pFFTDisp->m_dSINAD = pDoc->m_daResultSINAD[m_nPos];
// 			pFFTDisp->m_dENOB = pDoc->m_daResultENOB[m_nPos];

			pFFTDisp->m_dSNR = pGB->dataSet[j].SNR;// pDoc->m_daResultSNR[m_nPos];
			pFFTDisp->m_dSFDR = pGB->dataSet[j].SFDR;// pDoc->m_daResultSFDR[m_nPos];
			pFFTDisp->m_dSINAD = pGB->dataSet[j].SINAD;// pDoc->m_daResultSINAD[m_nPos];
			pFFTDisp->m_dENOB = pGB->dataSet[j].ENOB;// pDoc->m_daResultENOB[m_nPos];

			int k = 0;
			// 分3种情况考虑
			if ( m_bIData && !m_bQData )
			{
				//memcpy( pDataDisp->m_waDataDisp, pwTemp, nAlgDepth*sizeof(short) );
				for (k = 0; k < nAlgDepth; ++k)
				{
					pDataDisp->m_waDataDisp[k] = pGB->dataSet[j].i[k];
				}
				pDataDisp->m_nDisplaySel = 1;
			}
			else if ( !m_bIData && m_bQData )
			{
//				memcpy( pDataDisp->m_waDataDisp2, pwTemp2, nAlgDepth*sizeof(short) );
				for (k = 0; k < nAlgDepth; ++k)
				{
					pDataDisp->m_waDataDisp2[k] = pGB->dataSet[j].q[k];
				}
				pDataDisp->m_nDisplaySel = 2;
			}
			else if ( m_bIData && m_bQData )
			{
				// 拷贝数据(注意数据的大小!!)
//				memcpy( pDataDisp->m_waDataDisp, pwTemp, nAlgDepth*sizeof(short) );
//				memcpy( pDataDisp->m_waDataDisp2, pwTemp2, nAlgDepth*sizeof(short) );
				for (k = 0; k < nAlgDepth; ++k)
				{
					pDataDisp->m_waDataDisp[k] = pGB->dataSet[j].i[k];
					pDataDisp->m_waDataDisp2[k] = pGB->dataSet[j].q[k];
				}
				// 显示两个波形
				pDataDisp->m_nDisplaySel = 3;
			}
			else
			{
				pDataDisp->m_nDisplaySel = 0;
			}
			

			// 查找最大值，算频率
			int nPos;
			double dMaxData;
			nPos = 0;
			dMaxData = -10000;
			for ( i = 0; i < nAlgDepth / 2; i++ )
			{
				if ( pFFTDisp->m_FFTData[i] > dMaxData )
				{
					nPos = i;
					dMaxData = pFFTDisp->m_FFTData[i];
				}
			}
			// 计算时间显示一个周期的点数
			if ( nPos > 0 )
			{
				pDataDisp->m_nDotPerPeriod = nAlgDepth / nPos;
			}
			
			// 2.根据原始数据计算Ain					
			double dActualMax = -MAX_VALUE;
			double dActualMin = MAX_VALUE;
			// 查找最大值和最小值
			for ( i = 0; i < nAlgDepth; i++ )
			{
				if ( pDataDisp->m_waDataDisp[i] > dActualMax )
				{				
					dActualMax = pDataDisp->m_waDataDisp[i];
				}
				if ( pDataDisp->m_waDataDisp[i] < dActualMin )
				{			
					dActualMin = pDataDisp->m_waDataDisp[i];
				}
			}
			// 计算Vpp(Ain由Vpp计算得出)
			pFFTDisp->m_dVpp = (dActualMax - dActualMin) / MAX_VALUE;

			// 显示				
			pFFTDisp->DrawCurve();
			pDataDisp->DrawData();

//			slDataBuf.Unlock();			
		}		
	}	
	TRACE("AlgDispFourChannel...\n");
}
