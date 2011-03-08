#pragma once

#include "gkhy\qzebralib\qzebra_lib_global.hpp"
#include <QTcpServer>
#include <QList>

namespace gkhy
{
	namespace QZebraLib
	{
		class YaTcpServer : public QTcpServer
		{			
			Q_OBJECT

		public:
			YaTcpServer(QObject* parent = 0)  : QTcpServer(parent) {}		
	
		public:		
			bool hasPendingConnections() const
			{
				return pendingConns.count() > 0 ? true : false;
			}
			int nextPendingConnection2() 
			{
				if (!hasPendingConnections())
				{
					return -1;
				}

				int first = pendingConns.first();
				pendingConns.pop_front();
				return first;
			}
			
		protected:
			void incomingConnection(int handle)
			{
				pendingConns.push_back(handle);
			}	

			QTcpSocket* nextPendingConnection()
			{
				Q_ASSERT(false);
				return 0;
			}

		private:
			QList<int> pendingConns;			
		};
	}
}