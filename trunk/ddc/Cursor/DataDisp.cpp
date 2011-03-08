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
	// ��ɫ
	m_crImageBack = RGB( 0, 0, 0 );
	m_crImageFore = RGB( 0, 255, 0 );
	m_crYellow = RGB( 255, 255, 0 );
	// ����
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
                       DEFAULT_PITCH|FF_SWISS, "����") ;

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

	// �������ڴ�DC
	if ( m_dcGrid.GetSafeHdc() == NULL )
	{
		m_dcGrid.CreateCompatibleDC(&dc) ;
		m_bitmapGrid.CreateCompatibleBitmap(&dc, nClientWidth, nClientHeight) ;
		m_pbitmapOldGrid = m_dcGrid.SelectObject(&m_bitmapGrid) ;
	}	
	else
	{
		// �ָ�ԭ����λͼ����ɾ���½���λͼ
		m_dcGrid.SelectObject( m_pbitmapOldGrid );
		m_bitmapGrid.DeleteObject();
		// ��ɾ��ԭ����DC�������ӵ��µ�DC��
		m_dcGrid.DeleteDC();
		m_dcGrid.CreateCompatibleDC(&dc) ;
		m_bitmapGrid.CreateCompatibleBitmap(&dc, nClientWidth, nClientHeight) ;
		m_pbitmapOldGrid = m_dcGrid.SelectObject(&m_bitmapGrid) ;
	}
	
	int nSigPicWidth = rc.right - rc.left - LEFT_MARGIN * 2;
	int nSigPicHeight = rc.bottom - rc.top - TOP_MARGIN * 2;	
	int nSigPicSmallWidth = nSigPicWidth / NUM_HORZ;
	int nSigPicSmallHeight = nSigPicHeight / NUM_VERT;	

	// ��ɫ����
	m_dcGrid.FillSolidRect( rc, m_crImageBack );
