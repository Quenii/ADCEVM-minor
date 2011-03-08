// This file was created on Oct 8, 2008 by sif
// I created this Class to be able change the Color of your static text box
//
// There are two functions available Currently:
// SetBkColor(COLORREF crColor)
// SetTextColor(COLORREF crColor)
//
// How To Use:
// Add two files to your project
// ColorStatic.cpp, ColorStatic.h
//
// Add #include "ColorStatic.h" to your Dialogs Header file.
// Declare an instance of CColorStatic for each static text box being modified.
// Ex. CColorStatic m_stcName;
//
// In your OnInitDialog() initialize your color for each box 
// unless you want the default.
// Ex. m_stcName.SetTextColor( RGB(255,0,0) );

// ColorStatic.cpp : implementation file
//

#include "stdafx.h"
#include "ColorStatic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorStatic

CColorStatic::CColorStatic()
{
	m_crBkColor = ::GetSysColor(COLOR_3DFACE);
	m_crTextColor = RGB(  0,  0,  0);
	m_brBkgnd.CreateSolidBrush(m_crBkColor); 
}

CColorStatic::~CColorStatic()
{
}


BEGIN_MESSAGE_MAP(CColorStatic, CStatic)
	//{{AFX_MSG_MAP(CColorStatic)	
	ON_WM_CTLCOLOR_REFLECT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorStatic message handlers

void CColorStatic::SetBkColor(COLORREF crColor)
{
	m_crBkColor = crColor;
	m_brBkgnd.DeleteObject();
	m_brBkgnd.CreateSolidBrush(crColor);
	RedrawWindow();
}

void CColorStatic::SetTextColor(COLORREF crColor)
{
	m_crTextColor = crColor;
	RedrawWindow();
}

HBRUSH CColorStatic::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	// TODO: Change any attributes of the DC here
	HBRUSH hbr;
	hbr = (HBRUSH)m_brBkgnd; // Passing a Handle to the Brush
	pDC->SetBkColor(m_crBkColor); // Setting the Color of the Text Background to the one passed by the Dialog
	pDC->SetTextColor(m_crTextColor); // Setting the Text Color to the one Passed by the Dialog

	if (nCtlColor)       // To get rid of compiler warning
      nCtlColor += 0;

	return hbr;

	// TODO: Return a non-NULL brush if the parent's handler should not be called
	//return NULL;
}
