////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//     This software is supplied under the terms of a license agreement or    //
//     nondisclosure agreement with Boian Mitov and may not be copied         //
//     or disclosed except in accordance with the terms of that agreement.    //
//          Copyright(c) 2002-2009 Boian Mitov. All Rights Reserved.          //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#ifndef SLCIntegerBufferH
#define SLCIntegerBufferH
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
  typedef TSLVCSimpleIntegerBuffer TSLIntegerBuffer;
#endif

#ifndef __CLR_VER

class PACKAGE TSLCIntegerBuffer;

#endif

//==============================================================================
//   CLASS TSLCIntegerBuffer -- Integer Data Buffer Class
//==============================================================================

#ifdef __CLR_VER
#define TSLCIntegerBuffer IntegerBuffer

public class TSLExposedIntegerBuffer : public TSLIntegerBuffer
{
  friend ref class TSLCIntegerBuffer;
};

public ref class TSLCIntegerBuffer : public TSLCGenericBuffer
{
#else
class PACKAGE TSLCIntegerBuffer : public TSLCGenericBuffer
{
  class TSLExposedIntegerBuffer : public TSLIntegerBuffer
  {
    friend class TSLCIntegerBuffer;
  };
#endif

public:
    //
    //  Member Functions
    TSLCIntegerBuffer();
    TSLCIntegerBuffer( int size );
    TSLCIntegerBuffer( const TSLCIntegerBuffer __REF other );
#ifdef __CLR_VER
    TSLCIntegerBuffer( bool, int Handle ) {}
    TSLCIntegerBuffer( array<const int> ^ AData );
#endif
    TSLCIntegerBuffer( TSLIntegerBuffer *PascalBuffer );
    TSLCIntegerBuffer( int *AData, int ASize );

#ifndef __BORLANDC__
    // Provides VC++ buffer access proxy.
    TSLCIntegerBuffer( TSLUniVCBufferProxy *VCBufferProxy );
#endif

    virtual ~TSLCIntegerBuffer();
    //
    //  Buffer operations
    void  RemoveOwnerShip();

#ifndef __CLR_VER
    TSLCIntegerBuffer & operator ()()
        { return *this; };
#endif

    void      Resize( int size, bool preserve_data )
        {
        pPasBuffer->Resize( size, preserve_data );
        PopulateCahces();
        }

    void      Resize(int size)
        {
        pPasBuffer->Resize( size, false );
        PopulateCahces();
        }

public:
#ifdef __CLR_VER
public:
  array<int> ^ ToArray();
#endif

public:
  void       Copy( __CONST TSLCIntegerBuffer __REF Src );
  void       Set( int Value );
  void       Zero();

  void       Add( int Value );
  void       Add( __CONST TSLCIntegerBuffer __REF  Src);

  void       Multiply( int Value );
  void       Multiply( __CONST TSLCIntegerBuffer __REF Src);

  void       Divide( int Value );
  void       Divide( __CONST TSLCIntegerBuffer __REF Src);

  void       Subtract( int Value );
  void       Subtract( __CONST TSLCIntegerBuffer __REF Src);

  int        Dot( __CONST TSLCIntegerBuffer __REF Src);

  void       And( int Value );
  void       And( __CONST TSLCIntegerBuffer __REF Src);

  void       Or( int Value );
  void       Or( __CONST TSLCIntegerBuffer __REF Src);

  void       Xor( int Value );
  void       Xor( __CONST TSLCIntegerBuffer __REF Src);

  void       Mod( int Value );
  void       Mod( __CONST TSLCIntegerBuffer __REF Src);

  void       LShift( int Value );
  void       LShift( __CONST TSLCIntegerBuffer __REF Src );
  
  void       RShift( int Value );
  void       RShift( __CONST TSLCIntegerBuffer __REF Src );

public:
  bool IsEqual( int Value ) __CONST;
  bool IsEqual( __CONST TSLCIntegerBuffer __REF Other) __CONST;

  const int *Read() __CONST
    {
    return (const int *)FDataPtr;
    }
    
  int *Write()
    {
    Unique( false );
    return (int *)FDataPtr;
    }

  int *Modify()
    {
    Unique( true );
    return (int *)FDataPtr;
    }

#ifndef __CLR_VER
  int operator [] ( int Index ) const
    {
    return ((int *)FDataPtr )[ Index ];
    }

  int & operator [] ( int Index )
    {
    Unique( true );
    return ((int *)FDataPtr )[ Index ];
    }

  operator int * ()
      { return Write(); }

  operator const int * () const
      { return Read(); }
        
  TSLCIntegerBuffer& operator = (const TSLCIntegerBuffer &rhs)  { Assign( rhs ); return *this; }
  TSLCIntegerBuffer& operator = ( int rhs)                          { Set( rhs ); return *this; }
  TSLCIntegerBuffer& operator += (const TSLCIntegerBuffer& rhs) { Add( rhs ); return *this; }
  TSLCIntegerBuffer& operator += ( int rhs)                         { Add( rhs ); return *this; }
  TSLCIntegerBuffer& operator -= (const TSLCIntegerBuffer& rhs) { Subtract( rhs ); return *this; }
  TSLCIntegerBuffer& operator -= ( int rhs)                         { Subtract( rhs ); return *this; }
  TSLCIntegerBuffer& operator *= (const TSLCIntegerBuffer& rhs) { Multiply( rhs ); return *this; }
  TSLCIntegerBuffer& operator *= ( int rhs)                         { Multiply( rhs ); return *this; }
  TSLCIntegerBuffer& operator /= (const TSLCIntegerBuffer& rhs) { Divide( rhs ); return *this; }
  TSLCIntegerBuffer& operator /= ( int rhs)                         { Divide( rhs ); return *this; }
  TSLCIntegerBuffer& operator %= (const TSLCIntegerBuffer& rhs) { Mod(rhs); return *this; }
  TSLCIntegerBuffer& operator %= ( int rhs)                         { Mod(rhs); return *this; }

  TSLCIntegerBuffer& operator &= (const TSLCIntegerBuffer& rhs) { And(rhs); return *this; }
  TSLCIntegerBuffer& operator &= ( int rhs)                         { And(rhs); return *this; }
  TSLCIntegerBuffer& operator |= (const TSLCIntegerBuffer& rhs) { Or(rhs); return *this; }
  TSLCIntegerBuffer& operator |= ( int rhs)                         { Or(rhs); return *this; }
  TSLCIntegerBuffer& operator ^= (const TSLCIntegerBuffer& rhs) { Xor(rhs); return *this; }
  TSLCIntegerBuffer& operator ^= ( int rhs)                         { Xor(rhs); return *this; }

  TSLCIntegerBuffer& operator <<= ( int rhs )                       { LShift(rhs); return *this; }
  TSLCIntegerBuffer& operator <<= ( const TSLCIntegerBuffer& rhs )  { LShift(rhs); return *this; }

  TSLCIntegerBuffer& operator >>= ( int rhs )                       { RShift(rhs); return *this; }
  TSLCIntegerBuffer& operator >>= ( const TSLCIntegerBuffer& rhs )  { RShift(rhs); return *this; }
#else
  static TSLCIntegerBuffer ^ operator + ( TSLCIntegerBuffer ^ lhs, TSLCIntegerBuffer ^ rhs) { TSLCIntegerBuffer ^ tmp = gcnew TSLCIntegerBuffer( lhs ); tmp->Add( rhs ); return tmp; }
  static TSLCIntegerBuffer ^ operator + ( TSLCIntegerBuffer ^ lhs, int rhs) { TSLCIntegerBuffer ^ tmp = gcnew TSLCIntegerBuffer( lhs ); tmp->Add( rhs ); return tmp; }
  static TSLCIntegerBuffer ^ operator + ( int lhs, TSLCIntegerBuffer ^ rhs) { TSLCIntegerBuffer ^ tmp = gcnew TSLCIntegerBuffer( rhs ); tmp->Add( lhs ); return tmp; }

  static TSLCIntegerBuffer ^ operator - ( TSLCIntegerBuffer ^ lhs, TSLCIntegerBuffer ^ rhs) { TSLCIntegerBuffer ^ tmp = gcnew TSLCIntegerBuffer( lhs ); tmp->Subtract( rhs ); return tmp; }
  static TSLCIntegerBuffer ^ operator - ( TSLCIntegerBuffer ^ lhs, int rhs) { TSLCIntegerBuffer ^ tmp = gcnew TSLCIntegerBuffer( lhs ); tmp->Subtract( rhs ); return tmp; }
  static TSLCIntegerBuffer ^ operator - ( int lhs, TSLCIntegerBuffer ^ rhs) { TSLCIntegerBuffer ^ tmp = gcnew TSLCIntegerBuffer( rhs ); tmp->Subtract( lhs ); return tmp; }
  
  static TSLCIntegerBuffer ^ operator * ( TSLCIntegerBuffer ^ lhs, TSLCIntegerBuffer ^ rhs) { TSLCIntegerBuffer ^ tmp = gcnew TSLCIntegerBuffer( lhs ); tmp->Multiply( rhs ); return tmp; }
  static TSLCIntegerBuffer ^ operator * ( TSLCIntegerBuffer ^ lhs, int rhs) { TSLCIntegerBuffer ^ tmp = gcnew TSLCIntegerBuffer( lhs ); tmp->Multiply( rhs ); return tmp; }
  static TSLCIntegerBuffer ^ operator * ( int lhs, TSLCIntegerBuffer ^ rhs) { TSLCIntegerBuffer ^ tmp = gcnew TSLCIntegerBuffer( rhs ); tmp->Multiply( lhs ); return tmp; }
  
  static TSLCIntegerBuffer ^ operator / ( TSLCIntegerBuffer ^ lhs, TSLCIntegerBuffer ^ rhs) { TSLCIntegerBuffer ^ tmp = gcnew TSLCIntegerBuffer( lhs ); tmp->Divide( rhs ); return tmp; }
  static TSLCIntegerBuffer ^ operator / ( TSLCIntegerBuffer ^ lhs, int rhs) { TSLCIntegerBuffer ^ tmp = gcnew TSLCIntegerBuffer( lhs ); tmp->Divide( rhs ); return tmp; }

  static TSLCIntegerBuffer ^ operator & ( TSLCIntegerBuffer ^ lhs, TSLCIntegerBuffer ^ rhs) { TSLCIntegerBuffer ^ tmp = gcnew TSLCIntegerBuffer( lhs ); tmp->And( rhs ); return tmp; }
  static TSLCIntegerBuffer ^ operator & ( TSLCIntegerBuffer ^ lhs, int rhs) { TSLCIntegerBuffer ^ tmp = gcnew TSLCIntegerBuffer( lhs ); tmp->And( rhs ); return tmp; }
  static TSLCIntegerBuffer ^ operator & ( int lhs, TSLCIntegerBuffer ^ rhs) { TSLCIntegerBuffer ^ tmp = gcnew TSLCIntegerBuffer( rhs ); tmp->And( lhs ); return tmp; }

  static TSLCIntegerBuffer ^ operator | ( TSLCIntegerBuffer ^ lhs, TSLCIntegerBuffer ^ rhs) { TSLCIntegerBuffer ^ tmp = gcnew TSLCIntegerBuffer( lhs ); tmp->Or( rhs ); return tmp; }
  static TSLCIntegerBuffer ^ operator | ( TSLCIntegerBuffer ^ lhs, int rhs) { TSLCIntegerBuffer ^ tmp = gcnew TSLCIntegerBuffer( lhs ); tmp->Or( rhs ); return tmp; }
  static TSLCIntegerBuffer ^ operator | ( int lhs, TSLCIntegerBuffer ^ rhs) { TSLCIntegerBuffer ^ tmp = gcnew TSLCIntegerBuffer( rhs ); tmp->Or( lhs ); return tmp; }

  static TSLCIntegerBuffer ^ operator ^ ( TSLCIntegerBuffer ^ lhs, TSLCIntegerBuffer ^ rhs) { TSLCIntegerBuffer ^ tmp = gcnew TSLCIntegerBuffer( lhs ); tmp->Xor( rhs ); return tmp; }
  static TSLCIntegerBuffer ^ operator ^ ( TSLCIntegerBuffer ^ lhs, int rhs) { TSLCIntegerBuffer ^ tmp = gcnew TSLCIntegerBuffer( lhs ); tmp->Xor( rhs ); return tmp; }
  static TSLCIntegerBuffer ^ operator ^ ( int lhs, TSLCIntegerBuffer ^ rhs) { TSLCIntegerBuffer ^ tmp = gcnew TSLCIntegerBuffer( rhs ); tmp->Xor( lhs ); return tmp; }

  static TSLCIntegerBuffer ^ operator % ( TSLCIntegerBuffer ^ lhs, TSLCIntegerBuffer ^ rhs) { TSLCIntegerBuffer ^ tmp = gcnew TSLCIntegerBuffer( lhs ); tmp->Mod( rhs ); return tmp; }
  static TSLCIntegerBuffer ^ operator % ( TSLCIntegerBuffer ^ lhs, int rhs) { TSLCIntegerBuffer ^ tmp = gcnew TSLCIntegerBuffer( lhs ); tmp->Mod( rhs ); return tmp; }
  static TSLCIntegerBuffer ^ operator % ( int lhs, TSLCIntegerBuffer ^ rhs) { TSLCIntegerBuffer ^ tmp = gcnew TSLCIntegerBuffer( rhs ); tmp->Mod( lhs ); return tmp; }

  static TSLCIntegerBuffer ^ operator << ( TSLCIntegerBuffer ^ lhs, int rhs) { TSLCIntegerBuffer ^ tmp = gcnew TSLCIntegerBuffer( lhs ); tmp->LShift( rhs ); return tmp; }
  static TSLCIntegerBuffer ^ operator << ( TSLCIntegerBuffer ^ lhs, TSLCIntegerBuffer ^ rhs) { TSLCIntegerBuffer ^ tmp = gcnew TSLCIntegerBuffer( lhs ); tmp->LShift( rhs ); return tmp; }
  static TSLCIntegerBuffer ^ operator >> ( TSLCIntegerBuffer ^ lhs, int rhs) { TSLCIntegerBuffer ^ tmp = gcnew TSLCIntegerBuffer( lhs ); tmp->RShift( rhs ); return tmp; }
  static TSLCIntegerBuffer ^ operator >> ( TSLCIntegerBuffer ^ lhs, TSLCIntegerBuffer ^ rhs) { TSLCIntegerBuffer ^ tmp = gcnew TSLCIntegerBuffer( lhs ); tmp->RShift( rhs ); return tmp; }

  static bool operator == ( TSLCIntegerBuffer ^ lhs, TSLCIntegerBuffer ^ rhs) { return lhs->IsEqual( rhs ); }
  static bool operator != ( TSLCIntegerBuffer ^ lhs, TSLCIntegerBuffer ^ rhs) { return ! lhs->IsEqual( rhs ); }

  static bool operator == ( TSLCIntegerBuffer ^ lhs, int rhs) { return lhs->IsEqual( rhs ); }
  static bool operator != ( TSLCIntegerBuffer ^ lhs, int rhs) { return ! lhs->IsEqual( rhs ); }

  static bool operator == ( int lhs, TSLCIntegerBuffer ^ rhs) { return rhs->IsEqual( lhs ); }
  static bool operator != ( int lhs, TSLCIntegerBuffer ^ rhs) { return ! rhs->IsEqual( lhs ); }

#endif

protected:
    mutable TSLExposedIntegerBuffer *  pPasBuffer;

public:
  virtual void *GetPasBuffer() __OVERRIDE __CONST { return pPasBuffer; }

protected:
    //
    //  Member functions
    virtual void Assign( const TSLCIntegerBuffer __REF other );
    virtual void Assign( const int *AData, int ASize );

#ifdef __CLR_VER
public:
    property int default[int] 
    { 
        int get( int index ) 
        { 
            if( index < 0 || index >= (int)GetSize() )
                throw gcnew System::IndexOutOfRangeException();

            return ((int *)FDataPtr )[ index ]; 
        }

        void set( int index, int value )
        {
            if( index < 0 || index >= (int)GetSize() )
                throw gcnew System::IndexOutOfRangeException();

            Unique( true );
            ((int *)FDataPtr )[ index ] = value;
        }
    }

    property int default[unsigned int] 
    { 
        int get( unsigned int index ) 
        { 
            if( index >= GetSize() )
                throw gcnew System::IndexOutOfRangeException();

            return ((int *)FDataPtr )[ index ]; 
        }

        void set( unsigned int index, int value )
        {
            if( index >= GetSize() )
                throw gcnew System::IndexOutOfRangeException();

            Unique( true );
            ((int *)FDataPtr )[ index ] = value;
        }
    }
#endif

public :
    virtual unsigned int GetSize() __OVERRIDE __CONST { return pPasBuffer->GetSize(); };

};

//---------------------------------------------------------------------------

#ifndef __CLR_VER
//---------------------------------------------------------------------------
TSLCIntegerBuffer operator + (const TSLCIntegerBuffer& lhs, const TSLCIntegerBuffer& rhs);
TSLCIntegerBuffer operator + (const int Value, const TSLCIntegerBuffer& rhs);
TSLCIntegerBuffer operator + (const TSLCIntegerBuffer& lhs, const int Value);

TSLCIntegerBuffer operator - (const TSLCIntegerBuffer& lhs, const TSLCIntegerBuffer& rhs);
TSLCIntegerBuffer operator - (const TSLCIntegerBuffer& lhs, const int Value);
TSLCIntegerBuffer operator - (const TSLCIntegerBuffer& lhs);

TSLCIntegerBuffer operator * (const TSLCIntegerBuffer& lhs, const TSLCIntegerBuffer& rhs);
TSLCIntegerBuffer operator * (const TSLCIntegerBuffer& lhs, const int Value);
TSLCIntegerBuffer operator * (const int Value, const TSLCIntegerBuffer& rhs);

TSLCIntegerBuffer operator / (const TSLCIntegerBuffer& lhs, const TSLCIntegerBuffer& rhs);
TSLCIntegerBuffer operator / (const TSLCIntegerBuffer& lhs, const int Value);

TSLCIntegerBuffer operator & (const TSLCIntegerBuffer& lhs, const TSLCIntegerBuffer& rhs);
TSLCIntegerBuffer operator & (const int Value, const TSLCIntegerBuffer& rhs);
TSLCIntegerBuffer operator & (const TSLCIntegerBuffer& lhs, const int Value);

TSLCIntegerBuffer operator | (const TSLCIntegerBuffer& lhs, const TSLCIntegerBuffer& rhs);
TSLCIntegerBuffer operator | (const int Value, const TSLCIntegerBuffer& rhs);
TSLCIntegerBuffer operator | (const TSLCIntegerBuffer& lhs, const int Value);

TSLCIntegerBuffer operator ^ (const TSLCIntegerBuffer& lhs, const TSLCIntegerBuffer& rhs);
TSLCIntegerBuffer operator ^ (const int Value, const TSLCIntegerBuffer& rhs);
TSLCIntegerBuffer operator ^ (const TSLCIntegerBuffer& lhs, const int Value);

TSLCIntegerBuffer operator << (const TSLCIntegerBuffer& lhs, const int Value);
TSLCIntegerBuffer operator >> (const TSLCIntegerBuffer& lhs, const int Value);

bool operator == (const TSLCIntegerBuffer & lhs, const TSLCIntegerBuffer & rhs);
bool operator != (const TSLCIntegerBuffer & lhs, const TSLCIntegerBuffer & rhs);

bool operator == (const TSLCIntegerBuffer & lhs, int rhs);
bool operator != (const TSLCIntegerBuffer & lhs, int rhs);

bool operator == ( int lhs, const TSLCIntegerBuffer & rhs);
bool operator != ( int lhs, const TSLCIntegerBuffer & rhs);
//---------------------------------------------------------------------------

inline TSLCIntegerBuffer operator + (const TSLCIntegerBuffer& lhs, const TSLCIntegerBuffer& rhs) { TSLCIntegerBuffer tmp( lhs ); return tmp += rhs; }
inline TSLCIntegerBuffer operator + (const int Value, const TSLCIntegerBuffer& rhs) { TSLCIntegerBuffer tmp(rhs); return tmp += Value; }
inline TSLCIntegerBuffer operator + (const TSLCIntegerBuffer& lhs, const int Value) { TSLCIntegerBuffer tmp(lhs); return tmp += Value; }

inline TSLCIntegerBuffer operator - (const TSLCIntegerBuffer& lhs, const TSLCIntegerBuffer& rhs) { TSLCIntegerBuffer tmp(lhs); return tmp -= rhs; }
inline TSLCIntegerBuffer operator - (const TSLCIntegerBuffer& lhs, const int Value) { TSLCIntegerBuffer tmp(lhs); return tmp -= Value; }
inline TSLCIntegerBuffer operator - (const TSLCIntegerBuffer& lhs) { TSLCIntegerBuffer tmp(lhs); tmp.Multiply(-1); return tmp; }

inline TSLCIntegerBuffer operator * (const TSLCIntegerBuffer& lhs, const TSLCIntegerBuffer& rhs) { TSLCIntegerBuffer tmp(lhs); return tmp *= rhs; }
inline TSLCIntegerBuffer operator * (const TSLCIntegerBuffer& lhs, const int Value) { TSLCIntegerBuffer tmp(lhs); return tmp *= Value; }
inline TSLCIntegerBuffer operator * (const int Value, const TSLCIntegerBuffer& rhs) { TSLCIntegerBuffer tmp(rhs); return tmp *= Value; }

inline TSLCIntegerBuffer operator / (const TSLCIntegerBuffer& lhs, const TSLCIntegerBuffer& rhs) { TSLCIntegerBuffer tmp(lhs); return tmp /= rhs; }
inline TSLCIntegerBuffer operator / (const TSLCIntegerBuffer& lhs, const int Value) { TSLCIntegerBuffer tmp(lhs); return tmp /= Value; }

inline TSLCIntegerBuffer operator & (const TSLCIntegerBuffer& lhs, const TSLCIntegerBuffer& rhs) { TSLCIntegerBuffer tmp(lhs); return tmp &= rhs; }
inline TSLCIntegerBuffer operator & (const int Value, const TSLCIntegerBuffer& rhs) { TSLCIntegerBuffer tmp(rhs); return tmp &= Value; }
inline TSLCIntegerBuffer operator & (const TSLCIntegerBuffer& lhs, const int Value) { TSLCIntegerBuffer tmp(lhs); return tmp &= Value; }

inline TSLCIntegerBuffer operator | (const TSLCIntegerBuffer& lhs, const TSLCIntegerBuffer& rhs) { TSLCIntegerBuffer tmp(lhs); return tmp |= rhs; }
inline TSLCIntegerBuffer operator | (const int Value, const TSLCIntegerBuffer& rhs) { TSLCIntegerBuffer tmp(rhs); return tmp |= Value; }
inline TSLCIntegerBuffer operator | (const TSLCIntegerBuffer& lhs, const int Value) { TSLCIntegerBuffer tmp(lhs); return tmp |= Value; }

inline TSLCIntegerBuffer operator ^ (const TSLCIntegerBuffer& lhs, const TSLCIntegerBuffer& rhs) { TSLCIntegerBuffer tmp(lhs); return tmp ^= rhs; }
inline TSLCIntegerBuffer operator ^ (const int Value, const TSLCIntegerBuffer& rhs) { TSLCIntegerBuffer tmp(rhs); return tmp ^= Value; }
inline TSLCIntegerBuffer operator ^ (const TSLCIntegerBuffer& lhs, const int Value) { TSLCIntegerBuffer tmp(lhs); return tmp ^= Value; }

inline TSLCIntegerBuffer operator << (const TSLCIntegerBuffer& lhs, const int Value) { TSLCIntegerBuffer tmp(lhs); return tmp <<= Value; }
inline TSLCIntegerBuffer operator << (const TSLCIntegerBuffer& lhs, const TSLCIntegerBuffer& rhs) { TSLCIntegerBuffer tmp(lhs); return tmp <<= rhs; }

inline TSLCIntegerBuffer operator >> (const TSLCIntegerBuffer& lhs, const int Value) { TSLCIntegerBuffer tmp(lhs); return tmp >>= Value; }
inline TSLCIntegerBuffer operator >> (const TSLCIntegerBuffer& lhs, const TSLCIntegerBuffer& rhs) { TSLCIntegerBuffer tmp(lhs); return tmp >>= rhs; }

//---------------------------------------------------------------------------
inline bool operator == (const TSLCIntegerBuffer & lhs, const TSLCIntegerBuffer & rhs) { return lhs.IsEqual( rhs ); }
inline bool operator != (const TSLCIntegerBuffer & lhs, const TSLCIntegerBuffer & rhs) { return ! lhs.IsEqual( rhs ); }

inline bool operator == (const TSLCIntegerBuffer & lhs, int rhs) { return lhs.IsEqual( rhs ); }
inline bool operator != (const TSLCIntegerBuffer & lhs, int rhs) { return ! lhs.IsEqual( rhs ); }

inline bool operator == ( int lhs, const TSLCIntegerBuffer & rhs) { return rhs.IsEqual( lhs ); }
inline bool operator != ( int lhs, const TSLCIntegerBuffer & rhs) { return ! rhs.IsEqual( lhs ); }
//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------
#ifdef __CLR_VER
} // namespace Mitov
} // namespace SignalLab
#endif
//---------------------------------------------------------------------------
#endif
