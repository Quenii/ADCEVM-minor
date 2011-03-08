/*
 * MATLAB Compiler: 4.0 (R14)
 * Date: Sat Jan 03 19:51:52 2009
 * Arguments: "-B" "macro_default" "-B" "csharedlib:libfft" "-W" "lib:libfft"
 * "-T" "link:lib" "MyFft.m" "-v" 
 */

#ifndef __libfft_h
#define __libfft_h 1

#if defined(__cplusplus) && !defined(mclmcr_h) && defined(__linux__)
#  pragma implementation "mclmcr.h"
#endif
#include "mclmcr.h"
#ifdef __cplusplus
extern "C" {
#endif

extern bool libfftInitializeWithHandlers(mclOutputHandlerFcn error_handler,
                                         mclOutputHandlerFcn print_handler);
extern bool libfftInitialize(void);
extern void libfftTerminate(void);


extern void mlxMyfft(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);


extern void mlfMyfft(int nargout, mxArray** y, mxArray* x, mxArray* numpt);

#ifdef __cplusplus
}
#endif

#endif
