//------------------------------------------------------------------------------
//
//                    (C) Copyright Boian Mitov 2005
//                            www.mitov.com
//
//------------------------------------------------------------------------------

#ifndef CSLGenericComplex_H_
#define CSLGenericComplex_H_

//------------------------------------------------------------------------------
#ifndef CSLCommonFilter_H_
  #include <CSLCommonFilter.h>
#endif

#include <SLCComplexBuffer.h>
//------------------------------------------------------------------------------
#ifndef CVCSignalLabPkgCB6_H_
  #include <CVCSignalLabPkgCB6.h>
#endif

#ifndef CSLSyncTypes_H_
  #include <CSLSyncTypes.h>
#endif

//------------------------------------------------------------------------------
class CSLProcessComplexEvent : public CLPBaseEventProperty
{
  typedef CLPBaseEventProperty inherited;

private:
  typedef void (__stdcall CLPComponent::*TProcessCallBackFunction)( void *Sender, TSLCComplexBuffer BufferIn, TSLCComplexBuffer &BufferOut, bool &SendOutputData ); 
  TProcessCallBackFunction m_CallBackFunction;
  CLPComponent *m_Instance;

public:
  template< class T > bool Set( T *Instance, void (__stdcall T::*CallBackFunction)( void *Sender, TSLCComplexBuffer BufferIn, TSLCComplexBuffer &BufferOut, bool &SendOutputData ) )
  {
    if( CallBackFunction == NULL )
      return Clear();

    else
      {
      m_Instance = (CLPComponent *)Instance;
      m_CallBackFunction = (TProcessCallBackFunction)CallBackFunction; 
      void (__stdcall CSLProcessComplexEvent::*IntCallBackFunction)( void *Sender, TSLUniVCBufferProxy *BufferIn, TSLUniVCBufferProxy *BufferOut, BOOL *SendOutputData );
      IntCallBackFunction = &CSLProcessComplexEvent::IntOnFilterEvent;
      return m_control->Object->SetEvent( m_PropertyName.c_str(), IntCallBackFunction, this );
      }
  }

private:
  void __stdcall IntOnFilterEvent( void *Sender, TSLUniVCBufferProxy *BufferIn, TSLUniVCBufferProxy *BufferOut, BOOL *SendOutputData );

public:
  __LP__CONSTRUCTORS__( CSLProcessComplexEvent );

};
//------------------------------------------------------------------------------
class CTSLGenericComplex : public CTSLCommonComplexFilter
{
  typedef CTSLCommonComplexFilter inherited;

protected:
	void *LibraryHandle;

protected:
  virtual TLPFunctionEntry  GetFunction( const char *function_name );

public:    // Properties
  CLPEventProperty_2<2, void, void *, float> OnStart;
  CLPEventProperty_1<0, void, void *> OnStop;
  CSLProcessComplexEvent OnProcessData;
  CLPProperty<CTSLSynchronizeType> SynchronizeType;

public:
  void _stdcall SendStartCommand( float ARate );
  void SendStopCommand();
  void SendData( TSLCComplexBuffer OutBuffer );
  void ClearQueue();

public:
  CTSLGenericComplex();

};
//------------------------------------------------------------------------------
#include <CSLGenericComplexCode.h>
//------------------------------------------------------------------------------
#endif   // CSLGenericComplex_H_
//------------------------------------------------------------------------------
