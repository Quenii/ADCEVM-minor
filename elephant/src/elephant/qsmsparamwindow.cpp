#include "qsmsparamwindow.h"

QSmsParamWindow::QSmsParamWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setWindowTitle(tr("Storage Emulator"));
}

QSmsParamWindow::~QSmsParamWindow()
{

}

void QSmsParamWindow::get(SmsConfig& settings, int& ret)
{

}

void QSmsParamWindow::set(const SmsConfig& settings, int& ret)
{

}

void QSmsParamWindow::set(const SmsStatus& status, int& ret)
{

}