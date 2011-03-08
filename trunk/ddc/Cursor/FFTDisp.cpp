// FFTDisp.cpp : implementation file
//

#include "stdafx.h"
#include "AdcTestPlat.h"
#include "FFTDisp.h"
#include "math.h"
#include "AdcTestPlatView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define FFT_NUM_VERT 8
#define FFT_NUM_HORZ 10
#define FFT_LEFT_MARGIN 22
#define FFT_TOP_MARGIN  25
#define FFT_SCALE_LEN 5

CString g_strFFTX[FFT_NUM_HORZ+1] = { "0", "10", "20", "30", "40", "50", "60", "70", "80", "90", "100" };
CString g_strFFTY[FFT_NUM_VERT+1] = { "0", "-20", "-40", "-60", "-80", "-100", "-120", "-140", "-160" };
/////////////////////////////////////////////////////////////////////////////
// CFFTDisp

CFFTDisp::CFFTDisp()
{
	int i;
	m_pbitmapOldGrid = NULL ;
	m_pbitmapOldPlot = NULL ;
	m_crBackColor  = RGB( 0, 0, 0 ) ;
	m_crImageColor = RGB( 255, 0, 0 );		  
	m_brushBack.CreateSolidBrush(m_crBackColor) ;

	for ( i = 0; i < MAX_DEPTH; i++ )
	{
		m_FFTData[i] = 0.0;		
		m_daDispData[i] = 0.0;
	}
	//
	m_dMaxData = 1;		
	// 
//	m_dwDot = MAX_DEPTH / 2;
	m_dwDot = MAX_DEPTH;
	m_dwCurDot = m_dwDot / 2;
	m_nBeginPos = 0;
	m_bFirstVaule = TRUE;
	m_ptRightClick.x = FFT_LEFT_MARGIN;
	m_ptRightClick.y = FFT_TOP_MARGIN;
	//
	m_bInPic = FALSE;
	m_bDisplay = TRUE;
	// 
	m_dOrgSampFreq = 80.0;
	// 与坐标值相关
	// 最大间隔采样频率的一半
	m_dMaxGap = m_dOrgSampFreq / 2;
	m_dGap = m_dMaxGap / MAX_AXIS_VALUE;
	m_nRatio = 1;
	m_bShowParam = TRUE;
	m_dVpp = 2;
	m_dSNR = 0;
	m_dSFDR = 0;
	m_dSINAD = 0;
	m_dENOB = 0;
	// 字体
	m_fntScale.CreateFont (15, 5, 0, 0, 300,
                       FALSE, FALSE, 0, ANSI_CHARSET,
                       OUT_DEFAULT_PRECIS, 
                       CLIP_DEFAULT_PRECIS,
                       DEFAULT_QUALITY, 
                       DEFAULT_PITCH|FF_SWISS, "Times New Roman") ;
	m_fntTitle.CreateFont (15, 8, 0, 0, 300,
                       FALSE, FALSE, 0, ANSI_CHARSET,
                       OUT_DEFAULT_PRECIS, 
                       CLIP_DEFAULT_PRECIS,
                       DEFAULT_QUALITY, 
                       DEFAULT_PITCH|FF_SWISS, "宋体") ;

}

CFFTDisp::~CFFTDisp()
{
	if (m_pbitmapOldGrid != NULL)
		m_dcGrid.SelectObject(m_pbitmapOldGrid) ;  
	if (m_pbitmapOldPlot != NULL)
		m_dcPlot.SelectObject(m_pbitmapOldPlot) ;
}


BEGIN_MESSAGE_MAP(CFFTDisp, CWnd)
	//{{AFX_MSG_MAP(CFFTDisp)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()	
	ON_WM_CONTEXTMENU()	
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CFFTDisp message handlers

BOOL CFFTDisp::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID )
//Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	BOOL result ;
	static CString className = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW) ;

	result = CWnd::CreateEx(WS_EX_CLIENTEDGE | WS_EX_STATICEDGE, 
						  className, NULL, dwStyle, 
						  rect.left, rect.top, rect.right-rect.left, rect.bottom-rect.top,
						  pParentWnd->GetSafeHwnd(), (HMENU)nID) ;
	if (result != 0)
		InvalidateCtrl() ;

	return result ;

	//return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

