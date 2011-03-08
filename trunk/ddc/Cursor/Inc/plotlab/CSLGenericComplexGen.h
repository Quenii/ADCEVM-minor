//------------------------------------------------------------------------------
//
//                    (C) Copyright Boian Mitov 2005
//                            www.mitov.com
//
//------------------------------------------------------------------------------

#ifndef CSLGenericComplexGen_H_
#define CSLGenericComplexGen_H_

//------------------------------------------------------------------------------
#include <SLCComplexBuffer.h>
//------------------------------------------------------------------------------
#ifndef CVCSignalLabPkgCB6_H_
  #include <CVCSignalLabPkgCB6.h>
#endif

#ifndef CSLCommonGen_H_
  #include <CSLCommonGen.h>
#endif

//------------------------------------------------------------------------------
class CSLGenerateComplexEvent : public CLPBaseEventProperty
{
  typedef CLPBaseEventProperty inherited;

private:
  typedef void (__stdcall CLPComponent::*TProcessCallBackFunction)( void *Sender, TSLCComplexBuffer &BufferOut, bool &Populated, bool &Finished ); 
  TProcessCallBackFunction m_CallBackFunction;
  CLPComponent *m_Instance;

public:
  template< class T > bool Set( T *Instance, void (__stdcall T::*CallBackFunction)( void *Sender, TSLCComplexBuffer &BufferOut, bool &Populated, bool &Finished ) )
  {
    if( CallBackFunction == NULL )
      return Clear();

    else
      {
      m_Instance = (CLPComponent *)Instance;
      m_CallBackFunction = (TProcessCallBackFunction)CallBackFunction; 
      void (__stdcall CSLGenerateComplexEvent::*IntCallBackFunction)( void *Sender, TSLUniVCBufferProxy *BufferOut, BOOL *Populated, BOOL *Finished );
      IntCallBackFunction = &CSLGenerateComplexEvent::IntOnGenerateEvent;
      return m_control->Object->SetEvent( m_PropertyName.c_str(), IntCallBackFunction, this );
      }
  }

private:
  void __stdcall IntOnGenerateEvent( void *Sender, TSLUniVCBufferProxy *BufferOut, BOOL *Populated, BOOL *Finished );

public:
  __LP__CONSTRUCTORS__( CSLGenerateComplexEvent );

};
//------------------------------------------------------------------------------
class CTSLGenericComplexGen : public CTSLCommonComplexGen
{
  typedef CTSLCommonComplexGen inherited;

protected:
	void *LibraryHandle;

protected:
  virtual TLPFunctionEntry  GetFunction( const char *function_name );

public:    // Properties
  CSLGenerateComplexEvent OnGenerate;

public:
  CTSLGenericComplexGen();

};
//------------------------------------------------------------------------------
#include <CSLGenericComplexGenCode.h>
//------------------------------------------------------------------------------
#endif   // CSLGenericComplexGen_H_
//------------------------------------------------------------------------------
