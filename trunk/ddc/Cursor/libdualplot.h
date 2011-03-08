/*
 * MATLAB Compiler: 4.0 (R14)
 * Date: Tue Jan 20 13:34:12 2009
 * Arguments: "-B" "macro_default" "-B" "csharedlib:libdualplot" "-W"
 * "lib:libdualplot" "-T" "link:lib" "MyDualPlot.m" "-v" 
 */

#ifndef __libdualplot_h
#define __libdualplot_h 1

#if defined(__cplusplus) && !defined(mclmcr_h) && defined(__linux__)
#  pragma implementation "mclmcr.h"
#endif
#include "mclmcr.h"
#ifdef __cplusplus
extern "C" {
#endif

extern bool libdualplotInitializeWithHandlers(mclOutputHandlerFcn error_handler,
                                              mclOutputHandlerFcn print_handler);
extern bool libdualplotInitialize(void);
extern void libdualplotTerminate(void);


extern void mlxMydualplot(int nlhs, mxArray *plhs[],
                          int nrhs, mxArray *prhs[]);


extern void mlfMydualplot(mxArray* x1, mxArray* y1, mxArray* x2, mxArray* y2);

#ifdef __cplusplus
}
#endif

#endif
