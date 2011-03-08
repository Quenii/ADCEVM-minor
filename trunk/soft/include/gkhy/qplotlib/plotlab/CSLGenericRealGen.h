//------------------------------------------------------------------------------
//
//                    (C) Copyright Boian Mitov 2005
//                            www.mitov.com
//
//------------------------------------------------------------------------------

#ifndef CSLGenericRealGen_H_
#define CSLGenericRealGen_H_

//------------------------------------------------------------------------------
#ifndef VCLSupportH
  #include <VCLSupport.h>
#endif

#include <SLCRealBuffer.h>
//------------------------------------------------------------------------------
#ifndef CVCSignalLabPkgCB6_H_
  #include <CVCSignalLabPkgCB6.h>
#endif

#ifndef CSLCommonGen_H_
  #include <CSLCommonGen.h>
#endif

//------------------------------------------------------------------------------
class CSLGenerateRealEvent : public CLPBaseEventProperty
{
  typedef CLPBaseEventProperty inherited;

private:
  typedef void (__stdcall CLPComponent::*TProcessCallBackFunction)( void *Sender, TSLCRealBuffer &BufferOut, bool &Populated, bool &Finished ); 
  TProcessCallBackFunction m_CallBackFunction;
  CLPComponent *m_Instance;

public:
  template< class T > bool Set( T *Instance, void (__stdcall T::*CallBackFunction)( void *Sender, TSLCRealBuffer &BufferOut, bool &Populated, bool &Finished ) )
  {
    if( CallBackFunction == NULL )
      return Clear();

    else
      {
      m_Instance = (CLPComponent *)Instance;
      m_CallBackFunction = (TProcessCallBackFunction)CallBackFunction; 
      void (__stdcall CSLGenerateRealEvent::*IntCallBackFunction)( void *Sender, TSLUniVCBufferProxy *BufferOut, BOOL *Populated, BOOL *Finished );
      IntCallBackFunction = &CSLGenerateRealEvent::IntOnGenerateEvent;
      return m_control->Object->SetEvent( m_PropertyName.c_str(), IntCallBackFunction, this );
      }
  }

private:
  void __stdcall IntOnGenerateEvent( void *Sender, TSLUniVCBufferProxy *BufferOut, BOOL *Populated, BOOL *Finished );

public:
  __LP__CONSTRUCTORS__( CSLGenerateRealEvent );

};
//------------------------------------------------------------------------------
class CTSLGenericRealGen : public CTSLCommonRealGen
{
  typedef CTSLCommonRealGen inherited;

protected:
	void *LibraryHandle;

protected:
  virtual TLPFunctionEntry  GetFunction( const char *function_name );

public:    // Properties
  CSLGenerateRealEvent OnGenerate;

public:
  CTSLGenericRealGen();

};
//------------------------------------------------------------------------------
#include <CSLGenericRealGenCode.h>
//------------------------------------------------------------------------------
#endif   // CSLGenericRealGen_H_
//------------------------------------------------------------------------------
