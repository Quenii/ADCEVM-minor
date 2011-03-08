/*
 *
 * FileVersionInfo.cpp: implementation of the CFileVersionInfo class.
 *
 *
 * Copyright(c) 2009 北京国科环宇空间技术有限公司
 * website: http://www.gkhy.com.cn
 *
 * Author(S):
 *   Liu Peng<liupengee@126.com>
 *
 *
 * Created: Jan 19, 2009 
 *
 */

#include "stdafx.h"
#include "gkhy\mfcplus\FileVersionInfo.hpp"
#include <vector>

#pragma comment(lib, "Version.lib")

using namespace std;
using namespace gkhy::mfcplus;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CFileVersionInfo::CFileVersionInfo()
{

}

CFileVersionInfo::~CFileVersionInfo()
{

}

void CFileVersionInfo::Enum2Str(CString& infoStr, VerInfoString infoEnum)
{
	switch (infoEnum)
	{
	case VerInfoString_Comments:
		infoStr = _T("Comments");
		break;

	case VerInfoString_InternalName:
		infoStr = _T("InternalName");
		break;
	case VerInfoString_ProductName:
		infoStr = _T("ProductName");
		break;
	case VerInfoString_CompanyName:
		infoStr = _T("CompanyName");
		break;
	case VerInfoString_LegalCopyright:
		infoStr = _T("LegalCopyright");
		break;
	case VerInfoString_ProductVersion:
		infoStr = _T("ProductVersion");
		break;
	case VerInfoString_FileDescription:
		infoStr = _T("FileDescription");
		break;

	case VerInfoString_LegalTrademarks:
		infoStr = _T("LegalTrademarks");
		break;
	case VerInfoString_PrivateBuild:
		infoStr = _T("PrivateBuild");
		break;
	case VerInfoString_FileVersion:
		infoStr = _T("FileVersion");
		break;
	case VerInfoString_OriginalFilename:
		infoStr = _T("OriginalFilename");
		break;

	case VerInfoString_SpecialBuild:
		infoStr = _T("SpecialBuild");
		break;	
		 		
	default:
		break;
	}
}

BOOL CFileVersionInfo::GetInfoStr(CString& str, VerInfoString info, const TCHAR* file)
{
	TCHAR szName[MAX_PATH+1];
	memset(szName, '\0', sizeof(szName));

	if (!file) 
	{
		if (!GetModuleFileName(NULL,szName,MAX_PATH))
			return FALSE;		
	}
	else
	{
		_tcscpy_s(szName, _countof(szName), file);				
	}
	
	CString strInfo(_T(""));
	TCHAR* pstrVerInfo = NULL;
	DWORD VerInfoLen, imsi;
	UINT imsi2;
	LPVOID pstrInfo;
	if (! (VerInfoLen = GetFileVersionInfoSize( szName, &imsi )))
		return FALSE;
	
	vector<TCHAR> _pstrVerInfo(VerInfoLen);
	pstrVerInfo = &_pstrVerInfo[0]; // new TCHAR[VerInfoLen];
	
	if(! GetFileVersionInfo(szName, (DWORD )0, VerInfoLen,(LPVOID )pstrVerInfo ) )
		return FALSE;


	/* get lang-codepage string */
//	HRESULT hr;	
	struct LANGANDCODEPAGE {
		WORD wLanguage;
		WORD wCodePage;
	} *lpTranslate;

	UINT cbTranslate;
	
	// Read the list of languages and code pages.	
	if (! VerQueryValue(pstrVerInfo, TEXT("\\VarFileInfo\\Translation"), 
		(LPVOID*)&lpTranslate, &cbTranslate))
		return FALSE;
	if ( cbTranslate/sizeof(struct LANGANDCODEPAGE) < 1)
		return FALSE;
	
	TCHAR szPath[MAX_PATH];
	CString _infoStr;
	Enum2Str(_infoStr, info);
	//_stprintf(szPath,_T("\\StringFileInfo\\040904e4\\%s"), _infoStr);	
	_stprintf_s(szPath, _countof(szPath),  _T("\\StringFileInfo\\%04x%04x\\%s"), 
		lpTranslate[0].wLanguage, lpTranslate[0].wCodePage,	LPCTSTR(_infoStr));	
	if( ! VerQueryValue( pstrVerInfo, szPath, (LPVOID*)&pstrInfo, &imsi2 ) )
		return FALSE;
	
	strInfo = (TCHAR*)pstrInfo;
	
	//delete pstrVerInfo;
	pstrVerInfo = NULL;
	str = strInfo;
	
	return TRUE;
}

BOOL CFileVersionInfo::GetInfoNum(DWORD &dwMajor, DWORD &dwMinor,
	DWORD &dwSubMinor, DWORD &dwBuild, const TCHAR* file)
{
	TCHAR lpszFilePath[MAX_PATH+1];
	memset(lpszFilePath, '\0', sizeof(lpszFilePath));
	
	if (!file) 
	{
		if (!GetModuleFileName(NULL,lpszFilePath,MAX_PATH))
			return FALSE;		
	}
	else
	{
		_tcscpy_s(lpszFilePath, _countof(lpszFilePath),  file);		
	}

	DWORD dwDummy;
	bool bResult=false;
	DWORD dwFVISize = GetFileVersionInfoSize( lpszFilePath , &dwDummy ); 
	vector<BYTE> versionInfo(dwFVISize); //LPBYTE lpVersionInfo = new BYTE[dwFVISize]; 
	VS_FIXEDFILEINFO *lpFfi;
	bResult=GetFileVersionInfo( lpszFilePath , 0 , dwFVISize , 
		/*lpVersionInfo*/ &versionInfo[0] )?true:false; 
	if(!bResult){/* delete []lpVersionInfo;*/ return false;}
	UINT uLen; 
	bResult=VerQueryValue(/*lpVersionInfo*/ &versionInfo[0] , _T("\\") , 
		(LPVOID *)&lpFfi , &uLen )?true:false; 
	DWORD dwFileVersionMS = lpFfi->dwFileVersionMS; 
	DWORD dwFileVersionLS = lpFfi->dwFileVersionLS; 
	//delete [] lpVersionInfo; 
	dwMajor=HIWORD(dwFileVersionMS);
	dwMinor=LOWORD(dwFileVersionMS);
	dwSubMinor=HIWORD(dwFileVersionLS);
	dwBuild=LOWORD(dwFileVersionLS);
	return bResult;
}
