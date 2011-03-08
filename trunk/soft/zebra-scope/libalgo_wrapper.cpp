#include "AdcBoardTypes.hpp"

#ifdef MATLAB 

#include "libalgo_wrapper.h"
#include "libalgo.h"

void calc_dynam_params(std::vector<float> samples, int bitCount, FreqDomainReport& param)
{
	mwArray mwSamples(1, samples.size(), mxDOUBLE_CLASS);
	mwSamples.SetData(&samples[0], samples.size());
	mwArray mwBitCount(1, 1, mxDOUBLE_CLASS);
	mwBitCount.SetData(&bitCount, 1);

	mwArray A;
	mwArray AdB;
	mwArray SINAD;
	mwArray SNR;
	mwArray THD;
	mwArray SFDR;
	mwArray ENOB;
	mwArray HD;
	mwArray Spectrum;

	calc_dynam_params(9,
		A, AdB, SINAD, 
		SNR, THD, SFDR, 
		ENOB, HD, Spectrum,
		mwSamples,
		mwBitCount);	

	if (param.Spectrum.size() != Spectrum.NumberOfElements())
	{
		param.Spectrum.resize(Spectrum.NumberOfElements());
	}
	Spectrum.GetData(&param.Spectrum[0], param.Spectrum.size());

	if (param.HD.size() != HD.NumberOfElements())
	{
		param.HD.resize(HD.NumberOfElements());
	}
	HD.GetData(&param.HD[0], param.HD.size());

	A.GetData(&param.A, 1);
	AdB.GetData(&param.AdB, 1);
	SINAD.GetData(&param.SINAD, 1);
	SNR.GetData(&param.SNR, 1);
	THD.GetData(&param.THD, 1);
	SFDR.GetData(&param.SFDR, 1);
	ENOB.GetData(&param.ENOB, 1);


}

#endif // MATLAB
