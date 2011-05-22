#include "global.h"

#include <QLineEdit>
#include <QApplication>
#include <QMessageBox>

bool checkInputValidity(QLineEdit* input)
{
	if (!input->hasAcceptableInput())
	{
		QMessageBox::warning(input, QApplication::tr("Warning"), QApplication::tr("At lease one input is invalid."));
		input->setFocus();
		return false;
	}

	return true;
}

void claimFailedToStartTester()
{
	QMessageBox::warning(0, 
		QString::fromLocal8Bit("����"),
		QString::fromLocal8Bit("��ʼ����ʧ�ܣ��忨��ռ�á�"));
}