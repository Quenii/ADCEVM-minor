//------------------------------------------------------------------------------
//
//                    (C) Copyright Boian Mitov 2005
//                            www.mitov.com
//
//------------------------------------------------------------------------------
#ifndef CSLGenericRealGenCode_H_
#define CSLGenericRealGenCode_H_

//------------------------------------------------------------------------------
inline CTSLGenericRealGen::CTSLGenericRealGen() :
  OnGenerate( GetInstance(), _T( "OnGenerate" ))

{
  LibraryHandle = ::Get_VCSignalLabPkgCB6();
  CLPComponent::OpenComponent( _T( "TSLGenericVCRealGen" ));
}
//------------------------------------------------------------------------------
inline TLPFunctionEntry CTSLGenericRealGen::GetFunction( const char *function_name )
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
inline void __stdcall CSLGenerateRealEvent::IntOnGenerateEvent( void *Sender, TSLUniVCBufferProxy *BufferOut, BOOL *Populated, BOOL *Finished )
{
  TSLCRealBuffer OutBuffer( BufferOut );

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
#endif   // CSLGenericRealGenCode_H_
//------------------------------------------------------------------------------
