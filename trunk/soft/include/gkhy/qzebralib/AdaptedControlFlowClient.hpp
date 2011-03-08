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
			 * ���յ���tableת��ȥ, ���ready()��Ϊtrue����ô���������������κ����á�
			 * �ڵ���abort(), ����յ�configAck()�ź�ǰ�����뱣֤tableָ��һֱ��Ч��
			 */
			void slotSendTable(QHostAddress& hostAddr, quint16 port, Table* table);	

		private slots:
			/**
			 * ��m_adaptee���ӳɹ�ʱ,��slot������			
			 */
			void slotConnected();			
			
			/**			
			 * ��m_adaptee�յ�tableʱ,��slot������			
			 */
			void slotTableReceived(Table& table);

			/**			
			 * ��m_adaptee�ڹ涨��ʱ���ڻ�û�յ�ackʱ,��slot������			
			 */
			void slotTimeout();

		private:
			ControlFlowClient m_adaptee;
			Table* m_table;
			quint32 m_timeout;
			bool m_bStatusOn; // on or off
			ConfigAckTable m_configAckTable;
			// bool m_bConfigAckRecved;// �Ƿ�ӷ������յ���config ack
		};
	}
}