void CFFTDisp::InvalidateCtrl()
{
	CClientDC dc(this) ;
	
	int i;
	CRect rc;
	int nClientWidth;
	int nClientHeight;
	//CString strText;
	CSize szText;
	int x;
	int y;

	GetClientRect( &rc );
	nClientWidth = m_nClientWidth;
	nClientHeight = m_nClientHeight;	

	// 背景的内存DC
	if ( m_dcGrid.GetSafeHdc() == NULL )
	{
		m_dcGrid.CreateCompatibleDC(&dc) ;
		m_bitmapGrid.CreateCompatibleBitmap(&dc, nClientWidth, nClientHeight) ;
		m_pbitmapOldGrid = m_dcGrid.SelectObject(&m_bitmapGrid) ;
	}	
	else
	{
		// 恢复原来的位图，再删除新建的位图
		m_dcGrid.SelectObject( m_pbitmapOldGrid );
		m_bitmapGrid.DeleteObject();
		// 先删除原来的DC，再连接到新的DC上
		m_dcGrid.DeleteDC();
		m_dcGrid.CreateCompatibleDC(&dc) ;
		m_bitmapGrid.CreateCompatibleBitmap(&dc, nClientWidth, nClientHeight) ;
		m_pbitmapOldGrid = m_dcGrid.SelectObject(&m_bitmapGrid) ;
	}

	// 方格刻度
	int nSigPicWidth = rc.right - rc.left - FFT_LEFT_MARGIN * 2;
	int nSigPicHeight = rc.bottom - rc.top - FFT_TOP_MARGIN * 2;	
	int nSigPicSmallWidth = nSigPicWidth / FFT_NUM_HORZ;
	int nSigPicSmallHeight = nSigPicHeight / FFT_NUM_VERT;
	// 计算图像区
	m_rectPic.left = FFT_LEFT_MARGIN;
	m_rectPic.top = FFT_TOP_MARGIN;
	m_rectPic.right = FFT_LEFT_MARGIN + nSigPicSmallWidth*FFT_NUM_HORZ;
	m_rectPic.bottom = FFT_TOP_MARGIN + nSigPicSmallHeight*FFT_NUM_VERT;
	// 黑色背景
	m_dcGrid.FillSolidRect( rc, m_crBackColor );
	// 画笔
	CPen penAxi( PS_DOT, 1, RGB(128, 128, 128));
	CPen penSideAxi( PS_SOLID, 1, RGB(128, 128, 128));
	CPen *pOldPen = m_dcGrid.SelectObject( &penAxi );
	// 文本
	m_dcGrid.SetTextColor( RGB(128, 128, 128) );
	// 字体
	CFont* pOldFont = m_dcGrid.SelectObject( &m_fntScale );


	//绘制横坐标轴
	for ( i = 0; i < FFT_NUM_VERT+1; i++ )
	{		
		if ( i == 0 || i == FFT_NUM_VERT )
		{
			pOldPen = m_dcGrid.SelectObject( &penSideAxi );
		}
		else
		{
			pOldPen = m_dcGrid.SelectObject( &penAxi );
		}
		m_dcGrid.MoveTo( FFT_LEFT_MARGIN, FFT_TOP_MARGIN + nSigPicSmallHeight * i);
		m_dcGrid.LineTo( FFT_LEFT_MARGIN + nSigPicSmallWidth*FFT_NUM_HORZ, FFT_TOP_MARGIN + nSigPicSmallHeight * i );//- FFT_LEFT_MARGIN * 2
		// 刻度值
		szText =  m_dcGrid.GetTextExtent( g_strFFTY[i] );
		if ( szText.cx > FFT_LEFT_MARGIN )
		{
			x = 0;
		}
		else
		{
			x = FFT_LEFT_MARGIN - szText.cx;
		}
		if ( szText.cy / 2 > FFT_TOP_MARGIN ) 
		{
			y = FFT_TOP_MARGIN + nSigPicSmallHeight * i;
		}
		else
		{
			y = FFT_TOP_MARGIN + nSigPicSmallHeight * i - szText.cy / 2;
		}
		// 最下面的值
		if ( i == FFT_NUM_VERT )
		{
			y = FFT_TOP_MARGIN + nSigPicSmallHeight * i - szText.cy;
		}
		m_dcGrid.TextOut( x, y, g_strFFTY[i] );
		// 显示dB
		if ( i == 0 )
		{
			CString strMsg = "(dB)";
			szText = m_dcGrid.GetTextExtent( strMsg );
			m_dcGrid.TextOut( FFT_LEFT_MARGIN - szText.cx, 
				FFT_TOP_MARGIN + szText.cy / 2 - 2, strMsg );
		}
	}

	


/*
	// 纵向刻度
	m_dcGrid.MoveTo( FFT_LEFT_MARGIN, FFT_TOP_MARGIN );
	m_dcGrid.LineTo( FFT_LEFT_MARGIN, FFT_TOP_MARGIN + FFT_NUM_VERT * nSigPicSmallHeight );
	// 刻度数值
	//szText = m_dcGrid.GetTextExtent( g_strFFTX[0] ); 
	//m_dcGrid.TextOut( FFT_LEFT_MARGIN, FFT_TOP_MARGIN + FFT_NUM_VERT * nSigPicSmallHeight + 1, g_strFFTX[0] );
	for ( i = 1; i < FFT_NUM_HORZ; i++ )
	{
		// 上短线
		m_dcGrid.MoveTo( FFT_LEFT_MARGIN + i * nSigPicSmallWidth, FFT_TOP_MARGIN );
		m_dcGrid.LineTo( FFT_LEFT_MARGIN + i * nSigPicSmallWidth, FFT_TOP_MARGIN + FFT_SCALE_LEN );
		// 下短线
		m_dcGrid.MoveTo( FFT_LEFT_MARGIN + i * nSigPicSmallWidth, FFT_TOP_MARGIN + FFT_NUM_VERT * nSigPicSmallHeight - FFT_SCALE_LEN );
		m_dcGrid.LineTo( FFT_LEFT_MARGIN + i * nSigPicSmallWidth, FFT_TOP_MARGIN + FFT_NUM_VERT * nSigPicSmallHeight );
		// 刻度数值
		//szText = m_dcGrid.GetTextExtent( g_strFFTX[i] ); 
		//m_dcGrid.TextOut( FFT_LEFT_MARGIN + i * nSigPicSmallWidth - szText.cx / 2, FFT_TOP_MARGIN + FFT_NUM_VERT * nSigPicSmallHeight + 1, g_strFFTX[i] );
	}
	m_dcGrid.MoveTo( FFT_LEFT_MARGIN + FFT_NUM_HORZ * nSigPicSmallWidth, FFT_TOP_MARGIN );
	m_dcGrid.LineTo( FFT_LEFT_MARGIN + FFT_NUM_HORZ * nSigPicSmallWidth, FFT_TOP_MARGIN + FFT_NUM_VERT * nSigPicSmallHeight );
	// 刻度数值
	//szText = m_dcGrid.GetTextExtent( g_strFFTX[FFT_NUM_HORZ] ); 
	//m_dcGrid.TextOut( FFT_LEFT_MARGIN + FFT_NUM_HORZ * nSigPicSmallWidth - szText.cx / 2, FFT_TOP_MARGIN + FFT_NUM_VERT * nSigPicSmallHeight + 1, g_strFFTX[FFT_NUM_HORZ] );
*/
	// 恢复原来的画笔
	if ( pOldPen != NULL )
	{
		m_dcGrid.SelectObject( pOldPen );
	}
	// 恢复原来的字体
	if ( pOldFont != NULL )
	{
		
		m_dcGrid.SelectObject( pOldFont );
	}	
	penAxi.DeleteObject();
	penSideAxi.DeleteObject();

	// 波形的DC
	if ( m_dcPlot.GetSafeHdc() == NULL )
	{
		m_dcPlot.CreateCompatibleDC(&dc) ;
		m_bitmapPlot.CreateCompatibleBitmap(&dc, nClientWidth, nClientHeight) ;
		m_pbitmapOldPlot = m_dcPlot.SelectObject(&m_bitmapPlot) ;
	}
	else
	{
		m_dcPlot.SelectObject( m_pbitmapOldPlot );
		m_bitmapPlot.DeleteObject();
		m_dcPlot.DeleteDC();

		m_dcPlot.CreateCompatibleDC(&dc) ;
		m_bitmapPlot.CreateCompatibleBitmap(&dc, nClientWidth, nClientHeight) ;
		m_pbitmapOldPlot = m_dcPlot.SelectObject(&m_bitmapPlot) ;
	}
}

