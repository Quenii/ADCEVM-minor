// DataDisp.cpp : implementation file
//

#include "stdafx.h"
#include "AdcTestPlat.h"
#include "DataDisp.h"
#include "math.h"
#include "AdcTestPlatView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define DOT_NUM_OF_PERIOD 80 
#define SAMP_M (80.0)

//CString strScale[NUM_VERT+1] = { "255", "192", "128", "64", "0" };
CString strScale[NUM_VERT+1] = { "1.00", "0.75", "0.50", "0.25", "0", "-0.25", "-0.50", "-0.75", "-1.00" };

/////////////////////////////////////////////////////////////////////////////
// CDataDisp

CDataDisp::CDataDisp()
{
	m_bDisplay = TRUE;
	m_dMaxValue = MAX_VALUE;
	m_nDotPerPeriod = 80;
	m_nDisplaySel = 1;	
	m_dAmp = 1.00;
	m_bMv = FALSE;
}

CDataDisp::~CDataDisp()
{
	if (m_pbitmapOldGrid != NULL)
		m_dcGrid.SelectObject(m_pbitmapOldGrid) ;  
	if (m_pbitmapOldPlot != NULL)
		m_dcPlot.SelectObject(m_pbitmapOldPlot) ;
}


BEGIN_MESSAGE_MAP(CDataDisp, CWnd)
	//{{AFX_MSG_MAP(CDataDisp)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_CONTEXTMENU()	
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDataDisp message handlers

BOOL CDataDisp::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID )
//Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	// 颜色
	m_crImageBack = RGB( 0, 0, 0 );
	m_crImageFore = RGB( 0, 255, 0 );
	m_crYellow = RGB( 255, 255, 0 );
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

	BOOL result ;
	static CString className = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW) ;

	result = CWnd::CreateEx(WS_EX_CLIENTEDGE | WS_EX_STATICEDGE, 
						  className, "DataDisp", dwStyle, 
						  rect.left, rect.top, rect.right-rect.left, rect.bottom-rect.top,
						  pParentWnd->GetSafeHwnd(), (HMENU)nID) ;// lpszWindowName = NULL
	if (result != 0)
		InitDC() ;

	return result ;

	//return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

void CDataDisp::InitDC()
{
	//int i;
	CSize szText;
	//int x;
	//int y;
	CClientDC dc(this) ;
	CRect rc;
	GetClientRect( &rc );
	int nClientWidth = rc.right - rc.left;
	int nClientHeight = rc.bottom - rc.top;

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
	
	int nSigPicWidth = rc.right - rc.left - LEFT_MARGIN * 2;
	int nSigPicHeight = rc.bottom - rc.top - TOP_MARGIN * 2;	
	int nSigPicSmallWidth = nSigPicWidth / NUM_HORZ;
	int nSigPicSmallHeight = nSigPicHeight / NUM_VERT;	

	// 黑色背景
	m_dcGrid.FillSolidRect( rc, m_crImageBack );
/*
	// 轴的颜色
	CPen penAxi( PS_DOT, 1, RGB(128, 128, 128));//RGB(192, 192, 192)
	CPen penLightGray( PS_DOT, 1, RGB(255, 255, 255) );
	CPen *pOldPen = m_dcGrid.SelectObject( &penAxi );
	m_dcGrid.SetTextColor( RGB(128, 128, 128) );
	CFont* pOldFont = m_dcGrid.SelectObject( &m_fntScale );

	
	//绘制纵坐标轴
	for ( i = 0; i < NUM_HORZ+1; i++ )
	{
		if ( i == NUM_HORZ / 2 )
		{
			m_dcGrid.SelectObject( &penLightGray );
		}
		else
		{
			m_dcGrid.SelectObject( &penAxi );
		}
		// 只绘制两端的线，中间的线在画图像的时候绘制
		if ( i == 0 || i == NUM_HORZ )
		{
			m_dcGrid.MoveTo( LEFT_MARGIN + nSigPicSmallWidth * i, TOP_MARGIN );
			m_dcGrid.LineTo( LEFT_MARGIN + nSigPicSmallWidth * i, rc.bottom - TOP_MARGIN );
		}		
	}

	if ( pOldPen != NULL )
	{
		m_dcGrid.SelectObject( pOldPen );
	}
	if ( pOldFont != NULL )
	{
		// 恢复原来的字体
		m_dcGrid.SelectObject( pOldFont );
	}
	
	penAxi.DeleteObject();
	penLightGray.DeleteObject();
*/
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

void CDataDisp::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here	
	if ( cx > 0 && cy > 0 )
	{
		CRect rc;
		GetClientRect( &rc );
		m_nClientHeight = rc.Height();
		m_nClientWidth  = rc.Width();
		// 显示点数为实际点数的一半
		m_nDot = (rc.right - rc.left - LEFT_MARGIN * 2) / NUM_HORZ * NUM_HORZ / 2;
		m_nSaveDot = m_nDot;
		// 图像大小发生变化时，修改背景DC和图像DC的大小
		InitDC();
		// 重画图像
		DrawData();
	}
	
}

