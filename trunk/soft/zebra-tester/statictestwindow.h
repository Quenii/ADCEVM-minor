#ifndef STATICTESTWINDOW_H
#define STATICTESTWINDOW_H

#include <QWidget>
#include "ui_statictestwindow.h"

class StaticTestWindow : public QWidget
{
	Q_OBJECT

public:
	StaticTestWindow(QWidget *parent = 0);
	~StaticTestWindow();

private:
	Ui::StaticTestWindowClass ui;
};

#endif // STATICTESTWINDOW_H
