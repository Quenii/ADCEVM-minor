#pragma once

#include "gkhy\qzebralib\qzebra_lib_global.hpp"
#include "gkhy\qzebralib\Flow.hpp"
#include "gkhy\qzebralib\YaTcpServer.hpp"
#include <QObject>
#include <QHostAddress>
#include <QTimerEvent>
#include <QLinkedList>

namespace gkhy
{
	namespace QZebraLib
	{	
		class FlowServer : public QObject
		{
			Q_OBJECT
		public:
			FlowServer(QObject* parent, quint16 port, int maxServedListLen);
			virtual ~FlowServer();			
		private:
			Q_DISABLE_COPY(FlowServer)
		public:
			bool listen(const QHostAddress& ip);
			void close();		
		signals:
		   	void queryTable(QueryTableParam&);

		private slots:
			void slotNewConnection();
			void slotDeleteServed(QObject* servedFlow);		
			
		protected:
			virtual Flow* createFlow(int socket) = 0;
		private:		
			int m_maxServedListLen;			
			quint16 m_port;
			YaTcpServer m_tcpListenser;
			QLinkedList<Flow*> m_served;
		};

		template<class FlowType>
		class FlowServerTemplate: public FlowServer
		{
		public:
			FlowServerTemplate(QObject* parent, quint16 port, int maxServedListLen) : 
			  FlowServer(parent, port, maxServedListLen)  {	  }
			  virtual ~FlowServerTemplate() { }
		private:
			virtual Flow* createFlow(int socket) {
				FlowType* flow = new FlowType(this);					
				flow->slotSetTcpSocket(socket);	
				return flow;
			}			
		};

		class QZEBRA_LIB_EXPORT FlowManagerServer : public QObject
		{	
			Q_OBJECT
		public:
			FlowManagerServer(QObject *parent);
			virtual ~FlowManagerServer(void);

		private:
			Q_DISABLE_COPY(FlowManagerServer)
						
		signals:
			/**
			* 第二个参数为true代表客户端发的是configTable；false表示发送的是table
			* 查询。第三个参数指示是查询是否成功。
			*/
			void queryTable(QueryTableParam&);
			
		public:		
		   /**			
			* 各个flow在addr(ip地址)处监听,不传参数代表在任意地址监听
			* @return true if ok, else false			
			*/
		   	bool start(const QHostAddress & addr = QHostAddress::Any);
			void stop();
		
		private:		
			QLinkedList<FlowServer*> m_serverList;
		};
	}
}

