/*
 * MATLAB Compiler: 4.0 (R14)
 * Date: Mon Dec 15 22:19:08 2008
 * Arguments: "-B" "macro_default" "-B" "csharedlib:libplot" "-W" "lib:libplot"
 * "-T" "link:lib" "MyPlot.m" "-v" 
 */

#ifndef __libplot_h
#define __libplot_h 1

#if defined(__cplusplus) && !defined(mclmcr_h) && defined(__linux__)
#  pragma implementation "mclmcr.h"
#endif
#include "mclmcr.h"
#ifdef __cplusplus
extern "C" {
#endif

extern bool libplotInitializeWithHandlers(mclOutputHandlerFcn error_handler,
                                          mclOutputHandlerFcn print_handler);
extern bool libplotInitialize(void);
extern void libplotTerminate(void);


extern void mlxMyplot(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);


extern void mlfMyplot(mxArray* x, mxArray* y);

#ifdef __cplusplus
}
#endif

#endif
