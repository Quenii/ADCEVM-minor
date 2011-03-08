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
// Created : Feb 9, 2010 Liu Peng
//
// 
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "gkhy/mfcminus/mfcminus_global.hpp"

class DataScanCore;

namespace gkhy
{
	namespace MfcMinus
	{			
		class MFCMINUS_API DataScan
		{
		public:
			enum Mode 
			{
				CUL32, // counter-up, little-endian, 32-bit
				CUL32_1279Pack_CUB32, // 1acffc1d, 3-byte counter, cub32
			};

		public:		
			DataScan(Mode mode, int bufferSize = 256 * 1024 * 1024);
			virtual ~DataScan();		
		public:			
			void write(const char* buf, int len);
			void start();
			void stop();

		private:			
			DataScanCore* m_p;
		};
	}
}

