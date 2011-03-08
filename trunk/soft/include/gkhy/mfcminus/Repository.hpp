#pragma once
#include "gkhy/mfcminus/mfcminus_global.hpp"

namespace gkhy
{
	namespace MfcMinus
	{
		struct MFCMINUS_API RepositoryPerformance
		{
			unsigned long long nInTotal;
			unsigned int nInAvgThruput;
			unsigned int nInInstThruput;

			unsigned long long nOutTotal;
			unsigned int nOutAvgThruput;
			unsigned int nOutInstThruput;

			unsigned int nCurrentFilePercent;

			unsigned long long nFifoLeakCount;
			unsigned int nFifoPercent;
			
			long secTimeElapsed;
		};

		class MFCMINUS_API Repository
		{
		public:
			Repository(void) { }
			virtual ~Repository(void) {}
		public:
			virtual bool open() = 0;
			virtual void close() = 0;
			virtual void abort() = 0;	

			// false if overflow
			virtual bool write(const char* buff, int size) = 0;			
			virtual void getPerformance(RepositoryPerformance& rf) = 0;
		};
	}
}

