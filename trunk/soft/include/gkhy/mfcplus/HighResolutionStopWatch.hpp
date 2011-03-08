#pragma once

/////////////////////////////////////////////////////////
// HighResolutionStopWatch - A High Resolution Stopwatch
//
// Author: Liu Peng
// Email:  liupengee@126.com
// Copyright (c) 2008-2009, GKHY
//
// You may freely use or modify this code provided this
// Copyright is included in all derived versions.
//
// Created : 8/22/09 Liu Peng
//                
//
// This class implements a high resolution stopwatch.
//
// Sample code:
// =============
// 
//  int main()
//  {
//		HighResolutionStopWatch stopWatch;
//		stopWatch.start();
//      	
//		stopWatch.stop();
//		stopWatch.getTime_us(); // get us elapsed.
//		return 0;
//	}
// 
///////////////////////////////////////////////////////////


namespace gkhy
{
	namespace mfcplus
	{

		class AFX_EXT_CLASS HighResolutionStopWatch
		{
		public:
			HighResolutionStopWatch()
			{
				BOOL okay = QueryPerformanceFrequency(&m_freq);
				ASSERT(okay);
			}
			virtual ~HighResolutionStopWatch()
			{

			}

		public:
			bool start()
			{
				BOOL okay = QueryPerformanceCounter(&m_start);
				return okay ? true : false;
			}

			bool stop()
			{
				BOOL okay = QueryPerformanceCounter(&m_stop);		
				return okay ? true : false;
			}

			int getTime_us()
			{
				return int(1000 * 1000 * (m_stop.QuadPart - m_start.QuadPart) / m_freq.QuadPart);
			}

			int getTime_ms()
			{
				return int(1000 * (m_stop.QuadPart - m_start.QuadPart) / m_freq.QuadPart);
			}
			int getTime_s()
			{
				return int((m_stop.QuadPart - m_start.QuadPart) / m_freq.QuadPart);
			}

		private:
			LARGE_INTEGER m_start;
			LARGE_INTEGER m_stop;
			LARGE_INTEGER m_freq;
			int m_timer;
		};
	}
}
