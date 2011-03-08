//------------------------------------------------------------------------------
//
//                    (C) Copyright Boian Mitov 2005
//                            www.mitov.com
//
//------------------------------------------------------------------------------
#ifndef CSLGenericIntCode_H_
#define CSLGenericIntCode_H_

//------------------------------------------------------------------------------
inline CTSLGenericInt::CTSLGenericInt() :
  SynchronizeType( GetInstance(), _T( "SynchronizeType" )),
  OnStart( GetInstance(), _T( "OnStart" )),
  OnStop( GetInstance(), _T( "OnStop" )),
  OnProcessData( GetInstance(), _T( "OnProcessData" ))

{
  LibraryHandle = ::Get_VCSignalLabPkgCB6();
  CLPComponent::OpenComponent( _T( "TSLGenericVCInteger" ));
}
//------------------------------------------------------------------------------
inline TLPFunctionEntry CTSLGenericInt::GetFunction( const char *function_name )
{
  TLPFunctionEntry Result = VCL_GetFunction( LibraryHandle, function_name );
  if( Result )
    return Result;

  return inherited::GetFunction( function_name );
}
//------------------------------------------------------------------------------
inline void _stdcall CTSLGenericInt::SendStartCommand( float ARate )
{
  static void *__0_FuncPtr_ = NULL;
  if( __0_FuncPtr_ == NULL )
    __0_FuncPtr_ = (void *)( GetFunction( "@Slgenericvcinteger@TSLGenericVCInteger@SendStartCommand$qf" ));

  void *__0_ThisPtr_ = Get_VCL_Handle();

  if( __0_FuncPtr_ )
    {
    float __1_Param2 = ARate;

    _asm
      {
      push eax
      push edx
      push ecx
	  push __1_Param2

	  push dword ptr [ __0_ThisPtr_ ]
      call dword ptr [ __0_FuncPtr_ ]

      pop  ecx
      pop  ecx

      pop  ecx
      pop  edx
      pop  eax
      }
    }

}
//------------------------------------------------------------------------------
inline void CTSLGenericInt::SendStopCommand()
{
  static void *__0_FuncPtr_ = NULL;
  if( __0_FuncPtr_ == NULL )
    __0_FuncPtr_ = (void *)( GetFunction( "@Slgenericvcinteger@TSLGenericVCInteger@SendStopCommand$qqrv" ));

  void *__0_ThisPtr_ = Get_VCL_Handle();

  if( __0_FuncPtr_ )
    {
    _asm
      {
      push eax
      mov  eax,dword ptr [ __0_ThisPtr_ ]
      call dword ptr [ __0_FuncPtr_ ]
      pop  eax
      }
    }

}
//------------------------------------------------------------------------------
inline void CTSLGenericInt::SendData( TSLCIntegerBuffer OutBuffer )
{
  const TSLUniVCBufferProxy *ABufferProxy = OutBuffer.GetProxy();
  static void *__0_FuncPtr_ = NULL;
  if( __0_FuncPtr_ == NULL )
    __0_FuncPtr_ = (void *)( GetFunction( "@Slgenericvcinteger@TSLGenericVCInteger@SendData$qqrp19TSLUniVCBufferProxy" ));

  void *__0_ThisPtr_ = Get_VCL_Handle();

  if( __0_FuncPtr_ )
    {
    const void * __1_Param1 = ABufferProxy;

    _asm
      {
      push eax
      push edx
      mov edx,__1_Param1
      mov  eax,dword ptr [ __0_ThisPtr_ ]
      call dword ptr [ __0_FuncPtr_ ]
      pop  edx
      pop  eax
      }
    }

}
//------------------------------------------------------------------------------
inline void CTSLGenericInt::ClearQueue()
{
  static void *__0_FuncPtr_ = NULL;
  if( __0_FuncPtr_ == NULL )
    __0_FuncPtr_ = (void *)( GetFunction( "@Slgenericvcinteger@TSLGenericVCInteger@ClearQueue$qqrv" ));

  void *__0_ThisPtr_ = Get_VCL_Handle();

  if( __0_FuncPtr_ )
    {
    _asm
      {
      push eax
      mov  eax,dword ptr [ __0_ThisPtr_ ]
      call dword ptr [ __0_FuncPtr_ ]
      pop  eax
      }
    }

}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
inline void __stdcall CSLProcessIntegerEvent::IntOnFilterEvent( void *Sender, TSLUniVCBufferProxy *BufferIn, TSLUniVCBufferProxy *BufferOut, BOOL *SendOutputData )
{
  TSLCIntegerBuffer InBuffer( BufferIn );
  TSLCIntegerBuffer OutBuffer( BufferOut );

  bool aSendOutputData = ( *SendOutputData ) != 0;

  ( m_Instance->*m_CallBackFunction )( Sender, InBuffer, OutBuffer, aSendOutputData );

  *SendOutputData = (BOOL)aSendOutputData; 

}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
#endif   // CSLGenericIntCode_H_
//------------------------------------------------------------------------------
