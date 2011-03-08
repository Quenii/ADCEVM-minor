#pragma once

#include "gkhy/mfcplus/mfcplus_global.hpp"

namespace gkhy
{
	namespace mfcplus
	{
		class AFX_EXT_CLASS CTextProgressCtrl : public CProgressCtrl
		{
		public:
			enum Direction
			{
				DIR_LTOR = 0x00000001,
				DIR_RTOL = 0x00000002,
				DIR_TTOB = 0x00000004,
				DIR_BTOT = 0x00000008
			};

			// Construction
		public:
			CTextProgressCtrl();
			virtual ~CTextProgressCtrl();

		protected:
			// Generated message map functions
			//{{AFX_MSG(CTextProgressCtrl)
			afx_msg BOOL OnEraseBkgnd(CDC* pDC);
			afx_msg void OnPaint();
			afx_msg void OnSize(UINT nType, int cx, int cy);
			afx_msg LRESULT OnSetText(WPARAM wParam, LPARAM lParam);
			afx_msg LRESULT OnGetText(WPARAM wParam, LPARAM lParam);
			//}}AFX_MSG
			DECLARE_MESSAGE_MAP()

			// Operations
		public:
			int            SetPos(int nPos);
			int            StepIt();
			void        SetRange(int nLower, int nUpper);
			int            OffsetPos(int nPos);
			int            SetStep(int nStep);
			void        SetForeColour(COLORREF col);
			void        SetBkColour(COLORREF col);
			void        SetTextForeColour(COLORREF col);
			void        SetTextBkColour(COLORREF col);
			COLORREF    GetForeColour();
			COLORREF    GetBkColour();
			COLORREF    GetTextForeColour();
			COLORREF    GetTextBkColour();
			void        SetShowText(BOOL bShow);
			void		SetDirection(Direction dir);

		private:
			int         m_nPos, m_nStepSize, m_nMax, m_nMin;
			CString     m_strText;
			BOOL        m_bShowText;
			int         m_nBarWidth;
			COLORREF    m_colFore, m_colBk,	m_colTextFore,	m_colTextBk,m_colBoarder;
			Direction m_Direction;
		};
	};
};
