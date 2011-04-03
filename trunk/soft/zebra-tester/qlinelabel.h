#ifndef QLINELABEL_H
#define QLINELABEL_H

#include <QLabel>
#include "ui_qlinelabel.h"

class QLineLabel : public QLabel
{
	Q_OBJECT

public:
	QLineLabel(QWidget *parent = 0);
	~QLineLabel();

public:
	QSize sizeHint () const;
	QSize minimumSizeHint () const;

private:
	Ui::QLineLabelClass ui;
	QSize m_sizeHint;
	QSize m_minimumSizeHint;
};

#endif // QLINELABEL_H
