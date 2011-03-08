#pragma once
#include "gkhy/qplotlib/qplotlab_global.hpp"
#include <QWidget>

class CTSLScope;

namespace gkhy
{
	namespace QPlotLab
	{
		class QPLOTLAB_EXPORT QScope : public QWidget
		{
		public:
			QScope(QWidget* parent = 0, Qt::WindowFlags f = 0);
			virtual ~QScope();

		protected:
			CTSLScope& rawScope()	{ return *m_scope; }
			void resizeEvent(QResizeEvent * event);
			void showEvent(QShowEvent * event);
			void hideEvent(QHideEvent * event);

		private:
			CTSLScope* m_scope;
		};

	}
}

