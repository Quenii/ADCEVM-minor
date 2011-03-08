//////////////////////////////////////////////////////////////////////////
// DiskManager - 
//
// Author: Liu Peng
// Email:  liupengee@126.com
// Copyright (c) 2010, GKHY
//
// You may freely use or modify this code provided this
// Copyright is included in all derived versions.
//
// Created : Feb 25, 2010 Liu Peng
//
//
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "gkhy/mfcminus/mfcminus_global.hpp"
#include <string>
#include <list>

namespace gkhy
{
	namespace MfcMinus
	{			
		class MFCMINUS_API DiskManager
		{	
		public:
			DiskManager() { }
			virtual ~DiskManager() {}
		
		public:
			static bool getFreeSpace(
				const char* dir,
				long long* pFreeBytesAvailable,
				long long* pTotalNumberOfBytes = 0,
				long long* pTotalNumberOfFreeBytes = 0);			
 		};

		class MFCMINUS_API Dir 
		{
		public:
			Dir(const std::string dir)
			{
				m_dir = dir;
			}

			std::string pathAppend(const std::string& more);

			long long freeBytesAvailable()
			{
				long long val;
				DiskManager::getFreeSpace(m_dir.c_str(), &val);
				return val;
			}

			long long bytesOfOccupation();

			/*long long totalNumberOfBytes()
			{
				long long val;
				DiskManager::getFreeSpace(m_dir.c_str(), 0, &val);
				return val;
			}*/

			// subdirectories only, excluding . and ..
			void subDirs(std::list<std::string>& ref, const std::string& wildCard = "*");

			// subdirectories and files, excluding . and ..
			void subItems(std::list<std::string>& ref, const std::string& wildCard = "*");
			
		private:
			std::string m_dir;
		};
	}
}