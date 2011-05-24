#pragma once

#include <QString>
#include <QMetaType>
#include <QDataStream>
#include <QVariant>

#include "DacBoard.h"


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
	int step2n;
	
	operator QVariant() const {	return QVariant::fromValue(*this); }	
};

Q_DECLARE_METATYPE(StaticTestSettings);

inline QDataStream& operator<<(QDataStream& out, const StaticTestSettings& val)
{
	out << val.averageLevel;
	out << val.step2n;

	return out;
}

inline QDataStream& operator>>(QDataStream& in, StaticTestSettings& val)
{
	in >> val.averageLevel;
	in >> val.step2n;

	return in;
}

