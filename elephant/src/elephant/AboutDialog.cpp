#include "AboutDialog.h"
#include "ui_AboutDialog.h"

AboutDialog::AboutDialog(QWidget *parent)
	: QDialog(parent)
{
	ui = new Ui::AboutDialogClass();
	ui->setupUi(this);
}

AboutDialog::~AboutDialog()
{
	delete ui;
}

void AboutDialog::on_pushButtonOk_clicked()
{
	close();
}