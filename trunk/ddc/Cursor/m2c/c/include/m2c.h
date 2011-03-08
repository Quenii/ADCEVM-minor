// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the M2C_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// M2C_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.

#ifdef M2C_EXPORTS
#define M2C_API __declspec(dllexport)
#else
#define M2C_API __declspec(dllimport)
#endif

#ifdef __cplusplus

extern "C" {

#endif

M2C_API void AlgDynTest(double* cdata1, int cdata1_cnt,
						double* cdata2, int cdata2_cnt,
						double cnumpt, double cfclk, double cnumbit, double cr,
						double& cSNR__o, double& cSINAD__o, double& cSFDR__o, double& cENOB__o, double* cy);


//M2C_API void AdcDynTest(double* cdata, int cdata_cnt, double cfclk, double cnumbit, double cNFFT, double cV, double ccode,
//						double& cSNR__o, double& cSFDR__o, double& cSNRFS__o, double& cSINAD__o, double* cy);
M2C_API void AdcDynTest(double* cdata, int cdata_cnt, double cfclk, double cnumbit, double cNFFT, double cV, double ccode,
				double& cSNR__o, double& cSINAD__o, double& cSFDR__o, double& cENOB__o,
				double* cy);

M2C_API void FFT(double* data, int data_cnt, double* result, int result_cnt);
M2C_API void FFT_complex(double* r_data, double* i_data, int data_cnt, double* result, int result_cnt);

#ifdef __cplusplus

} 

#endif