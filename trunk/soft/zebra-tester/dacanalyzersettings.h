#pragma once

#include "types.h"

#include <QSettings>

class DacAnalyzerSettings
{
public:
	DacAnalyzerSettings(void);
	virtual ~DacAnalyzerSettings(void);

public:
	DacTypeSettings dacTypeSettings() const;
	void setDacTypeSettings(const DacTypeSettings& val);
	
	StaticTestSettings staticTestSettings() const;
	void setStaticTestSettings(const StaticTestSettings& val);
	
	float clockFreq() const;
	void setClockFreq(const float& val);
	
	QPoint powerMonitorWidgetPos() const;
	void setPowerMonitorWidgetPos(const QPoint& val);

	bool powerMonitorWidgetVisible() const;
	void setPowerMonitorWidgetVisible(const bool& val);



private:
	QSettings m_s;
};
