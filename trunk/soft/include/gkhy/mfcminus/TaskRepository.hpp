#pragma once

#include "gkhy/mfcminus/mfcminus_global.hpp"
#include "gkhy/mfcminus/Repository.hpp"

class TaskRepositoryPrivateEx;

namespace gkhy
{
	namespace MfcMinus
	{			
		class MFCMINUS_API TaskRepository : gkhy::MfcMinus::Repository
		{
		public:
			//TaskRepository();
			TaskRepository(
				const std::string& dir, 
				long long footPrint, // assign -1 if all free diskspace is wanted.
				long long fileSize, 
				int timeout_s, // assign -1 if timeout feature is not wanted.
				int bufferSize = 100 * 1024 * 1024);  // 100 MBytes
			virtual ~TaskRepository();

		public:
			bool open();
			void close();
			void abort();	

			// false if overflow
			bool write(const char* buff, int size);			
			void getPerformance(RepositoryPerformance& rf);

		private:
			TaskRepositoryPrivateEx& m_p;		

		};
	}
}