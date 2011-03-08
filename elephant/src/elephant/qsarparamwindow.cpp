#include "qsarparamwindow.h"

QSarParamWindow::QSarParamWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

QSarParamWindow::~QSarParamWindow()
{

}

void QSarParamWindow::get(SarConfig& settings, int& ret)
{

}

void QSarParamWindow::set(const SarConfig& settings, int& ret)
{

}

void QSarParamWindow::set(const SarStatus& status, int& ret)
{
	QString time = QString("%1:%2:%3")
		.arg(status.secondElapsed / 3600)
		.arg(status.secondElapsed % 3600 / 60)
		.arg(status.secondElapsed % 60);

	ui.lineEditTimeElapsed->setText(time);

	ret  = 1;	
}