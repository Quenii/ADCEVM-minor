/*
* 
* FileVersionInfo.h: interface for the CFileVersionInfo class.
* 
* This class is intended to retrieve the version infomation
* of the specified file.
*
*
* Copyright(c) 2009 北京国科环宇空间技术有限公司
* website: http://www.gkhy.com.cn
*
*
* Author(S):
*   Liu Peng<liupengee@126.com>
* 
*   Naren Neelamegam<loveablevirus@yahoo.com>
*   Web : http://www.narenn.com/
*   Main parts of the code snippets are copied and modified from
*   Neelamegam's codeproject(www.codeproject.com) article "Changing 
*   Windows XP's Bootskin, Windows File Protection, and Themes
*   programmatically".
*
*
* Created: Jan 19, 2009
*
*/

#if !defined(AFX_FILEVERSIONINFO_H__36DB81E9_6A97_41B1_A586_DD51E7D59E72__INCLUDED_)
#define AFX_FILEVERSIONINFO_H__36DB81E9_6A97_41B1_A586_DD51E7D59E72__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace gkhy
{

	namespace mfcplus
	{

		class AFX_EXT_CLASS CFileVersionInfo  
		{

		public:
			enum VerInfoString
			{
				VerInfoString_Comments,
				VerInfoString_InternalName,
				VerInfoString_ProductName,
				VerInfoString_CompanyName,
				VerInfoString_LegalCopyright,
				VerInfoString_ProductVersion,		
				VerInfoString_FileDescription,
				VerInfoString_LegalTrademarks,
				VerInfoString_PrivateBuild, 
				VerInfoString_FileVersion,
				VerInfoString_OriginalFilename,
				VerInfoString_SpecialBuild 		
			};

		public:
			CFileVersionInfo();
			virtual ~CFileVersionInfo();

		public:

			/**
			* GetInfoStr - Retrieve the ProductName + FileVersion
			* 
			* @param file - Pointer to a null-terminated string that 
			* specifies the name of the file of interest. NULL for current
			* process module.
			* 
			* @return TRUE is succeeded, or else FALSE.
			*/
			virtual	BOOL GetInfoStr(CString& str, VerInfoString info, const TCHAR* file = NULL);	

			/**
			* GetInfoNum - Retrieve the version number.
			*
			* @return TRUE is succeeded, or else FALSE.
			*/
			virtual BOOL GetInfoNum(DWORD &dwMajor, DWORD &dwMinor,
				DWORD &dwSubMinor, DWORD &dwBuild, const TCHAR* file = NULL);

		private:
			void Enum2Str(CString& infoStr, VerInfoString infoEnum);
		};
	};

};


#endif // !defined(AFX_FILEVERSIONINFO_H__36DB81E9_6A97_41B1_A586_DD51E7D59E72__INCLUDED_)
