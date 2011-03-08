#include "qdactypewidget.h"

QDacTypeWidget::QDacTypeWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

QDacTypeWidget::~QDacTypeWidget()
{

}

void QDacTypeWidget::setDacTypeSettings(const DacTypeSettings& val)
{
	m_dacTypeSettings = val;

	ui.lineEditDacType->setText(val.type);
	ui.lineEditVa->setText(QString("%L1").arg(val.va));
	ui.lineEditVd->setText(QString("%L1").arg(val.vd));
	ui.lineEditBitCount->setText(QString("%1").arg(val.bitCount));
	ui.lineEditRefVolt->setText(QString("%L1").arg(val.refVolt));
	ui.lineEditPhase->setText(QString("%L1").arg(val.phase));
}
