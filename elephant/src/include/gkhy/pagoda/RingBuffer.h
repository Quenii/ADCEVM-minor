#pragma once

#include "gkhy/pagoda/pagoda_global.h"

#include <vector>

namespace gkhy
{
	namespace pagoda
	{			
		template <typename T>
		class PAGODA_EXPORT RingBuffer
		{		
			class ByteVector : public std::vector<T> 
			{
			public:
				T* data()
				{
					return (size() > 0) ? &(this->operator [](0)) : 0;
				}
			};

		public:
			RingBuffer(int size = 4096)
			{
				head = 0;
				tail = 0;		

				resize(size);
			}

			virtual ~RingBuffer()
			{
				clear();
			}


		private:
			// Q_DISABLE_COPY(RingBuffer);
			
		public:
			void clear()
			{
				chop(count());
			}

			void resize(int newSize)			
			{
				buffer.resize(newSize);
				head = tail = 0;
			}

			int size() const
			{
				return int(buffer.size());
			}

			int count() const {
				//return (tail + buffer.size() - head) % buffer.size();
				int t = tail + int(buffer.size()) - head;
				return (t >= int(buffer.size())) ? t - int(buffer.size()) : t; 
			}

			int write(const T* data, int maxLen)
			{
				int bytesToWrite = qMin(maxLen, totalWritableSize());
				int written = 0;
				while (written != bytesToWrite)
				{
					int blkSize = nextWriteBlockSize();
					int left = bytesToWrite - written;						 
					int toWrite = qMin(blkSize, left);
					memcpy(nextWriteBlock(), data + written, toWrite);

					commit(toWrite); // tail = (tail + toWrite) % size();
					written += toWrite;
				}

				return bytesToWrite;
			}

			int commit(int len)
			{
				int totalWritable = totalWritableSize();			
				int toCommit = qMin(len, totalWritable);
				tail = (tail + toCommit) % size();

				return toCommit;
			}

			int totalWritableSize() const
			{
				return size() - 1 - count();
			}

			T* nextWriteBlock()
			{
				return (buffer.data() + tail);
			}


			int nextWriteBlockSize() const
			{
				// return (tail >= head) ? buffer.size() - head : head - tail;
				if (head > tail)
				{
					return head - tail;
				}
				else
				{
					int a = int(buffer.size()) - tail;
					int b = totalWritableSize();
					return qMin(a, b);				
				}
			}

			T* nextReadBlock()	{	return &buffer[head]; }

			int nextReadBlockSize() const
			{
				return (tail >= head) ? tail - head : int(buffer.size()) - head;
			}

			int chop(int len)
			{
				int cnt = count();				
				int toChop = qMin(len, cnt);
				head = head + toChop;
				if (head >= size())
					head -= size();

				// it's a bug to do this because at this time the writer may
				// hold the buffer for writing.
				/* if (head == tail)
				head = tail = 0;				
				*/

				return toChop;
			}


			int read(T* data, int maxLen)
			{
				int cnt = count();
				//assert(maxLen <= cnt);
				int toRead = qMin(maxLen, cnt);
				int read = 0;
				while(read < toRead)
				{
					int blkSize = nextReadBlockSize();
					int left = toRead - read;
					int subRead = qMin(left, blkSize);
					memcpy(data + read, nextReadBlock(), subRead);
					chop(subRead);
					read += subRead;
				}

				return toRead;
			}

		private:
			ByteVector buffer;
			int head, tail;					
		};
	}
}

