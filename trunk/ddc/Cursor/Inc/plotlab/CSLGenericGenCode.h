//------------------------------------------------------------------------------
//
//                    (C) Copyright Boian Mitov 2005
//                            www.mitov.com
//
//------------------------------------------------------------------------------
#ifndef CSLGenericGenCode_H_
#define CSLGenericGenCode_H_

//------------------------------------------------------------------------------
inline CTSLGenericGen::CTSLGenericGen() :
  OnGenerate( GetInstance(), _T( "OnGenerate" ))

{
  LibraryHandle = ::Get_VCSignalLabPkgCB6();
  CLPComponent::OpenComponent( _T( "TSLGenericVCGen" ));
}
//------------------------------------------------------------------------------
inline TLPFunctionEntry CTSLGenericGen::GetFunction( const char *function_name )
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
inline void __stdcall CSLGenerateBlockEvent::IntOnGenerateEvent( void *Sender, TSLUniVCBufferProxy *BufferOut, BOOL *Populated, BOOL *Finished )
{
  TSLCBlockBuffer OutBuffer( BufferOut );

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
#endif   // CSLGenericGenCode_H_
//------------------------------------------------------------------------------
