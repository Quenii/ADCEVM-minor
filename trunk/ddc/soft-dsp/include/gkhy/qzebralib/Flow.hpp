#ifndef FLOW_HPP
#define FLOW_HPP

#include "gkhy\qzebralib\qzebra_lib_global.hpp"
#include "gkhy\qzebralib\Table.hpp"
#include "gkhy\qzebralib\Messenger.hpp"
#include "gkhy\qzebralib\Message.hpp"
#include <QObject>
#include <QTcpSocket>

namespace gkhy
{
	namespace QZebraLib
	{
		enum QZEBRA_LIB_EXPORT FlowTcpPort : unsigned short
		{
			MonitoringFlowPort		= 3000,
			VectorAnalysisFlowPort	= 3055,
			ControlFlowPort			= 3001,
			TelemetryDataFlowPort	= 3075,
			ProbeFlowPort			= 3056,
		};		

		enum QZEBRA_LIB_EXPORT FlowType
		{
			MonitoringFlow		= 0x01,
			VectorAnalysisFlow	= 0x02,
			ControlFlow			= 0x03,
			TelemetryDataFlow	= 0x04,
			ProbeFlow			= 0x05,
		};

		struct QZEBRA_LIB_EXPORT QueryTableParam
		{
			FlowType flowType;
			Table* table;
			//bool configNotQuery;
			bool queryOkay;
		};

		class QZEBRA_LIB_EXPORT Flow : public QObject
		{
			Q_OBJECT

		public:
			Flow(QObject *parent);
			virtual ~Flow();		

		private:
			Q_DISABLE_COPY(Flow)

		public:			
			// 是否可以再发送一个长度为len的table，使得所有table占用的发生缓冲区不超过
		    // max(max_len_sent, len) * bufferLimitFactor.
			bool isReadyToWrite(int len);
			virtual FlowType type() = 0;			
			void connectToServer(QHostAddress& hostAddr,  quint16 port, bool autoConnect = false);
		
		public slots:
			void slotConnectToServer(QHostAddress& hostAddr,  quint16 port);
			void slotSetTcpSocket(int socket);				
			void slotDisconnect();

			int sendTable(Table& table);	
			
			// 超过最大连接数发送
			int sendRejectionMsg();

			int sendNegativeMsg();
			
			int getFlowId();
			void setFlowId(int nFlowId);
			/**			 
			 * 检查flowID是否为合法的		
			 */
			bool checkFlowId(int nFlowId);

			/**			 
			 * 该flow是否还活着			
			 */
			bool isAlive();
			
		signals:
			void connected();
			void disconnected();
			void bytesWritten(qint64 bytes);

		protected slots:
			/**		
			 * messenger收到msg时调用此slot			
			 */
			virtual void slotRecvTable(Message& msg) = 0; // {};

		private:
			void init();
		
		private:	
			Messenger m_messenger;
			Message m_message;		
			int m_nFlowId;
		};
	}
}
#endif // FLOW_HPP
