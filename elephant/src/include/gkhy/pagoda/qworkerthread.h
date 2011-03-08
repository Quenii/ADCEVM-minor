#pragma once 


#include "pagoda_global.h"

#include <QAtomicInt> 
#include <QThread>

class QWorkerThreadPrivate;

namespace gkhy
{
	namespace pagoda
	{
		class PAGODA_EXPORT QWorkerThread
		{
			friend QWorkerThreadPrivate;
		
		public:
			QWorkerThread();
			~QWorkerThread();

		public:
			void start(QThread::Priority priority = QThread::InheritPriority);
			void stop();

			bool started() { return m_started ? true : false; }
			
		protected:
			bool shouldStop();
			virtual void run() = 0; 
			
			static void sleep(unsigned long secs);
			static void msleep(unsigned long msecs);
			
		private:
			QAtomicInt m_enabled;
			bool m_started;
			QWorkerThreadPrivate* m_p;
		};

	}
}

