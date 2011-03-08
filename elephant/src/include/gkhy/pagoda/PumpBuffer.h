#pragma once

#include "gkhy/pagoda/pagoda_global.h"

#include <vector>
#include <cassert>

namespace gkhy
{
	namespace pagoda
	{
		template <typename T>
		class PAGODA_EXPORT PumpBuffer
		{
		public:
			PumpBuffer(int size) 
			{
				clear();
				resize(size);
			}
			virtual ~PumpBuffer()
			{

			}
		private:
			PumpBuffer(const PumpBuffer&);
			PumpBuffer& operator= (const PumpBuffer&);
			
		public:
			void clear()
			{
				// it's stupidly buggy to write: m_mem.resize(0); 
				m_start = m_end =0;
			}

			int writeBufferSize()
			{
				return int(m_mem.size()) - m_end;
			}

			int size()
			{
				return int(m_mem.size());
			}

			void resize(int newSize)
			{
				m_mem.resize(newSize);
			}

			T* reserve(int sizeToReserve)
			{
				int newSpace = sizeToReserve - writeBufferSize();
				if (newSpace > 0)
				{
					m_mem.resize(m_mem.size() + newSpace);
				}

				return readBuffer();
			}

			T* writeBuffer()
			{
				return (T*)&m_mem[m_end];
			}

			T* readBuffer()
			{
				return (T*)&m_mem[m_start];
			}

			void commit(int n)
			{
				assert(int(m_mem.size()) - m_end >= n);
				m_end += n;
			}

			int chop(int n)
			{
				int cnt =  count();
				int toChop = qMin(cnt, n);
				m_start += toChop;
				
				if (count() == 0)
				{
					squeeze();
				}

				return toChop;
			}

			int count()
			{
				assert(m_end >= m_start);
				return (m_end - m_start);
			}

			void squeeze()
			{
				if (0 != m_start)			
				{
					int cnt = 0;
					if ( (cnt  = count()) > 0 )
					{
						memmove(&m_mem[0], &m_mem[0] + m_start, cnt);
					}

					m_end = m_end - m_start;
					m_start = 0;
				}									
			}

		private:
			std::vector<T> m_mem;
			int m_start;
			int m_end;
		};

	}
}

