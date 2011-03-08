#ifndef ADCSETTINGSWIDGET_H
#define ADCSETTINGSWIDGET_H

#include <QWidget>
#include "ui_AdcSettingsWidget.h"
#include "AdcSettingsDialog.h"

using namespace Ui;

class AdcSettingsWidget : public QWidget, public AdcSettingsWidgetClass
{
	Q_OBJECT

public:
	AdcSettingsWidget(QWidget *parent = 0);
	~AdcSettingsWidget();

public slots:
	void setSettings(const AdcSettings& settings);
public:
	void settings(AdcSettings& settings);

signals:
	void settingsChanged();

private slots:
	void on_pushButtonChangeSettings_clicked();

private:
	AdcSettings m_settings;
};

#endif // ADCSETTINGSWIDGET_H
