#pragma once

#include "gkhy/qplotlib/qplotlab_global.hpp"
#include "gkhy/qplotlib/qscope.hpp"

#include <vector>
#include <complex>

class SquareWidgetContainer;
class QWidget;
class CTSLScope;

namespace gkhy
{
	namespace QPlotLab
	{
		class QPLOTLAB_EXPORT QConstScope : public QWidget
		{	
			class Scope : public gkhy::QPlotLab::QScope
			{
			public:
				Scope(QWidget* parent = 0, Qt::WindowFlags f = 0) : gkhy::QPlotLab::QScope(parent, f) {}
				CTSLScope& rawScope() { return gkhy::QPlotLab::QScope::rawScope(); }
			};

		public:
			QConstScope(QWidget* parent = 0, Qt::WindowFlags f = 0);
			virtual ~QConstScope();
		private:
			Q_DISABLE_COPY(QConstScope)

		public:
			void setData(float data[], int size);
			void setData(std::vector< std::complex< float > >& data);
			void clear();

		private:
			void showIQ();

		private:
			std::vector<float> m_di;
			std::vector<float> m_dq;
			float m_fXMax;	
			float m_fXMin;
			float m_fYMax;
			float m_fYMin;	

			Scope* m_scope;
			SquareWidgetContainer* m_scopeContainer;
		};
	}
}



