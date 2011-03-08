#ifndef SIGNALSETTINGSDIALOG_H
#define SIGNALSETTINGSDIALOG_H

#include <QDialog>
#include "ui_SignalSettingsDialog.h"
#include "AdcBoardTypes.hpp"

using namespace Ui;

class SignalSettingsDialog : public QDialog, public SignalSettingsDialogClass
{
	Q_OBJECT

public:
	SignalSettingsDialog(QWidget *parent = 0);
	~SignalSettingsDialog();

public:
	void setSettings(const SignalSettings& settings);
	void settings(SignalSettings& settings);
};

#endif // SIGNALSETTINGSDIALOG_H
