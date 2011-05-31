#pragma once

#include "gkhy/qplotlib/qscope.hpp"
#include <vector>

namespace gkhy
{
	namespace QPlotLab
	{
		class QPLOTLAB_EXPORT QStaticTestPlot : public gkhy::QPlotLab::QScope
		{		
		public:
			QStaticTestPlot(QWidget* parent = 0, Qt::WindowFlags f = 0);
			virtual ~QStaticTestPlot();
		private:
			Q_DISABLE_COPY(QStaticTestPlot)

		public:
			void addData(float ideal, float measured);
			void clear();

		private:
			std::vector<float> m_ideal;
			std::vector<float> m_measured;
		};
	}
}

