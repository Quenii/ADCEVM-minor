#ifndef SIGNALSETTINGSWIDGET_H
#define SIGNALSETTINGSWIDGET_H

#include <QWidget>
#include "ui_SignalSettingsWidget.h"
#include "AdcBoardTypes.hpp"

using namespace Ui;

class SignalSettingsWidget : public QWidget, public SignalSettingsWidgetClass
{
	Q_OBJECT

public:
	SignalSettingsWidget(QWidget *parent = 0);
	~SignalSettingsWidget();

public:
	void settings(SignalSettings& settings);
public slots:
	void setSettings(const SignalSettings& settings);

signals:
	void settingsChanged();

private slots:
	void on_pushButtonChangeSettings_clicked();

private:
	SignalSettings m_settings;

};

#endif // SIGNALSETTINGSWIDGET_H
