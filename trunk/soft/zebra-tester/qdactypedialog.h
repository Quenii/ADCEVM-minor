#ifndef QDACTYPEDIALOG_H
#define QDACTYPEDIALOG_H

#include "ui_qdactypedialog.h"
#include "types.h"

#include <QDialog>


class QDacTypeDialog : public QDialog
{
	Q_OBJECT

public:
	QDacTypeDialog(QWidget *parent = 0);
	~QDacTypeDialog();

protected:
	void accept();

private:
	void setSettings(const DacTypeSettings& val);

private:
	Ui::QDacTypeDialogClass ui;
};

#endif // QDACTYPEDIALOG_H
