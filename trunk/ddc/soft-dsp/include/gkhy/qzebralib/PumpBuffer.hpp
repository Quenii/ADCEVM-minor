#pragma once
#include "gkhy/qzebralib/qzebra_lib_global.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qlist.h>

namespace gkhy
{
	namespace QZebraLib
	{
		class QZEBRA_LIB_EXPORT PumpBuffer
		{
		public:
			PumpBuffer() 
			{
				clear();
			}
			virtual ~PumpBuffer()
			{

			}
		private:
			Q_DISABLE_COPY(PumpBuffer)

		public:
			void clear()
			{
				m_mem.resize(0);
				m_start = m_end =0;
			}

			int writeBufferSize()
			{
				return m_mem.size() - m_end;
			}

			void reserve(int sizeToReserve)
			{
				int newSpace = sizeToReserve - writeBufferSize();
				if (newSpace > 0)
				{
					m_mem.resize(m_mem.size() + newSpace);
				}
			}

			char* writeBuffer()
			{
				return m_mem.data() + m_end;
			}

			char* readBuffer()
			{
				return m_mem.data() + m_start;
			}

			void commit(int n)
			{
				Q_ASSERT(m_mem.size() - m_end >= n);
				m_end += n;
			}

			void chop(int n)
			{
				Q_ASSERT(n <= count());
				m_start += n;					
			}

			int count()
			{
				Q_ASSERT(m_end >= m_start);
				return (m_end - m_start);
			}

			void squeeze()
			{
				if (0 != m_start)			
				{
					memmove(m_mem.data(), m_mem.data() + m_start, count());
					m_end = m_end - m_start;
					m_start = 0;
				}									
			}

		private:
			QByteArray m_mem;
			int m_start;
			int m_end;
		};

	}
}

