#include "qstatictestwidget.h"
#include "global.h"
#include "qstatictestsettingsdialog.h"

QStaticTestWidget::QStaticTestWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	connect(QStaticTester::instance(), SIGNAL(stopped()), this, SLOT(stopped_Received()));


}

QStaticTestWidget::~QStaticTestWidget()
{

}

void QStaticTestWidget::on_pushButtonSetStaticTest_clicked()
{
	QStaticTestSettingsDialog dlg;	
	dlg.exec();
}

void QStaticTestWidget::on_pushButtonStartStop_clicked()
{
	QStaticTester* tester = QStaticTester::instance();
	if (tester->isRunning() != true)
	{
		if (tester->start())
		{
			ui.pushButtonStartStop->setText(QString::fromLocal8Bit("停止"));
			ui.pushButtonSetStaticTest->setEnabled(false);
		}
	}
	else // if (tester->isRunning())
	{
		tester->stop();
		ui.pushButtonStartStop->setText(QString::fromLocal8Bit("开始"));
		ui.pushButtonSetStaticTest->setEnabled(true);
	}
}

void QStaticTestWidget::stopped_Received()
{
	ui.pushButtonStartStop->setText(QString::fromLocal8Bit("开始"));
	ui.pushButtonSetStaticTest->setEnabled(true);
}