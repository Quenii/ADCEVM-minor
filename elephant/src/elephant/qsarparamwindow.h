#ifndef QSARPARAMWINDOW_H
#define QSARPARAMWINDOW_H

#include "ui_qsarparamwindow.h"
#include "qsartypes.h"

#include <QWidget>

class QSarParamWindow : public QWidget
{
	Q_OBJECT

public:
	QSarParamWindow(QWidget *parent = 0);
	~QSarParamWindow();

public slots:
	void get(SarConfig& settings, int& ret);
	void set(const SarConfig& settings, int& ret);
	void set(const SarStatus& status, int& ret);

private:
	Ui::QSarParamWindowClass ui;
};

#endif // QSARPARAMWINDOW_H
