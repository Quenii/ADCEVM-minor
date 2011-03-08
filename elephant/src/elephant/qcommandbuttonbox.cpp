#include "QCommandButtonBox.h"

QCommandButtonBox::QCommandButtonBox(QWidget* parent /*= 0*/, Qt::WindowFlags flags /*= 0*/)
: QWidget(parent, flags)
{
	setupUi(this);
	
	configPushButton->setEnabled(true);
	applyPushButton->setEnabled(false);
	abortPushButton->setEnabled(false);

	m_bConfiguring = false;
}

QCommandButtonBox::~QCommandButtonBox(void)
{
}

bool QCommandButtonBox::isConfiguring()
{
	return m_bConfiguring;
}
 
void QCommandButtonBox::on_configPushButton_clicked()
{
	bool ok = true;
	emit configClicked(ok);
	if (ok)
	{
		configPushButton->setEnabled(false);
		applyPushButton->setEnabled(true);
		abortPushButton->setEnabled(true);

		m_bConfiguring = true;
	}
}

void QCommandButtonBox::on_applyPushButton_clicked()
{
	bool ok = true;
	emit applyClicked(ok);
	if (ok)
	{
		configPushButton->setEnabled(true);
		applyPushButton->setEnabled(false);
		abortPushButton->setEnabled(false);

		m_bConfiguring = false;
	}
}

void QCommandButtonBox::on_abortPushButton_clicked()
{
	bool ok = true;
	emit abortClicked(ok);
	if (ok)
	{
		configPushButton->setEnabled(true);
		applyPushButton->setEnabled(false);
		abortPushButton->setEnabled(false);

		m_bConfiguring = false;
	}
}