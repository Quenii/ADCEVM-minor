#pragma once
#include "gkhy/mfcminus/mfcminus_global.hpp"
#include <Windows.h>
#include <vector>
#include <cassert>
#include <string>

namespace gkhy
{
	namespace MfcMinus
	{			
		class MFCMINUS_API RingBuffer
		{		

			//////////////////////////////////////////////////////////////////////////
			// nested class declaration.
		private:
			class char_vector : private std::vector<char>
			{
			public:
				inline void swap(char_vector& ref)
				{
					vector<char>::swap(ref);
				}

				inline void resize(int newSize)
				{
					try
					{
						std::vector<char>::resize(newSize);
					}
					catch (std::bad_alloc& ba)
					{	
						std::string msg = 
							std::string("Application cannot continue any more because:") +
							std::string("\n    ") + std::string(ba.what()) +	std::string("  in function " __FUNCTION__ "") +
							std::string("\n\nIf you couldn't fix this, please contact the author of this program.") +
							std::string("\nIt's a shame any way.");				
						MessageBoxA(0, msg.c_str(), "Exception", 0);
						exit(1);
					}
				}

				inline int size() { return int(vector<char>::size()); }
				inline int size() const { return int(vector<char>::size()); }

				inline const char& operator[] (size_type _Pos) const
				{
					return vector<char>::operator[](_Pos);
				}

				inline char& operator[](size_type _Pos)
				{
					return vector<char>::operator[](_Pos);
				}
			};
			
			
			//////////////////////////////////////////////////////////////////////////
			// class body.
		public:
			RingBuffer(int size = 4096)
			{
				resize(size);
			}
				
			virtual ~RingBuffer()
			{

			}

			RingBuffer(const RingBuffer& ref)
			{				
				buffer.resize(ref.size());
				
				head = ref.head;
				tail = ref.tail;
				
				if (tail > head)
				{
					memcpy(&buffer[head], &ref.buffer[head], tail - head);
				}
				else if (tail < head)
				{
					memcpy(&buffer[0], &ref.buffer[0], tail);
					memcpy(&buffer[head], &ref.buffer[head], buffer.size() - head);					
				}

			}
		public:
			void clear()
			{
				chop(count());
			}

			void resize(int newSize)			
			{
				// + 1 is enough in principle but 
				// 4KB is actually added for sake of efficiency.
				char_vector tmp;
				tmp.resize(newSize + 4 * 1024);
				// Releases any memory not required to store the array's data.
				buffer.swap(tmp);

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

			int write(const char* data, int maxLen)
			{
				int totalWritable = totalWritableSize();
				int bytesToWrite = qMin(maxLen, totalWritable);
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

			char* nextWriteBlock()
			{
				return &buffer[0] + tail;
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

			char* nextReadBlock()
			{
				return &buffer[0] + head;
			}

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


			int read(char *data, int maxLen)
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
			char_vector buffer;
			int head, tail;		
			
		};
	}
}

