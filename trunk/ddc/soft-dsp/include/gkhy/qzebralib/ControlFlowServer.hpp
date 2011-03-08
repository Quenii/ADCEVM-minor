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
 			 * �ڶ�������Ϊtrue����ͻ��˷�����configTable��false��ʾ���͵���table
 			 * ��ѯ������������ָʾ�ǲ�ѯ�Ƿ�ɹ���
 			 */
 			void queryTable(QueryTableParam&);

		private slots:
			/**	    
			 * messenger�յ�msgʱ���ô�slot		    
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