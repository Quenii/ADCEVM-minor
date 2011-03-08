#pragma once

#include "gkhy\qzebralib\qzebra_lib_global.hpp"
#include <QObject>
#include <QTimerEvent>
#include <QHostAddress>
#include "gkhy\qzebralib\Flow.hpp"

namespace gkhy
{
	namespace QZebraLib
	{
		class QZEBRA_LIB_EXPORT MonitoringFlowClient : public Flow
		{
			Q_OBJECT

		public:
			MonitoringFlowClient(QObject* parent);
			~MonitoringFlowClient();		

		public:
			FlowType type()
			{
				return MonitoringFlow;
			}

		private:
			Q_DISABLE_COPY(MonitoringFlowClient)

        signals:
			/**			 
			 * �յ���������������Tableʱ�����ʹ�signal			 
			 */
			void tableReceived(Table& table);
			
		private slots:			
			/**		 
			 * messenger�յ�msgʱ���ô�slot			 
			 */
			void slotRecvTable(Message& msg);	

		private:
			// QHostAddress m_hostAddr;

			RejectionTable m_rejectionTable;
			NegtiveTable m_negtiveTable; 
			AllComponentTable m_allCompTable;
			GlobalHdrTable m_GlobalHdrTable;
			DmuTable m_dmuTable;
			DpuTable m_dpuTable;
			
		};
		///////////////////////////////////the end of CLocalCliMonFlow ///////////////////////////
	}
}