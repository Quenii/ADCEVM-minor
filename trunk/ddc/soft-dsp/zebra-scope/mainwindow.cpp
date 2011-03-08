#include "mainwindow.h"
#include "ControlPanel.h"
#include "gkhy/qplotlib/WaveWnd.hpp"
#include "gkhy/qplotlib/FFTWnd.hpp"
#include "gkhy/qplotlib/LogicWaveWnd.hpp"
#include "RegAccess.hpp"
#include "QZebraScopeSettings.h"
#include "QZebraScopeSerializer.h"

#include <QMdiArea>
#include <QSplitter>
#include <QMdiSubWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QHBoxLayout>
#include <QList>
#include <QMessageBox>
#include <QFileDialog>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	adcBoard = AdcBoard::instance(); //new AdcBoard(this);

	ui.setupUi(this);
	

	waveWnd = new gkhy::QPlotLab::WaveWnd();
	ui.dockWidgetWave->setWidget(waveWnd);
	
	fftWnd = new gkhy::QPlotLab::FFTWnd();
	ui.dockWidgetFFT->setWidget(fftWnd);


	logicWaveWnd = new gkhy::QPlotLab::LogicWaveWnd();
	ui.dockWidgetLogicWave->setWidget(logicWaveWnd);

	ui.actionSpectrum->setChecked(true);

	bool okay = connect(adcBoard, SIGNAL(devListChanged(const QList<AdcBoardInfo>&)), ui.controlPanel, SLOT(setDevList(const QList<AdcBoardInfo>&)));
	Q_ASSERT(okay);

	okay = connect(ui.controlPanel, SIGNAL(devSelected(QString)), adcBoard, SLOT(open(QString)));
//	okay = connect(ui.controlPanel, SIGNAL(devSelected(int)), adcBoard, SLOT(open(int)));
	Q_ASSERT(okay);

	okay = connect(adcBoard, SIGNAL(boardReport(const AdcBoardReport&)), this, SLOT(slotShowBoardReport(const AdcBoardReport&)));
	Q_ASSERT(okay);

	okay = connect(this, SIGNAL(settingsLoaded(const SignalSettings&)), 
		ui.controlPanel, SIGNAL(changeSettings(const SignalSettings&)));
	Q_ASSERT(okay);

	okay = connect(this, SIGNAL(settingsLoaded(const AdcSettings&)), 
		ui.controlPanel, SIGNAL(changeSettings(const AdcSettings&)));
	Q_ASSERT(okay);

	okay = connect(this, SIGNAL(adcBoardReportLoaded(const AdcBoardReport&)), this, SLOT(slotShowBoardReport(const AdcBoardReport&)));
	Q_ASSERT(okay);

	setCentralWidget(0);

	createMenus();
}

MainWindow::~MainWindow()
{
	if (regAccess)
		regAccess->deleteLater();
}

void MainWindow::createMenus()
{
	QMenu* menuWindow = ui.menuWindow; 

	menuWindow->addAction(ui.dockWidgetControlPanel->toggleViewAction());		
	menuWindow->addAction(ui.dockWidgetWave->toggleViewAction());	
	menuWindow->addAction(ui.dockWidgetFFT->toggleViewAction());	
	menuWindow->addAction(ui.dockWidgetLogicWave->toggleViewAction());	

	connect(ui.action_AboutAdcAnalyzer, SIGNAL(triggered()), this, SLOT(slotShowAbout()));
}

static QString getSettingsFileName(QString adcDataFileName)
{
	QFileInfo fi(adcDataFileName);
	QString settingsFileName = QDir(fi.dir()).absoluteFilePath(fi.completeBaseName() + ".ini");
	return settingsFileName;
}

static QString make_dot_adc_file_name(QString fn)
{
	if (! fn.endsWith(".adc", Qt::CaseInsensitive)) 
		fn += ".adc"; // default

	return fn;
}

