#include "..\include\gkhy\BoardApi\DacBoard.h"

DacBoard DacBoard::m_inst;

DacBoard::DacBoard(QObject* parent) 
: Board(parent)
{
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