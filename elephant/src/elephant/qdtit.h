#pragma once 

#include "gkhy/pagoda/qrdmpacket.h"
#include <qobject>

class QDtit;

struct DtitSettings
{

};

struct DtitSattus
{

};

#define DTIT_PACKET 0x4000

typedef gkhy::pagoda::QRdmSettingsPacketTemplate<QDtit, DtitSettings, DTIT_PACKET | 1> QDtitSettingsRdmPacket;

class QDtit : QObject
{
	Q_OBJECT

public:
	QDtit(QObject* parent);
	virtual ~QDtit();

public:
	bool set(const DtitSettings& settings)
	{

		return true;
	}

	bool get(const DtitSettings& settings) const
	{

		return true;
	}
	
};
