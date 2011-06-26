#pragma once

#include <QString>
#include <QMetaType>
#include <QDataStream>
#include <QVariant>

enum TestMode
{
	StaticTest,
	DynamicTest,
	InstTest,
	Calibration
};

struct StaticTestSettings
{
	int averageLevel;
	int nplc;
	int left;
	int right;
	
	operator QVariant() const {	return QVariant::fromValue(*this); }	
};

Q_DECLARE_METATYPE(StaticTestSettings);

inline QDataStream& operator<<(QDataStream& out, const StaticTestSettings& val)
{
	out << val.averageLevel;
	out << val.nplc;
	out << val.left;
	out << val.right;

	return out;
}

inline QDataStream& operator>>(QDataStream& in, StaticTestSettings& val)
{
	in >> val.averageLevel;
	in >> val.nplc;
	in >> val.left;
	in >> val.right;

	return in;
}

struct DynamicTestSettings
{
	float vpp;
	int bitCount;
	float clockFreq;
	float signalFreq;

	operator QVariant() const {	return QVariant::fromValue(*this); }	
};

Q_DECLARE_METATYPE(DynamicTestSettings);

inline QDataStream& operator<<(QDataStream& out, const DynamicTestSettings& val)
{
	out << val.vpp;
	out << val.bitCount;
	out << val.clockFreq;
	out << val.signalFreq;

	return out;
}

inline QDataStream& operator>>(QDataStream& in, DynamicTestSettings& val)
{
	in >> val.vpp;
	in >> val.bitCount;
	in >> val.clockFreq;
	in >> val.signalFreq;

	return in;
}

struct PowerMonitorData
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

