/*
 * MATLAB Compiler: 4.0 (R14)
 * Date: Tue Jan 20 13:04:55 2009
 * Arguments: "-B" "macro_default" "-B" "csharedlib:libtriplot" "-W"
 * "lib:libtriplot" "-T" "link:lib" "MyTriPlot.m" "-v" 
 */

#ifndef __libtriplot_h
#define __libtriplot_h 1

#if defined(__cplusplus) && !defined(mclmcr_h) && defined(__linux__)
#  pragma implementation "mclmcr.h"
#endif
#include "mclmcr.h"
#ifdef __cplusplus
extern "C" {
#endif

extern bool libtriplotInitializeWithHandlers(mclOutputHandlerFcn error_handler,
                                             mclOutputHandlerFcn print_handler);
extern bool libtriplotInitialize(void);
extern void libtriplotTerminate(void);


extern void mlxMytriplot(int nlhs, mxArray *plhs[],
                         int nrhs, mxArray *prhs[]);


extern void mlfMytriplot(mxArray* x1, mxArray* y1, mxArray* x2
                         , mxArray* y2, mxArray* y3);

#ifdef __cplusplus
}
#endif

#endif
