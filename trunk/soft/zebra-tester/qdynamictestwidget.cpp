#include "qdynamictestwidget.h"
#include "qdynamictestsettingsdialog.h"
#include "qdynamictester.h"

QDynamicTestWidget::QDynamicTestWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

QDynamicTestWidget::~QDynamicTestWidget()
{

}

void QDynamicTestWidget::on_pushButtonSetDynTest_clicked()
{
	QDynamicTestSettingsDialog dlg;	
	dlg.exec();
}

void QDynamicTestWidget::on_pushButtonStartDynamicTest_clicked()
{
	QDynamicTester* tester = QDynamicTester::instance();

	tester->start();
}