void CDataDisp::DrawData()
{
	int i;
	int x, y;
	CPen *pOldPen;
	CFont* pOldFont;
	CString strMsg;
	CSize szText;
	double m_dMaxData;
	double m_dMinData;
	double dPointYpixel;
	int nMaxPos;
	int nMinPos;
	double dActualMax;
	double dActualMin;

	if ( m_dcPlot.GetSafeHdc() != NULL )
	{
		// 刷背景
		CRect rcPic;
		GetClientRect( &rcPic );
		int nWidth = rcPic.right - rcPic.left - LEFT_MARGIN*2;
		int nHeight = rcPic.bottom - rcPic.top - TOP_MARGIN*2;			
		int nSigPicSmallWidth = nWidth / NUM_HORZ;
		int nSigPicSmallHeight = nHeight / NUM_VERT;
		// 对齐后的宽度和高度
		int nPicWidth = nSigPicSmallWidth * NUM_HORZ;
		int nPicHeight = nSigPicSmallHeight * NUM_VERT;
		m_dcPlot.FillSolidRect( rcPic, m_crImageBack );
		// 标题
		pOldFont = m_dcPlot.SelectObject( &m_fntTitle );
		m_dcPlot.SetTextColor( m_crImageFore );
		m_dcPlot.TextOut( 2, 2, m_strTitle );
		if ( pOldFont != NULL )
		{
			// 恢复原来的字体
			m_dcPlot.SelectObject( pOldFont );
		}		
		// 两路都不显示
		if ( m_nDisplaySel == 0 )
		{
			Invalidate();
			return;
		}
		
		// 画横轴
		CPen penAxi( PS_DOT, 1, RGB(128, 128, 128));
		CPen penLightGray( PS_DOT, 1, RGB(255, 255, 255) );
		pOldPen = m_dcPlot.SelectObject( &penAxi );
		for ( i = 0; i < NUM_VERT+1; i++ )
		{
			if ( i == NUM_VERT / 2 )
			{
				m_dcPlot.SelectObject( &penLightGray );
			}
			else
			{
				m_dcPlot.SelectObject( &penAxi );
			}
			m_dcPlot.MoveTo( LEFT_MARGIN, TOP_MARGIN + nSigPicSmallHeight * i);
			m_dcPlot.LineTo( LEFT_MARGIN+nPicWidth, TOP_MARGIN + nSigPicSmallHeight * i );
		}
		// 画纵轴
		m_dcPlot.MoveTo( LEFT_MARGIN, TOP_MARGIN );
		m_dcPlot.LineTo( LEFT_MARGIN, TOP_MARGIN + nPicHeight );
		m_dcPlot.MoveTo( LEFT_MARGIN + nPicWidth, TOP_MARGIN );
		m_dcPlot.LineTo( LEFT_MARGIN + nPicWidth, TOP_MARGIN + nPicHeight );
		// 如果周期过多，每几个周期显示一次
		int nPeriod = m_nDot / m_nDotPerPeriod / 10;
		if ( nPeriod < 1 )
		{
			nPeriod = 1;
		}
		for ( i = 1; i < m_nDot / m_nDotPerPeriod + 1; i++ )
		{
			// 几个周期显示一次
			if ( i % nPeriod == 0 )
			{
				x = LEFT_MARGIN + i * m_nDotPerPeriod * nWidth / m_nDot;
				m_dcPlot.MoveTo( x,	TOP_MARGIN );
				m_dcPlot.LineTo( x,	TOP_MARGIN + nPicHeight );
			}			
		}
		if ( pOldPen != NULL )
		{
			m_dcPlot.SelectObject( pOldPen );
		}

		// 显示第一路图像
		if ( m_nDisplaySel == 1 || m_nDisplaySel == 3 )
		{
			// 从文档对象获取原始数据进行显示		
			CPen penDataSignal( PS_SOLID, 1, m_crImageFore );
			pOldPen = m_dcPlot.SelectObject( &penDataSignal );		
					
			// 14位带符号数的最大值为8192
			//m_dMaxData = 8192;
			//m_dMinData = -8192;
			// 16位带符号数的最大值为32768
			m_dMaxData = m_dMaxValue;
			m_dMinData = -m_dMaxValue;
			dPointYpixel = (nPicHeight - 0.0 ) / (m_dMaxData-m_dMinData);
			// 绘图
			m_dcPlot.MoveTo( LEFT_MARGIN, 
				TOP_MARGIN + nPicHeight - (int)((m_waDataDisp[0] - m_dMinData)*dPointYpixel) );
					
			// 每一个点都绘制
			for ( i = 1; i < m_nDot; i++ )
			{
				x = LEFT_MARGIN + i * nWidth / m_nDot;
				y = TOP_MARGIN + nPicHeight - (int)((m_waDataDisp[i] - m_dMinData)*dPointYpixel);			
				m_dcPlot.LineTo( x, y );
			}
			// 放大的时候，最后一个点可能不到边，增加最后一个靠边的点
			x = LEFT_MARGIN + nWidth;
			y = TOP_MARGIN + nPicHeight - (int)((m_waDataDisp[i] - m_dMinData)*dPointYpixel);
			m_dcPlot.LineTo( x, y );			
			// 恢复
			if ( pOldPen != NULL )
			{
				m_dcPlot.SelectObject( pOldPen );
			}
		}
		// 显示第二个图形
		if ( m_nDisplaySel == 2 || m_nDisplaySel == 3 )
		{
			CPen penDataSignal2( PS_SOLID, 1, m_crYellow );
			pOldPen = m_dcPlot.SelectObject( &penDataSignal2 );			
			// 16位带符号数的最大值为32768
			m_dMaxData = m_dMaxValue;
			m_dMinData = -m_dMaxValue;
			dPointYpixel = (nPicHeight - 0.0 ) / (m_dMaxData-m_dMinData);
			// 绘图
			m_dcPlot.MoveTo( LEFT_MARGIN, 
				TOP_MARGIN + nPicHeight - (int)((m_waDataDisp2[0] - m_dMinData)*dPointYpixel) );
					
			// 每一个点都绘制
			for ( i = 1; i < m_nDot; i++ )
			{
				x = LEFT_MARGIN + i * nWidth / m_nDot;
				y = TOP_MARGIN + nPicHeight - (int)((m_waDataDisp2[i] - m_dMinData)*dPointYpixel);			
				m_dcPlot.LineTo( x, y );
			}
			// 放大的时候，最后一个点可能不到边，增加最后一个靠边的点
			x = LEFT_MARGIN + nWidth;
			y = TOP_MARGIN + nPicHeight - (int)((m_waDataDisp2[i] - m_dMinData)*dPointYpixel);
			m_dcPlot.LineTo( x, y );
			// 恢复
			if ( pOldPen != NULL )
			{
				m_dcPlot.SelectObject( pOldPen );
			}
		}
//		
		// 擦除多余部分
		CRect rcBottom( 0, TOP_MARGIN + NUM_VERT * nSigPicSmallHeight + 2,
			rcPic.right - rcPic.left, rcPic.bottom - rcPic.top );		
		m_dcPlot.FillSolidRect( rcBottom, m_crImageBack );
		CRect rcTop( 0, 0,	rcPic.right - rcPic.left, TOP_MARGIN );		
		m_dcPlot.FillSolidRect( rcTop, m_crImageBack );
//

		// 标题
		pOldFont = m_dcPlot.SelectObject( &m_fntTitle );
		m_dcPlot.SetTextColor( m_crImageFore );
		m_dcPlot.TextOut( 2, 2, m_strTitle );
		if ( pOldFont != NULL )
		{			
			m_dcPlot.SelectObject( pOldFont );
		}		
		
		// 写横向刻度
		m_dcPlot.SetTextColor( RGB(128, 128, 128) );
		pOldFont = m_dcPlot.SelectObject( &m_fntScale );		
		for ( i = 0; i < NUM_VERT+1; i++ )
		{			
			// 刻度值
			szText =  m_dcPlot.GetTextExtent( strScale[i] );
			if ( szText.cx > LEFT_MARGIN )
			{
				x = 0;
			}
			else
			{
				x = LEFT_MARGIN - szText.cx;
			}
			if ( szText.cy / 2 > TOP_MARGIN ) 
			{
				y = TOP_MARGIN + nSigPicSmallHeight * i;
			}
			else
			{
				y = TOP_MARGIN + nSigPicSmallHeight * i - szText.cy / 2;
			}
			// 最下面的值
			if ( i == NUM_VERT )
			{
				y = TOP_MARGIN + nSigPicSmallHeight * i - szText.cy;
			}
			m_dcPlot.TextOut( x, y, strScale[i] );
			// 显示v
			if ( i == 0 )
			{
				CString strMsg;
				if ( m_bMv )
				{
					strMsg = "(mv)";
				}
				else
				{
					strMsg = "(v)";
				}
				// x
				szText = m_dcPlot.GetTextExtent( strMsg );
				if ( szText.cx > LEFT_MARGIN )
				{
					x = 0;
				}
				else
				{
					x = LEFT_MARGIN - szText.cx;
				}
				// y
				szText = m_dcPlot.GetTextExtent( strScale[0] );
				y = TOP_MARGIN + szText.cy / 2 - 2;
				m_dcPlot.TextOut( x, y, strMsg );
			}
		}
		
		// 写纵向刻度
		strMsg = "0";
		m_dcPlot.TextOut( LEFT_MARGIN, TOP_MARGIN + nPicHeight, strMsg );		
		for ( i = 1; i < m_nDot / m_nDotPerPeriod + 1; i++ )
		{						
			// 几个周期显示一次
			if ( i % nPeriod == 0 )
			{
				x = LEFT_MARGIN + i * m_nDotPerPeriod * nWidth / m_nDot;
				strMsg.Format( "%.2fus", i * m_nDotPerPeriod / SAMP_M );
				szText = m_dcPlot.GetTextExtent( strMsg );
				m_dcPlot.TextOut( x - szText.cx / 2, TOP_MARGIN + nPicHeight + 2, strMsg );
			}			
		}		
		if ( pOldFont != NULL )
		{
			m_dcPlot.SelectObject( pOldFont );
		}		
		
		// 计算最大值、最小值和Vpp
		// 第一个图形
		if ( m_nDisplaySel == 1 || m_nDisplaySel == 3 )
		{					
			dActualMax = -m_dMaxValue;
			dActualMin = m_dMaxValue;
			// 从视图里面查找最大值和最小值
			for ( i = 0; i < m_nDot; i++ )
			{
				if ( m_waDataDisp[i] > dActualMax )
				{
					nMaxPos = i;
					dActualMax = m_waDataDisp[i];
				}
				if ( m_waDataDisp[i] < dActualMin )
				{
					nMinPos = i;
					dActualMin = m_waDataDisp[i];
				}
			}
			// 绘制最大值、最小值和Vpp
			pOldFont = m_dcPlot.SelectObject( &m_fntTitle );
			m_dcPlot.SetTextColor( m_crImageFore );// RGB(0,255,255)

			if ( m_bMv )
			{
				strMsg.Format( "%.0fmv", dActualMax * 1000 / MAX_VALUE );
			}
			else
			{
				strMsg.Format( "%1.2fv", dActualMax / MAX_VALUE );
			}			
			szText = m_dcPlot.GetTextExtent( strMsg );
			x = LEFT_MARGIN + nMaxPos * nWidth / m_nDot;
			y = TOP_MARGIN + nPicHeight - (int)((dActualMax - m_dMinData)*dPointYpixel) - szText.cy;		
			m_dcPlot.TextOut( x, y, strMsg );
			//m_dcPlot.SetPixel( x, y, RGB(0,255,255) );

			if ( m_bMv )
			{
				strMsg.Format( "%.0fmv", dActualMin * 1000 / MAX_VALUE );
			}
			else
			{
				strMsg.Format( "%1.2fv", dActualMin / MAX_VALUE );
			}			
			szText = m_dcPlot.GetTextExtent( strMsg );
			x = LEFT_MARGIN + nMinPos * nWidth / m_nDot;
			y = TOP_MARGIN + nPicHeight - (int)((dActualMin - m_dMinData)*dPointYpixel) + 2;		
			m_dcPlot.TextOut( x, y, strMsg );
			
			if ( m_bMv )
			{
				strMsg.Format( "Vpp = %.0fmv", (dActualMax - dActualMin) * 1000 / MAX_VALUE );
			}
			else
			{
				strMsg.Format( "Vpp = %1.2fv", (dActualMax - dActualMin) / MAX_VALUE );
			}
			szText = m_dcPlot.GetTextExtent( strMsg );		
			x = rcPic.right - LEFT_MARGIN - szText.cx;
			y = TOP_MARGIN + 2;		
			m_dcPlot.TextOut( x, y, strMsg );

			if ( pOldFont != NULL )
			{			
				m_dcPlot.SelectObject( pOldFont );
			}		
		}		
		// 第二个图形
		if ( m_nDisplaySel == 2 || m_nDisplaySel == 3 )
		{
			// 从视图里面查找最大值和最小值
			dActualMax = -m_dMaxValue;
			dActualMin = m_dMaxValue;			
			for ( i = 0; i < m_nDot; i++ )
			{
				if ( m_waDataDisp2[i] > dActualMax )
				{
					nMaxPos = i;
					dActualMax = m_waDataDisp2[i];
				}
				if ( m_waDataDisp2[i] < dActualMin )
				{
					nMinPos = i;
					dActualMin = m_waDataDisp2[i];
				}
			}
			// 绘制最大值、最小值和Vpp
			pOldFont = m_dcPlot.SelectObject( &m_fntTitle );
			m_dcPlot.SetTextColor( m_crYellow );
			
			if ( m_bMv )
			{
				strMsg.Format( "%.0fmv", dActualMax * 1000 / MAX_VALUE );
			}
			else
			{
				strMsg.Format( "%1.2fv", dActualMax / MAX_VALUE );
			}	
			szText = m_dcPlot.GetTextExtent( strMsg );
			x = LEFT_MARGIN + nMaxPos * nWidth / m_nDot;
			y = TOP_MARGIN + nPicHeight - (int)((dActualMax - m_dMinData)*dPointYpixel) - szText.cy;		
			m_dcPlot.TextOut( x, y, strMsg );
			

			if ( m_bMv )
			{
				strMsg.Format( "%.0fmv", dActualMin * 1000 / MAX_VALUE );
			}
			else
			{
				strMsg.Format( "%1.2fv", dActualMin / MAX_VALUE );
			}	
			szText = m_dcPlot.GetTextExtent( strMsg );
			x = LEFT_MARGIN + nMinPos * nWidth / m_nDot;
			y = TOP_MARGIN + nPicHeight - (int)((dActualMin - m_dMinData)*dPointYpixel) + 2;		
			m_dcPlot.TextOut( x, y, strMsg );
			
			if ( m_bMv )
			{
				strMsg.Format( "Vpp = %.0fmv", (dActualMax - dActualMin) * 1000 / MAX_VALUE );
			}
			else
			{
				strMsg.Format( "Vpp = %1.2fv", (dActualMax - dActualMin) / MAX_VALUE );
			}
			szText = m_dcPlot.GetTextExtent( strMsg );		
			x = rcPic.right - LEFT_MARGIN - szText.cx;
			y = TOP_MARGIN + 2 + szText.cy;		
			m_dcPlot.TextOut( x, y, strMsg );

			if ( pOldFont != NULL )
			{			
				m_dcPlot.SelectObject( pOldFont );
			}
		}
		
		penAxi.DeleteObject();
		penLightGray.DeleteObject();

		Invalidate();
	}
	
}

