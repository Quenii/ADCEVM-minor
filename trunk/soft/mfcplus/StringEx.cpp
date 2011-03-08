#include "StdAfx.h"
#include "gkhy\mfcplus\StringEx.hpp"
#include <AtlBase.h>
#include <AtlConv.h >
#include <cmath>
using namespace std;

using namespace gkhy::mfcplus;

CStringEx::CStringEx(void)
{
}

CStringEx::~CStringEx(void)
{
}

void CStringEx::IntToHex(UINT n32)
{
	Format(_T("%08X"), n32);
}

int CStringEx::HexToInt()
{
	int i;
	i = _tcstol(GetBuffer(), NULL, 16);
	ReleaseBuffer();
	return i;
};

int CStringEx::ToInt()
{
	int i;		
	i = _tcstol(GetBuffer(), NULL, 10);
	ReleaseBuffer();
	return i;
}

// void CStringEx::Int64ToSeperatedDec(INT64 i64)
// {
// 	Format(_T("%I64i"), i64);
// 	int nLen = GetLength();
// 	for (int i = nLen - 3; i > 0; i -= 3)
// 	{
// 		Insert(i, _T(","));
// 	}
// }
// 
// void CStringEx::UINTToSeperatedDec(UINT i32)
// {
// 	Format(_T("%I32i"), i32);
// 	int nLen = GetLength();
// 	for (int i = nLen - 3; i > 0; i -= 3)
// 	{
// 		Insert(i, _T(","));
// 	}
// }

void CStringEx::ToSeperatedDec(INT64 i64)
{
	Format(_T("%I64i"), i64);
	int nLen = GetLength();
	for (int i = nLen - 3; i > 0; i -= 3)
	{
		Insert(i, _T(","));
	}
}

void CStringEx::ToSeperatedDec(UINT64 u64)
{
	Format(_T("%I64u"), u64); // sprintf format string ...
	int nLen = GetLength();
	for (int i = nLen - 3; i > 0; i -= 3)
	{
		Insert(i, _T(","));
	}
}

void CStringEx::ToSeperatedDec(UINT u32)
{
	Format(_T("%u"), u32);
	int nLen = GetLength();
	for (int i = nLen - 3; i > 0; i -= 3)
	{
		Insert(i, _T(","));
	}
}

void CStringEx::ToSeperatedDec(INT i32)
{
	Format(_T("%i"), i32);
	int nLen = GetLength();
	for (int i = nLen - 3; i > 0; i -= 3)
	{
		Insert(i, _T(","));
	}
}

std::string CStringEx::ToAnsi()
{
	USES_CONVERSION;
	return std::string(T2A(*this));
}

void CStringEx::FromAnsi(const char* szStr)
{
	USES_CONVERSION;
	*this = A2T(szStr);
}