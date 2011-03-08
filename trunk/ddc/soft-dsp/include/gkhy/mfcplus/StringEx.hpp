
#pragma once
#include <string>

namespace gkhy 
{
	namespace mfcplus
	{
		class AFX_EXT_CLASS CStringEx : public CString
		{
		public:
			CStringEx(void); 
			CStringEx(CString& str) : CString(str) { }
			CStringEx(LPCTSTR str) : CString(str) { }
			CStringEx(const char* szStr) { FromAnsi(szStr); }
			virtual ~CStringEx(void);

		public:
			void IntToHex(UINT n32);
			int HexToInt(void);

			// 	void Int64ToSeperatedDec(INT64 i64);
			// 	void UINTToSeperatedDec(UINT i32);
			void ToSeperatedDec(INT64 i64);
			void ToSeperatedDec(UINT64 u64);
			
			void ToSeperatedDec(UINT u32);
			void ToSeperatedDec(INT i32);
			int ToInt(void);		
			std::string ToAnsi();	
			void FromAnsi(const char* szStr);
		};
	}
}

