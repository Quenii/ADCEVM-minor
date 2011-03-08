// LabelEx.cpp : implementation file
//

#include "stdafx.h"
#include "gkhy\mfcplus\LabelEx.hpp"

using namespace gkhy::mfcplus;
// CLabelEx

IMPLEMENT_DYNAMIC(CLabelEx, CStatic)

CLabelEx::CLabelEx()
{
	 m_BkColor = RGB(0, 255, 0);     
	 m_BkBrush.CreateSolidBrush(m_BkColor);
}

CLabelEx::~CLabelEx()
{
	m_BkBrush.DeleteObject();
}


BEGIN_MESSAGE_MAP(CLabelEx, CStatic)
	ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()



// CLabelEx message handlers

void CLabelEx::SetBkColor(COLORREF color)
{
	m_BkColor = color;
	m_BkBrush.DeleteObject();
	m_BkBrush.CreateSolidBrush(m_BkColor);
	RedrawWindow();
}
HBRUSH CLabelEx::CtlColor(CDC* pDC, UINT nCtlColor)
{
	// TODO:  Change any attributes of the DC here
	pDC->SetBkColor(m_BkColor);

	// TODO:  Return a non-NULL brush if the parent's handler should not be called
	//	return NULL;
	return (HBRUSH)m_BkBrush.GetSafeHandle();
}
