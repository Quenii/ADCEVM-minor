#ifndef QDYNAMICTESTSETTINGSDIALOG_H
#define QDYNAMICTESTSETTINGSDIALOG_H

#include "types.h"

#include <QDialog>
#include "ui_qdynamictestdialog.h"


class QDynamicTestSettingsDialog : public QDialog
{
	Q_OBJECT

public:
	QDynamicTestSettingsDialog(QWidget *parent = 0);
	~QDynamicTestSettingsDialog();

protected:
	void accept();

private:
	bool validate(QLineEdit* lineEdit);

private:
	Ui::QDynamicTestDialogClass ui;
};

#endif // QDYNAMICTESTSETTINGSDIALOG_H
