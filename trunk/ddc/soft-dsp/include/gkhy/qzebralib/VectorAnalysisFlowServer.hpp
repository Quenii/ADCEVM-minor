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
		// VectorAnalysisFlowServer -- server control flow
		class QZEBRA_LIB_EXPORT VectorAnalysisFlowServer : public Flow
		{
			Q_OBJECT

		public:
			VectorAnalysisFlowServer(QObject* parent);
			virtual ~VectorAnalysisFlowServer();		

		public:
			FlowType type()
			{
				return VectorAnalysisFlow;
			}

 		signals:
 		   	void queryTable(QueryTableParam&);			

		private slots:
			/**
			 * messenger�յ�msgʱ���ô�slot			
			 */
			void slotRecvTable(Message& msg);			


		private:
			VectorAnalysisDataMsgTable m_vectorAnalysisDataTab;
		};
		////////////////////////////////// the end of VectorAnalysisFlowServer //////////////////////////
	}
}