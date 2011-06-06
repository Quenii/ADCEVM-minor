#include "qdynamictestwidget.h"
#include "qdynamictestsettingsdialog.h"

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
