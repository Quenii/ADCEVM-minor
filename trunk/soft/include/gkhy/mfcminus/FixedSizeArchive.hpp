//////////////////////////////////////////////////////////////////////////
// DataScan 
//
// Author: Liu Peng
// Email:  liupengee@126.com
// Copyright(c)2010, GKHY
//
// You may freely use or modify this code provided this
// Copyright is included in all derived versions.
//
// Created : Feb 22, 2010 Liu Peng
//
// 
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "gkhy/mfcminus/mfcminus_global.hpp"
#include <string>

namespace gkhy
{
	namespace MfcMinus
	{			
		class FastFileWriter;

		class MFCMINUS_API FixedSizeArchive
		{
		public:
			FixedSizeArchive();
			virtual ~FixedSizeArchive();

		private:
			FixedSizeArchive(const FixedSizeArchive&);
			FixedSizeArchive& operator=(const FixedSizeArchive&);
		
		public:
			bool isOpen() { return m_bOpen; }
			bool open(const char* fileName, long long fileSize);
			bool write(const char* buf, int len);
			bool close();	
			long long size() { return m_archiveSize; }			

		private:
			FastFileWriter* createwriter();

		private:
			bool m_bOpen;
			FastFileWriter* m_pwriter;
			int m_seed;
			std::string m_fileName;
			long long m_fileSize;
			long long m_archiveSize;
		};
	}
}

