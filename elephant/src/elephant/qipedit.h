#ifndef QIPEdit_H
#define QIPEdit_H

#include "ui_qipedit.h"

#include <QLineEdit>

class QIPEdit : public QLineEdit
{
	Q_OBJECT

public:
	QIPEdit(QWidget *parent = 0);
	~QIPEdit();

private:
	Ui::QIpEditClass ui;
};

#endif // QIPEdit_H
