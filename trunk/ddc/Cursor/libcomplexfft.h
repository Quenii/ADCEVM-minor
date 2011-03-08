/*
 * MATLAB Compiler: 4.0 (R14)
 * Date: Fri Jan 16 17:12:26 2009
 * Arguments: "-B" "macro_default" "-B" "csharedlib:libcomplexfft" "-W"
 * "lib:libcomplexfft" "-T" "link:lib" "MyComplexFft.m" "-v" 
 */

#ifndef __libcomplexfft_h
#define __libcomplexfft_h 1

#if defined(__cplusplus) && !defined(mclmcr_h) && defined(__linux__)
#  pragma implementation "mclmcr.h"
#endif
#include "mclmcr.h"
#ifdef __cplusplus
extern "C" {
#endif

extern bool libcomplexfftInitializeWithHandlers(mclOutputHandlerFcn error_handler,
                                                mclOutputHandlerFcn print_handler);
extern bool libcomplexfftInitialize(void);
extern void libcomplexfftTerminate(void);


extern void mlxMycomplexfft(int nlhs, mxArray *plhs[],
                            int nrhs, mxArray *prhs[]);


extern void mlfMycomplexfft(int nargout, mxArray** y, mxArray* x1
                            , mxArray* x2, mxArray* numpt);

#ifdef __cplusplus
}
#endif

#endif
