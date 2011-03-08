// GlobalData.cpp: implementation of the GlobalData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GlobalData.h"

#include <stdlib.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GlobalData::GlobalData()
{
	for (int i = 0; i < sizeof(dataSet)/sizeof(dataSet[0]); ++ i)
	{
		dataSet->i.resize(MAX_DEPTH);
		dataSet->q.resize(MAX_DEPTH);
		dataSet->y.resize(MAX_DEPTH);
	}
}

GlobalData::~GlobalData()
{

}

GlobalData * GlobalData::lockInstance()
{
	static GlobalData _instance;
	_instance.cs.Lock();
	return &_instance;
}

void GlobalData::unlock()
{
	cs.Unlock();
}
