#pragma once

#include "boardapi_global.h"
#include "Board.h"

class QTimerEvent;

struct BOARDAPI_EXPORT PowerMonitorData
{
	float va;
	float vd;
	float ia;
	float id;
	float p;
};

class BOARDAPI_EXPORT DacBoard : public Board
{
	Q_OBJECT
public:
	virtual ~DacBoard(void);

private:
	Q_DISABLE_COPY(DacBoard)
	DacBoard(QObject* parent = 0);
	static DacBoard m_inst;

signals:
	void powerMonitorDataUpdated(const PowerMonitorData& data);

public:
	static DacBoard* instance() { return &m_inst; }
	bool readPowerMonitorData(PowerMonitorData& powerStatus);
	bool setDacOutput(unsigned short val);

private:
	void timerEvent(QTimerEvent * e);
};
