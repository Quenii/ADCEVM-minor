#pragma once

#include <QString>
#include <QMetaType>
#include <QDataStream>
#include <QVariant>

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

