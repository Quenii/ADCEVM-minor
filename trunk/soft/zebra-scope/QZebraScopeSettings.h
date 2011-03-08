#pragma once

#include <QSettings>

#include "AdcBoardTypes.hpp"

class QZebraScopeSettings : public QSettings
{
public:
	QZebraScopeSettings(const QString & fileName, Format format, QObject * parent = 0);
	QZebraScopeSettings(QObject * parent = 0);
	~QZebraScopeSettings(void);

public:
	void setAdcSettings(const AdcSettings& data);
	void adcSettings(AdcSettings& data);

	void setSignalSettings(const SignalSettings& data);
	void signalSettings(SignalSettings& data);
};
