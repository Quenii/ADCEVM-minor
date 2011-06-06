#ifndef QDYNAMICTESTSETTINGSDIALOG_H
#define QDYNAMICTESTSETTINGSDIALOG_H

#include "types.h"

#include <QDialog>
#include "ui_qdynamictestsettingsdialog.h"


class QDynamicTestSettingsDialog : public QDialog
{
	Q_OBJECT

public:
	QDynamicTestSettingsDialog(QWidget *parent = 0);
	~QDynamicTestSettingsDialog();

protected:
	void accept();

private:
	bool validate(QDoubleSpinBox *);
	bool validate(QSpinBox * spinBox);

private:
	Ui::QDynamicTestSettingsDialogClass ui;
};

#endif // QDYNAMICTESTSETTINGSDIALOG_H