void CDataDisp::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CDC memDC ;
	CBitmap memBitmap ;
	CBitmap* oldBitmap ; // bitmap originally found in CMemDC
	
	CRect rc;
	GetClientRect( &rc );
	int nClientWidth = rc.right - rc.left;
	int nClientHeight = rc.bottom - rc.top;

	// no real plotting work is performed here, 
	// just putting the existing bitmaps on the client

	// to avoid flicker, establish a memory dc, draw to it 
	// and then BitBlt it to the client
	memDC.CreateCompatibleDC(&dc) ;
	memBitmap.CreateCompatibleBitmap(&dc, nClientWidth, nClientHeight) ;
	oldBitmap = (CBitmap *)memDC.SelectObject(&memBitmap) ;

	if (memDC.GetSafeHdc() != NULL)
	{
		// first drop the grid on the memory dc
		memDC.BitBlt(0, 0, nClientWidth, nClientHeight, 
					 &m_dcGrid, 0, 0, SRCCOPY) ;
		// now add the plot on top as a "pattern" via SRCPAINT.
		// works well with dark background and a light plot
		memDC.BitBlt(0, 0, nClientWidth, nClientHeight, 
					 &m_dcPlot, 0, 0, SRCPAINT) ;  //SRCPAINT
		// finally send the result to the display
		dc.BitBlt(0, 0, nClientWidth, nClientHeight, 
				  &memDC, 0, 0, SRCCOPY) ;
	}

	memDC.SelectObject(oldBitmap) ;

	// Do not call CWnd::OnPaint() for painting messages
}

