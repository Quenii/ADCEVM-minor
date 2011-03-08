#pragma once

#include "gkhy/qzebralib/qzebra_lib_global.hpp"
#include "gkhy/qzebralib/Table.hpp"
#include "gkhy/qzebralib/ControlFlowClient.hpp"
#include <QObject>
#include <QTimer>
#include <QHostAddress>

namespace gkhy
{
	namespace QZebraLib
	{	
		enum ConfigAckCode
		{
			Succeeded			= 1,
			FaiedToConnect		= 2,
			AckMessageTimeout	= 3,
			BadReq				= 4
		};

		class QZEBRA_LIB_EXPORT AdaptedControlFlowClient : public QObject
		{
		public:

			Q_OBJECT

		public:
			AdaptedControlFlowClient(QObject *parent, quint32 timeout = 1000);//10 seconds
			virtual ~AdaptedControlFlowClient();

		private:
			Q_DISABLE_COPY(AdaptedControlFlowClient)

		public:
			bool ready() { return !m_bStatusOn; }

		signals:
			void configAck(ConfigAckCode ack);    

		public slots:		
			/**						 
			 * 将收到的table转出去, 如果ready()不为true，那么，本操作不产生任何作用。
			 * 在调用abort(), 或接收到configAck()信号前，必须保证table指针一直有效。
			 */
			void slotSendTable(QHostAddress& hostAddr, quint16 port, Table* table);	

		private slots:
			/**
			 * 当m_adaptee连接成功时,此slot被调用			
			 */
			void slotConnected();			
			
			/**			
			 * 当m_adaptee收到table时,此slot被调用			
			 */
			void slotTableReceived(Table& table);

			/**			
			 * 当m_adaptee在规定的时间内还没收到ack时,此slot被调用			
			 */
			void slotTimeout();

		private:
			ControlFlowClient m_adaptee;
			Table* m_table;
			quint32 m_timeout;
			bool m_bStatusOn; // on or off
			ConfigAckTable m_configAckTable;
			// bool m_bConfigAckRecved;// 是否从服务器收到了config ack
		};
	}
}


