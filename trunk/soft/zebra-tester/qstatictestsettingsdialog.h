#ifndef QSTATICTESTSETTINGSDIALOG_H
#define QSTATICTESTSETTINGSDIALOG_H

#include "types.h"

#include <QDialog>
#include "ui_qstatictestsettingsdialog.h"


class QStaticTestSettingsDialog : public QDialog
{
	Q_OBJECT

public:
	QStaticTestSettingsDialog(QWidget *parent = 0);
	~QStaticTestSettingsDialog();

protected:
	void accept();

private:
	Ui::QStaticTestSettingsDialogClass ui;
};

#endif // QSTATICTESTSETTINGSDIALOG_H