void CFFTDisp::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	GetClientRect(m_rectPlot);  
	m_nClientHeight = m_rectPlot.Height();
	m_nClientWidth  = m_rectPlot.Width();
	m_dwPicWidth = (m_nClientWidth - FFT_LEFT_MARGIN * 2) / FFT_NUM_HORZ * FFT_NUM_HORZ;
	// 显示点数与视图大小一致
	//m_dwDot = (m_nClientWidth - FFT_LEFT_MARGIN * 2) / FFT_NUM_HORZ * FFT_NUM_HORZ;
	if ( cx > 0 && cy > 0 )
	{
		// 图像大小发生变化时，修改背景DC和图像DC的大小
		InvalidateCtrl();
		// 重画图像
		//DrawSpectrum();
		CSingleLock slDataBuf( &m_csFftDataBuf );
		slDataBuf.Lock();
		DrawCurve();
		slDataBuf.Unlock();
	}
	
}

void CFFTDisp::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CDC memDC ;
	CBitmap memBitmap ;
	CBitmap* oldBitmap ; // bitmap originally found in CMemDC

	// no real plotting work is performed here, 
	// just putting the existing bitmaps on the client

	// to avoid flicker, establish a memory dc, draw to it 
	// and then BitBlt it to the client
	memDC.CreateCompatibleDC(&dc) ;
	memBitmap.CreateCompatibleBitmap(&dc, m_nClientWidth, m_nClientHeight) ;
	oldBitmap = (CBitmap *)memDC.SelectObject(&memBitmap) ;

	if (memDC.GetSafeHdc() != NULL)
	{
		// first drop the grid on the memory dc
		memDC.BitBlt(0, 0, m_nClientWidth, m_nClientHeight, 
					 &m_dcGrid, 0, 0, SRCCOPY) ;
		// now add the plot on top as a "pattern" via SRCPAINT.
		// works well with dark background and a light plot
		memDC.BitBlt(0, 0, m_nClientWidth, m_nClientHeight, 
					 &m_dcPlot, 0, 0, SRCPAINT) ;  //SRCPAINT
		// finally send the result to the display
		dc.BitBlt(0, 0, m_nClientWidth, m_nClientHeight, 
				  &memDC, 0, 0, SRCCOPY) ;
	}

	memDC.SelectObject(oldBitmap) ;

	// Do not call CWnd::OnPaint() for painting messages
}

BOOL CFFTDisp::OnEraseBkgnd(CDC* pDC) 
{
	// 直接返回,效果是不会闪动
	return TRUE;
	
}

void CFFTDisp::OnMouseMove(UINT nFlags, CPoint point) 
{
	// 找到主框架
	CMainFrame* pFrame = NULL;
	pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);
	if ( pFrame != NULL )
	{
		if ( pFrame->m_bZoomOut )
		{
			::SetCursor( pFrame->m_hCursorOut );
		}
		else if ( pFrame->m_bZoomIn )
		{
			::SetCursor( pFrame->m_hCursorIn );
		}
		else
		{
			::SetCursor( ::LoadCursor( NULL, IDC_ARROW ) );
		}
	}
	// 记录移动坐标	
	m_ptMove = point;	
	CSingleLock slDataBuf( &m_csFftDataBuf );
	slDataBuf.Lock();
	DrawCurve();
	slDataBuf.Unlock();
	
	CWnd::OnMouseMove(nFlags, point);
}

