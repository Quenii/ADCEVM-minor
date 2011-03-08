#pragma once

#include "gkhy\qzebralib\qzebra_lib_global.hpp"
#include <map>
#include "gkhy\qzebralib\Flow.hpp"
#include "gkhy\qzebralib\Table.hpp"
#include "gkhy\qzebralib\Messenger.hpp"

namespace gkhy
{
	namespace QZebraLib
	{
		///////////////////////////////////////////////////////////////////////////////////
		// ControlFlowServer -- server control flow
		class QZEBRA_LIB_EXPORT ControlFlowServer : public Flow
		{
			Q_OBJECT

		public:
			ControlFlowServer(QObject* parent);
			virtual ~ControlFlowServer();	
		public:
			FlowType type()
			{
				return ControlFlow;
			}

 		signals:
 			/**
 			 * 第二个参数为true代表客户端发的是configTable；false表示发送的是table
 			 * 查询。第三个参数指示是查询是否成功。
 			 */
 			void queryTable(QueryTableParam&);

		private slots:
			/**	    
			 * messenger收到msg时调用此slot		    
			 */
			void slotRecvTable(Message& msg);	

		private:
			DpuConfigTable m_dpuConfigTable;
			DmuConfigTable m_dmuConfigTable;	
			ConfigAckTable m_configAckkTable;
		};
		////////////////////////////////// the end of ControlFlowServer //////////////////////////
	}
}