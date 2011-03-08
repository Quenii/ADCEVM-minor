//------------------------------------------------------------------------------
//
//                    (C) Copyright Boian Mitov 2005 - 2009
//                            www.mitov.com
//
//------------------------------------------------------------------------------

#ifndef CSignalLabScopePkgCB6_H_
#define CSignalLabScopePkgCB6_H_

//------------------------------------------------------------------------------
#ifndef VCLLoaderH
  #include <VCLLoader.h>
#endif
//------------------------------------------------------------------------------
inline void *Get_SignalLabScopePkgCB6()
{
	static void *_LibraryHandle = NULL;
	if( ! _LibraryHandle )
		_LibraryHandle = VCL_LoadLibrary( "SignalLabScopePkgCB6.bpl" );

	return _LibraryHandle;
}
//------------------------------------------------------------------------------
#endif   // CSignalLabScopePkgCB6_H_
//------------------------------------------------------------------------------