void CDataDisp::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	
	CMenu menuZoom;
	menuZoom.LoadMenu( IDR_MENU_ZOOM );	

	// 获取菜单所属窗口
	CWnd* pWndPopupOwner = this;
	while ( pWndPopupOwner->GetStyle() & WS_CHILD )
	{
		pWndPopupOwner = pWndPopupOwner->GetParent();
	}	
	
	menuZoom.GetSubMenu(0)->TrackPopupMenu( TPM_LEFTALIGN, point.x, point.y, pWndPopupOwner  );//this	
	// 当前为第几个data视图保存到mainfrm
	((CMainFrame*)pWndPopupOwner)->m_byDataIndex = m_byIndex;
}

void CDataDisp::OnMouseMove(UINT nFlags, CPoint point) 
{
	//::SetCursor( ::LoadCursor( NULL, IDC_ARROW ) );
/*
	// 保存当前坐标
	CPoint ptTemp;
	ptTemp = point;
	ScreenToClient( &ptTemp );	
	// 在图像区域内时弹出菜单
	CRect rc( LEFT_MARGIN, TOP_MARGIN, m_nClientWidth - LEFT_MARGIN, m_nClientHeight - TOP_MARGIN );
	if ( rc.PtInRect(ptTemp) )
*/
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
	}
	
}


