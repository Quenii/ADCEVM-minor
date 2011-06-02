#include "qcentralwidget.h"
#include "qstatictester.h"



QCentralWidget::QCentralWidget(QWidget *parent)
	: QStackedWidget(parent)
{
	ui.setupUi(this);
	
	staticPlot = new QStaticTestPlot(this);
	bool ok = connect( QStaticTester::instance(), SIGNAL(newData(float, float)), 
		staticPlot, SLOT(addData(float, float)) );

	dynamicPlot = new QDynamicTestPlot(this);

	addWidget(staticPlot);
	addWidget(dynamicPlot);
}

QCentralWidget::~QCentralWidget()
{

}

void QCentralWidget::changeMode(TestMode mode)
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