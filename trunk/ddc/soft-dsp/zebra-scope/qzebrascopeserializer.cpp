#include "qzebrascopeserializer.h"

QZebraScopeSerializer::QZebraScopeSerializer(const QString &name, QObject *parent /* = 0 */)
	: QFile(name, parent)
{

}

QZebraScopeSerializer::~QZebraScopeSerializer()
{

}

void QZebraScopeSerializer::serialize(const AdcBoardReport& data)
{
	serialize(data.powerStatus);
	serialize(data.fdReport);
	serialize(data.tdReport);
}

bool QZebraScopeSerializer::deserialize(AdcBoardReport& data)
{
	if (deserialize(data.powerStatus) && 
		deserialize(data.fdReport) &&
		deserialize(data.tdReport))
		return true;
	else
		return false;
}

void QZebraScopeSerializer::serialize(const PowerStatus& data) 
{
	write((const char*)&data, sizeof(data));
}

bool QZebraScopeSerializer::deserialize(PowerStatus& data)
{
	if (bytesAvailable() < sizeof(data))
		return false;

	read((char*)&data, sizeof(data));

	return true;
}

void QZebraScopeSerializer::serialize(const TimeDomainReport& data)
{
	serialize(data.samples);
	serialize(data.xaxis);
	serialize(data.rawSamples);
	serialize(data.min);
	serialize(data.max);
}

bool QZebraScopeSerializer::deserialize(TimeDomainReport& data)
{
	if (deserialize(data.samples) && 
		deserialize(data.xaxis) &&
		deserialize(data.rawSamples) &&
		deserialize(data.min) &&
		deserialize(data.max))
		return true;
	else
		return false;
}

void QZebraScopeSerializer::serialize(const FreqDomainReport& data)
{
	serialize(data.Spectrum);
	serialize(data.xaxis);
	serialize(data.A);
	serialize(data.AdB);
	serialize(data.SINAD);
	serialize(data.SNR);
	serialize(data.THD);
	serialize(data.SFDR);
	serialize(data.ENOB);
	serialize(data.HD);
}

bool QZebraScopeSerializer::deserialize(FreqDomainReport& data)
{
	if (deserialize(data.Spectrum) &&
		deserialize(data.xaxis) &&
		deserialize(data.A) &&
		deserialize(data.AdB) &&
		deserialize(data.SINAD) &&
		deserialize(data.SNR) &&
		deserialize(data.THD) &&
		deserialize(data.SFDR) &&
		deserialize(data.ENOB) &&
		deserialize(data.HD))
		return true;
	else 
		return false;
}

