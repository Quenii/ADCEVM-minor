#pragma once
#include "gkhy/qzebralib/qzebra_lib_global.hpp"
#include <QObject>
#include <QHostAddress>
#include "gkhy/qzebralib/Table.hpp"
#include "gkhy/qzebralib/MonitoringFlowClient.hpp"
#include "gkhy/qzebralib/AdaptedControlFlowClient.hpp"
#include "gkhy/qzebralib/VectorAnalysisFlowClient.hpp"
#include "gkhy/qzebralib/ProbeFlowClient.hpp"

namespace gkhy
{	
	namespace QZebraLib
	{		
		class QZEBRA_LIB_EXPORT FlowManagerClient : public QObject
		{
			 Q_OBJECT

			 Q_DISABLE_COPY(FlowManagerClient)

		public:
			FlowManagerClient(QObject *parent);
			virtual ~FlowManagerClient(void);

		public:
			void setProbeFlowEnabled(bool enabled);

		signals:
			// monitoring flow
			void monitorFlowConnected();
			void monitorFlowDisconnected();
			void monTableReceived(Table& table);					

			// control flow
			// 当收到服务器返回的config ack时，发送此signal给core						
			void configAck(ConfigAckCode ConfigAckCode);		

			// probe flow
			void probeTableReceived(Table& table);					

		public slots:
			void slotStart(QHostAddress& hostAddr);
			void slotStop();
			// monitoring flow
			
			// control flow

			// control flow
			void slotResetBert();
			void slotConfig(Table& table);

			// probe flow
		protected:
			void timerEvent(QTimerEvent* event);
			
		private:	
			QHostAddress m_hostAddr;

			int m_timerId;

			//bool m_monFlowOn;
			MonitoringFlowClient m_monFlowCli;
			AdaptedControlFlowClient m_adapConFlowCli;
			bool m_vectFlowOn;
			VectorAnalysisFlowClient m_vectorAnalysisFli;
			bool m_probeFlowOn;
			ProbeFlowClient m_probeFlowCli;
		};
	}
}
