#pragma once

#include "ui_qcommandbuttonbox.h"
#include <QWidget>

class QCommandButtonBox : public QWidget, private Ui::QCommandButtonBoxClass
{
	Q_OBJECT

public:
	QCommandButtonBox(QWidget* parent = 0, Qt::WindowFlags flags = 0);
	virtual ~QCommandButtonBox(void);

public:
	bool isConfiguring();

signals:
	void abortClicked(bool& ok);
	void configClicked(bool& ok);
	void applyClicked(bool& ok);

private slots:
	void on_abortPushButton_clicked();
	void on_configPushButton_clicked();
	void on_applyPushButton_clicked();
private:
	bool m_bConfiguring;
};
