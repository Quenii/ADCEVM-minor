/*
 * MATLAB Compiler: 4.0 (R14)
 * Date: Sun Sep 19 23:06:40 2010
 * Arguments: "-B" "macro_default" "-B" "csharedlib:libadc" "-W" "lib:libadc"
 * "-T" "link:lib" "-W" "lib:libadc" "-T" "link:lib" "AdcDynTest.m" "-v" 
 */

#ifndef __libadc_h
#define __libadc_h 1

#if defined(__cplusplus) && !defined(mclmcr_h) && defined(__linux__)
#  pragma implementation "mclmcr.h"
#endif
#include "mclmcr.h"
#ifdef __cplusplus
extern "C" {
#endif

extern bool libadcInitializeWithHandlers(mclOutputHandlerFcn error_handler,
                                         mclOutputHandlerFcn print_handler);
extern bool libadcInitialize(void);
extern void libadcTerminate(void);


extern void mlxAdcdyntest(int nlhs, mxArray *plhs[],
                          int nrhs, mxArray *prhs[]);


extern void mlfAdcdyntest(int nargout, mxArray** SNR, mxArray** SINAD
                          , mxArray** SFDR, mxArray** ENOB, mxArray* data
                          , mxArray* numpt, mxArray* fclk, mxArray* numbit);

#ifdef __cplusplus
}
#endif

#endif
