#pragma once


// CLabelEx


namespace gkhy 
{
	namespace mfcplus
	{
		class AFX_EXT_CLASS CLabelEx : public CStatic
		{
			DECLARE_DYNAMIC(CLabelEx)

		public:
			CLabelEx();
			virtual ~CLabelEx();

		protected:
			afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
			DECLARE_MESSAGE_MAP()

		public:
			void SetBkColor(COLORREF color);

		private:
			COLORREF m_BkColor;
			CBrush   m_BkBrush;      

		};
	};
};


