#ifndef QSARTYPES_H
#define QSARTYPES_H

#include "gkhy/pagoda/qrdmpacket.h"
#include "gkhy/pagoda/qthruputmeter.h"

#include <QObject>
#include <qsettings.h>

using namespace gkhy::pagoda;

struct SarConfig
{
	int t1;
	int t2;
	int t3;
	int t4;
	int clk;

	void fromSettings(const QSettings& s);
	void toSettings(QSettings& s) const;
};

struct SarStatus
{
	int isRunning;
	qint64 secondElapsed;
	ThruputMeterValue thruput;
};

struct SarCommand
{
	bool switch_on_or_else_off;
};

#define SAR_PACKET						0x1000
#define QSarConfig_ID					(SAR_PACKET | 0x1)
#define QSarStatus_ID					(SAR_PACKET | 0x2)
#define QSarCommand_ID					(SAR_PACKET | 0x3)


class QSarConfig : public gkhy::pagoda::QRdmPacketTemplate<SarConfig, QSarConfig_ID, QRdmPacket::ConfigPacket>	
{																		
	Q_OBJECT															
public:																	
	QSarConfig(QObject* parent = 0) : QRdmPacketTemplate<SarConfig, QSarConfig_ID, QRdmPacket::ConfigPacket>(parent) {}																		
signals:																	
	void setLocal(const SarConfig& data, int& ret) const;						
	void getLocal(SarConfig& data, int& ret);							
public:																		
	int setLocal() const															
	{																		
		int ret = 0;														
		emit setLocal(payload(), ret);										
		return ret;															
	}																		
	int getLocal() 															
	{																		
		int ret = 0;														
		emit getLocal(payload(), ret);										
		return ret;															
	}																		
};

class QSarStatus : public gkhy::pagoda::QRdmPacketTemplate<SarStatus, QSarStatus_ID, QRdmPacket::StatusPacket>	
{																		
	Q_OBJECT															
public:																	
	QSarStatus(QObject* parent = 0) : QRdmPacketTemplate<SarStatus, QSarStatus_ID, QRdmPacket::StatusPacket>(parent) {}																		
signals:																	
	void getLocal(SarStatus& data, int& ret);							
	void setLocal(const SarStatus& data, int& ret) const; 							 
public:																
	int getLocal() 															
	{																		
		int ret = 0;														
		emit getLocal(payload(), ret);										
		return ret;															
	}																		

	int setLocal() const
	{
		int ret = 0;
		emit setLocal(payload(), ret);
		return ret;
	}
};

class QSarCommand : public gkhy::pagoda::QRdmPacketTemplate<SarCommand, QSarCommand_ID, QRdmPacket::CommandPacket>	
{																		
	Q_OBJECT															
public:																	
	QSarCommand(QObject* parent = 0) : QRdmPacketTemplate<SarCommand, QSarCommand_ID, QRdmPacket::CommandPacket>(parent) {}																		
signals:																	
	void setLocal(const SarCommand& data, int& ret) const;	
public:																		
	int setLocal() const													
	{																		
		int ret = 0;														
		emit setLocal(payload(), ret);										
		return ret;															
	}																		
};

class QSarPackets : public QObject
{
public:
	QSarPackets(QObject* parent = 0) : QObject(parent)
	{
		list.push_back(&sarConfig);
		list.push_back(&sarStatus);                          
		list.push_back(&sarCommand);
	}

	QSarConfig sarConfig;
	QSarStatus sarStatus;     
	QSarCommand sarCommand;

	QList<QRdmPacket*> list;
};

#endif // QSARTYPES_H
