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


struct DacTypeSettings
{
	QString type;
	float va;
	float vd;
	int bitCount;
	float refVolt;
	float phase;	

	operator QVariant() const {	return QVariant::fromValue(*this); }	
};

Q_DECLARE_METATYPE(DacTypeSettings);


inline QDataStream& operator<<(QDataStream& out, const DacTypeSettings& val)
{
	out << val.type;
	out << val.va;
	out << val.vd;
	out << val.bitCount;
	out << val.refVolt;
	out << val.phase;	

	return out;
}

inline QDataStream& operator>>(QDataStream& in, DacTypeSettings& val)
{
	in >> val.type;
	in >> val.va;
	in >> val.vd;
	in >> val.bitCount;
	in >> val.refVolt;
	in >> val.phase;	

	return in;
}


class BOARDAPI_EXPORT DacBoard : public Board
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
