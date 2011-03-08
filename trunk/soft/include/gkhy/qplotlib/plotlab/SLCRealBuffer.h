////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//     This software is supplied under the terms of a license agreement or    //
//     nondisclosure agreement with Boian Mitov and may not be copied         //
//     or disclosed except in accordance with the terms of that agreement.    //
//          Copyright(c) 2002-2009 Boian Mitov. All Rights Reserved.          //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#ifndef SLCRealBufferH
#define SLCRealBufferH
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
  typedef TSLVCSimpleRealBuffer TSLRealBuffer;

#endif

#ifndef __CLR_VER

class PACKAGE TSLCRealBuffer;

#endif

//==============================================================================
//   CLASS TSLCRealBuffer -- Real Data Buffer Class
//==============================================================================

#ifdef __CLR_VER
#define TSLCRealBuffer RealBuffer

class TSLExposedRealBuffer : public TSLRealBuffer
{
  friend ref class TSLCRealBuffer;
};

public ref class TSLCRealBuffer : public TSLCGenericBuffer
{
#else
class PACKAGE TSLCRealBuffer : public TSLCGenericBuffer
{
  class TSLExposedRealBuffer : public TSLRealBuffer
  {
    friend class TSLCRealBuffer;
  };

#endif
  
public:
    //
    //  Member Functions
    TSLCRealBuffer()
        :  pPasBuffer( (TSLExposedRealBuffer *)new TSLRealBuffer(( unsigned int)0 ))
        {
        pPasBuffer->_AddRef();
        PopulateCahces();
        }

    TSLCRealBuffer(int size);
    TSLCRealBuffer(const TSLCRealBuffer __REF other);
#ifdef __CLR_VER
    TSLCRealBuffer( bool, int Handle ) {}
    TSLCRealBuffer( array<const double> ^ AData );
#endif
    TSLCRealBuffer( TSLRealBuffer *PascalBuffer );
    TSLCRealBuffer( double *AData, int ASize );

#ifndef __BORLANDC__
    // Provides VC++ buffer access proxy.
    TSLCRealBuffer( TSLUniVCBufferProxy *VCBufferProxy );
#endif

    virtual ~TSLCRealBuffer();

#ifdef __CLR_VER
public:
  array<double> ^ ToArray();
#endif

public:
    //
    //  Buffer operations
    void  RemoveOwnerShip();

#ifndef __CLR_VER
    TSLCRealBuffer & operator ()()
        { return *this; };
#endif

    void      Resize( int size, bool preserve_data )
        {
        pPasBuffer->Resize( size, preserve_data );
        PopulateCahces();
        }

    void      Resize( int size )
        {
        pPasBuffer->Resize( size, false );
        PopulateCahces();
        }

    void      ToChar(char *OutBuffer, bool Round);
    void      ToShort(short *OutBuffer, bool Round);
    void      ToInt(int *OutBuffer, bool Round);

    void      ToDouble( double *OutBuffer );
    void      ToFloat( float *OutBuffer );

    void      FromChar(const char *InBuffer);
    void      FromShort(const short *InBuffer);
    void      FromInt(const int *InBuffer);

    void      FromDouble( const double *InBuffer );
    void      FromFloat( const float *InBuffer );

public:
    const double *Read() __CONST
      {
      return (const double *)FDataPtr;
      }

    double *Write()
      {
      Unique( false );
      return (double *)FDataPtr;
      }

    double *Modify()
      {
      Unique( true );
      return (double *)FDataPtr;       
      }

public:
    void      Copy(__CONST TSLCRealBuffer __REF Src);
    void      Set(double value);
    void      Zero();
    void      Add(double value);
    void      Add( __CONST TSLCRealBuffer __REF Src);
    void      Multiply(double value);
    void      Multiply( __CONST TSLCRealBuffer __REF Src);
    void      Divide(double value);
    void      Divide( __CONST TSLCRealBuffer __REF Src);
    void      Subtract(double value);
    void      Subtract( __CONST TSLCRealBuffer __REF Src);
    void      Normalize(double Offset, double Factor);
    void      Normalize( __CONST TSLCRealBuffer __REF Src, double Offset, double Factor);
    double    Dot( __CONST TSLCRealBuffer __REF Src);
    void      Threshold(double Threshold, TSLThresholdType Type);
    void      Threshold( __CONST TSLCRealBuffer __REF Src, double Threshold, TSLThresholdType Type);
    void      Abs();
    void      Abs( __CONST TSLCRealBuffer __REF Src);
    void      Sqr();
    void      Sqr( __CONST TSLCRealBuffer __REF Src);
    void      Sqrt();
    void      Sqrt( __CONST TSLCRealBuffer __REF Src);

    void      Exp();
    void      Exp( __CONST TSLCRealBuffer __REF Src);
    void      Ln();
    void      Ln( __CONST TSLCRealBuffer __REF Src);
    double    Max();
    double    Max(int & index);
    double    Min();
    double    Min(int & index);
    double    Mean();
    double    StdDev();
    double    Norm( __CONST TSLCRealBuffer __REF Src, TSLNormType type);

    void      dB(int bits);
    void      dB() { dB(16); } 

    bool      IsEqual(__CONST TSLCRealBuffer __REF Other) __CONST;
    bool      IsEqual( double Value ) __CONST;

    void      Convolve( __CONST TSLCRealBuffer __REF Src, __CONST TSLCRealBuffer __REF H);
    void      Convolve( __CONST TSLCRealBuffer __REF H);
    void      AutoCorr( __CONST TSLCRealBuffer __REF Src, TSLAutoCorrType type);
    void      CrossCorr( __CONST TSLCRealBuffer __REF Src1, __CONST TSLCRealBuffer __REF Src2, int LoLag );
    void      CrossCorr( __CONST TSLCRealBuffer __REF Src1, int LoLag );
  
public:

#ifndef __CLR_VER
    operator double * ()
        { return Write(); };

    operator const double * () const
        { return Read(); };

    double operator [] ( int Index ) const
      {
      return ((double *)FDataPtr )[ Index ];
      }

    double & operator [] ( int Index )
      {
      Unique( true );
      return ((double *)FDataPtr )[ Index ];
      }

    TSLCRealBuffer& operator = (const TSLCRealBuffer & rhs) { Assign( rhs ); return *this; }
    TSLCRealBuffer& operator = (double rhs)                     { Set( rhs ); return *this; }
    TSLCRealBuffer& operator += (const TSLCRealBuffer& rhs) { Add( rhs ); return *this; }
    TSLCRealBuffer& operator += (double rhs)                    { Add( rhs ); return *this; }
    TSLCRealBuffer& operator -= (const TSLCRealBuffer& rhs) { Subtract( rhs ); return *this; }
    TSLCRealBuffer& operator -= (double rhs)                    { Subtract( rhs ); return *this; }
    TSLCRealBuffer& operator *= (const TSLCRealBuffer& rhs) { Multiply( rhs ); return *this; }
    TSLCRealBuffer& operator *= (double rhs)                    { Multiply( rhs ); return *this; }
    TSLCRealBuffer& operator /= (const TSLCRealBuffer& rhs) { Divide( rhs ); return *this; }
    TSLCRealBuffer& operator /= (double rhs)                    { Divide( rhs ); return *this; }
#else
    static TSLCRealBuffer ^ operator + ( TSLCRealBuffer ^ lhs, TSLCRealBuffer ^ rhs) { TSLCRealBuffer ^ tmp = gcnew TSLCRealBuffer( lhs ); tmp->Add( rhs ); return tmp; }
    static TSLCRealBuffer ^ operator + ( TSLCRealBuffer ^ lhs, double rhs) { TSLCRealBuffer ^ tmp = gcnew TSLCRealBuffer( lhs ); tmp->Add( rhs ); return tmp; }
    static TSLCRealBuffer ^ operator + ( double lhs, TSLCRealBuffer ^ rhs) { TSLCRealBuffer ^ tmp = gcnew TSLCRealBuffer( rhs ); tmp->Add( lhs ); return tmp; }

    static TSLCRealBuffer ^ operator - ( TSLCRealBuffer ^ lhs, TSLCRealBuffer ^ rhs) { TSLCRealBuffer ^ tmp = gcnew TSLCRealBuffer( lhs ); tmp->Subtract( rhs ); return tmp; }
    static TSLCRealBuffer ^ operator - ( TSLCRealBuffer ^ lhs, double rhs) { TSLCRealBuffer ^ tmp = gcnew TSLCRealBuffer( lhs ); tmp->Subtract( rhs ); return tmp; }
    static TSLCRealBuffer ^ operator - ( double lhs, TSLCRealBuffer ^ rhs) { TSLCRealBuffer ^ tmp = gcnew TSLCRealBuffer( rhs ); tmp->Subtract( lhs ); return tmp; }

    static TSLCRealBuffer ^ operator * ( TSLCRealBuffer ^ lhs, TSLCRealBuffer ^ rhs) { TSLCRealBuffer ^ tmp = gcnew TSLCRealBuffer( lhs ); tmp->Multiply( rhs ); return tmp; }
    static TSLCRealBuffer ^ operator * ( TSLCRealBuffer ^ lhs, double rhs) { TSLCRealBuffer ^ tmp = gcnew TSLCRealBuffer( lhs ); tmp->Multiply( rhs ); return tmp; }
    static TSLCRealBuffer ^ operator * ( double lhs, TSLCRealBuffer ^ rhs) { TSLCRealBuffer ^ tmp = gcnew TSLCRealBuffer( rhs ); tmp->Multiply( lhs ); return tmp; }

    static TSLCRealBuffer ^ operator / ( TSLCRealBuffer ^ lhs, TSLCRealBuffer ^ rhs) { TSLCRealBuffer ^ tmp = gcnew TSLCRealBuffer( lhs ); tmp->Divide( rhs ); return tmp; }
    static TSLCRealBuffer ^ operator / ( TSLCRealBuffer ^ lhs, double rhs) { TSLCRealBuffer ^ tmp = gcnew TSLCRealBuffer( lhs ); tmp->Divide( rhs ); return tmp; }

    static bool operator == ( TSLCRealBuffer ^ lhs, TSLCRealBuffer ^ rhs) { return lhs->IsEqual( rhs ); }
    static bool operator != ( TSLCRealBuffer ^ lhs, TSLCRealBuffer ^ rhs) { return ! lhs->IsEqual( rhs ); }

    static bool operator == ( TSLCRealBuffer ^ lhs, int rhs) { return lhs->IsEqual( rhs ); }
    static bool operator != ( TSLCRealBuffer ^ lhs, int rhs) { return ! lhs->IsEqual( rhs ); }

    static bool operator == ( int lhs, TSLCRealBuffer ^ rhs) { return rhs->IsEqual( lhs ); }
    static bool operator != ( int lhs, TSLCRealBuffer ^ rhs) { return ! rhs->IsEqual( lhs ); }
#endif

#ifdef __CLR_VER
internal:
    mutable TSLExposedRealBuffer *  pPasBuffer;
#else
protected:
    mutable TSLExposedRealBuffer *  pPasBuffer;
#endif

public:
    virtual void *GetPasBuffer() __OVERRIDE __CONST { return pPasBuffer; }

protected:
    //
    //  Member functions
#ifdef __CLR_VER
    virtual void Assign( array<const double> ^ AData );
#endif
    virtual void Assign( const TSLCRealBuffer __REF other );
    virtual void Assign( const double *AData, int ASize );

#ifdef __CLR_VER
public:
    property double default[int] 
    { 
        double get( int index ) 
        { 
            if( index < 0 || index >= (int)GetSize() )
                throw gcnew System::IndexOutOfRangeException();

            return ((double *)FDataPtr )[ index ]; 
        }

        void set( int index, double value )
        {
            if( index < 0 || index >= (int)GetSize() )
                throw gcnew System::IndexOutOfRangeException();

            Unique( true );
            ((double *)FDataPtr )[ index ] = value;
        }
    }

    property double default[unsigned int] 
    { 
        double get( unsigned int index ) 
        { 
            if( index >= GetSize() )
                throw gcnew System::IndexOutOfRangeException();

            return ((double *)FDataPtr )[ index ]; 
        }

        void set( unsigned int index, double value )
        {
            if( index >= GetSize() )
                throw gcnew System::IndexOutOfRangeException();

            Unique( true );
            ((double *)FDataPtr )[ index ] = value;
        }
    }
#endif

public :
    virtual unsigned int GetSize() __OVERRIDE __CONST { return pPasBuffer->GetSize(); };

};


#ifndef __CLR_VER
//---------------------------------------------------------------------------
TSLCRealBuffer operator + (const TSLCRealBuffer& lhs, const TSLCRealBuffer& rhs);
TSLCRealBuffer operator + (const double value, const TSLCRealBuffer& rhs);
TSLCRealBuffer operator + (const TSLCRealBuffer& lhs, const double value);
TSLCRealBuffer operator - (const TSLCRealBuffer& lhs, const TSLCRealBuffer& rhs);
TSLCRealBuffer operator - (const TSLCRealBuffer& lhs, const double value);

TSLCRealBuffer operator - (const TSLCRealBuffer& lhs);
TSLCRealBuffer operator * (const TSLCRealBuffer& lhs, const TSLCRealBuffer& rhs);
TSLCRealBuffer operator * (const double value, const TSLCRealBuffer& rhs);
TSLCRealBuffer operator * (const TSLCRealBuffer& lhs, const double value);

TSLCRealBuffer operator / (const TSLCRealBuffer& lhs, const TSLCRealBuffer& rhs);
TSLCRealBuffer operator / (const TSLCRealBuffer& lhs, const double value);

bool operator == (const TSLCRealBuffer & lhs, const TSLCRealBuffer & rhs);
bool operator != (const TSLCRealBuffer & lhs, const TSLCRealBuffer & rhs);


inline TSLCRealBuffer operator + (const TSLCRealBuffer& lhs, const TSLCRealBuffer& rhs) { TSLCRealBuffer tmp( lhs ); return tmp += rhs; }
inline TSLCRealBuffer operator + (const double value, const TSLCRealBuffer& rhs) { TSLCRealBuffer tmp( rhs ); return tmp += value; }
inline TSLCRealBuffer operator + (const TSLCRealBuffer& lhs, const double value) { TSLCRealBuffer tmp( lhs ); return tmp += value; }
inline TSLCRealBuffer operator - (const TSLCRealBuffer& lhs, const TSLCRealBuffer& rhs) { TSLCRealBuffer tmp( lhs ); return tmp -= rhs; }
inline TSLCRealBuffer operator - (const TSLCRealBuffer& lhs, const double value) { TSLCRealBuffer tmp( lhs ); return tmp -= value; }

inline TSLCRealBuffer operator - (const TSLCRealBuffer& lhs) { TSLCRealBuffer tmp( lhs ); tmp.Multiply(-1.0); return tmp; }
inline TSLCRealBuffer operator * (const TSLCRealBuffer& lhs, const TSLCRealBuffer& rhs) { TSLCRealBuffer tmp( rhs ); return tmp *= rhs; }
inline TSLCRealBuffer operator * (const double value, const TSLCRealBuffer& rhs) { TSLCRealBuffer tmp( rhs ); return tmp *= value; }
inline TSLCRealBuffer operator * (const TSLCRealBuffer& lhs, const double value) { TSLCRealBuffer tmp( lhs ); return tmp *= value; }

inline TSLCRealBuffer operator / (const TSLCRealBuffer& lhs, const TSLCRealBuffer& rhs) { TSLCRealBuffer tmp( lhs ); return tmp /= rhs; }
inline TSLCRealBuffer operator / (const TSLCRealBuffer& lhs, const double value) { TSLCRealBuffer tmp( lhs ); return tmp /= value; }

inline bool operator == (const TSLCRealBuffer & lhs, const TSLCRealBuffer & rhs) { return lhs.IsEqual( rhs ); }
inline bool operator != (const TSLCRealBuffer & lhs, const TSLCRealBuffer & rhs) { return ! lhs.IsEqual( rhs ); }

inline bool operator == (const TSLCRealBuffer & lhs, double rhs) { return lhs.IsEqual( rhs ); }
inline bool operator != (const TSLCRealBuffer & lhs, double rhs) { return ! lhs.IsEqual( rhs ); }

inline bool operator == (double & lhs, const TSLCRealBuffer & rhs) { return rhs.IsEqual( lhs ); }
inline bool operator != (double & lhs, const TSLCRealBuffer & rhs) { return ! rhs.IsEqual( lhs ); }
#endif
//---------------------------------------------------------------------------
#ifdef __CLR_VER
} // namespace Mitov
} // namespace SignalLab
#endif
//---------------------------------------------------------------------------
#endif
