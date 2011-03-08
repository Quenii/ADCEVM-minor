////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//     This software is supplied under the terms of a license agreement or    //
//     nondisclosure agreement with Boian Mitov and may not be copied         //
//     or disclosed except in accordance with the terms of that agreement.    //
//          Copyright(c) 2002-2009 Boian Mitov. All Rights Reserved.          //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#ifndef SLCComplexBufferH
#define SLCComplexBufferH
//---------------------------------------------------------------------------
#include <SLCRealBuffer.h>

#ifdef __CLR_VER
namespace Mitov
{
namespace SignalLab
{
#endif

#ifndef __BORLANDC__   // VC++
  typedef TSLVCSimpleComplexBuffer TSLComplexBuffer;
#endif

#ifndef __CLR_VER
class PACKAGE TSLCComplexBuffer;
#endif

//==============================================================================
//   CLASS TSLCComplexBuffer -- Complex Data Buffer Class
//==============================================================================

#ifdef __CLR_VER
#define TSLCComplexBuffer ComplexBuffer

class TSLExposedComplexBuffer : public TSLComplexBuffer
{
  friend ref class TSLCComplexBuffer;
};

public ref class TSLCExposedRealBuffer : public TSLCRealBuffer
{
//  friend ref class TSLCComplexBuffer;
};

public ref class TSLCComplexBuffer : public TSLCGenericBuffer
{
#else
class PACKAGE TSLCComplexBuffer : public TSLCGenericBuffer
{
  class TSLExposedComplexBuffer : public TSLComplexBuffer
  {
    friend class TSLCComplexBuffer;
  };

  class TSLCExposedRealBuffer : public TSLCRealBuffer
  {
    friend class TSLCComplexBuffer;
  };
#endif

public:
    //
    //  Member Functions
    TSLCComplexBuffer();
    TSLCComplexBuffer(int size);
    TSLCComplexBuffer(const TSLCComplexBuffer __REF other);
#ifdef __CLR_VER
    TSLCComplexBuffer( bool, int Handle ) {}
//    TSLCComplexBuffer( array<const TOWRealComplex> ^ AData );
#endif
    TSLCComplexBuffer( TSLComplexBuffer *PascalBuffer );
    TSLCComplexBuffer( TOWRealComplex *AData, int Size );

#ifndef __BORLANDC__
    // Provides VC++ buffer access proxy.
    TSLCComplexBuffer( TSLUniVCBufferProxy *VCBufferProxy );
#endif

    virtual ~TSLCComplexBuffer();
    //
    //  Buffer operations
    void  RemoveOwnerShip();

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
  void       Set( __CONST TSLCRealBuffer __REF RealValue, __CONST TSLCRealBuffer __REF ImagValue );
  void       Set( double Real, double Imaginary );
  void       Set( TOWRealComplex Value );
  void       Zero();

  void       Copy( __CONST TSLCComplexBuffer __REF Src );

  void       Add( TOWRealComplex Value );
  void       Add( double Real, double Imaginary );
  void       Add( __CONST TSLCComplexBuffer __REF Src);

  void       Multiply( TOWRealComplex Value );
  void       Multiply( double Real, double Imaginary );
  void       Multiply( __CONST TSLCComplexBuffer __REF Src);

  void       Divide( TOWRealComplex Value );
  void       Divide( double Real, double Imaginary );
  void       Divide( __CONST TSLCComplexBuffer __REF Src);

  void       Subtract( TOWRealComplex Value );
  void       Subtract( double Real, double Imaginary );
  void       Subtract( __CONST TSLCComplexBuffer __REF Src);

  void       Normalize( TOWRealComplex Offset, double Factor ) { Normalize( __THIS, Offset, Factor); }
  void       Normalize( __CONST TSLCComplexBuffer __REF Src, TOWRealComplex Offset, double Factor );
  void       Normalize( double RealOffset, double ImaginaryOffset, double Factor );
  void       Normalize( __CONST TSLCComplexBuffer __REF Src, double RealOffset, double ImaginaryOffset, double Factor );

  TOWRealComplex Dot( __CONST TSLCComplexBuffer __REF Src);

  void       Threshold(double Threshold, TSLThresholdType Type);
  void       Threshold( __CONST TSLCComplexBuffer __REF Src, double Threshold, TSLThresholdType Type);
  void       Sqr();
  void       Sqr( __CONST TSLCComplexBuffer __REF Src);
  void       Sqrt();
  void       Sqrt( __CONST TSLCComplexBuffer __REF Src);
  TOWRealComplex Mean();

  void       AutoCorr( __CONST TSLCComplexBuffer __REF Src, TSLAutoCorrType type);
  void       CrossCorr( __CONST TSLCComplexBuffer __REF Src1, __CONST TSLCComplexBuffer __REF Src2,
                              int LoLag );
  void       CrossCorr( __CONST TSLCComplexBuffer __REF Src1, int LoLag );

  TSLCRealBuffer __IREF Phase();
  TSLCRealBuffer __IREF Magnitude();
  TSLCRealBuffer __IREF PowerSpectrum();
  TSLCRealBuffer __IREF GetReal();
  TSLCRealBuffer __IREF GetImaginary();

public:
  const TOWRealComplex *Read() __CONST
    {
    return (const TOWRealComplex *)FDataPtr;
    }

  TOWRealComplex *Write()
    {
    Unique( false );
    return (TOWRealComplex *)FDataPtr;
    }

  TOWRealComplex *Modify()
    {
    Unique( true );
    return (TOWRealComplex *)FDataPtr;
    }

  bool IsEqual( __CONST TSLCComplexBuffer __REF Other ) __CONST;
  bool IsEqual( TOWRealComplex Value ) __CONST;
  
#ifndef __CLR_VER
  TOWRealComplex operator [] ( int Index ) const
    {
    return ((TOWRealComplex *)FDataPtr )[ Index ];
    }

  TOWRealComplex & operator [] ( int Index )
    {
    Unique( true );
    return ((TOWRealComplex *)FDataPtr )[ Index ];
    }

  TSLCComplexBuffer& operator = (const TSLCComplexBuffer &other )
      { Assign(other); return *this; }
  TSLCComplexBuffer& operator = ( TOWRealComplex rhs)
      { Set(rhs); return *this; }
  TSLCComplexBuffer& operator += (const TSLCComplexBuffer& rhs)
      { Add(rhs); return *this; }
  TSLCComplexBuffer& operator += ( TOWRealComplex rhs)
      { Add(rhs); return *this; }
  TSLCComplexBuffer& operator -= (const TSLCComplexBuffer& rhs)
      { Subtract(rhs); return *this; }
  TSLCComplexBuffer& operator -= ( TOWRealComplex rhs)
      { Subtract(rhs); return *this; }
  TSLCComplexBuffer& operator *= (const TSLCComplexBuffer& rhs)
      { Multiply(rhs); return *this; }
  TSLCComplexBuffer& operator *= ( TOWRealComplex rhs)
      { Multiply(rhs); return *this; }
  TSLCComplexBuffer& operator /= (const TSLCComplexBuffer& rhs)
      { Divide(rhs); return *this; }
  TSLCComplexBuffer& operator /= ( TOWRealComplex rhs)
      { Divide(rhs); return *this; }

  operator TOWRealComplex * ()
      { return Write(); };
      
  operator const TOWRealComplex * () const
      { return Read(); };

#else
    static TSLCComplexBuffer ^ operator + ( TSLCComplexBuffer ^ lhs, TSLCComplexBuffer ^ rhs) { TSLCComplexBuffer ^ tmp = gcnew TSLCComplexBuffer( lhs ); tmp->Add( rhs ); return tmp; }
    static TSLCComplexBuffer ^ operator + ( TSLCComplexBuffer ^ lhs, TOWRealComplex rhs) { TSLCComplexBuffer ^ tmp = gcnew TSLCComplexBuffer( lhs ); tmp->Add( rhs ); return tmp; }
    static TSLCComplexBuffer ^ operator + ( TOWRealComplex lhs, TSLCComplexBuffer ^ rhs) { TSLCComplexBuffer ^ tmp = gcnew TSLCComplexBuffer( rhs ); tmp->Add( lhs ); return tmp; }

    static TSLCComplexBuffer ^ operator - ( TSLCComplexBuffer ^ lhs, TSLCComplexBuffer ^ rhs) { TSLCComplexBuffer ^ tmp = gcnew TSLCComplexBuffer( lhs ); tmp->Subtract( rhs ); return tmp; }
    static TSLCComplexBuffer ^ operator - ( TSLCComplexBuffer ^ lhs, TOWRealComplex rhs) { TSLCComplexBuffer ^ tmp = gcnew TSLCComplexBuffer( lhs ); tmp->Subtract( rhs ); return tmp; }
    static TSLCComplexBuffer ^ operator - ( TOWRealComplex lhs, TSLCComplexBuffer ^ rhs) { TSLCComplexBuffer ^ tmp = gcnew TSLCComplexBuffer( rhs ); tmp->Subtract( lhs ); return tmp; }

    static TSLCComplexBuffer ^ operator * ( TSLCComplexBuffer ^ lhs, TSLCComplexBuffer ^ rhs) { TSLCComplexBuffer ^ tmp = gcnew TSLCComplexBuffer( lhs ); tmp->Multiply( rhs ); return tmp; }
    static TSLCComplexBuffer ^ operator * ( TSLCComplexBuffer ^ lhs, TOWRealComplex rhs) { TSLCComplexBuffer ^ tmp = gcnew TSLCComplexBuffer( lhs ); tmp->Multiply( rhs ); return tmp; }
    static TSLCComplexBuffer ^ operator * ( TOWRealComplex lhs, TSLCComplexBuffer ^ rhs) { TSLCComplexBuffer ^ tmp = gcnew TSLCComplexBuffer( rhs ); tmp->Multiply( lhs ); return tmp; }

    static TSLCComplexBuffer ^ operator / ( TSLCComplexBuffer ^ lhs, TSLCComplexBuffer ^ rhs) { TSLCComplexBuffer ^ tmp = gcnew TSLCComplexBuffer( lhs ); tmp->Divide( rhs ); return tmp; }
    static TSLCComplexBuffer ^ operator / ( TSLCComplexBuffer ^ lhs, TOWRealComplex rhs) { TSLCComplexBuffer ^ tmp = gcnew TSLCComplexBuffer( lhs ); tmp->Divide( rhs ); return tmp; }

    static bool operator == ( TSLCComplexBuffer ^ lhs, TSLCComplexBuffer ^ rhs) { return lhs->IsEqual( rhs ); }
    static bool operator != ( TSLCComplexBuffer ^ lhs, TSLCComplexBuffer ^ rhs) { return ! lhs->IsEqual( rhs ); }

    static bool operator == ( TSLCComplexBuffer ^ lhs, TOWRealComplex rhs) { return lhs->IsEqual( rhs ); }
    static bool operator != ( TSLCComplexBuffer ^ lhs, TOWRealComplex rhs) { return ! lhs->IsEqual( rhs ); }

    static bool operator == ( TOWRealComplex lhs, TSLCComplexBuffer ^ rhs) { return rhs->IsEqual( lhs ); }
    static bool operator != ( TOWRealComplex lhs, TSLCComplexBuffer ^ rhs) { return ! rhs->IsEqual( lhs ); }

#endif

protected:
    mutable TSLExposedComplexBuffer *  pPasBuffer;

public:
  virtual void *GetPasBuffer() __OVERRIDE __CONST { return pPasBuffer; }

protected:
    //
    //  Member functions
    virtual void Assign( __CONST TSLCComplexBuffer __REF other );
    virtual void Assign( const double *AData, int ASize );

#ifdef __CLR_VER
public:
    property TOWRealComplex default[int] 
    { 
        TOWRealComplex get( int index ) 
        { 
            if( index < 0 || index >= (int)GetSize() )
                throw gcnew System::IndexOutOfRangeException();

            return ((TOWRealComplex *)FDataPtr )[ index ]; 
        }

        void set( int index, TOWRealComplex value )
        {
            if( index < 0 || index >= (int)GetSize() )
                throw gcnew System::IndexOutOfRangeException();

            Unique( true );
            ((TOWRealComplex *)FDataPtr )[ index ] = value;
        }
    }

    property TOWRealComplex default[unsigned int] 
    { 
        TOWRealComplex get( unsigned int index ) 
        { 
            if( index >= GetSize() )
                throw gcnew System::IndexOutOfRangeException();

            return ((TOWRealComplex *)FDataPtr )[ index ]; 
        }

        void set( unsigned int index, TOWRealComplex value )
        {
            if( index >= GetSize() )
                throw gcnew System::IndexOutOfRangeException();

            Unique( true );
            ((TOWRealComplex *)FDataPtr )[ index ] = value;
        }
    }
#endif

public :
  virtual unsigned int GetSize() __OVERRIDE __CONST { return pPasBuffer->GetSize(); };

};

#ifndef __CLR_VER

//---------------------------------------------------------------------------
TSLCComplexBuffer operator + (const TSLCComplexBuffer& lhs, const TSLCComplexBuffer& rhs);
TSLCComplexBuffer operator + (const TOWRealComplex value, const TSLCComplexBuffer& rhs);
TSLCComplexBuffer operator + (const TSLCComplexBuffer& lhs, const TOWRealComplex value);

TSLCComplexBuffer operator - (const TSLCComplexBuffer& lhs, const TSLCComplexBuffer& rhs);
TSLCComplexBuffer operator - (const TSLCComplexBuffer& lhs, const TOWRealComplex value);
TSLCComplexBuffer operator - (const TSLCComplexBuffer& lhs);

TSLCComplexBuffer operator * (const TSLCComplexBuffer& lhs, const TSLCComplexBuffer& rhs);
TSLCComplexBuffer operator * (const TSLCComplexBuffer& lhs, const TOWRealComplex value);
TSLCComplexBuffer operator * (const TOWRealComplex value, const TSLCComplexBuffer& rhs);

TSLCComplexBuffer operator / (const TSLCComplexBuffer& lhs, const TSLCComplexBuffer& rhs);
TSLCComplexBuffer operator / (const TSLCComplexBuffer& lhs, const TOWRealComplex value);

bool operator == (const TSLCComplexBuffer & lhs, const TSLCComplexBuffer & rhs);
bool operator != (const TSLCComplexBuffer & lhs, const TSLCComplexBuffer & rhs);

bool operator == (const TSLCComplexBuffer & lhs, const TOWRealComplex rhs);
bool operator != (const TSLCComplexBuffer & lhs, const TOWRealComplex rhs);

bool operator == (const TOWRealComplex lhs, const TSLCComplexBuffer & rhs);
bool operator != (const TOWRealComplex lhs, const TSLCComplexBuffer & rhs);


inline TSLCComplexBuffer operator + (const TSLCComplexBuffer& lhs, const TSLCComplexBuffer& rhs) { TSLCComplexBuffer tmp( lhs ); return tmp += rhs; }
inline TSLCComplexBuffer operator + (const TOWRealComplex value, const TSLCComplexBuffer& rhs) { TSLCComplexBuffer tmp( rhs ); return tmp += value; }
inline TSLCComplexBuffer operator + (const TSLCComplexBuffer& lhs, const TOWRealComplex value) { TSLCComplexBuffer tmp( lhs ); return tmp += value; }

inline TSLCComplexBuffer operator - (const TSLCComplexBuffer& lhs, const TSLCComplexBuffer& rhs) { TSLCComplexBuffer tmp( lhs ); return tmp -= rhs; }
inline TSLCComplexBuffer operator - (const TSLCComplexBuffer& lhs, const TOWRealComplex value) { TSLCComplexBuffer tmp( lhs ); return tmp -= value; }

inline TSLCComplexBuffer operator - (const TSLCComplexBuffer& lhs) { TSLCComplexBuffer tmp( lhs ); tmp.Multiply(-1.0, -1.0); return tmp; }

inline TSLCComplexBuffer operator * (const TSLCComplexBuffer& lhs, const TSLCComplexBuffer& rhs) { TSLCComplexBuffer tmp( lhs ); return tmp *= rhs; }
inline TSLCComplexBuffer operator * (const TSLCComplexBuffer& lhs, const TOWRealComplex value) { TSLCComplexBuffer tmp( lhs ); return tmp *= value; }
inline TSLCComplexBuffer operator * (const TOWRealComplex value, const TSLCComplexBuffer& rhs) { TSLCComplexBuffer tmp( rhs ); return tmp *= value; }

inline TSLCComplexBuffer operator / (const TSLCComplexBuffer& lhs, const TSLCComplexBuffer& rhs) { TSLCComplexBuffer tmp( rhs ); return tmp /= rhs; }
inline TSLCComplexBuffer operator / (const TSLCComplexBuffer& lhs, const TOWRealComplex value) { TSLCComplexBuffer tmp( lhs ); return tmp /= value; }

inline bool operator == (const TSLCComplexBuffer & lhs, const TSLCComplexBuffer & rhs) { return lhs.IsEqual( rhs ); }
inline bool operator != (const TSLCComplexBuffer & lhs, const TSLCComplexBuffer & rhs) { return ! lhs.IsEqual( rhs ); }

inline bool operator == (const TSLCComplexBuffer & lhs, const TOWRealComplex rhs) { return lhs.IsEqual( rhs ); }
inline bool operator != (const TSLCComplexBuffer & lhs, const TOWRealComplex rhs) { return ! lhs.IsEqual( rhs ); }

inline bool operator == (const TOWRealComplex lhs, const TSLCComplexBuffer & rhs) { return rhs.IsEqual( lhs ); }
inline bool operator != (const TOWRealComplex lhs, const TSLCComplexBuffer & rhs) { return ! rhs.IsEqual( lhs ); }
//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------
#ifdef __CLR_VER
} // namespace Mitov
} // namespace SignalLab
#endif
//---------------------------------------------------------------------------
#endif
