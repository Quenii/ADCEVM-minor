#include "qtestwidget.h"
#include "qstatictestsettingsdialog.h"

#include <QTimer>
#include <QMessageBox>

static void updateStartStopButtonText(QPushButton* button, unsigned int state)
{
	button->setText(state ? 
		QString::fromLocal8Bit("Í£Ö¹") : QString::fromLocal8Bit("¿ªÊ¼"));

}

QTestWidget::QTestWidget(QWidget *parent)
	: QWidget(parent)
{
	m_state.testStarted = 0;
	setupUi(this);

	QTimer::singleShot(0, this, SLOT(on_tabWidget_currentChanged()));	

	updateStartStopButtonText(pushButtonStartStaticTest, m_state.staticTestStarted);
	updateStartStopButtonText(pushButtonStartDynamicTest, m_state.dynamicTestStarted);
	updateStartStopButtonText(pushButtonStartInstTest, m_state.instTestStarted);
	updateStartStopButtonText(pushButtonStartCalibration, m_state.calibrationStarted);
}

QTestWidget::~QTestWidget()
{

}

void QTestWidget::anotherTestIsRunningWarning()
{
	QMessageBox::warning(this, tr("Warning"),
		tr("Another test is already running. To start this one, stop it first."));
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
	QStaticTestSettingsDialog dlg;
	if (QDialog::Accepted == dlg.exec())
	{
		
	}
}

void QTestWidget::on_pushButtonStartStaticTest_clicked()
{
	if (m_state.testStarted && !m_state.staticTestStarted)
	{
		anotherTestIsRunningWarning();
		return ;
	}

	if (!m_state.staticTestStarted)
	{
		
	}
	else
	{

	}

	m_state.staticTestStarted = ~m_state.staticTestStarted;
	updateStartStopButtonText(pushButtonStartStaticTest, m_state.staticTestStarted);
}


void QTestWidget::on_pushButtonStartDynamicTest_clicked()
{
	if (m_state.testStarted && !m_state.dynamicTestStarted)
	{
		anotherTestIsRunningWarning();
		return ;
	}

	if (!m_state.dynamicTestStarted)
	{

	}
	else
	{

	}

	m_state.dynamicTestStarted = ~m_state.dynamicTestStarted;
	updateStartStopButtonText(pushButtonStartDynamicTest, m_state.dynamicTestStarted);

}

void QTestWidget::on_pushButtonStartInstTest_clicked()
{
	if (m_state.testStarted && !m_state.instTestStarted)
	{
		anotherTestIsRunningWarning();
		return ;
	}

	if (!m_state.instTestStarted)
	{

	}
	else
	{

	}

	m_state.instTestStarted = ~m_state.instTestStarted;
	updateStartStopButtonText(pushButtonStartInstTest, m_state.instTestStarted);

}

void QTestWidget::on_pushButtonStartCalibration_clicked()
{
	if (m_state.testStarted && !m_state.calibrationStarted)
	{
		anotherTestIsRunningWarning();
		return ;
	}

	if (!m_state.calibrationStarted)
	{

	}
	else
	{

	}

	m_state.calibrationStarted = ~m_state.calibrationStarted;
	updateStartStopButtonText(pushButtonStartCalibration, m_state.calibrationStarted);

}