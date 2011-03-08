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

#define IMPLEMENT_FastFileWriter

#ifdef IMPLEMENT_FastFileWriter

class FastFilewriterPrivate;

namespace gkhy
{
	namespace MfcMinus
	{			
		class MFCMINUS_API FastFileWriter
		{
		public:
			FastFileWriter();
			virtual ~FastFileWriter();

		private:
			FastFileWriter(const FastFileWriter&);
			FastFileWriter& operator = (const FastFileWriter&);

		public:		
			bool isOpen();
			bool open(const char* fileName);
			bool write(const char* buf, int len);
			bool close();
			long long size() { return m_size; }		

		private:
			FastFilewriterPrivate& m_p;		
			long long m_size;
		};
	}
}

#else

#include <fstream>

namespace gkhy
{
	namespace MfcMinus
	{	
		class MFCMINUS_API FastFileWriter
		{

		public:
			FastFileWriter() {}
			~FastFileWriter() {}

		public:
			bool open(const char* fileName)
			{
				m_size = 0;
				try
				{
					m_of.open(fileName);
				}
				catch(...)
				{
					return false;
				}

				return true;
			}
			bool write(const char* buf, int len)
			{
				try
				{
					m_of.write(buf, len);
				}
				catch(...)
				{
					return false;
				}

				m_size += len;

				return true;
			}
			bool close()
			{
				try
				{
					m_of.close();
				}
				catch (...)
				{
					return false;
				}

				return true;
			}

			long long size() { return m_size; }

		private:
			std::ofstream m_of;
			long long m_size;

		};
	}
}

#endif;