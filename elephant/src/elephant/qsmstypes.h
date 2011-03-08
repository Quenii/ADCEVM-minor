#ifndef QSMSTYPES_H
#define QSMSTYPES_H

#include "gkhy/pagoda/qrdmpacket.h"

#include <QObject>
#include <qsettings.h>
#include <QList>

using namespace gkhy::pagoda;

struct SmsConfig
{/*
	int t1;
	int t2;
	int t3;
	int t4;
	int clk;
	*/

	void fromSettings(const QSettings& s);
	void toSettings(QSettings& s) const;
};

struct SmsStatus
{
	/*bool isRunning;

	long long nPcieTotal;
	int nPcieAvgThruput;
	int nPcieInstThruput;

	long long nDiskTotal;
	int nDiskAvgThruput;
	int nDiskInstThruput;

	// int nFilePercent;

	// UINT64 nFifoLeakCount;
	//UINT nFifoPercent;
	// TimeElapsed;
	*/
};

struct SmsCommand
{
	bool switch_on_or_else_off;
};

#define SMS_PACKET						0x2000
#define QSmsConfig_ID					(SMS_PACKET | 0x1)
#define QSmsStatus_ID					(SMS_PACKET | 0x2)
#define QSmsCommand_ID					(SMS_PACKET | 0x3)


class QSmsConfig : public gkhy::pagoda::QRdmPacketTemplate<SmsConfig, QSmsConfig_ID, QRdmPacket::ConfigPacket>	
{																		
	Q_OBJECT															
public:																	
	QSmsConfig(QObject* parent = 0) : QRdmPacketTemplate<SmsConfig, QSmsConfig_ID, QRdmPacket::ConfigPacket>(parent) {}																		
signals:																	
	void setLocal(const SmsConfig& data, int& ret) const;						
	void getLocal(SmsConfig& data, int& ret);							
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

class QSmsStatus : public gkhy::pagoda::QRdmPacketTemplate<SmsStatus, QSmsStatus_ID, QRdmPacket::StatusPacket>	
{																		
	Q_OBJECT															
public:																	
	QSmsStatus(QObject* parent = 0) : QRdmPacketTemplate<SmsStatus, QSmsStatus_ID, QRdmPacket::StatusPacket>(parent) {}																		
signals:																	
	void setLocal(const SmsStatus& data, int& ret) const;						
	void getLocal(SmsStatus& data, int& ret);							
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

class QSmsCommand : public gkhy::pagoda::QRdmPacketTemplate<SmsCommand, QSmsCommand_ID, QRdmPacket::CommandPacket>	
{																		
	Q_OBJECT															
public:																	
	QSmsCommand(QObject* parent = 0) : QRdmPacketTemplate<SmsCommand, QSmsCommand_ID, QRdmPacket::CommandPacket>(parent) {}																		
signals:																	
	void setLocal(const SmsCommand& data, int& ret) const;						
	void getLocal(SmsCommand& data, int& ret);							
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

class QSmsPackets : public QObject
{
public:
	QSmsPackets(QObject* parent = 0) : QObject(parent)
	{
		list.push_back(&smsConfig);
		list.push_back(&smsStatus);
		list.push_back(&smsCommand);
	}

	QSmsConfig smsConfig;
	QSmsStatus smsStatus;
	QSmsCommand smsCommand;

	QList<QRdmPacket*> list;
};


#endif // QSMSTYPES_H
