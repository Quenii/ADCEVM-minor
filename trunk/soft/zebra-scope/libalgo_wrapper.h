#pragma once

#define USE_MATLAB

#include <vector>
#include <AdcBoardTypes.hpp>



//struct DynamParams
//{
//	std::vector<float> Spectrum;
//	float A;
//	float AdB;
//	float SINAD;
//	float SNR;
//	float THD;
//	float SFDR;
//	float ENOB;
//	float HD;
//};

void calc_dynam_params(std::vector<float> samples, int bitCount, FreqDomainReport& param);