void CDataDisp::ZoomIn()
{
	int i;
	int nGap;

	// 找到主框架
	CMainFrame* pFrame = NULL;
	pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);
	if ( pFrame != NULL )
	{
		// 水平缩小
		if ( pFrame->m_bZoomH )
		{
			m_nDot = m_nDot * 2;
			if ( m_nDot > 1024 )
			{
				m_nDot = 1024;
			}
		}
		// 垂直缩小
		if ( pFrame->m_bZoomV )
		{
			if ( m_dMaxValue < MAX_VALUE / 2 )
			{
				m_dMaxValue *= 2;
				m_dAmp *= 2;
				// 小于0.5v时转换为mv显示
				if ( m_dAmp < 0.5 )
				{
					m_bMv = TRUE;
					// 一个格的大小(mv)
					nGap = m_dAmp * 1000 / (NUM_VERT/2);
					nGap = FindNearValue( nGap );
					// 新的最大值
					m_dMaxValue = nGap * (NUM_VERT/2) * m_dMaxValue / (m_dAmp * 1000);
					m_dAmp = nGap * (NUM_VERT/2) * 1.0 / 1000;
					// 计算坐标值
					for ( i = 0; i < NUM_VERT+1; i++ )
					{
						strScale[i].Format( "%d", nGap * (4-i) );
					}
				}
				else
				{
					m_bMv = FALSE;
					// 计算坐标值
					for ( i = 0; i < NUM_VERT+1; i++ )
					{
						strScale[i].Format( "%.2f", m_dAmp / (NUM_VERT/2) * (4-i) );
					}
				}
			}
			// 否则，恢复
			else
			{
				ZoomRestore();
			}
		}
	}
	
	DrawData();
}

