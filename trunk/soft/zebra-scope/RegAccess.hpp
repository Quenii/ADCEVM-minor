#pragma once

#include "ui_RegAccess.h"
#include "AdcBoard.hpp"

#include <QWidget>
#include <QPointer>
#include <QList>
#include <QSettings>

class QModelIndex;
class QStandardItemModel;
class RegAccessItem;

class RegAccess : public QWidget , public Ui::FormRegAccess
{
	Q_OBJECT

public:
	RegAccess(QWidget *parent = 0, Qt::WFlags flags = 0);
	virtual ~RegAccess();

private:
	void back2Top();

	// return values:
	// -1 - failed
	// 0 - end of list reached
	// 1 - succeeded
	int nextStep();

	void readSettings(QSettings& settings);
	void writeSettings(QSettings& settings);

public slots:
	void slotRegAccessItemStateChanged(QWidget* item);
	void on_pushButtonResetCircuit_clicked();
	void on_pushButtonOpenScan_clicked();
	void on_pushButtonAutoExec_clicked();
	//void on_sbSampleRate_valueChanged();
	void on_pushButtonStep_clicked();
	void on_pushButtonBack2Top_clicked();
	void on_pushButtonSaveSettings_clicked();
	void on_pushButtonReadSettings_clicked();

private:
	QVector<RegAccessItem*> m_regAccessItems;
	int m_currentStep;
	QSettings m_settings;
	bool m_bEnable_SlotRegAccessItemStateChanged;
};

