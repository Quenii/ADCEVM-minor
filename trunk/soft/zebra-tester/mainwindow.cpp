#include "mainwindow.h"
#include "qmdisubwindowex.h"
#include "qdactypedialog.h"
#include "qclockfreqdialog.h"
#include "DacAnalyzerSettings.h"

#include <QPushButton>
#include <QList>
#include <QPointer>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.menuWindow->addAction(ui.dockWidgetConsole->toggleViewAction());
	ui.menuWindow->addAction(ui.dockWidgetPowerMonitor->toggleViewAction());

	loadSettings();
}

MainWindow::~MainWindow()
{
	
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	saveSettings();
}

void MainWindow::loadSettings()
{
	DacAnalyzerSettings s;	
	ui.dockWidgetPowerMonitor->move(s.powerMonitorWidgetPos());
}

void MainWindow::saveSettings()
{
	DacAnalyzerSettings s;

	s.setPowerMonitorWidgetPos(ui.dockWidgetPowerMonitor->pos());
}

void MainWindow::on_actionDacType_triggered(bool checked)
{
	QDacTypeDialog dlg;
	if (QDialog::Accepted == dlg.exec())
	{
		ui.dacTypeWidget->setDacTypeSettings(DacAnalyzerSettings().dacTypeSettings());
	}
}

void MainWindow::on_actionClockFrequency_triggered(bool checked)
{
	QClockFreqDialog dlg;
	if (QDialog::Accepted == dlg.exec())
	{
		ui.clockFreqWidget->setClockFreq(DacAnalyzerSettings().clockFreq());
	}
}

void MainWindow::on_actionAboutCETC58DACAnalyzer_triggered(bool checked)
{
	QMessageBox::about(this, tr("About CETC58 DAC Analyzer"),
		tr("<br><b>DAC Analyzer</b> is designed to work with the USB-DAC evaluation board.<br><br><div align=center>Copyright (c) CETC58, 2011</div><br> "));
}

