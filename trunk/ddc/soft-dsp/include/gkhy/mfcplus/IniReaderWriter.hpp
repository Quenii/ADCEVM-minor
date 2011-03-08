//////////////////////////////////////////////////////////////////////////
// CIniReader & CIniWriter - Twin classes for INI file read and write.
//
// Author: Liu Peng
// Email:  liupengee@126.com
// Copyright (c) 2009, GKHY Co., Ltd
//
// You may freely use or modify this code provided this
// Copyright is included in all derived versions.
//
// Created : 8/22/09 Liu Peng               
//
// The code is copied from the codeproject(http://www.codeproject.com) article:
//          A Small Class to Read INI File By xiaohe521
//
//
//  int main(int argc, char * argv[])
//  {
//  	CIniWriter iniWriter(".\\Logger.ini");
//  	iniWriter.WriteString("Setting", "Name", "jianxx");   
//  	iniWriter.WriteInteger("Setting", "Age", 27); 
//  	iniWriter.WriteFloat("Setting", "Height", 1.82f); 
//  	iniWriter.WriteBoolean("Setting", "Marriage", false);  
//  	CIniReader iniReader(".\\Logger.ini");
//  	char *szName = iniReader.ReadString("Setting", "Name", "");   
//  	int iAge = iniReader.ReadInteger("Setting", "Age", 25); 
//  	float fltHieght = iniReader.ReadFloat("Setting", "Height", 1.80f); 
//  	bool bMarriage = iniReader.ReadBoolean("Setting", "Marriage", true); 
//  
//  	std::cout<<"Name:"<<szName<<std::endl
//  		<<"Age:"<<iAge<<std::endl 
//  		<<"Height:"<<fltHieght<<std::endl 
//  		<<"Marriage:"<<bMarriage<<std::endl; 
//  	delete szName;  
//  	return 1;   
//  }
//////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>
namespace gkhy 
{
	namespace mfcplus
	{
		class AFX_EXT_CLASS CIniReader
		{
		public:
			CIniReader(const char* szFileName); 
			int ReadInteger(char* szSection, char* szKey, int iDefaultValue);
			float ReadFloat(char* szSection, char* szKey, float fltDefaultValue);
			bool ReadBoolean(char* szSection, char* szKey, bool bolDefaultValue);
			std::string ReadString(char* szSection, char* szKey, const char* szDefaultValue);
		private:
			char m_szFileName[255];
		};

		class AFX_EXT_CLASS CIniWriter
		{
		public:
			CIniWriter(const char* szFileName); 
			void WriteInteger(char* szSection, char* szKey, int iValue);
			void WriteFloat(char* szSection, char* szKey, float fltValue);
			void WriteBoolean(char* szSection, char* szKey, bool bolValue);
			void WriteString(char* szSection, char* szKey, char* szValue);
		private:
			char m_szFileName[255];
		};
	}
}

