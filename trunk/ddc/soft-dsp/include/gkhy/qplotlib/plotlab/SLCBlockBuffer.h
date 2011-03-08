////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//     This software is supplied under the terms of a license agreement or    //
//     nondisclosure agreement with Boian Mitov and may not be copied         //
//     or disclosed except in accordance with the terms of that agreement.    //
//          Copyright(c) 2002-2009 Boian Mitov. All Rights Reserved.          //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#ifndef SLCBlockBufferH
#define SLCBlockBufferH
//---------------------------------------------------------------------------
#include <SLCBufferDefs.h>
#include <SLCGenericBuffer.h>

#ifdef __CLR_VER
namespace Mitov
{
namespace SignalLab
{
#endif

#ifndef __BORLANDC__
  typedef TSLVCSimpleBlockBuffer TSLBlockBuffer;
#endif

#ifndef __CLR_VER
class PACKAGE TSLCBlockBuffer;
#endif

//==============================================================================
//   CLASS TSLCBlockBuffer -- Real Data Buffer Class
//==============================================================================

#ifdef __CLR_VER
#define TSLCBlockBuffer BlockBuffer

class TSLExposedBlockBuffer : public TSLBlockBuffer
{
  friend ref class TSLCBlockBuffer;
};

public ref class TSLCBlockBuffer : public TSLCGenericBuffer
{
#else
class PACKAGE TSLCBlockBuffer : public TSLCGenericBuffer
{
  class TSLExposedBlockBuffer : public TSLBlockBuffer
  {
    friend class TSLCBlockBuffer;
  };
#endif

public:
    //
    //  Member Functions
    TSLCBlockBuffer()
        :  pPasBuffer( (TSLExposedBlockBuffer *)new TSLBlockBuffer(( unsigned int)0 ))
        {
        pPasBuffer->_AddRef();
        PopulateCahces();
        }

    TSLCBlockBuffer(int size);
    TSLCBlockBuffer( const TSLCBlockBuffer __REF other);
#ifdef __CLR_VER
    TSLCBlockBuffer( bool, int Handle ) {}
    TSLCBlockBuffer( array<const System::Byte> ^ AData );
#endif
    TSLCBlockBuffer( TSLBlockBuffer *PascalBuffer );
    TSLCBlockBuffer( const BYTE *AData, int ASize );

#ifndef __BORLANDC__
    // Provides VC++ buffer access proxy.
    TSLCBlockBuffer( TSLUniVCBufferProxy *VCBufferProxy );
#endif

    virtual ~TSLCBlockBuffer();
    //
    //  Buffer operations
    void  RemoveOwnerShip();
#ifndef __CLR_VER
    TSLCBlockBuffer & operator ()()
        { return *this; };
#endif

    void    Resize( int size, bool preserve_data )
        {
        pPasBuffer->Resize( size, preserve_data );
        PopulateCahces();
        }

    void    Resize( int size )
        {
        pPasBuffer->Resize( size, false );
        PopulateCahces();
        }

public:
  void      Copy( __CONST TSLCBlockBuffer __REF Src);
  void      Set( BYTE value );
  void      Zero();

  bool      IsEqual( __CONST TSLCBlockBuffer __REF Other ) __CONST;
  bool      IsEqual( BYTE value ) __CONST;

public:
  const BYTE *Read() __CONST
    {
    return (const BYTE *)FDataPtr; 
    }

  BYTE *Write()
    {
    Unique( false );
    return (BYTE *)FDataPtr;
    }

  BYTE *Modify()
    {
    Unique( true );
    return (BYTE *)FDataPtr;
    }

#ifndef __CLR_VER
  operator BYTE * ()
      { return Write(); };

  operator const BYTE * () const
      { return Read(); };

  BYTE operator [] ( int Index ) const
    {
    return ((BYTE *)FDataPtr )[ Index ];
    }

  BYTE & operator [] ( int Index )
    {
    Unique( true );
    return ((BYTE *)FDataPtr )[ Index ];
    }

  TSLCBlockBuffer& operator = (const TSLCBlockBuffer & rhs) { Assign( rhs ); return *this; }
  TSLCBlockBuffer& operator = (BYTE rhs)                     { Set( rhs ); return *this; }

#else
public:
    property BYTE default[int]
    {
        BYTE get( int index )
        {
            if( index < 0 || index >= (int)GetSize() )
                throw gcnew System::IndexOutOfRangeException();

            return ((BYTE *)FDataPtr )[ index ];
        }

        void set( int index, BYTE value )
        {
            if( index < 0 || index >= (int)GetSize() )
                throw gcnew System::IndexOutOfRangeException();

            Unique( true );
            ((BYTE *)FDataPtr )[ index ] = value;
        }
    }

    property BYTE default[unsigned int]
    {
        BYTE get( unsigned int index )
        {
            if( index >= GetSize() )
                throw gcnew System::IndexOutOfRangeException();

            return ((BYTE *)FDataPtr )[ index ];
        }

        void set( unsigned int index, BYTE value )
        {
            if( index >= GetSize() )
                throw gcnew System::IndexOutOfRangeException();

            Unique( true );
            ((BYTE *)FDataPtr )[ index ] = value;
        }
    }

  static bool operator == ( TSLCBlockBuffer ^ lhs, TSLCBlockBuffer ^ rhs) { return lhs->IsEqual( rhs ); }
  static bool operator != ( TSLCBlockBuffer ^ lhs, TSLCBlockBuffer ^ rhs) { return ! lhs->IsEqual( rhs ); }

  static bool operator == ( TSLCBlockBuffer ^ lhs, BYTE rhs) { return lhs->IsEqual( rhs ); }
  static bool operator != ( TSLCBlockBuffer ^ lhs, BYTE rhs) { return ! lhs->IsEqual( rhs ); }

  static bool operator == ( BYTE lhs, TSLCBlockBuffer ^ rhs) { return rhs->IsEqual( lhs ); }
  static bool operator != ( BYTE lhs, TSLCBlockBuffer ^ rhs) { return ! rhs->IsEqual( lhs ); }
  
#endif

protected:
    mutable TSLExposedBlockBuffer *  pPasBuffer;
    
public:
  virtual void *GetPasBuffer() __OVERRIDE __CONST { return pPasBuffer; }
  
protected:
    //
    //  Member functions
    virtual void Assign( const TSLCBlockBuffer __REF other );
    virtual void Assign( const BYTE *AData, int ASize );

public :
    virtual unsigned int GetSize() __OVERRIDE __CONST { return pPasBuffer->GetSize(); };

};
//---------------------------------------------------------------------------
#ifdef __CLR_VER
} // namespace Mitov
} // namespace SignalLab
#endif
//---------------------------------------------------------------------------
#endif
