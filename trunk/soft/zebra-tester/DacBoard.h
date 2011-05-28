#pragma once
#include "Board.h"

#include "types.h"

class QTimerEvent;

class DacBoard : public Board
{
	Q_OBJECT
public:
	virtual ~DacBoard(void);

private:
	Q_DISABLE_COPY(DacBoard)
	DacBoard(QObject* parent = 0);

signals:
	void powerMonitorDataUpdated(const PowerMonitorData& data);

public:
	static DacBoard* instance() 
	{ 
		static DacBoard inst;
		return &inst; 
	}

	bool setDacTypeSettings(const DacTypeSettings& settings);

	bool readPowerMonitorData(PowerMonitorData& powerStatus);
	bool setDacOutput(unsigned short val);

private:
	void timerEvent(QTimerEvent * e);
};
