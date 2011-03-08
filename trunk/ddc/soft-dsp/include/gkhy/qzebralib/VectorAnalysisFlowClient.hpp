#pragma once

#include "gkhy\qzebralib\qzebra_lib_global.hpp"
#include <QObject>
#include <QTimerEvent>
#include <QHostAddress>
#include "gkhy\qzebralib\Flow.hpp"

namespace gkhy
{
	namespace QZebraLib
	{
		class QZEBRA_LIB_EXPORT VectorAnalysisFlowClient : public Flow
		{
			Q_OBJECT

		public:
			VectorAnalysisFlowClient(QObject* parent);
			virtual ~VectorAnalysisFlowClient();
		private:
			Q_DISABLE_COPY(VectorAnalysisFlowClient)

		public:
			FlowType type()
			{
				return VectorAnalysisFlow;
			}


        signals:
			/**
			 * �յ���������������Tableʱ�����ʹ�signal
			 */
			void tableReceived(Table& table);

		private slots:			
			/**
			 * messenger�յ�msgʱ���ô�slot
			 */
			void slotRecvTable(Message& msg);
		
		private:
			RejectionTable m_vectorRejectionTab;
			NegativeVectorAnalysisAckTable m_vetorNegtiveTab; 
			VectorAnalysisDataMsgTable m_vectorAnalysisDataTab;			
		};
		///////////////////////////////////the end of CLocalCliMonFlow ///////////////////////////
	}
}