#include "qstatictestsettingsdialog.h"
#include "dacanalyzersettings.h"
#include "global.h"

#include <QMessageBox>

QStaticTestSettingsDialog::QStaticTestSettingsDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	ui.lineEditAverageLevel->setValidator(new QIntValidator(1, 999, this));
	ui.lineEditStep2n->setValidator(new QIntValidator(1, 32, this));
	
	StaticTestSettings val =  DacAnalyzerSettings().staticTestSettings();
	ui.lineEditAverageLevel->setText(QString::number(val.averageLevel));
	ui.lineEditStep2n->setText(QString::number(val.nplc));
	ui.lineEditLeft->setText(QString::number(val.left));
	ui.lineEditRight->setText(QString::number(val.right));
}

QStaticTestSettingsDialog::~QStaticTestSettingsDialog()
{

}

bool QStaticTestSettingsDialog::validate(QLineEdit* inputFreqlineEdit)
{
	return checkInputValidity(inputFreqlineEdit);
}

void QStaticTestSettingsDialog::accept()
{
	StaticTestSettings val;

	if (! validate(ui.lineEditAverageLevel)) return ;
	val.averageLevel = ui.lineEditAverageLevel->text().toInt();

//	if (! validate(ui.lineEditStep2n)) return ;
	val.nplc = ui.lineEditStep2n->text().toInt();

	if (! validate(ui.lineEditLeft)) return;
	val.left = ui.lineEditLeft->text().toInt();
	
	if (! validate(ui.lineEditRight)) return;
	val.right = ui.lineEditRight->text().toInt();
	

	DacAnalyzerSettings().setStaticTestSettings(val);
	QDialog::accept();
}