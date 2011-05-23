#include "qstatictestwidget.h"
#include "global.h"
#include "qstatictestsettingsdialog.h"

QStaticTestWidget::QStaticTestWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
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
			ui.pushButtonStartStop->setText(QString::fromLocal8Bit("Í£Ö¹"));
			ui.pushButtonSetStaticTest->setEnabled(false);
		}
	}
	else // if (tester->isRunning())
	{
		tester->stop();
		ui.pushButtonStartStop->setText(QString::fromLocal8Bit("¿ªÊ¼"));
		ui.pushButtonSetStaticTest->setEnabled(true);
	}
}