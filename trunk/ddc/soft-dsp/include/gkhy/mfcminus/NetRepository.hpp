#pragma once
#include "gkhy/mfcminus/mfcminus_global.hpp"
#include "gkhy/mfcminus/Repository.hpp"

/*class SimpleSvrHDR;*/
class NetRepositoryPrivate;

namespace gkhy
{
	namespace MfcMinus
	{
		//class MFCMINUS_API NetRepository : public Repository
		//{
		//public:
		//	NetRepository(unsigned short port, int fifoSize);
		//	virtual ~NetRepository(void);
		//public:
		//	bool open();
		//	void close();
		//	void abort();	

		//	// false if overflow
		//	bool write(const char* buff, int size);			
		//	void getPerformance(RepositoryPerformance& rf);

		//private:		
		//	int m_fifoSize;
		//	unsigned short m_port;
		//	SimpleSvrHDR& m_server;
		//};

		class MFCMINUS_API NetRepository : public Repository
		{
		public:
			NetRepository(unsigned short port, int fifoSize);
			virtual ~NetRepository(void);
		public:
			bool open();
			void close();
			void abort();	

			// false if overflow
			bool write(const char* buff, int size);			
			void getPerformance(RepositoryPerformance& rf);

		private:
			NetRepositoryPrivate& m_p;
		};
	}
}