void CFFTDisp::OnContextMenu(CWnd* pWnd, CPoint point) 
{
/*
	// 保存当前坐标
	CPoint ptTemp;
	ptTemp = point;
	ScreenToClient( &ptTemp );	
	// 在图像区域内时弹出菜单
	CRect rc( FFT_LEFT_MARGIN, FFT_TOP_MARGIN, m_nClientWidth - FFT_LEFT_MARGIN, m_nClientHeight - FFT_TOP_MARGIN );
	if ( rc.PtInRect(ptTemp) )
	{
		m_ptRightClick = ptTemp;
		CMenu menuZoom;
		menuZoom.LoadMenu( IDR_MENU_ZOOM );
		menuZoom.GetSubMenu(0)->TrackPopupMenu( TPM_LEFTALIGN, point.x, point.y, this );	
	}
*/	
	// 保存当前坐标
	CPoint ptTemp;
	ptTemp = point;
	ScreenToClient( &ptTemp );
	m_ptRightClick = ptTemp;

	// 加载弹出式菜单
	CMenu menuZoom;
	menuZoom.LoadMenu( IDR_MENU_FFT_ZOOM );	

	// 获取菜单所属窗口
	CWnd* pWndPopupOwner = this;
	while ( pWndPopupOwner->GetStyle() & WS_CHILD )
	{
		pWndPopupOwner = pWndPopupOwner->GetParent();
	}	
	
	menuZoom.GetSubMenu(0)->TrackPopupMenu( TPM_LEFTALIGN, point.x, point.y, pWndPopupOwner  );
	// 当前为第几个fft视图保存到mainfrm
	((CMainFrame*)pWndPopupOwner)->m_byFftIndex = m_byIndex;
}


void CFFTDisp::ZoomIn()
{
	// 根据右击位置，计算对应的点
	if ( m_ptRightClick.x > FFT_LEFT_MARGIN && m_dwDot < MAX_DEPTH / 4 )
	{
	
		// 计算开始位置
		DWORD dwNewDot = m_dwDot * 2;
		DWORD dwMousePoint = ( m_ptRightClick.x - FFT_LEFT_MARGIN ) * m_dwDot / m_dwPicWidth + m_nBeginPos;
		// 显示区域 [dwMousePoint - dwNewDot / 2, dwMousePoint + dwNewDot / 2]
		m_nBeginPos = dwMousePoint - dwNewDot / 2;
		//  修改最大间隔
		m_dMaxGap = m_dMaxGap * 2;
		CString strMsg = "1.00";
		CSize szText = m_dcPlot.GetTextExtent( strMsg );
		int nAxisPointNum = m_dwPicWidth / (szText.cx * 2);
		if ( nAxisPointNum > MAX_AXIS_VALUE )
		{
			nAxisPointNum = MAX_AXIS_VALUE;
		}
		if ( nAxisPointNum < 1 )
		{
			nAxisPointNum = 1;
		}
		double dGap = m_dMaxGap / nAxisPointNum;
		m_dGap = FindNearFloatValue( dGap );
		// 重新计算最大间隔和最大点数
		m_dMaxGap = m_dGap * nAxisPointNum;
		m_dwDot = m_dMaxGap * MAX_DEPTH / m_dOrgSampFreq;
		CSingleLock slDataBuf( &m_csFftDataBuf );
		slDataBuf.Lock();
		DrawCurve();
		slDataBuf.Unlock();
	}
	if ( m_dwDot >= MAX_DEPTH / 4 )
	{
		//SendMessage( ID_MENU_ZOOM_RESTORE );
		ZoomRestore();
	}
}

void CFFTDisp::ZoomOut()
{

	// 根据右击位置，计算对应的点(坐标间隔最小为1，所以点数不能太少)
	if ( m_ptRightClick.x > FFT_LEFT_MARGIN && m_dwDot > 20 )
	{
	
		// 计算开始位置
		DWORD dwNewDot = m_dwDot / 2;
		DWORD dwMousePoint = ( m_ptRightClick.x - FFT_LEFT_MARGIN ) * m_dwDot / m_dwPicWidth + m_nBeginPos;
		// 显示区域 [dwMousePoint - dwNewDot / 2, dwMousePoint + dwNewDot / 2]
		m_nBeginPos = dwMousePoint - dwNewDot / 2;
		//  修改最大间隔
		m_dMaxGap = m_dMaxGap / 2;
		CString strMsg = "1.00";
		CSize szText = m_dcPlot.GetTextExtent( strMsg );
		int nAxisPointNum = m_dwPicWidth / (szText.cx * 2);
		if ( nAxisPointNum > MAX_AXIS_VALUE )
		{
			nAxisPointNum = MAX_AXIS_VALUE;
		}
		if ( nAxisPointNum < 1 )
		{
			nAxisPointNum = 1;
		}
		double dGap = m_dMaxGap / nAxisPointNum;
		m_dGap = FindNearFloatValue( dGap );
		// 重新计算最大间隔和最大点数
		m_dMaxGap = m_dGap * nAxisPointNum;
		m_dwDot = m_dMaxGap * MAX_DEPTH / m_dOrgSampFreq;
		CSingleLock slDataBuf( &m_csFftDataBuf );
		slDataBuf.Lock();
		DrawCurve();
		slDataBuf.Unlock();
	}
	if ( m_dwDot <= 20 )
	{
		//SendMessage( ID_MENU_ZOOM_RESTORE );
		ZoomRestore();
	}
}

