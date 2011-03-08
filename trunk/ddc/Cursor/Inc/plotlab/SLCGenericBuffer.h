////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//     This software is supplied under the terms of a license agreement or    //
//     nondisclosure agreement with Boian Mitov and may not be copied         //
//     or disclosed except in accordance with the terms of that agreement.    //
//          Copyright(c) 2002-2009 Boian Mitov. All Rights Reserved.          //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#ifndef SLCGenericBufferH
#define SLCGenericBufferH
//---------------------------------------------------------------------------
#ifdef __BORLANDC__
  #include <SLSimpleDataBuffer.hpp>
  #include <vcl.h>

#else   // VC++
  #include <SLVCInternalStore.h>

  #define PACKAGE

#endif

#ifdef __CLR_VER
namespace Mitov
{
namespace SignalLab
{
#endif
//---------------------------------------------------------------------------
#ifdef __CLR_VER
  #define __REF ^
  #define __IREF ^
  #define __PREF ^
  #define __CONST
  #define __OVERRIDE override
  #define __DREF ->
  #define __THIS this
  #define INTERNAL internal

#else
  #define __REF &
  #define __IREF
  #define __PREF *
  #define __CONST const
  #define __OVERRIDE
  #define __DREF .
  #define __THIS *this
  #define INTERNAL protected

#endif

//---------------------------------------------------------------------------
#ifndef __BORLANDC__
  #define TSLGenericBuffer TSLVCSimpleGenericBuffer
#endif

#ifndef __CLR_VER
//---------------------------------------------------------------------------
class PACKAGE TSLCGenericBuffer;
//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------
#ifdef __CLR_VER
#define TSLCGenericBuffer GenericBuffer

public ref class TSLCGenericBuffer
{
#else
class PACKAGE TSLCGenericBuffer
{
#endif

protected:
  mutable void *FDataPtr;
  mutable unsigned int   FByteSize;
  mutable unsigned int   FSize;

public:
    virtual void *GetPasBuffer() __CONST { return NULL; }

public:
  TSLGenericBuffer *GetIntPasBuffer() __CONST { return (TSLGenericBuffer *)GetPasBuffer(); }

protected:
  virtual void PopulateCahces() __CONST;

#ifdef __CLR_VER
public:
  TSLCGenericBuffer( bool, int Handle ) {}
  TSLCGenericBuffer( const TSLCGenericBuffer __REF other ) {}
#endif

protected:
  TSLCGenericBuffer();
  
public:
  void  Unique( bool PreserveData ) __CONST
    {
    if( GetIntPasBuffer()->MakeUnique( PreserveData ) )
      PopulateCahces();
    }

public:
  virtual ~TSLCGenericBuffer();

#ifdef __CLR_VER
public:
    property unsigned int Size{ unsigned int get() { return GetSize(); } }
#endif

public:

#ifndef __BORLANDC__
	const TSLUniVCBufferProxy *GetProxy();
#endif

    virtual unsigned int GetSize() __CONST { return 0; }
};
//---------------------------------------------------------------------------
#ifdef __CLR_VER
} // namespace Mitov
} // namespace SignalLab
#endif
//---------------------------------------------------------------------------
#endif

