#ifndef ADCSETTINGSDIALOG_H
#define ADCSETTINGSDIALOG_H

#include <QDialog>
#include "ui_AdcSettingsDialog.h"
#include "AdcBoardTypes.hpp"

using namespace Ui;

class AdcSettingsDialog : public QDialog, public AdcSettingsDialogClass
{
	Q_OBJECT

public:
	AdcSettingsDialog(QWidget *parent = 0);
	~AdcSettingsDialog();

public:
	void setSettings(const AdcSettings& settings);
	void settings(AdcSettings& settings);
};

#endif // ADCSETTINGSDIALOG_H
