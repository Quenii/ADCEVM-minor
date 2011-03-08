/*
 * MATLAB Compiler: 4.0 (R14)
 * Date: Sun Sep 19 23:06:06 2010
 * Arguments: "-B" "macro_default" "-B" "csharedlib:libalg" "-W" "lib:libalg"
 * "-T" "link:lib" "-T" "link:lib" "AlgDynTest" "-v" 
 */

#ifndef __libalg_h
#define __libalg_h 1

#if defined(__cplusplus) && !defined(mclmcr_h) && defined(__linux__)
#  pragma implementation "mclmcr.h"
#endif
#include "mclmcr.h"
#ifdef __cplusplus
extern "C" {
#endif

extern bool libalgInitializeWithHandlers(mclOutputHandlerFcn error_handler,
                                         mclOutputHandlerFcn print_handler);
extern bool libalgInitialize(void);
extern void libalgTerminate(void);


extern void mlxAlgdyntest(int nlhs, mxArray *plhs[],
                          int nrhs, mxArray *prhs[]);


extern void mlfAlgdyntest(int nargout, mxArray** SNR, mxArray** SINAD
                          , mxArray** SFDR, mxArray** ENOB, mxArray* data1
                          , mxArray* data2, mxArray* numpt, mxArray* fclk
                          , mxArray* numbit);

#ifdef __cplusplus
}
#endif

#endif
