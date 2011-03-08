#ifndef DYNAMICTESTWINDOW_H
#define DYNAMICTESTWINDOW_H

#include <QWidget>
#include "ui_dynamictestwindow.h"

class DynamicTestWindow : public QWidget
{
	Q_OBJECT

public:
	DynamicTestWindow(QWidget *parent = 0);
	~DynamicTestWindow();

private:
	Ui::DynamicTestWindowClass ui;
};

#endif // DYNAMICTESTWINDOW_H
