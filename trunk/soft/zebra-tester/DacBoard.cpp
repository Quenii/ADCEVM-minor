#include "DacBoard.h"


DacBoard::DacBoard(QObject* parent) 
: Board(parent)
{
	DacTypeSettings settings;
	settings.va = 1.8f;
	settings.vd = 1.8f;

	setDacTypeSettings(settings);

	startTimer(500);
}

DacBoard::~DacBoard(void)
{
}

void DacBoard::timerEvent(QTimerEvent *e)
{
	if (!isOpen())
	{
		open();
	}

	if (!isOpen())
	{
		return ;
	}

	PowerMonitorData data;
	if (readPowerMonitorData(data))
	{
		emit powerMonitorDataUpdated(data);
	}
}

bool DacBoard::readPowerMonitorData(PowerMonitorData & powerStatus)
{
	unsigned short reg = 0;
	writeReg(9, 0xA400);  //select 3548, work at default mode
	writeReg(9, 0xA400);  //select 3548, work at default mode

	writeReg(9, 0x7FFF);  //select 3548, select 7th channel
	writeReg(9, 0x7FFF);  //select 3548, select 7th channel
	writeReg(9, 0xeFFF);  //select 3548, read out 7th channel volage
	writeReg(9, 0xeFFF);  //select 3548, read out 7th channel volage
	readReg(0x0009, reg);
	powerStatus.va = (float(reg>>2)) * 4 / 16384;

	writeReg(9, 0x3FFF);  //select 3548, select 7th channel
	writeReg(9, 0x3FFF);  //select 3548, select 7th channel
	writeReg(9, 0xeFFF);  //select 3548, read out 7th channel volage
	writeReg(9, 0xeFFF);  //select 3548, read out 7th channel volage
	readReg(0x0009, reg);
	powerStatus.vd = (float(reg>>2)) * 4 / 16384;

	writeReg(9, 0x4FFF);  //select 3548, select 7th channel
	writeReg(9, 0x4FFF);  //select 3548, select 7th channel
	writeReg(9, 0xeFFF);  //select 3548, read out 7th channel volage
	writeReg(9, 0xeFFF);  //select 3548, read out 7th channel volage
	readReg(0x0009, reg);
	powerStatus.ia = (float(reg>>2)) * 500 * 4 / 16384;

	writeReg(9, 0x1FFF);  //select 3548, select 7th channel
	writeReg(9, 0x1FFF);  //select 3548, select 7th channel
	writeReg(9, 0xeFFF);  //select 3548, read out 7th channel volage
	writeReg(9, 0xeFFF);  //select 3548, read out 7th channel volage
	readReg(0x0009, reg);
	powerStatus.id = (float(reg>>2)) * 500 * 4 / 16384;

	powerStatus.p = powerStatus.va * powerStatus.ia + powerStatus.vd * powerStatus.id;

	return true;

}

bool DacBoard::setDacOutput(unsigned short val)
{

	return true;
}

bool DacBoard::setDacTypeSettings(const DacTypeSettings& settings)
{
	unsigned short regValue = 0;

	regValue = setVoltage(0x3FFF, 0, settings.vd);
	setVoltage(0x7FFF, 2, settings.va);

	if (!writeReg(5, regValue)) //设置VIO = VD
		return false;
	if (!writeReg(6, 0x0004))  //执行 通道E
		return false;

	return true;
}