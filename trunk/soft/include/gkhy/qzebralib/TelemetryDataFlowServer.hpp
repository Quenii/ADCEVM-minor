#pragma once

#include "gkhy\qzebralib\qzebra_lib_global.hpp"
#include <map>
#include "gkhy\qzebralib\Flow.hpp"
#include "gkhy\qzebralib\Table.hpp"
#include "gkhy\qzebralib\Messenger.hpp"


namespace gkhy
{
	namespace QZebraLib
	{
		///////////////////////////////////////////////////////////////////////////////////
		// TelemetryDataFlowServer -- server control flow
		class QZEBRA_LIB_EXPORT TelemetryDataFlowServer : public Flow
		{
			Q_OBJECT

		public:
			TelemetryDataFlowServer(QObject* parent);
			virtual ~TelemetryDataFlowServer();
		public:
			FlowType type()
			{
				return TelemetryDataFlow;
			}

		
 		signals:
 		   void queryTable(QueryTableParam&);	

		private slots:
			/**	    
			 * messenger收到msg时调用此slot		    
			 */
			void slotRecvTable(Message& msg);
			void on_timer_timeout();
			
		private:
			void sendTables();			

		private:
			TelemetryTable m_telemtryTable;

		};
		////////////////////////////////// the end of TelemetryDataFlowServer //////////////////////////
	}
}