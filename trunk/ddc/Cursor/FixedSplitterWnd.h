#pragma once
#include "afxext.h"

class CFixedSplitterWnd : public CSplitterWnd
{
public:
	CFixedSplitterWnd(void);
public:
	~CFixedSplitterWnd(void);
public:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
