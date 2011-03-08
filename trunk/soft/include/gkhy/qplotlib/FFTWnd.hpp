#pragma once
#include "gkhy/qplotlib/qplotlab_global.hpp"
#include "gkhy/qplotlib/qscope.hpp"
#include <vector>

namespace gkhy
{
	namespace QPlotLab
	{
		class QPLOTLAB_EXPORT FFTWnd : public gkhy::QPlotLab::QScope
		{
		public:
			FFTWnd(QWidget* parent = 0, Qt::WindowFlags f = 0); 
			virtual ~FFTWnd();

		public:
			//void update(const std::vector<float> & data);
			void update(const std::vector<float> & xdata, const std::vector<float> & ydata);
		};
	}
}

