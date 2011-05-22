#include "qstatictestwidget.h"

QStaticTestWidget::QStaticTestWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

QStaticTestWidget::~QStaticTestWidget()
{

}

void QStaticTestWidget::on_pushButtonStartStop_clicked()
{
	QTester* tester = QTester::instance();
	if (tester->isRunning() != true)
	{
		tester->start(StaticTest);
	}
	else if (tester->isRunning() && tester->currentMode() == StaticTest)
	{
		tester->stop();
	}
}