#pragma once

#include "gkhy/pagoda/pagoda_global.h"
#include "gkhy/pagoda/qworkerthread.h"
#include "gkhy/pagoda/HugeRingBuffer.h"
#include "gkhy/pagoda/qThruputMeter.h"

#include <QTime>
#include <QString>
#include <QAtomicInt>

class QMutex;
class QSessionalRepositoryManager;

namespace gkhy
{
	namespace pagoda
	{
		struct SessionalRepositoryStatistics
		{
			ThruputMeterValue in;
			ThruputMeterValue out;

			qint64 nCurrentFilePercent;
			qint64 nFifoLeakCount;
			qint64 nFifoPercent;
			qint64 secElapsedTime;
		};

		template <typename T>
		class QSessionalRepository : protected gkhy::pagoda::QWorkerThread
		{
		public:
			QSessionalRepository(
				QString dir, 
				qint64 footPrint, // assign -1 if all free diskspace is wanted.
				qint64 fileSize, 
				int timeout_s = -1, // assign -1 if timeout feature is not wanted.
				bool makeTimeSubDir = true,
				int bufferSize = 100 * 1024 * 1024); // 100 MBytes
			virtual ~QSessionalRepository();

		private:
			Q_DISABLE_COPY(QSessionalRepository)

		public:
			bool open();
			void close();
			void abort();	

			int totalWritableSize() const;
			int nextWriteBlockSize();
			T* nextWriteBlock();
			int commit(int len);
			int write(const T* data, int maxLen);
			SessionalRepositoryStatistics statistics() const;

		private:
			QString taskDir();
			void run();
			void run_session();

		private slots:
			void fileCreated(QString fileName);

		private:
			QThruputMeter m_inMeter;
			QThruputMeter m_outMeter;
			gkhy::pagoda::HugeRingBuffer<T> m_buffer;
			QSessionalRepositoryManager* m_sessionalRepositoryManager;
			// SessionalRepositoryStatistics m_statistics;
			
			QMutex* m_lock;

			const QString m_dir;
			const qint64 m_fileSize;
			const int m_timeout_s;	
			const bool m_makeTimeSubDir;
			QAtomicInt m_abort;
		};

		class  PAGODA_EXPORT QSessionalRepositoryA : public QSessionalRepository<char>
		{
		public:
			QSessionalRepositoryA(
				QString dir, 
				qint64 footPrint, // assign -1 if all free diskspace is wanted.
				qint64 fileSize, 
				int timeout_s = -1, // assign -1 if timeout feature is not wanted.
				bool makeTimeSubDir = true,
				int bufferSize = 100 * 1024 * 1024) :  // 100 MBytes
			QSessionalRepository<char>(
				dir, 
				footPrint, // assign -1 if all free diskspace is wanted.
				fileSize, 
				timeout_s, // assign -1 if timeout feature is not wanted.
				makeTimeSubDir,
				bufferSize) // 100 MBytes
			{

			}
		};


		class  PAGODA_EXPORT QSessionalRepositoryDW : public QSessionalRepository<unsigned int>
		{
		public:
			QSessionalRepositoryDW(
				QString dir, 
				qint64 footPrint, // assign -1 if all free diskspace is wanted.
				qint64 fileSize, 
				int timeout_s = -1, // assign -1 if timeout feature is not wanted.
				bool makeTimeSubDir = true,
				int bufferSize = 100 * 1024 * 1024) :  // 100 MBytes
			QSessionalRepository<unsigned int>(
				dir, 
				footPrint, // assign -1 if all free diskspace is wanted.
				fileSize, 
				timeout_s, // assign -1 if timeout feature is not wanted.
				makeTimeSubDir,
				bufferSize) // 100 MBytes
			{

			}
		};

	}
}