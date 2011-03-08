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
		// ProbeFlowServer -- server control flow
		class QZEBRA_LIB_EXPORT ProbeFlowServer : public Flow
		{
			Q_OBJECT

		public:
			ProbeFlowServer(QObject* parent);
			virtual ~ProbeFlowServer();		

		public:
			FlowType type()
			{
				return ProbeFlow;
			}

 		signals:
 		   	void queryTable(QueryTableParam&);			

		private slots:
			/**
			 * messenger收到msg时调用此slot			
			 */
			void slotRecvTable(Message& msg);		

		private:
			ProbeTable m_probeTable;
		};
		////////////////////////////////// the end of ProbeFlowServer //////////////////////////
	}
}