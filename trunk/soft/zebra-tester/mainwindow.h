#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"

class QPushButton;
class QWidget;
class QMdiSubWindowEx;
class QCloseEvent;
class QPowerMonitor;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

public:
	void loadSettings();
	void saveSettings();

public slots:
	void on_actionDacType_triggered(bool checked);
	void on_actionClockFrequency_triggered(bool checked);
	void on_actionAboutCETC58DACAnalyzer_triggered(bool checked);

protected:
	void closeEvent(QCloseEvent *event);

private:
	Ui::MainWindowClass ui;
	QPowerMonitor* m_powerMonitorWidget;
};

#endif // MAINWINDOW_H
