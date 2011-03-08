//------------------------------------------------------------------------------
//
//                    (C) Copyright Boian Mitov 2005 - 2009
//                            www.mitov.com
//
//------------------------------------------------------------------------------

#ifndef CSignalLabBasicPkgCB6_H_
#define CSignalLabBasicPkgCB6_H_

//------------------------------------------------------------------------------
#ifndef VCLLoaderH
  #include <VCLLoader.h>
#endif
//------------------------------------------------------------------------------
inline VCLHANDLE Get_SignalLabBasicPkgCB6()
{
	static VCLHANDLE _LibraryHandle = 0;
	if( ! _LibraryHandle )
		_LibraryHandle = (VCLHANDLE)VCL_LoadLibrary( "SignalLabBasicPkgCB6.bpl" );

	return _LibraryHandle;
}
//------------------------------------------------------------------------------
#endif   // CSignalLabBasicPkgCB6_H_
//------------------------------------------------------------------------------
