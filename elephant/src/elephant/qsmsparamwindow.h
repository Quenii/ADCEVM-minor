#ifndef QSMSPARAMWINDOW_H
#define QSMSPARAMWINDOW_H

#include "ui_qsmsparamwindow.h"
#include "qsmstypes.h"

#include <QWidget>

class QSmsParamWindow : public QWidget
{
	Q_OBJECT

public:
	QSmsParamWindow(QWidget *parent = 0);
	~QSmsParamWindow();

public slots:
	void get(SmsConfig& settings, int& ret);
	void set(const SmsConfig& settings, int& ret);
	void set(const SmsStatus& status, int& ret);

private:
	Ui::QSmsParamWindowClass ui;
};

#endif // QSMSPARAMWINDOW_H
