// AdcTestPlat.h : main header file for the ADCTESTPLAT application
//

#if !defined(AFX_ADCTESTPLAT_H__0C346E59_89DF_40B7_8D2E_230B21BEC522__INCLUDED_)
#define AFX_ADCTESTPLAT_H__0C346E59_89DF_40B7_8D2E_230B21BEC522__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CAdcTestPlatApp:
// See AdcTestPlat.cpp for the implementation of this class
//



class CAdcTestPlatApp : public CWinApp
{
public:
	HANDLE m_hDevice;
	BOOL DetectedCards( void );
	CAdcTestPlatApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAdcTestPlatApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CAdcTestPlatApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADCTESTPLAT_H__0C346E59_89DF_40B7_8D2E_230B21BEC522__INCLUDED_)