void CFFTDisp::ZoomRestore()
{
	m_nBeginPos = 0;
//	m_dwDot = MAX_DEPTH/2;
	m_dwDot = MAX_DEPTH;
	m_dMaxGap = m_dOrgSampFreq / 2;
	m_dGap = m_dMaxGap / MAX_AXIS_VALUE;
	m_nRatio = 1;
	CSingleLock slDataBuf( &m_csFftDataBuf );
	slDataBuf.Lock();
	DrawCurve();
	slDataBuf.Unlock();
}

// 绘制的顺序，先坐标，再曲线、擦除多余的曲线、坐标值、标记、参数值
void CFFTDisp::DrawCurve()
{
	int i,j;
	CSize szText;
	int x;
	int y;
	CFont* pOldFont;
	CString strMsg;
	CPen *pOldPen;
	double dErr = 0;

	// 与背景对齐
	int nSigPicWidth = m_nClientWidth - FFT_LEFT_MARGIN * 2;
	int nSigPicHeight = m_nClientHeight - FFT_TOP_MARGIN * 2;	
	int nSigPicSmallWidth = nSigPicWidth / FFT_NUM_HORZ;
	int nSigPicSmallHeight = nSigPicHeight / FFT_NUM_VERT;
	// 对齐后的宽度和高度
	int nPicWidth = nSigPicSmallWidth * FFT_NUM_HORZ;
	int nPicHeight = nSigPicSmallHeight * FFT_NUM_VERT;
	
	if ( m_dcPlot.GetSafeHdc() != NULL )
	{		
		// 清除原来的图像
		m_dcPlot.SetBkColor (m_crBackColor) ;
		m_dcPlot.FillRect(m_rectPlot, &m_brushBack) ;
		// 标题
		///////////////////////////////////////////////////////////////////////////
		pOldFont = m_dcPlot.SelectObject( &m_fntTitle );
		m_dcPlot.SetTextColor( m_crImageColor );
		m_dcPlot.TextOut( 2, 2, m_strTitle );
		if ( pOldFont != NULL )
		{			
			m_dcPlot.SelectObject( pOldFont );
		}
		///////////////////////////////////////////////////////////////////////////

		/*
		// 计算Ain
		dErr = 0;		
		CAdcTestPlatView* pView = (CAdcTestPlatView*)GetParent();
		if ( pView != NULL && pView->m_dVpp > 0 )
		{
			// Ain(峰峰值最大为2V)
			dErr = 20*log10( pView->m_dVpp / 2);
		}
		*/

		// 计算Ain
		dErr = 0;
// 		if ( m_dVpp > 0 )
// 		{
// 			dErr = 20*log10( m_dVpp / 2);
// 		}

		// 显示曲线、坐标
		/////////////////////////////////////////////////////////////////////////
		// 画笔
		CPen penCh1Signal( PS_SOLID, 1, m_crImageColor );
		pOldPen = m_dcPlot.SelectObject( &penCh1Signal );
		// 先进行修正(原来更新点数为m_dwDot，所以出现只更新前面数据，后面数据不更新的情况)
		// m_dwDot -> MAX_DEPTH
		for ( i = 0; i < MAX_DEPTH; i++ )
		{
			//m_FFTData[i] += dErr;
			m_daDispData[i] = m_FFTData[i] + dErr;
		}
		// 计算最大值/最小值(这段没有意义，实际的最大最小在下面指定)
		m_dMaxData = -10000;
		m_dMinData = 0;
		for ( i = 0; i < m_dwDot; i++ )
		{
			if ( m_nBeginPos+i >= 0 && m_nBeginPos+i < MAX_DEPTH/2 )
			{
				if ( m_daDispData[m_nBeginPos+i] > m_dMaxData )
				{
					m_dMaxData = m_daDispData[m_nBeginPos+i];
				}
				if ( m_daDispData[m_nBeginPos+i] < m_dMinData )
				{
					m_dMinData = m_daDispData[m_nBeginPos+i];
				}
			}
			
		}
		// 最大值为0dB
		m_dMaxData = 0;
		// 最小值为-120dB -> -160
		m_dMinData = -160;
		// 每像素的点数
		double dPointXpixel = (nPicWidth - 0.0) / m_dwDot;
		double dPointYpixel = (nPicHeight - 0.0 ) / (m_dMaxData-m_dMinData);		

		
		// 画笔
		CPen penAxi( PS_DOT, 1, RGB(128, 128, 128));		
		pOldPen = m_dcPlot.SelectObject( &penAxi );
		
		// 画坐标
		double dData;
		int nCount;
		for ( i = 0; i < m_dwDot; i++ )
		{			
			dData = (m_nBeginPos+i)*m_dOrgSampFreq/MAX_DEPTH;
			// 先找到开始的大小
			if ( i == 0 )
			{
				nCount = dData / m_dGap;//  + 1
			}
			if ( dData >= nCount * m_dGap )
			{
				// 画坐标线
				x = FFT_LEFT_MARGIN + (int)(i*dPointXpixel);			
				y = FFT_TOP_MARGIN;					
				m_dcPlot.MoveTo( x, y );
				x = FFT_LEFT_MARGIN + (int)(i*dPointXpixel);			
				y = FFT_TOP_MARGIN + nPicHeight;					
				m_dcPlot.LineTo( x, y );	
				// 找到第一个后更新计数的大小
				nCount++;
			}
		}
		if ( pOldPen != NULL )
		{
			m_dcPlot.SelectObject( pOldPen );
		}
		CPen penSideAxi( PS_SOLID, 1, RGB(128, 128, 128));	
		pOldPen = m_dcPlot.SelectObject( &penSideAxi );
		// 开始和最后的两根线
		x = FFT_LEFT_MARGIN;			
		y = FFT_TOP_MARGIN;					
		m_dcPlot.MoveTo( x, y );
		x = FFT_LEFT_MARGIN;			
		y = FFT_TOP_MARGIN + nPicHeight;					
		m_dcPlot.LineTo( x, y );
		x = FFT_LEFT_MARGIN + nPicWidth;			
		y = FFT_TOP_MARGIN;					
		m_dcPlot.MoveTo( x, y );
		x = FFT_LEFT_MARGIN + nPicWidth;			
		y = FFT_TOP_MARGIN + nPicHeight;					
		m_dcPlot.LineTo( x, y );
		// 恢复现场		
		if ( pOldPen != NULL )
		{
			m_dcPlot.SelectObject( pOldPen );
		}
		penAxi.DeleteObject();
		penSideAxi.DeleteObject();

		// 显示曲线
		m_bFirstVaule = TRUE;		
		for ( i = 0; i < m_dwDot; i++ )
		{
			// 先移动到第一个有效的点
			if ( m_bFirstVaule && m_nBeginPos+i >= 0 && m_nBeginPos+i < MAX_DEPTH )
			{
				m_bFirstVaule = FALSE;
				m_dcPlot.MoveTo( FFT_LEFT_MARGIN + (int)(i*dPointXpixel), 
					FFT_TOP_MARGIN + nPicHeight - (int)((m_daDispData[m_nBeginPos+i] - m_dMinData)*dPointYpixel) );	
			}
			// 画线
			if ( m_nBeginPos+i >= 0 && m_nBeginPos+i < MAX_DEPTH )
			{
				x = FFT_LEFT_MARGIN + (int)(i*dPointXpixel);			
				y = FFT_TOP_MARGIN + nPicHeight - (int)((m_daDispData[m_nBeginPos+i] - m_dMinData)*dPointYpixel);					
				m_dcPlot.LineTo( x, y );
			}			
		}				
		m_dcPlot.SelectObject( pOldPen );
		penCh1Signal.DeleteObject();
		
		// 擦除多余部分
		CRect rcFill( 0, FFT_TOP_MARGIN + FFT_NUM_VERT * nSigPicSmallHeight,
			m_nClientWidth, m_nClientHeight );
		m_dcPlot.FillRect( rcFill, &m_brushBack );
		/////////////////////////////////////////////////////////////////////////////

		// 显示坐标值
		///////////////////////////////////////////////////////////////////////////
		// 字体
		m_dcPlot.SetTextColor( RGB(128, 128, 128) );		
		pOldFont = m_dcPlot.SelectObject( &m_fntScale );
		// 坐标值
		for ( i = 0; i < m_dwDot; i++ )
		{			
			dData = (m_nBeginPos+i)*m_dOrgSampFreq/MAX_DEPTH;
			// 先找到开始的大小
			if ( i == 0 )
			{
				if ( dData > 0 )
				{
					nCount = dData / m_dGap + 1;
				}
				else
				{
					nCount = dData / m_dGap;
				}
			}
			if ( dData >= nCount * m_dGap )			
			{				
				// 刻度值
				//strMsg.Format( "%d", m_nBeginPos+i );
				//strMsg.Format( "%.2f", (m_nBeginPos+i)*m_dOrgSampFreq/MAX_DEPTH );
				strMsg.Format( "%.2f", nCount * m_dGap - m_dOrgSampFreq / 2 );
				szText = m_dcPlot.GetTextExtent( strMsg );
				x = FFT_LEFT_MARGIN + (int)(i*dPointXpixel) - szText.cx / 2;
				y = FFT_TOP_MARGIN + nPicHeight + 2;
				m_dcPlot.TextOut( x, y, strMsg );
				nCount++;
			}
		}
		// 显示单位
		strMsg = "(MHz)";
		szText = m_dcPlot.GetTextExtent( strMsg );
		x = FFT_LEFT_MARGIN + nPicWidth/2 - szText.cx / 2;
		y = FFT_TOP_MARGIN + nPicHeight + szText.cy;
		m_dcPlot.TextOut( x, y, strMsg );
		if ( pOldFont != NULL )
		{			
			m_dcPlot.SelectObject( pOldFont );
		}
		//////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////
		// 画标记
#define MARK_NUM 6
#define MINGAP 200
		double dMaxData;
		int nPos;
		int naPos[MARK_NUM];		
		
		int t;
		bool bMax = FALSE;

		for ( i = 0; i < MARK_NUM; i++ )
		{
			naPos[i] = -1;
		}
		// 查找5个最大值
		for ( i = 0; i < MARK_NUM; i++ )
		{
			dMaxData = -10000;
			//j>0, ignore DC
			for ( j = 1; j < MAX_DEPTH; j++ )
			{
				
// 				if ( j != naPos[0] && j != naPos[1] && j != naPos[2] 
// 					&& j != naPos[3] && j != naPos[4] && m_daDispData[j] > dMaxData 
// 					&& abs(j-naPos[0])>MINGAP && abs(j-naPos[1])>MINGAP && abs(j-naPos[2])>MINGAP 
// 					&& abs(j-naPos[3])>MINGAP && abs(j-naPos[4])>MINGAP)
// 				{
// 					dMaxData = m_daDispData[j];
// 					nPos = j;
// 				}

				if ( m_daDispData[j] > dMaxData)
				{
					bMax = TRUE;
					for (t=0; t<i; ++t)
					{
						if (j==naPos[t] || abs(j-naPos[t])<MINGAP)
						{
							bMax = FALSE;
						}
					}
					if (bMax)
					{
						dMaxData = m_daDispData[j];
						nPos = j;
					}
				}
			}
			for (t=i; t<MARK_NUM; ++t)
			{
				naPos[t] = nPos;
			}
			//TRACE( "pos = %d, data = %f\n", naPos[i], m_daDispData[ naPos[i] ] );
		}

		pOldFont = m_dcPlot.SelectObject( &m_fntTitle );
		m_dcPlot.SetTextColor( RGB(0,255,255) );		

		// 画标记
		CString strMax;
		for ( i = 0; i < MARK_NUM; i++ )
		{
			// 在当前显示的点数范围内才显示
			if ( naPos[i] - m_nBeginPos < m_dwDot )
			{
				x = FFT_LEFT_MARGIN + (int)( (naPos[i]-m_nBeginPos) * dPointXpixel );			
				y = FFT_TOP_MARGIN + nPicHeight - (int)((m_daDispData[ naPos[i] ] - m_dMinData)*dPointYpixel); 
				DrawMark( x, y, 'x', RGB(0,255,255) );
				strMax.Format( "(%.2f,%.2f)", naPos[i]*m_dOrgSampFreq/MAX_DEPTH, 
					m_daDispData[ naPos[i] ] );
				m_dcPlot.TextOut(x+3, y-3, strMax );
			}			
		}
		////////////////////////////////////////////////////////////////////////

		// 显示参数
		////////////////////////////////////////////////////////////////////////
		
		if ( m_dVpp > 0 && m_bShowParam )
		{
			// 查找最长的，左边对齐
			strMsg.Format( "SFDR = %2.2fdB", m_dSFDR );
			szText = m_dcPlot.GetTextExtent( strMsg );		
			int nLen = szText.cx;

			// Ain(峰峰值最大为2V)
			dErr = 20*log10( m_dVpp / 2);
			strMsg.Format( "AIN  = %.2fdB", dErr );
			szText = m_dcPlot.GetTextExtent( strMsg );		
			x = m_nClientWidth - FFT_LEFT_MARGIN - nLen;
			y = FFT_TOP_MARGIN + 2;		
			m_dcPlot.TextOut( x, y, strMsg );

			// SNR
			strMsg.Format( "SNR  = %.2fdB", m_dSNR );
			szText = m_dcPlot.GetTextExtent( strMsg );		
			x = m_nClientWidth - FFT_LEFT_MARGIN - nLen;
			y = FFT_TOP_MARGIN + 2 + szText.cy;		
			m_dcPlot.TextOut( x, y, strMsg );

			// SFDR
			strMsg.Format( "SFDR = %.2fdB", m_dSFDR );
			szText = m_dcPlot.GetTextExtent( strMsg );		
			x = m_nClientWidth - FFT_LEFT_MARGIN - nLen;
			y = FFT_TOP_MARGIN + 2 + szText.cy*2;		
			m_dcPlot.TextOut( x, y, strMsg );

			// SINAD
			strMsg.Format( "SINAD = %.2fdB", m_dSINAD );
			szText = m_dcPlot.GetTextExtent( strMsg );		
			x = m_nClientWidth - FFT_LEFT_MARGIN - nLen;
			y = FFT_TOP_MARGIN + 2 + szText.cy*3;		
			m_dcPlot.TextOut( x, y, strMsg );

			// ENOB
			strMsg.Format( "ENOB = %.2f", m_dENOB );
			szText = m_dcPlot.GetTextExtent( strMsg );		
			x = m_nClientWidth - FFT_LEFT_MARGIN - nLen;
			y = FFT_TOP_MARGIN + 2 + szText.cy*4;		
			m_dcPlot.TextOut( x, y, strMsg );
		}
		if ( pOldFont != NULL )
		{			
			m_dcPlot.SelectObject( pOldFont );
		}
		//////////////////////////////////////////////////////////////////////////
		
		//////////////////////////////////////////////////////////////////
		// 在顶部显示五个最大值
		CString straValue[MARK_NUM];
		DWORD dwMarkWidth;

		dwMarkWidth = 0;
		for ( i = 0; i < MARK_NUM; i++ )
		{
			// 安全检查
			if ( naPos[i] > 0 )
			{
				straValue[i].Format( "(%.2f,%.2f)", naPos[i]*m_dOrgSampFreq/MAX_DEPTH, 
					m_daDispData[ naPos[i] ] );
			}			
			szText = m_dcPlot.GetTextExtent( straValue[i] );
			dwMarkWidth += szText.cx;
		}

		pOldFont = m_dcPlot.SelectObject( &m_fntTitle );
		m_dcPlot.SetTextColor( RGB(0,255,255) );
		// 视图足够宽时显示5个值
		if ( dwMarkWidth < nPicWidth )
		{
			x = (nPicWidth-dwMarkWidth)/2;
			y = 0;
			szText.cx = 0;
			for ( i = 0; i < MARK_NUM; i++ )
			{
				if ( i > 0 )
				{
					szText = m_dcPlot.GetTextExtent( straValue[i-1] );
				}
				x += szText.cx;
				m_dcPlot.TextOut( x, y, straValue[i] );
			}
		}
		if ( pOldFont != NULL )
		{			
			m_dcPlot.SelectObject( pOldFont );
		}
		///////////////////////////////////////////////////////////////////////////

		///////////////////////////////////////////////////////////////////////////
		// 鼠标移动显示坐标值
		if ( m_ptMove.x >= FFT_LEFT_MARGIN && m_ptMove.x <= FFT_LEFT_MARGIN + nPicWidth
			&& m_ptMove.y >= FFT_TOP_MARGIN && m_ptMove.y <= FFT_TOP_MARGIN + nPicHeight )
		{
			CString strValue;
			int nPos;
			nPos = (m_ptMove.x - FFT_LEFT_MARGIN)*m_dwDot/nPicWidth + m_nBeginPos;
			if ( nPos >= 0 && nPos < MAX_DEPTH / 2 )
			{
				// 显示鼠标点的坐标
				//strValue.Format( "(%.2f , %.2f)", nPos * m_dOrgSampFreq / MAX_DEPTH,	
				//	-(m_ptMove.y - FFT_TOP_MARGIN) / dPointYpixel  );

				// 显示曲线上的点频率和幅度
				strValue.Format( "(%.2f , %.2f)", nPos * m_dOrgSampFreq / MAX_DEPTH,	
					m_daDispData[nPos]  );
				// 字体
				pOldFont = m_dcPlot.SelectObject( &m_fntTitle );
				m_dcPlot.SetTextColor( RGB(0,255,255) );
				// 显示的区域
				szText = m_dcPlot.GetTextExtent( strValue );
				if ( m_ptMove.x + szText.cx <= FFT_LEFT_MARGIN + nPicWidth
					&& m_ptMove.y >= FFT_TOP_MARGIN )
				{
					m_dcPlot.TextOut( m_ptMove.x, m_ptMove.y - szText.cy, strValue );
				}
			}			
		}
		//////////////////////////////////////////////////////////////////////////////
		
		Invalidate();
	}

	
}

