#if !defined(AFX_COLORSTATIC_H__6C8D6ED7_CB5D_4506_83F7_D4113F8200F2__INCLUDED_)
#define AFX_COLORSTATIC_H__6C8D6ED7_CB5D_4506_83F7_D4113F8200F2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColorStatic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CColorStatic window

class CColorStatic : public CStatic
{
// Construction
public:
	CColorStatic();

// Attributes
public:
	CBrush m_brBkgnd;
	COLORREF m_crBkColor;
	COLORREF m_crTextColor;

// Operations
public:
	void SetBkColor(COLORREF crColor); 
	void SetTextColor(COLORREF crColor);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorStatic)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CColorStatic();

	// Generated message map functions
protected:
	//{{AFX_MSG(CColorStatic)	
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORSTATIC_H__6C8D6ED7_CB5D_4506_83F7_D4113F8200F2__INCLUDED_)
