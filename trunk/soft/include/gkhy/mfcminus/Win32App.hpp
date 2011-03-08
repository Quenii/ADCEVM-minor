//////////////////////////////////////////////////////////////////////////
// Win32App - 
//
// Author: Liu Peng
// Email:  liupengee@126.com
// Copyright (c) 2010, GKHY
//
// You may freely use or modify this code provided this
// Copyright is included in all derived versions.
//
// Created : Feb 27, 2010 Liu Peng
//
//
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "gkhy/mfcminus/mfcminus_global.hpp"
#include <string>
#include <vector>

#pragma warning(disable: 4251)

namespace gkhy
{
	namespace MfcMinus
	{				
		class MFCMINUS_API Win32App
		{			
		public:
			Win32App(const std::vector<std::string>& args);
			virtual ~Win32App();
			
		public:
			static unsigned int exec();
			static Win32App* instance();

			static std::string appName();
			static void setAppName(const std::string & appName);		
			
			static std::string filePath();					
			static std::string dirPath();	

			static void sleep(int mSec);
			static void args(int& argc, char**& argv);
			static const std::vector< std::string >& args();

			static bool setPriorityClass(unsigned int priorityClass);

		protected:
			virtual unsigned int exec(const std::vector< std::string >& args);	
			
		private:
			static Win32App* m_instance;
			std::vector< std::string > m_args;
			int m_argc;
			char** m_argv;

			std::string m_appName;
 		};
	}
}