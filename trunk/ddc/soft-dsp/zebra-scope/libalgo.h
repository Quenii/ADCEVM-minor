//
// MATLAB Compiler: 4.8 (R2008a)
// Date: Sat Jun 19 22:45:32 2010
// Arguments: "-B" "macro_default" "-W" "cpplib:libalgo" "-T" "link:lib"
// "myfft" "calc_dynam_params" 
//

#ifndef __libalgo_h
#define __libalgo_h 1

#if defined(__cplusplus) && !defined(mclmcrrt_h) && defined(__linux__)
#  pragma implementation "mclmcrrt.h"
#endif
#include "mclmcrrt.h"
#include "mclcppclass.h"
#ifdef __cplusplus
extern "C" {
#endif

#if defined(__SUNPRO_CC)
/* Solaris shared libraries use __global, rather than mapfiles
 * to define the API exported from a shared library. __global is
 * only necessary when building the library -- files including
 * this header file to use the library do not need the __global
 * declaration; hence the EXPORTING_<library> logic.
 */

#ifdef EXPORTING_libalgo
#define PUBLIC_libalgo_C_API __global
#else
#define PUBLIC_libalgo_C_API /* No import statement needed. */
#endif

#define LIB_libalgo_C_API PUBLIC_libalgo_C_API

#elif defined(_HPUX_SOURCE)

#ifdef EXPORTING_libalgo
#define PUBLIC_libalgo_C_API __declspec(dllexport)
#else
#define PUBLIC_libalgo_C_API __declspec(dllimport)
#endif

#define LIB_libalgo_C_API PUBLIC_libalgo_C_API


#else

#define LIB_libalgo_C_API

#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_libalgo_C_API 
#define LIB_libalgo_C_API /* No special import/export declaration */
#endif

extern LIB_libalgo_C_API 
bool MW_CALL_CONV libalgoInitializeWithHandlers(mclOutputHandlerFcn error_handler,
                                                mclOutputHandlerFcn print_handler);

extern LIB_libalgo_C_API 
bool MW_CALL_CONV libalgoInitialize(void);

extern LIB_libalgo_C_API 
void MW_CALL_CONV libalgoTerminate(void);



extern LIB_libalgo_C_API 
void MW_CALL_CONV libalgoPrintStackTrace(void);


extern LIB_libalgo_C_API 
bool MW_CALL_CONV mlxMyfft(int nlhs, mxArray *plhs[],
                           int nrhs, mxArray *prhs[]);

extern LIB_libalgo_C_API 
bool MW_CALL_CONV mlxCalc_dynam_params(int nlhs, mxArray *plhs[],
                                       int nrhs, mxArray *prhs[]);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

/* On Windows, use __declspec to control the exported API */
#if defined(_MSC_VER) || defined(__BORLANDC__)

#ifdef EXPORTING_libalgo
#define PUBLIC_libalgo_CPP_API __declspec(dllexport)
#else
#define PUBLIC_libalgo_CPP_API __declspec(dllimport)
#endif

#define LIB_libalgo_CPP_API PUBLIC_libalgo_CPP_API

#else

#if !defined(LIB_libalgo_CPP_API)
#if defined(LIB_libalgo_C_API)
#define LIB_libalgo_CPP_API LIB_libalgo_C_API
#else
#define LIB_libalgo_CPP_API /* empty! */ 
#endif
#endif

#endif

extern LIB_libalgo_CPP_API void MW_CALL_CONV myfft(int nargout, mwArray& ret
                                                   , const mwArray& x);

extern LIB_libalgo_CPP_API void MW_CALL_CONV calc_dynam_params(int nargout
                                                               , mwArray& A
                                                               , mwArray& AdB
                                                               , mwArray& SINAD
                                                               , mwArray& SNR
                                                               , mwArray& THD
                                                               , mwArray& SFDR
                                                               , mwArray& ENOB
                                                               , mwArray& HD
                                                               , mwArray& Spectrum
                                                               , const mwArray& samples
                                                               , const mwArray& numbit);

#endif

#endif
