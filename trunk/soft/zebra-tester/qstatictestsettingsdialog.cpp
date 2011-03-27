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
	ui.lineEditStep2n->setText(QString::number(val.step2n));
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

	if (! validate(ui.lineEditStep2n)) return ;
	val.step2n = ui.lineEditStep2n->text().toInt();

	DacAnalyzerSettings().setStaticTestSettings(val);
	QDialog::accept();
}