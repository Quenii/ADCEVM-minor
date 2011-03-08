#ifndef ELEPHANT_H
#define ELEPHANT_H

#include <QtGui/QMainWindow>
#include "ui_qelephantmainwindow.h"

class QMdiSubWindowEx;

class QElephantMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	QElephantMainWindow(QWidget *parent = 0, Qt::WFlags flags = 0);
	~QElephantMainWindow();

private:
	void addMdiWindow(QWidget* widget, QPushButton* btn = 0);

private slots:
	void on_actionAbout_triggered(bool checked);

private:
	Ui::MainWindow ui;
};

#endif // ELEPHANT_H