/*
	// �����ɫ
	CPen penAxi( PS_DOT, 1, RGB(128, 128, 128));//RGB(192, 192, 192)
	CPen penLightGray( PS_DOT, 1, RGB(255, 255, 255) );
	CPen *pOldPen = m_dcGrid.SelectObject( &penAxi );
	m_dcGrid.SetTextColor( RGB(128, 128, 128) );
	CFont* pOldFont = m_dcGrid.SelectObject( &m_fntScale );

	
	//������������
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
		// ֻ�������˵��ߣ��м�����ڻ�ͼ���ʱ�����
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
		// �ָ�ԭ��������
		m_dcGrid.SelectObject( pOldFont );
	}
	
	penAxi.DeleteObject();
	penLightGray.DeleteObject();
*/
	// ���ε�DC
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
		// ��ʾ����Ϊʵ�ʵ�����һ��
		m_nDot = (rc.right - rc.left - LEFT_MARGIN * 2) / NUM_HORZ * NUM_HORZ / 2;
		m_nSaveDot = m_nDot;
		// ͼ���С�����仯ʱ���޸ı���DC��ͼ��DC�Ĵ�С
		InitDC();
		// �ػ�ͼ��
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
		// ˢ����
		CRect rcPic;
		GetClientRect( &rcPic );
		int nWidth = rcPic.right - rcPic.left - LEFT_MARGIN*2;
		int nHeight = rcPic.bottom - rcPic.top - TOP_MARGIN*2;			
		int nSigPicSmallWidth = nWidth / NUM_HORZ;
		int nSigPicSmallHeight = nHeight / NUM_VERT;
		// �����Ŀ�Ⱥ͸߶�
		int nPicWidth = nSigPicSmallWidth * NUM_HORZ;
		int nPicHeight = nSigPicSmallHeight * NUM_VERT;
		m_dcPlot.FillSolidRect( rcPic, m_crImageBack );
		// ����
		pOldFont = m_dcPlot.SelectObject( &m_fntTitle );
		m_dcPlot.SetTextColor( m_crImageFore );
		m_dcPlot.TextOut( 2, 2, m_strTitle );
		if ( pOldFont != NULL )
		{
			// �ָ�ԭ��������
			m_dcPlot.SelectObject( pOldFont );
		}		
		// ��·������ʾ
		if ( m_nDisplaySel == 0 )
		{
			Invalidate();
			return;
		}
		
		// ������
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
		// ������
		m_dcPlot.MoveTo( LEFT_MARGIN, TOP_MARGIN );
		m_dcPlot.LineTo( LEFT_MARGIN, TOP_MARGIN + nPicHeight );
		m_dcPlot.MoveTo( LEFT_MARGIN + nPicWidth, TOP_MARGIN );
		m_dcPlot.LineTo( LEFT_MARGIN + nPicWidth, TOP_MARGIN + nPicHeight );
		// ������ڹ��࣬ÿ����������ʾһ��
		int nPeriod = m_nDot / m_nDotPerPeriod / 10;
		if ( nPeriod < 1 )
		{
			nPeriod = 1;
		}
		for ( i = 1; i < m_nDot / m_nDotPerPeriod + 1; i++ )
		{
			// ����������ʾһ��
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

		// ��ʾ��һ·ͼ��
		if ( m_nDisplaySel == 1 || m_nDisplaySel == 3 )
		{
			// ���ĵ������ȡԭʼ���ݽ�����ʾ		
			CPen penDataSignal( PS_SOLID, 1, m_crImageFore );
			pOldPen = m_dcPlot.SelectObject( &penDataSignal );		
					
			// 14λ�������������ֵΪ8192
			//m_dMaxData = 8192;
			//m_dMinData = -8192;
			// 16λ�������������ֵΪ32768
			m_dMaxData = m_dMaxValue;
			m_dMinData = -m_dMaxValue;
			dPointYpixel = (nPicHeight - 0.0 ) / (m_dMaxData-m_dMinData);
			// ��ͼ
			m_dcPlot.MoveTo( LEFT_MARGIN, 
				TOP_MARGIN + nPicHeight - (int)((m_waDataDisp[0] - m_dMinData)*dPointYpixel) );
					
			// ÿһ���㶼����
			for ( i = 1; i < m_nDot; i++ )
			{
				x = LEFT_MARGIN + i * nWidth / m_nDot;
				y = TOP_MARGIN + nPicHeight - (int)((m_waDataDisp[i] - m_dMinData)*dPointYpixel);			
				m_dcPlot.LineTo( x, y );
			}
			// �Ŵ��ʱ�����һ������ܲ����ߣ��������һ�����ߵĵ�
			x = LEFT_MARGIN + nWidth;
			y = TOP_MARGIN + nPicHeight - (int)((m_waDataDisp[i] - m_dMinData)*dPointYpixel);
			m_dcPlot.LineTo( x, y );			
			// �ָ�
			if ( pOldPen != NULL )
			{
				m_dcPlot.SelectObject( pOldPen );
			}
		}
		// ��ʾ�ڶ���ͼ��
		if ( m_nDisplaySel == 2 || m_nDisplaySel == 3 )
		{
			CPen penDataSignal2( PS_SOLID, 1, m_crYellow );
			pOldPen = m_dcPlot.SelectObject( &penDataSignal2 );			
			// 16λ�������������ֵΪ32768
			m_dMaxData = m_dMaxValue;
			m_dMinData = -m_dMaxValue;
			dPointYpixel = (nPicHeight - 0.0 ) / (m_dMaxData-m_dMinData);
			// ��ͼ
			m_dcPlot.MoveTo( LEFT_MARGIN, 
				TOP_MARGIN + nPicHeight - (int)((m_waDataDisp2[0] - m_dMinData)*dPointYpixel) );
					
			// ÿһ���㶼����
			for ( i = 1; i < m_nDot; i++ )
			{
				x = LEFT_MARGIN + i * nWidth / m_nDot;
				y = TOP_MARGIN + nPicHeight - (int)((m_waDataDisp2[i] - m_dMinData)*dPointYpixel);			
				m_dcPlot.LineTo( x, y );
			}
			// �Ŵ��ʱ�����һ������ܲ����ߣ��������һ�����ߵĵ�
			x = LEFT_MARGIN + nWidth;
			y = TOP_MARGIN + nPicHeight - (int)((m_waDataDisp2[i] - m_dMinData)*dPointYpixel);
			m_dcPlot.LineTo( x, y );
			// �ָ�
			if ( pOldPen != NULL )
			{
				m_dcPlot.SelectObject( pOldPen );
			}
		}
//		
		// �������ಿ��
		CRect rcBottom( 0, TOP_MARGIN + NUM_VERT * nSigPicSmallHeight + 2,
			rcPic.right - rcPic.left, rcPic.bottom - rcPic.top );		
		m_dcPlot.FillSolidRect( rcBottom, m_crImageBack );
		CRect rcTop( 0, 0,	rcPic.right - rcPic.left, TOP_MARGIN );		
		m_dcPlot.FillSolidRect( rcTop, m_crImageBack );
//

		// ����
		pOldFont = m_dcPlot.SelectObject( &m_fntTitle );
		m_dcPlot.SetTextColor( m_crImageFore );
		m_dcPlot.TextOut( 2, 2, m_strTitle );
		if ( pOldFont != NULL )
		{			
			m_dcPlot.SelectObject( pOldFont );
		}		
		
		// д����̶�
		m_dcPlot.SetTextColor( RGB(128, 128, 128) );
		pOldFont = m_dcPlot.SelectObject( &m_fntScale );		
		for ( i = 0; i < NUM_VERT+1; i++ )
		{			
			// �̶�ֵ
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
			// �������ֵ
			if ( i == NUM_VERT )
			{
				y = TOP_MARGIN + nSigPicSmallHeight * i - szText.cy;
			}
			m_dcPlot.TextOut( x, y, strScale[i] );
			// ��ʾv
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
		
		// д����̶�
		strMsg = "0";
		m_dcPlot.TextOut( LEFT_MARGIN, TOP_MARGIN + nPicHeight, strMsg );		
		for ( i = 1; i < m_nDot / m_nDotPerPeriod + 1; i++ )
		{						
			// ����������ʾһ��
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
		
		// �������ֵ����Сֵ��Vpp
		// ��һ��ͼ��
		if ( m_nDisplaySel == 1 || m_nDisplaySel == 3 )
		{					
			dActualMax = -m_dMaxValue;
			dActualMin = m_dMaxValue;
			// ����ͼ����������ֵ����Сֵ
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
			// �������ֵ����Сֵ��Vpp
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
		// �ڶ���ͼ��
		if ( m_nDisplaySel == 2 || m_nDisplaySel == 3 )
		{
			// ����ͼ����������ֵ����Сֵ
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
			// �������ֵ����Сֵ��Vpp
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

	// ��ȡ�˵���������
	CWnd* pWndPopupOwner = this;
	while ( pWndPopupOwner->GetStyle() & WS_CHILD )
	{
		pWndPopupOwner = pWndPopupOwner->GetParent();
	}	
	
	menuZoom.GetSubMenu(0)->TrackPopupMenu( TPM_LEFTALIGN, point.x, point.y, pWndPopupOwner  );//this	
	// ��ǰΪ�ڼ���data��ͼ���浽mainfrm
	((CMainFrame*)pWndPopupOwner)->m_byDataIndex = m_byIndex;
}

void CDataDisp::OnMouseMove(UINT nFlags, CPoint point) 
{
	//::SetCursor( ::LoadCursor( NULL, IDC_ARROW ) );
/*
	// ���浱ǰ����
	CPoint ptTemp;
	ptTemp = point;
	ScreenToClient( &ptTemp );	
	// ��ͼ��������ʱ�����˵�
	CRect rc( LEFT_MARGIN, TOP_MARGIN, m_nClientWidth - LEFT_MARGIN, m_nClientHeight - TOP_MARGIN );
	if ( rc.PtInRect(ptTemp) )
*/
	{
		// �ҵ������
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

	// �ҵ������
	CMainFrame* pFrame = NULL;
	pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);
	if ( pFrame != NULL )
	{
		// ˮƽ��С
		if ( pFrame->m_bZoomH )
		{
			m_nDot = m_nDot * 2;
			if ( m_nDot > 1024 )
			{
				m_nDot = 1024;
			}
		}
		// ��ֱ��С
		if ( pFrame->m_bZoomV )
		{
			if ( m_dMaxValue < MAX_VALUE / 2 )
			{
				m_dMaxValue *= 2;
				m_dAmp *= 2;
				// С��0.5vʱת��Ϊmv��ʾ
				if ( m_dAmp < 0.5 )
				{
					m_bMv = TRUE;
					// һ����Ĵ�С(mv)
					nGap = m_dAmp * 1000 / (NUM_VERT/2);
					nGap = FindNearValue( nGap );
					// �µ����ֵ
					m_dMaxValue = nGap * (NUM_VERT/2) * m_dMaxValue / (m_dAmp * 1000);
					m_dAmp = nGap * (NUM_VERT/2) * 1.0 / 1000;
					// ��������ֵ
					for ( i = 0; i < NUM_VERT+1; i++ )
					{
						strScale[i].Format( "%d", nGap * (4-i) );
					}
				}
				else
				{
					m_bMv = FALSE;
					// ��������ֵ
					for ( i = 0; i < NUM_VERT+1; i++ )
					{
						strScale[i].Format( "%.2f", m_dAmp / (NUM_VERT/2) * (4-i) );
					}
				}
			}
			// ���򣬻ָ�
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

	// �ҵ������
	CMainFrame* pFrame = NULL;
	pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);
	if ( pFrame != NULL )
	{
		// ˮƽ�Ŵ�
		if ( pFrame->m_bZoomH )
		{
			m_nDot = m_nDot / 2;
			if ( m_nDot < 40 )
			{
				m_nDot = 40;
			}
		}
		// ��ֱ�Ŵ�
		if ( pFrame->m_bZoomV )
		{
			//if ( m_dMaxValue > 2 )
			// ��С�̶�Ϊ1mv, 4����Ϊ4mv��С��8mvʱ�����ٷŴ�
			if ( m_dAmp > 0.007 )
			{
				m_dMaxValue /= 2;
				m_dAmp /= 2;
				// С��0.5vʱת��Ϊmv��ʾ
				if ( m_dAmp < 0.5 )
				{
					m_bMv = TRUE;
					// һ����Ĵ�С(mv)
					nGap = m_dAmp * 1000 / (NUM_VERT/2);
					nGap = FindNearValue( nGap );
					// �µ����ֵ
					m_dMaxValue = nGap * (NUM_VERT/2) * m_dMaxValue / (m_dAmp * 1000);
					m_dAmp = nGap * (NUM_VERT/2) * 1.0 / 1000;
					// ��������ֵ
					for ( i = 0; i < NUM_VERT+1; i++ )
					{
						strScale[i].Format( "%d", nGap * (4-i) );
					}
				}
				else
				{
					m_bMv = FALSE;
					// ��������ֵ
					for ( i = 0; i < NUM_VERT+1; i++ )
					{
						strScale[i].Format( "%.2f", m_dAmp / (NUM_VERT/2) * (4-i) );
					}
				}
			}
			// ���ܷŴ�ʱ���ָ�
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
	// ��������ֵ
	for ( int i = 0; i < NUM_VERT+1; i++ )
	{
		strScale[i].Format( "%.2f", m_dAmp / (NUM_VERT/2) * (4-i) );
	}
	DrawData();
}

void CDataDisp::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	// �ҵ������
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

	// ���Ҵ�Լ�ķ�Χ
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