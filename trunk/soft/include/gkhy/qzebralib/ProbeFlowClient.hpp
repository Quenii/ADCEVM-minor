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
		class QZEBRA_LIB_EXPORT ProbeFlowClient : public Flow
		{
			Q_OBJECT
			
			Q_DISABLE_COPY(ProbeFlowClient)

		public:
			ProbeFlowClient(QObject* parent);
			virtual ~ProbeFlowClient();
			
		public:
			FlowType type()	{ return ProbeFlow; }

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
			RejectionTable m_probeRejectionTab;
			NegativeProbeAckTable m_probeNegtiveTab; 
			ProbeTable m_probeTable;			
		};
		///////////////////////////////////the end of CLocalCliMonFlow ///////////////////////////
	}
}