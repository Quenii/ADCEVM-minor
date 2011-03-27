#include "qtestwidget.h"

#include <QTimer>

QTestWidget::QTestWidget(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);

	QTimer::singleShot(0, this, SLOT(on_tabWidget_currentChanged()));		
}

QTestWidget::~QTestWidget()
{

}

void QTestWidget::on_tabWidget_currentChanged(/*int index*/)
{
	Mode mode;
	QWidget* current = tabWidget->currentWidget();
	if (current == tabStaticTest)
		mode = StaticTest;
	else if (current == tabDynamicTest)
		mode = DynamicTest;
	else if (current == tabInstTest)
		mode = InstantTest;
	else if (current == tabCalibration)
		mode = Calibration;
	else
		Q_ASSERT(!"Invalid contidion!");  

	emit modeActivated(mode);
}

void QTestWidget::on_pushButtonSetStaticTest_clicked()
{

}

void QTestWidget::on_pushButtonStartStaticTest_clicked()
{

}