/*
 * MATLAB Compiler: 4.0 (R14)
 * Date: Sun Sep 19 00:24:45 2010
 * Arguments: "-B" "macro_default" "-B" "csharedlib:libalgo" "-W" "lib:libalgo"
 * "-T" "link:lib" "-W" "lib:libalgo" "-T" "link:lib" "ddc_func" "-v" 
 */

#ifndef __libalgo_h
#define __libalgo_h 1

#if defined(__cplusplus) && !defined(mclmcr_h) && defined(__linux__)
#  pragma implementation "mclmcr.h"
#endif
#include "mclmcr.h"
#ifdef __cplusplus
extern "C" {
#endif

extern bool libalgoInitializeWithHandlers(mclOutputHandlerFcn error_handler,
                                          mclOutputHandlerFcn print_handler);
extern bool libalgoInitialize(void);
extern void libalgoTerminate(void);


extern void mlxDdc_func(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);


extern void mlfDdc_func(int nargout, mxArray** ENOB, mxArray** SNR
                        , mxArray** SFDR_mdfy, mxArray** SINAD
                        , mxArray* data_i, mxArray* data_q
                        , mxArray* numbit, mxArray* r, mxArray* fs);

#ifdef __cplusplus
}
#endif

#endif