int CFFTDisp::FindNearValue(int nValue)
{
	int nRetValue;
	int nPow;
	int nBase;
	int nTemp;

	// 查找大约的范围
	nPow = 1;
	for ( int i = MAX_POW; i >= 0 ; i-- )
	{
		nTemp = pow(10,i);
		if ( nValue / nTemp != 0 )
		{
			nPow = i;
			break;
		}
	}
	// 
	nBase = nValue / pow(10,nPow);
	if ( nBase != 1 && nBase != 2 && nBase != 5 )
	{
		if ( nBase == 3 )
		{
			nBase = 2;
		}
		else if ( nBase > 5 )
		{
			nBase = 5;
		}
	}
	nRetValue = nBase * pow( 10, nPow );
	return nRetValue;
}

void CFFTDisp::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	// 保存当前坐标
	CPoint ptTemp;
	ptTemp = point;
	//ScreenToClient( &ptTemp );
	m_ptRightClick = ptTemp;

	// 找到主框架
	CMainFrame* pFrame = NULL;
	pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);
	if ( pFrame != NULL )
	{
		if ( pFrame->m_bZoomOut )
		{
			ZoomOut();
		}
		else if ( pFrame->m_bZoomIn )
		{
			ZoomIn();
		}		
	}

	CWnd::OnLButtonUp(nFlags, point);
}

