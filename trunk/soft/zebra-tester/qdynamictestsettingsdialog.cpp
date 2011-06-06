#include "qdynamictestsettingsdialog.h"
#include "dacanalyzersettings.h"
#include "global.h"

#include <QMessageBox>

QDynamicTestSettingsDialog::QDynamicTestSettingsDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	//ui.lineEditAverageLevel->setValidator(new QIntValidator(1, 999, this));
	//ui.lineEditStep2n->setValidator(new QIntValidator(1, 32, this));
	
	DynamicTestSettings val =  DacAnalyzerSettings().dynamicTestSettings();
	ui.
	//ui.lineEditAverageLevel->setText(QString::number(val.averageLevel));
	//ui.lineEditStep2n->setText(QString::number(val.step2n));
}

QDynamicTestSettingsDialog::~QDynamicTestSettingsDialog()
{

}

bool QDynamicTestSettingsDialog::validate(QLineEdit* inputFreqlineEdit)
{
	return checkInputValidity(inputFreqlineEdit);
}

void QDynamicTestSettingsDialog::accept()
{
	DynamicTestSettings val;

	//if (! validate(ui.lineEditAverageLevel)) return ;
	//val.averageLevel = ui.lineEditAverageLevel->text().toInt();

	//if (! validate(ui.lineEditStep2n)) return ;
	//val.step2n = ui.lineEditStep2n->text().toInt();

	//if (! validate(ui.lineEditLeft)) return;
	//val.left = ui.lineEditLeft->text().toInt();
	//
	//if (! validate(ui.lineEditRight)) return;
	//val.right = ui.lineEditRight->text().toInt();

	DacAnalyzerSettings().setDynamicTestSettings(val);
	QDialog::accept();
}
