#pragma once

#include "gkhy\qzebralib\qzebra_lib_global.hpp"
#include <QObject>
#include <QHostAddress>
#include <QTimerEvent>
#include "gkhy\qzebralib\Flow.hpp"

namespace gkhy
{
	namespace QZebraLib
	{
		class QZEBRA_LIB_EXPORT ControlFlowClient : public Flow
		{			
			Q_OBJECT

		public:
			ControlFlowClient(QObject* parent);
			~ControlFlowClient();
		private:
			Q_DISABLE_COPY(ControlFlowClient)

		public:
			FlowType type()
			{
				return ControlFlow;
			}
		
        signals:
			/**
			 *
			 * �յ���������������Tableʱ�����ʹ�signal
			 *
			 */
			void tableReceived(Table& table);

		private slots:
			/**
			 * messenger�յ�msgʱ���ô�slot
			 */
			void slotRecvTable(Message& msg);

		private:
			ConfigAckTable m_configAckTable;
		};
		///////////////////////////////////the end of CLocalCliMonFlow ///////////////////////////
	}
}