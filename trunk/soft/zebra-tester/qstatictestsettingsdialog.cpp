#include "qstatictestsettingsdialog.h"
#include "dacanalyzersettings.h"

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


void QStaticTestSettingsDialog::accept()
{
	StaticTestSettings val;

	val.averageLevel = ui.lineEditAverageLevel->text().toInt();
	val.step2n = ui.lineEditStep2n->text().toInt();

	DacAnalyzerSettings().setStaticTestSettings(val);
	QDialog::accept();
}