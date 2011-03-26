#include "qcentralwidget.h"

QCentralWidget::QCentralWidget(QWidget *parent)
	: QStackedWidget(parent)
{
	ui.setupUi(this);
}

QCentralWidget::~QCentralWidget()
{

}
