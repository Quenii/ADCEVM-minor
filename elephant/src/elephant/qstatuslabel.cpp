#include "QStatusLabel.h"

#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>

QStatusLabel::QStatusLabel(QWidget *parent)
: QWidget(parent)
{	
	ui.setupUi(this);

	setStatus(QStatusLabel::Disabled);	
	ui.label->hide();
}

QStatusLabel::~QStatusLabel()
{

}

void QStatusLabel::setColor(Color color)
{
	QString styleStr;
	switch (color)
	{
	case Red:
		//if (!stored()) store();
		styleStr = 
			"color:rgb(255,255,255);" 
			"background-color:rgb(255,0,0);";
		break;

	case Yellow:
		//if (!stored()) store();
		styleStr =
			"color:rgb(0,0,0);"
			"background-color:rgb(255,255,0);";
		break;

	case Green:
		//if (!stored()) store();
		styleStr = 
			"color:rgb(0,0,0);"
			"background-color:rgb(85, 255, 127);";
		break;

	case Normal:
		styleSheet();
		break;

	default:
		break;
	}

	ui.lineEdit->setStyleSheet(styleStr);	
}

void QStatusLabel::setText(const QString& text)
{
	ui.lineEdit->setText(text);	
}


void QStatusLabel::setLabel(const QString& text)
{
	ui.label->setText(text);
	ui.label->show();
}

void QStatusLabel::setStatus(Status status)
{
	if (m_status == status) return;

	m_status = status; 

	switch (status)
	{
	case Disabled:
		setText(tr("Disabled"));
		setColor(Red);
		break;

	case Functions:
		setText(tr("Functions"));
		setColor(Green);
		break;

	case Unconnected:
		setText(tr("Unconnected"));
		setColor(Red);
		break;

	case Connecting:
		setText(tr("Connecting"));
		setColor(Yellow);
		break;

	case Connected:
		setText(tr("Connected"));
		setColor(Green);
		break;

	case Alarm:
		setText(tr("Alarm"));
		setColor(Yellow);
		break;

	case Search:
		setText(tr("Search"));
		setColor(Yellow);
		break;

	case Check:
		setText(tr("Check"));
		setColor(Yellow);
		break;

	case Acquisition:
		setText(tr("Acquisition"));
		setColor(Yellow);
		break;

	case Unlocked:
		setText(tr("Unlocked"));
		setColor(Red);
		break;

	case Locked:
		setText(tr("Locked"));
		setColor(Green);
		break;

	case NotAvailable:
		setText(tr("N/A"));
		setColor(Yellow);
		break;


	case Okay:
		setText(tr("Okay"));
		setColor(Green);
		break;

	default:
		break;
	}	
}
