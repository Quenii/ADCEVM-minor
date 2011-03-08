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
		class QZEBRA_LIB_EXPORT TelemetryDataFlowClient : public Flow
		{			
			Q_OBJECT

		public:
			TelemetryDataFlowClient(QObject* parent);
			~TelemetryDataFlowClient();
		private:
			Q_DISABLE_COPY(TelemetryDataFlowClient)

		public:
			FlowType type()
			{
				return TelemetryDataFlow;
			}
		
        signals:
			/**
			 *
			 * 收到服务器发过来的Table时，发送此signal
			 *
			 */
			void tableReceived(Table& table);

		private slots:
			/**
			 * messenger收到msg时调用此slot
			 */
			void slotRecvTable(Message& msg);

		private:
			TelemetryTable m_telemtryTable;
		};
		///////////////////////////////////the end of CLocalCliMonFlow ///////////////////////////
	}
}