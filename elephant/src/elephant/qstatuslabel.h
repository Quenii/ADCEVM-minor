#ifndef QStatusLabel_H
#define QStatusLabel_H

#include "ui_qstatuslabel.h"

#include <QWidget>

class QStatusLabel : public QWidget
{
	Q_OBJECT

public:
	enum Status
	{				
		Disabled,		
		Functions,

		Unconnected,
		Connecting,
		Connected,

		Search,
		Check,
		Acquisition,

		Unlocked,
		Locked,
		NotAvailable,

		Alarm,
		Okay
	};

	enum Color 
	{
		Normal,
		Red,
		Yellow,
		Green
	};


public:
	QStatusLabel(QWidget * parent = 0);
	~QStatusLabel();

public:
	void setStatus(Status status);
	Status status() { return m_status; }

	void setLabel(const QString& text);

private:
	void setColor(Color color);	
	void setText(const QString& text);

private:
	Status m_status;
	Ui::StatusLabelClass ui;
};

// 	}
// }

#endif // QStatusLabel_H