void CDataDisp::ZoomOut()
{
	int i;
	int nGap;

	// 找到主框架
	CMainFrame* pFrame = NULL;
	pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);
	if ( pFrame != NULL )
	{
		// 水平放大
		if ( pFrame->m_bZoomH )
		{
			m_nDot = m_nDot / 2;
			if ( m_nDot < 40 )
			{
				m_nDot = 40;
			}
		}
		// 垂直放大
		if ( pFrame->m_bZoomV )
		{
			//if ( m_dMaxValue > 2 )
			// 最小刻度为1mv, 4个格为4mv，小于8mv时不能再放大
			if ( m_dAmp > 0.007 )
			{
				m_dMaxValue /= 2;
				m_dAmp /= 2;
				// 小于0.5v时转换为mv显示
				if ( m_dAmp < 0.5 )
				{
					m_bMv = TRUE;
					// 一个格的大小(mv)
					nGap = m_dAmp * 1000 / (NUM_VERT/2);
					nGap = FindNearValue( nGap );
					// 新的最大值
					m_dMaxValue = nGap * (NUM_VERT/2) * m_dMaxValue / (m_dAmp * 1000);
					m_dAmp = nGap * (NUM_VERT/2) * 1.0 / 1000;
					// 计算坐标值
					for ( i = 0; i < NUM_VERT+1; i++ )
					{
						strScale[i].Format( "%d", nGap * (4-i) );
					}
				}
				else
				{
					m_bMv = FALSE;
					// 计算坐标值
					for ( i = 0; i < NUM_VERT+1; i++ )
					{
						strScale[i].Format( "%.2f", m_dAmp / (NUM_VERT/2) * (4-i) );
					}
				}
			}
			// 不能放大时，恢复
			else
			{
				ZoomRestore();
			}
		}
	}
	DrawData();
}

void CDataDisp::ZoomRestore()
{
	m_nDot = m_nSaveDot;
	m_dMaxValue = MAX_VALUE;	
	m_dAmp = 1.00;	
	// 计算坐标值
	for ( int i = 0; i < NUM_VERT+1; i++ )
	{
		strScale[i].Format( "%.2f", m_dAmp / (NUM_VERT/2) * (4-i) );
	}
	DrawData();
}

void CDataDisp::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
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

int CDataDisp::FindNearValue(int nValue)
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