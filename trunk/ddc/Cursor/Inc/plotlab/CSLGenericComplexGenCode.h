//------------------------------------------------------------------------------
//
//                    (C) Copyright Boian Mitov 2005
//                            www.mitov.com
//
//------------------------------------------------------------------------------
#ifndef CSLGenericComplexGenCode_H_
#define CSLGenericComplexGenCode_H_

//------------------------------------------------------------------------------
inline CTSLGenericComplexGen::CTSLGenericComplexGen() :
  OnGenerate( GetInstance(), _T( "OnGenerate" ))

{
  LibraryHandle = ::Get_VCSignalLabPkgCB6();
  CLPComponent::OpenComponent( _T( "TSLGenericVCComplexGen" ));
}
//------------------------------------------------------------------------------
inline TLPFunctionEntry CTSLGenericComplexGen::GetFunction( const char *function_name )
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
inline void __stdcall CSLGenerateComplexEvent::IntOnGenerateEvent( void *Sender, TSLUniVCBufferProxy *BufferOut, BOOL *Populated, BOOL *Finished )
{
  TSLCComplexBuffer OutBuffer( BufferOut );

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
#endif   // CSLGenericComplexGenCode_H_
//------------------------------------------------------------------------------
