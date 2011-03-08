//
// MATLAB Compiler: 4.8 (R2008a)
// Date: Sat Jun 19 22:45:32 2010
// Arguments: "-B" "macro_default" "-W" "cpplib:libalgo" "-T" "link:lib"
// "myfft" "calc_dynam_params" 
//

#include <stdio.h>
#define EXPORTING_libalgo 1
#include "libalgo.h"
#ifdef __cplusplus
extern "C" {
#endif

extern mclComponentData __MCC_libalgo_component_data;

#ifdef __cplusplus
}
#endif


static HMCRINSTANCE _mcr_inst = NULL;


#if defined( _MSC_VER) || defined(__BORLANDC__) || defined(__WATCOMC__) || defined(__LCC__)
#ifdef __LCC__
#undef EXTERN_C
#endif
#include <windows.h>

static char path_to_dll[_MAX_PATH];

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, void *pv)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        if (GetModuleFileName(hInstance, path_to_dll, _MAX_PATH) == 0)
            return FALSE;
    }
    else if (dwReason == DLL_PROCESS_DETACH)
    {
    }
    return TRUE;
}
#endif
#ifdef __cplusplus
extern "C" {
#endif

static int mclDefaultPrintHandler(const char *s)
{
  return mclWrite(1 /* stdout */, s, sizeof(char)*strlen(s));
}

#ifdef __cplusplus
} /* End extern "C" block */
#endif

#ifdef __cplusplus
extern "C" {
#endif

static int mclDefaultErrorHandler(const char *s)
{
  int written = 0;
  size_t len = 0;
  len = strlen(s);
  written = mclWrite(2 /* stderr */, s, sizeof(char)*len);
  if (len > 0 && s[ len-1 ] != '\n')
    written += mclWrite(2 /* stderr */, "\n", sizeof(char));
  return written;
}

#ifdef __cplusplus
} /* End extern "C" block */
#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_libalgo_C_API 
#define LIB_libalgo_C_API /* No special import/export declaration */
#endif

LIB_libalgo_C_API 
bool MW_CALL_CONV libalgoInitializeWithHandlers(
    mclOutputHandlerFcn error_handler,
    mclOutputHandlerFcn print_handler
)
{
  if (_mcr_inst != NULL)
    return true;
  if (!mclmcrInitialize())
    return false;
  if (!GetModuleFileName(GetModuleHandle("libalgo"), path_to_dll, _MAX_PATH))
    return false;
  if (!mclInitializeComponentInstanceWithEmbeddedCTF(&_mcr_inst,
                                                     &__MCC_libalgo_component_data,
                                                     true, NoObjectType,
                                                     LibTarget, error_handler,
                                                     print_handler, 81652, path_to_dll))
    return false;
  return true;
}

LIB_libalgo_C_API 
bool MW_CALL_CONV libalgoInitialize(void)
{
  return libalgoInitializeWithHandlers(mclDefaultErrorHandler,
                                       mclDefaultPrintHandler);
}

LIB_libalgo_C_API 
void MW_CALL_CONV libalgoTerminate(void)
{
  if (_mcr_inst != NULL)
    mclTerminateInstance(&_mcr_inst);
}

LIB_libalgo_C_API 
void MW_CALL_CONV libalgoPrintStackTrace(void) 
{
  char** stackTrace;
  int stackDepth = mclGetStackTrace(_mcr_inst, &stackTrace);
  int i;
  for(i=0; i<stackDepth; i++)
  {
    mclWrite(2 /* stderr */, stackTrace[i], sizeof(char)*strlen(stackTrace[i]));
    mclWrite(2 /* stderr */, "\n", sizeof(char)*strlen("\n"));
  }
  mclFreeStackTrace(&stackTrace, stackDepth);
}


LIB_libalgo_C_API 
bool MW_CALL_CONV mlxMyfft(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "myfft", nlhs, plhs, nrhs, prhs);
}

LIB_libalgo_C_API 
bool MW_CALL_CONV mlxCalc_dynam_params(int nlhs, mxArray *plhs[],
                                       int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "calc_dynam_params", nlhs, plhs, nrhs, prhs);
}

LIB_libalgo_CPP_API 
void MW_CALL_CONV myfft(int nargout, mwArray& ret, const mwArray& x)
{
  mclcppMlfFeval(_mcr_inst, "myfft", nargout, 1, 1, &ret, &x);
}

LIB_libalgo_CPP_API 
void MW_CALL_CONV calc_dynam_params(int nargout, mwArray& A, mwArray& AdB
                                    , mwArray& SINAD, mwArray& SNR, mwArray& THD
                                    , mwArray& SFDR, mwArray& ENOB, mwArray& HD
                                    , mwArray& Spectrum, const mwArray& samples
                                    , const mwArray& numbit)
{
  mclcppMlfFeval(_mcr_inst, "calc_dynam_params", nargout,
                 9, 2, &A, &AdB, &SINAD, &SNR, &THD, &SFDR,
                 &ENOB, &HD, &Spectrum, &samples, &numbit);
}
