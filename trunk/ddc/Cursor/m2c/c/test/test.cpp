// test.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <tchar.h>
#include <vector>
#include "m2c.h"

using namespace std;

#pragma comment(lib, "m2c.lib")

int _tmain(int argc, _TCHAR* argv[])
{
	vector<double> buff(32768);
	vector<double> buff2(32768);
	
	while (1)
	{
		//FFT(&buff[0], buff.size(), &buff2[0], buff2.size());
		//FFT_complex(&buff[0], &buff[0], buff.size(), &buff2[0], buff2.size());
		

		double cnumpt = buff.size(), cfclk = 8e6, cnumbit = 12, cr = 20;
		double cSNR__o, cSINAD__o, cENOB__o, cSFDR__o, SNRFS__o;

		//AlgDynTest(&buff[0], buff.size(), &buff[0], buff.size(),
		//	cnumpt, cfclk, cnumbit, cr,
		//	cSNR__o, cSINAD__o, cSFDR__o, cENOB__o);

		AdcDynTest(&buff[0], buff.size(), cfclk, cnumbit, buff.size(), 2, 1,
			cSNR__o, cSFDR__o, SNRFS__o, cSINAD__o, &buff2[0]);
		

	}

	return 0;
}

