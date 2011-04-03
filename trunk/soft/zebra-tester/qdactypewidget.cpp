#include "qdactypewidget.h"
#include "dacanalyzersettings.h"

QDacTypeWidget::QDacTypeWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	reloadSettings();

}

QDacTypeWidget::~QDacTypeWidget()
{

}

void QDacTypeWidget::reloadSettings()
{
	const DacTypeSettings& val = DacAnalyzerSettings().dacTypeSettings();

	ui.dacType->setText(val.type);
	ui.va->setText(QString("%L1").arg(val.va));
	ui.vd->setText(QString("%L1").arg(val.vd));
	ui.bitCount->setText(QString("%1").arg(val.bitCount));
	ui.refVolt->setText(QString("%L1").arg(val.refVolt));
	ui.phase->setText(QString("%L1").arg(val.phase));
}
