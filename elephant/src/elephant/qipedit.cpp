#include "QIPEdit.h"
#include "QIpValidator.h"

QIPEdit::QIPEdit(QWidget *parent)
	: QLineEdit(parent)
{
	ui.setupUi(this);

	setValidator(new QIPValidator(this));
}

QIPEdit::~QIPEdit()
{
}