void MainWindow::on_actionLoadData_triggered(bool checked /*= false*/)
{
	QString fileName = QFileDialog::getOpenFileName(
		this, tr("Open File..."), "", tr("ADC Samples (*.adc)"));
	if (!fileName.isEmpty())
	{
		fileName = make_dot_adc_file_name(fileName);
		QString settingsFileName = getSettingsFileName(fileName);
		if (QFile::exists(settingsFileName))
		{
			QZebraScopeSettings settings(settingsFileName, QZebraScopeSettings::IniFormat, 0);			
			SignalSettings signalSettings;
			AdcSettings adcSettings;

			settings.signalSettings(signalSettings);
			settings.adcSettings(adcSettings);

			emit settingsLoaded(adcSettings);
			emit settingsLoaded(signalSettings);		
		}		

		QZebraScopeSerializer serializer(fileName);
		if (serializer.open(QZebraScopeSerializer::ReadOnly))
		{
			AdcBoardReport report;
			if (serializer.deserialize(report))
			{
				emit adcBoardReportLoaded(report);
			}
		}
	}
}

void MainWindow::on_actionSaveData_triggered(bool checked /* = false */)
{
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save as..."),
		QString(), tr("ADC Samples (*.adc)"));

	if (!fileName.isEmpty())
	{
		fileName = make_dot_adc_file_name(fileName);

		QZebraScopeSettings settings;
		SignalSettings signalSettings;
		AdcSettings adcSettings;
		settings.signalSettings(signalSettings);
		settings.adcSettings(adcSettings);

		QString settingsFileName = getSettingsFileName(fileName);
		QZebraScopeSettings toSave(settingsFileName, QSettings::IniFormat, 0);
		toSave.setSignalSettings(signalSettings);
		toSave.setAdcSettings(adcSettings);

		QZebraScopeSerializer reportFile(fileName);
		if (reportFile.open(QZebraScopeSerializer::Truncate | QZebraScopeSerializer::WriteOnly))
			reportFile.serialize(AdcBoard::instance()->reportRef());

	}
}

void MainWindow::slotShowWaveWnd()
{
	waveWnd->show();
}

void MainWindow::slotShowFFtWnd()
{
	fftWnd->show();
}

void MainWindow::slotShowControlPanel()
{
	ui.controlPanel->show();
}

void MainWindow::slotShowAbout()
{
	QMessageBox::about(this, tr("About CETC58 ADC Analyzer"),
		tr("<br><b>ADC Analyzer</b> is designed to work with the USB-ADC evaluation board.<br><br><div align=center>Copyright (c) CETC58, 2010</div><br> "));
}

void MainWindow::slotShowBoardReport(const AdcBoardReport& report)
{
	waveWnd->update(report.tdReport.xaxis, report.tdReport.samples);
	fftWnd->update(report.fdReport.xaxis, report.fdReport.Spectrum);
	logicWaveWnd->update(report.tdReport.rawSamples);
	ui.controlPanel->updateReport(report);
}

void MainWindow::on_actionSpiCtrl_triggered(bool checked)
{
	if (!regAccess)
	{
		regAccess = new RegAccess(0, 0);
		regAccess->setAttribute(Qt::WA_DeleteOnClose,true);
	}

	regAccess->show();
}

void MainWindow::on_actionSpectrum_toggled(bool checked)
{
	if (checked)
	{
		ui.actionLogic->setChecked(!checked);
		ui.dockWidgetWave->setVisible(checked);
		ui.dockWidgetFFT->setVisible(checked);
		ui.dockWidgetLogicWave->setVisible(!checked);
	}
};

void MainWindow::on_actionLogic_toggled(bool checked)
{
	if (checked)
	{
		ui.actionSpectrum->setChecked(!checked);
		ui.dockWidgetWave->setVisible(checked);
		ui.dockWidgetFFT->setVisible(!checked);
		ui.dockWidgetLogicWave->setVisible(checked);
	}
};

void MainWindow::on_menuSettings_hovered(QAction * action)
{
	bool running = AdcBoard::instance()->isRunning();
	ui.actionSpiCtrl->setEnabled(!running);
	ui.actionFftDepth->setEnabled(!running);
}

