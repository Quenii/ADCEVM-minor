//////////////////////////////////////////////////////////////////////////
// HugeRingBuffer - Huge Ring Buffer
//
// Author: Liu Peng
// Email:  liupengee@126.com
// Copyright 2008-2009, GKHY
//
// You may freely use or modify this code provided this
// Copyright is included in all derived versions.
//
// Created : 21/12/09 Liu Peng
//
// Huge Ring Buffer is built upon the RingBuffer class, which is a 
// conventional circular FIFO. 
//
// - But why not just use RingBuffer?
// - RingBuffer allocates linear memory internally, there has been cases
// that an attempt to allocate huge memory(like 200 MiBytes) would fail
// sometimes or on some PC's. So hereby i write a HugeRingBuffer, which
// holds a list of much smaller RingBuffers internally. The interfaces of
// HugeRingBuffer are the same as RingBuffer.
// 
// 
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "gkhy/mfcminus/mfcminus_global.hpp"
#include "gkhy/mfcminus/RingBuffer.hpp"
#include <list>
#include <cassert>

class CCriticalSection;

namespace gkhy
{
	namespace MfcMinus
	{	
		class HugeRingBuffer;

		class MFCMINUS_API HugeRingBufferLocker
		{
		public:
			HugeRingBufferLocker(HugeRingBuffer* p);
			virtual ~HugeRingBufferLocker();

		private:
			HugeRingBuffer* buffer;

		};

		class MFCMINUS_API HugeRingBuffer
		{
		public:		
			HugeRingBuffer(int blockSize = 16 * 1024 * 1024);
			virtual ~HugeRingBuffer(void);
		
			/*template<class T>
			inline const T & Min ( const T & value1, const T & value2 ) { return (value1 < value2) ? value1 : value2; }
			*/
			
		private:
			HugeRingBuffer(HugeRingBuffer&);
			HugeRingBuffer& operator=(const HugeRingBuffer &);

		public:			
			void lock();
			void unlock();
			inline int size() const { return fifoSize; }
			void resize(int newSize);

			inline int totalWritableSize() const { return fifoSize - dataCount; }
			inline int nextWriteBlockSize() 
			{
				if (totalWritableSize() > 0 && 0 == fifoList[tail]->totalWritableSize())
						advanceHeadTailPtr(tail);				
						
				return fifoList[tail]->nextWriteBlockSize(); 
			}

			inline char* nextWriteBlock() {
				if (totalWritableSize() > 0 && 0 == fifoList[tail]->totalWritableSize())
					advanceHeadTailPtr(tail);				
					
				return fifoList[tail]->nextWriteBlock(); 
			}

			int commit(int len);
			// reture could be less than maxLen if fifo full.
			int write(const char* data, int maxLen);
			
			inline int count() const { return dataCount; }
			inline int peakCount() const { return peakDataCount; }
			void clear();			
			inline int nextReadBlockSize() 
			{
				if (count() > 0 && 0 == fifoList[head]->count())
					advanceHeadTailPtr(head);								
					
				return fifoList[head]->nextReadBlockSize(); 
			}			
			inline char* nextReadBlock() 
			{
				if (count() > 0 && 0 == fifoList[head]->count())
					advanceHeadTailPtr(head);								

				return fifoList[head]->nextReadBlock();
			}
			int chop(int len);	
			int read(char* data, int maxLen);	

		private:
			int& advanceHeadTailPtr(int& ptr)
			{
				++ptr;
				if (ptr >= int(fifoList.size())) 
					ptr = ptr - int(fifoList.size());
				
				return ptr;
			}
						
		private:
			std::vector< gkhy::MfcMinus::RingBuffer* > fifoList;
			int head;
			int tail;
			//list< gkhy::MfcMinus::RingBuffer* >::iterator tailFifo;
			int fifoSize;
			int blockSize;		
			int dataCount;
			int peakDataCount;
			CCriticalSection* cs;
		};		
	}
}

