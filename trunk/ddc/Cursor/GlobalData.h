// GlobalData.h: interface for the GlobalData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLOBALDATA_H__1F294658_2886_4AEA_B19C_66B763C6E5BC__INCLUDED_)
#define AFX_GLOBALDATA_H__1F294658_2886_4AEA_B19C_66B763C6E5BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "AdcTestPlatDoc.h"

#include <afxmt.h>
#include <vector>

using namespace std;


class GlobalData  
{
	struct DataSet
	{
		vector<double> i;
		vector<double> q;
		vector<double> y;

		double SNR;
		double SFDR;	
		double SINAD;
		double ENOB;
	};

private:
	GlobalData();
public:
	virtual ~GlobalData();

public:
	static GlobalData * lockInstance();
	void unlock();

public:
	DataSet dataSet[4];	
	CCriticalSection cs;
};

#endif // !defined(AFX_GLOBALDATA_H__1F294658_2886_4AEA_B19C_66B763C6E5BC__INCLUDED_)
