#pragma once

#include "gkhy\qzebralib\qzebra_lib_global.hpp"
#include <map>
#include <QObject>
#include "gkhy\qzebralib\Flow.hpp"
#include "gkhy\qzebralib\Table.hpp"
#include "gkhy\qzebralib\Messenger.hpp"


namespace gkhy
{
	namespace QZebraLib
	{
		///////////////////////////////////////////////////////////////////////////////////
		// MonitoringFlowServer -- server monitoring flow
		class QZEBRA_LIB_EXPORT MonitoringFlowServer : public Flow
		{
			Q_OBJECT

		public:
			MonitoringFlowServer(QObject* parent);
			virtual ~MonitoringFlowServer();

		public:
			FlowType type()
			{
				return MonitoringFlow;
			}

 		signals: 			
 			void queryTable(QueryTableParam&);		
			
		private slots:
			/**		     
		     * messenger收到msg时调用此slot		  
		     */
			void slotRecvTable(Message& msg);

		private:
			AllComponentTable m_AllComponentTable;// component code:3100H, All component tables
		};
		////////////////////////////////// the end of MonitoringFlowServer //////////////////////////
	}
}