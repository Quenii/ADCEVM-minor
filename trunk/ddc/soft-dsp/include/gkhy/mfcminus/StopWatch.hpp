//////////////////////////////////////////////////////////////////////////
// StopWatch - a Stop Watch
//
// Author: Liu Peng
// Email:  liupengee@126.com
// Copyright(c)2010, GKHY
//
// You may freely use or modify this code provided this
// Copyright is included in all derived versions.
//
// Created : Jan 20, 2010 Liu Peng
//
// 
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "gkhy/mfcminus/mfcminus_global.hpp"

namespace gkhy
{
	namespace MfcMinus
	{	
		
		class MFCMINUS_API StopWatch
		{
		public:		
			StopWatch() { reset(); }
			virtual ~StopWatch(void) { }

		private:
			StopWatch(StopWatch&);
			StopWatch& operator=(const StopWatch &);

		public:						
			void reset();			
			unsigned int getTime_ms();			
			unsigned int getTime_s() { return (getTime_ms() + 999) / 1000; }	

		private:
			unsigned int m_start;
		};
	}
}

