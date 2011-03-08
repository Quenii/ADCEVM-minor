#pragma once

#include "gkhy/qplotlib/qscope.hpp"
#include <vector>

namespace gkhy
{
	namespace QPlotLab
	{
		class QPLOTLAB_EXPORT QFreqScope : public gkhy::QPlotLab::QScope
		{		
		public:
			QFreqScope(QWidget* parent = 0, Qt::WindowFlags f = 0);
			virtual ~QFreqScope();
		private:
			Q_DISABLE_COPY(QFreqScope)

		public:
			void setData(const std::vector<float>& data);
			void clear();
		};
	}
}

