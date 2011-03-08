#pragma once
#include "gkhy/qzebralib/qzebra_lib_global.hpp"

namespace gkhy
{
	namespace QZebraLib
	{
		class DynamicRingBufferPrivate;

		class QZEBRA_LIB_EXPORT DynamicRingBuffer
		{

		public:
			DynamicRingBuffer(int size = 4096);
			virtual ~DynamicRingBuffer();
		private:
			Q_DISABLE_COPY(DynamicRingBuffer)

		public:
			void clear();
			void resize(int newSize);

			// but size() is dynamically changeable.
			int size() const;
			int count() const;
			int write(const char* data, int maxLen);
			void chop(int len);
			void commit(int len);
			int totalWritableSize();
			char* nextWriteBlock();
			int nextWriteBlockSize() const;
			char* nextReadBlock();
			int nextReadBlockSize() const;

		private:
			DynamicRingBufferPrivate& m_p;
		};
	}
}

