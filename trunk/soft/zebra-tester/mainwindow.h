#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"

class QPushButton;
class QWidget;
class QMdiSubWindowEx;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

public:
	//QMdiSubWindowEx* addMdiWindow(QWidget* widget, QPushButton* btn);

public slots:
	void on_actionDacType_triggered(bool checked);
	void on_actionClockFrequency_triggered(bool checked);
	void on_actionAboutCETC58DACAnalyzer_triggered(bool checked);

private:
	Ui::MainWindowClass ui;
};

#endif // MAINWINDOW_H
