//////////////////////////////////////////////////////////////////////////
// AsyncHugeRingBuffer - Asynchronous Huge Ring Buffer
//
// Author: Liu Peng
// Email:  liupengee@126.com
// Copyright 2008-2009, GKHY
//
// You may freely use or modify this code provided this
// Copyright is included in all derived versions.
//
// Created : 22/12/09 Liu Peng
//
// AsyncHugeRingBuffer is built upon the HugeRingBuffer which is designed
// for use in single threaded context.
// 
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "gkhy/mfcminus/mfcminus_global.hpp"
#include "gkhy/mfcminus/HugeRingBuffer.hpp"

namespace gkhy
{
	namespace MfcMinus
	{
		class MFCMINUS_API AsyncHugeRingBuffer
		{
		public:		
			AsyncHugeRingBuffer(int blockSize /*= 16 * 1024 * 1024*/) : buffer(blockSize)
			{
			}
			virtual ~AsyncHugeRingBuffer(void){}

		private:
			AsyncHugeRingBuffer(AsyncHugeRingBuffer&);
			AsyncHugeRingBuffer& operator=(const AsyncHugeRingBuffer &);

		public:			
			// do not call this when buffer is being accessed.
			void syncResize(int newSize)
			{
				HugeRingBufferLocker lock(&buffer);
				buffer.resize(newSize);
			}
			// do not call this when buffer is being accessed.
			void syncClear()
			{
				HugeRingBufferLocker lock(&buffer);
				buffer.clear();
			}
			int size()
			{
				HugeRingBufferLocker lock(&buffer);
				return buffer.size();
			}
		
			int totalWritableSize() 
			{
				HugeRingBufferLocker lock(&buffer);
				return buffer.totalWritableSize();
			}

			int nextWriteBlockSize() 
			{
				HugeRingBufferLocker lock(&buffer);
				return buffer.nextWriteBlockSize();
			}

			char* nextWriteBlock()
			{
				HugeRingBufferLocker lock(&buffer);
				return buffer.nextWriteBlock();
			}

			int commit(int len)
			{
				HugeRingBufferLocker lock(&buffer);
				return buffer.commit(len);
			}

			// return could be less than maxLen if fifo full.
			int write(const char* data, int maxLen)
			{
				HugeRingBufferLocker lock(&buffer);
				return buffer.write(data, maxLen);
			}
			
			int count() 
			{
				HugeRingBufferLocker lock(&buffer);
				return buffer.count();
			}

			int peakCount() 
			{
				HugeRingBufferLocker lock(&buffer);
				return buffer.peakCount();

			}

			int nextReadBlockSize()
			{
				HugeRingBufferLocker lock(&buffer);
				return buffer.nextReadBlockSize();
			}

			char* nextReadBlock()
			{
				HugeRingBufferLocker lock(&buffer);
				return buffer.nextReadBlock();
			}

			int chop(int len)
			{
				HugeRingBufferLocker lock(&buffer);
				return buffer.chop(len);
			}

			int read(char* data, int maxLen)
			{
				HugeRingBufferLocker lock(&buffer);
				return buffer.read(data, maxLen);
			}						

		private:		
			HugeRingBuffer buffer;					
		};
	}
}

