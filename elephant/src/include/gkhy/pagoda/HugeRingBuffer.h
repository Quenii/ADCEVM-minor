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

#include "gkhy/pagoda/pagoda_global.h"
#include "gkhy/pagoda/RingBuffer.h"

#include <vector>
#include <QMutexLocker>
#include <QList>
#include <string>
#include <strstream>
#include <cassert>
#include <QMutex>

class CCriticalSection;

namespace gkhy
{
	namespace pagoda
	{	
		template<typename T>
		class PAGODA_EXPORT HugeRingBuffer
		{			
		public:		
			HugeRingBuffer(int bufferSize /*= 16 * 1024 * 1024*/, int blockSize = 16 * 1024 * 1024, bool threadSafe = false)
				: blockSize(blockSize)
				, m_mutex(threadSafe ? (new QMutex(QMutex::Recursive)) : 0)
			{ 
				QMutexLocker lock(m_mutex);

				resize(bufferSize);
				clear();
			}		

			virtual ~HugeRingBuffer(void)
			{
				QMutexLocker lock(m_mutex);
			}
			
		private:
			Q_DISABLE_COPY(HugeRingBuffer);

		public:			
			void resize(int newSize)
			{
				QMutexLocker lock(m_mutex);

				fifoSize = 0;		
				dataCount = 0;
				peakDataCount = 0;

				unsigned blocks = (newSize + (blockSize - 1)) / blockSize;		
				if(blocks <= 0)	blocks = 1;	 	

				fifoList.clear();

				while (fifoList.size() < blocks)
				{			
					fifoList.push_back(RingBuffer<T>(blockSize));		
					assert(fifoList[fifoList.count() - 1].size() == blockSize);
				}	

				assert(blocks == fifoList.size());

				head = tail = 0;
				fifoSize = 0;
				for (int i = 0; i < int(fifoList.size()); ++i)
				{
					fifoList[i].clear();
					fifoSize += fifoList[i].totalWritableSize();
				}

			}

			inline int size() const
			{ 	
				QMutexLocker lock(m_mutex);
				return fifoSize; 
			}		

			inline int totalWritableSize() const 
			{ 
				QMutexLocker lock(m_mutex);
				return fifoSize - dataCount;
			}

			inline int nextWriteBlockSize() 
			{
				QMutexLocker lock(m_mutex);

				if (totalWritableSize() > 0 && 0 == fifoList[tail].totalWritableSize())
						advanceHeadTailPtr(tail);				
						
				return fifoList[tail].nextWriteBlockSize(); 
			}

			inline T* nextWriteBlock()
			{
				QMutexLocker lock(m_mutex);

				if (totalWritableSize() > 0 && 0 == fifoList[tail].totalWritableSize())
					advanceHeadTailPtr(tail);				
					
				return fifoList[tail].nextWriteBlock(); 
			}

			int commit(int len)
			{
				QMutexLocker lock(m_mutex);

				int totalWritable = totalWritableSize();
				int toCommit = qMin(len, totalWritable);
				int done = 0;
				while (done != toCommit)
				{
					if (0 == fifoList[tail].totalWritableSize())
						advanceHeadTailPtr(tail);		
					done += fifoList[tail].commit(toCommit - done);
				}

				dataCount += done;
				peakDataCount = qMax(peakDataCount, dataCount);

				return toCommit;
			}

			// reture could be less than maxLen if fifo full.
			int write(const T* data, int maxLen)
			{
				QMutexLocker lock(m_mutex);

				int totalWritable = totalWritableSize();
				int bytesToWrite = qMin(maxLen, totalWritable);
				int written = 0;	
				while (written != bytesToWrite)
				{
					int subWrite = qMin(nextWriteBlockSize(), bytesToWrite - written);
					memcpy(nextWriteBlock(), data + written, subWrite);
					written += commit(subWrite);
				}

				return written;
			}

			
			inline int count() const 
			{ 
				QMutexLocker lock(m_mutex);
				return dataCount; 
			}

			inline int peakCount() const
			{
				QMutexLocker lock(m_mutex);
				return peakDataCount; 
			}

			void clear()
			{
				QMutexLocker lock(m_mutex);

				chop(count());
				peakDataCount = 0;
			}

			inline int nextReadBlockSize() 
			{
				QMutexLocker lock(m_mutex);

				if (count() > 0 && 0 == fifoList[head].count())
					advanceHeadTailPtr(head);								
					
				return fifoList[head].nextReadBlockSize(); 
			}			

			inline T* nextReadBlock() 
			{
				QMutexLocker lock(m_mutex);

				if (count() > 0 && 0 == fifoList[head].count())
					advanceHeadTailPtr(head);								

				return fifoList[head].nextReadBlock();
			}
			int chop(int len)
			{
				QMutexLocker lock(m_mutex);


				int cnt = count();
				int toChop = qMin(len, cnt);
				int done = 0;
				while (done < toChop)
				{
					if (0 == fifoList[head].count())
						advanceHeadTailPtr(head);		
					// chop as much as possible.
					done += fifoList[head].chop(toChop - done);
				}

				dataCount -= done;

				return done;
			}

			int read(T* data, int maxLen)	
			{
				QMutexLocker lock(m_mutex);

				int cnt = count();
				int toRead = qMin(maxLen,  cnt);
				int done = 0;
				while(done != toRead)
				{
					int a = nextReadBlockSize();
					int b = toRead - done;
					int subRead = qMin(a, b);
					memcpy(data + done, nextReadBlock(), subRead);
					int chopped = chop(subRead);
					assert(chopped == subRead);
					done += subRead;
				}

				return done;
			}

		private:
			int& advanceHeadTailPtr(int& ptr)
			{
				QMutexLocker lock(m_mutex);

				++ptr;
				if (ptr >= int(fifoList.size())) 
					ptr = ptr - int(fifoList.size());
				
				return ptr;
			}
						
		private:
			QList< RingBuffer<T> > fifoList;
			int head;
			int tail;
			//list< gkhy::MfcMinus::RingBuffer* >::iterator tailFifo;
			int fifoSize;
			int blockSize;		
			int dataCount;
			int peakDataCount;

			QMutex* m_mutex;
		};		
	}
}