// 在图像上做标记
void CFFTDisp::DrawMark( int x, int y, char type, COLORREF color)
{
	if ( m_dcPlot == NULL )
	{
		return;
	}

	int len = 3;
	CPen penMark( PS_SOLID, 1, color );
	CPen* pOldPen = m_dcPlot.SelectObject( &penMark );
	switch ( type )
	{
		case '+':
		{
			m_dcPlot.MoveTo( x-len, y );
			m_dcPlot.LineTo( x+len, y );
			m_dcPlot.MoveTo( x, y-len );
			m_dcPlot.LineTo( x, y+len );
			break;
		}
		case 'x':
		{
			m_dcPlot.MoveTo( x-len, y-len );
			m_dcPlot.LineTo( x+len, y+len );
			m_dcPlot.MoveTo( x-len, y+len );
			m_dcPlot.LineTo( x+len, y-len );
			break;
		}
		case 's':
		{
			m_dcPlot.MoveTo( x-len, y-len );
			m_dcPlot.LineTo( x+len, y-len );
			m_dcPlot.MoveTo( x-len, y+len );
			m_dcPlot.LineTo( x+len, y+len );
			break;
		}
		default:
			break;
	}

	if ( pOldPen != NULL )
	{
		m_dcPlot.SelectObject( pOldPen );
	}
	
}

double CFFTDisp::FindNearFloatValue( double dGap )
{
	double dRetValue;
	int nPow;
	int nBase;
	double dTemp;

	// 查找大约的范围
	nPow = 1;
	for ( int i = MAX_POW; i > -MAX_POW ; i-- )
	{
		dTemp = pow(10,i);		
		if ( dGap >= dTemp )
		{
			nPow = i;
			break;
		}
	}
	// 
	nBase = dGap / pow(10,nPow);
	if ( nBase != 1 && nBase != 2 && nBase != 5 )
	{
		if ( nBase == 3 )
		{
			nBase = 2;
		}
		else if ( nBase > 5 )
		{
			nBase = 5;
		}
	}
	dRetValue = nBase * pow( 10, nPow );
	return dRetValue;
}
