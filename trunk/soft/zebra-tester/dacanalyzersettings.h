#pragma once

#include "qdactypedialog.h"

#include <QSettings>

class DacAnalyzerSettings
{
public:
	DacAnalyzerSettings(void);
	virtual ~DacAnalyzerSettings(void);

public:
	void setDacTypeSettings(const DacTypeSettings& val);
	DacTypeSettings dacTypeSettings() const;

	void setClockFreq(const float& val);
	float clockFreq() const;

private:
	QSettings m_s;
};
