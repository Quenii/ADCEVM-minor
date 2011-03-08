#pragma once
#include "gkhy/qplotlib/qscope.hpp"
#include <QWidget>
#include <vector>
#include <complex>

namespace gkhy
{
	namespace QPlotLab
	{
		class QPLOTLAB_EXPORT QEyeScope : public QWidget
		{	
			class Scope : public gkhy::QPlotLab::QScope
			{
			public:
				Scope(QWidget* parent = 0, Qt::WindowFlags f = 0) : gkhy::QPlotLab::QScope(parent, f) {}
				CTSLScope& rawScope() { return gkhy::QPlotLab::QScope::rawScope(); }
			};

		public:
			QEyeScope(QWidget* parent = 0, Qt::WindowFlags f = 0);
			virtual ~QEyeScope();
		private:
			Q_DISABLE_COPY(QEyeScope)

		public:
			void setData(std::vector< std::complex< float > >& data);
			void clear();

		private:
			Scope* m_scopeI;
			Scope* m_scopeQ;
			int m_iSamplesPerSymbol;
			int m_iSymbolsPerTrace;
			float m_fYMax;
			float m_fYMin;
			std::vector<float> m_x;
			std::vector<float> m_di;
			std::vector<float> m_dq;
		};
	}
}

