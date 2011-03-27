#include "qcentralwidget.h"

#include "qstatictestplot.h"
#include "qdynamictestplot.h"

QCentralWidget::QCentralWidget(QWidget *parent)
	: QStackedWidget(parent)
{
	ui.setupUi(this);
	
	staticPlot = new QStaticTestPlot(this);
	dynamicPlot = new QDynamicTestPlot(this);

	addWidget(staticPlot);
	addWidget(dynamicPlot);
}

QCentralWidget::~QCentralWidget()
{

}

void QCentralWidget::activateMode(Mode mode)
{
	QWidget* widget = 0;
	switch (mode)
	{
	case StaticTest:
		widget = staticPlot;
		break;

	case DynamicTest:
		widget = dynamicPlot;
		break;

	default:
		Q_ASSERT(false);
	}

	if (widget)
	{
		setCurrentWidget(widget);
	}
} 