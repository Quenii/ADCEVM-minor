//------------------------------------------------------------------------------
//
//                    (C) Copyright Boian Mitov 2005
//                            www.mitov.com
//
//------------------------------------------------------------------------------
#ifndef CSLGenericIntGenCode_H_
#define CSLGenericIntGenCode_H_

//------------------------------------------------------------------------------
inline CTSLGenericIntGen::CTSLGenericIntGen() :
  OnGenerate( GetInstance(), _T( "OnGenerate" ))

{
  LibraryHandle = ::Get_VCSignalLabPkgCB6();
  CLPComponent::OpenComponent( _T( "TSLGenericVCIntegerGen" ));
}
//------------------------------------------------------------------------------
inline TLPFunctionEntry CTSLGenericIntGen::GetFunction( const char *function_name )
{
  TLPFunctionEntry Result = VCL_GetFunction( LibraryHandle, function_name );
  if( Result )
    return Result;

  return inherited::GetFunction( function_name );
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
inline void __stdcall CSLGenerateIntegerEvent::IntOnGenerateEvent( void *Sender, TSLUniVCBufferProxy *BufferOut, BOOL *Populated, BOOL *Finished )
{
  TSLCIntegerBuffer OutBuffer( BufferOut );

  bool aPopulated = ( *Populated ) != 0;
  bool aFinished = ( *Finished ) != 0;

  ( m_Instance->*m_CallBackFunction )( Sender, OutBuffer, aPopulated, aFinished );

  *Finished = (BOOL)aFinished; 
  *Populated = (BOOL)aPopulated; 

}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
#endif   // CSLGenericIntGenCode_H_
//------------------------------------------------------------------------------
