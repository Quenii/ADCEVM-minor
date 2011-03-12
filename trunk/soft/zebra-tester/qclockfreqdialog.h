#ifndef QCLOCKFREQDIALOG_H
#define QCLOCKFREQDIALOG_H

#include <QDialog>
#include "ui_qclockfreqdialog.h"

class QClockFreqDialog : public QDialog
{
	Q_OBJECT

public:
	QClockFreqDialog(QWidget *parent = 0);
	~QClockFreqDialog();

public:
	float clockFreq() { return m_clockFreq; }

protected:
	void accepted();

private:
	void setClockFreq(const float& val);

private:
	Ui::QClockFreqDialogClass ui;
	float m_clockFreq;
};

#endif // QCLOCKFREQDIALOG_H
