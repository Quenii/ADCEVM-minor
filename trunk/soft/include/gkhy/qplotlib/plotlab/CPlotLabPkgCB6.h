//------------------------------------------------------------------------------
//
//                    (C) Copyright Boian Mitov 2005
//                            www.mitov.com
//
//------------------------------------------------------------------------------

#ifndef CPlotLabPkgCB6_H_
#define CPlotLabPkgCB6_H_

//------------------------------------------------------------------------------
#ifndef VCLLoaderH
  #include <VCLLoader.h>
#endif
//------------------------------------------------------------------------------
inline void *Get_PlotLabPkgCB6()
{
	static void *_LibraryHandle = NULL;
	if( ! _LibraryHandle )
		_LibraryHandle = VCL_LoadLibrary( "PlotLabPkgCB6.bpl" );

	return _LibraryHandle;
}
//------------------------------------------------------------------------------
#endif   // CVideoLabBasicPkgCB6_H_
//------------------------------------------------------------------------------
