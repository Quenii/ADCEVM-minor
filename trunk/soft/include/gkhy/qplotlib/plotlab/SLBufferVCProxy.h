//---------------------------------------------------------------------------

#ifndef SLBufferVCProxyH
#define SLBufferVCProxyH
//---------------------------------------------------------------------------
#define __MSCALL  __stdcall

#ifdef __BORLANDC__
  #include <SLSimpleDataBuffer.hpp>

#else
  #include <basetsd.h>

/* Aff this to fix big in some versions of Win32 SDK :

  #undef POINTER_64
*/

  #include <windows.h>

  typedef void *_di_ISLDataBuffer;

#endif
//---------------------------------------------------------------------------
#include <SLCBufferDefs.h>
//---------------------------------------------------------------------------
struct TSLUniVCBufferProxyMethods
{
  bool ( __MSCALL * MakeUnique)( void *Instance, bool Preserve );
  void ( __MSCALL * Assign)( void *Instance, void *OtherBufferInstance );
  void *( __MSCALL * ByteRead)( void *Instance );
  void *( __MSCALL * ByteWrite)( void *Instance );
  void *( __MSCALL * ByteModify)( void *Instance );
  unsigned int   ( __MSCALL * GetByteSize)( void *Instance );
  unsigned int   ( __MSCALL * GetSize)( void *Instance );
};
//---------------------------------------------------------------------------
struct TSLUniMemoryVCBufferProxyMethods
{
  TSLUniVCBufferProxyMethods Iherited;
  
  void  ( __MSCALL * SetSize)( void *Instance, int Size, bool Preserve );
};
//---------------------------------------------------------------------------
struct TSLBlockVCBufferProxyMethods
{
  TSLUniMemoryVCBufferProxyMethods Iherited;

  void ( __MSCALL * SetValue)( void *Instance, unsigned char value );
  void ( __MSCALL * Zero)( void *Instance );
};
//---------------------------------------------------------------------------
struct TSLIntegerVCBufferProxyMethods
{
  TSLUniMemoryVCBufferProxyMethods Iherited;

  void ( __MSCALL * SetValue)( void *Instance, int value );
  void ( __MSCALL * AddValue)( void *Instance, int value );
  void ( __MSCALL * SubValue)( void *Instance, int value );
  void ( __MSCALL * MulValue)( void *Instance, int value );
  void ( __MSCALL * DivValue)( void *Instance, int value );
  void ( __MSCALL * ModValue)( void *Instance, int value );
  void ( __MSCALL * AndValue)( void *Instance, int value );
  void ( __MSCALL * OrValue)( void *Instance, int value );
  void ( __MSCALL * XorValue)( void *Instance, int value );
  void ( __MSCALL * LShiftValue)( void *Instance, int value );
  void ( __MSCALL * RShiftValue)( void *Instance, int value );
  void ( __MSCALL * Zero)( void *Instance );
  void ( __MSCALL * Add)( void *Instance, void *OtherBufferInstance );
  void ( __MSCALL * Subtract)( void *Instance, void *OtherBufferInstance );
  void ( __MSCALL * Multiply)( void *Instance, void *OtherBufferInstance );
  void ( __MSCALL * Divide)( void *Instance, void *OtherBufferInstance );
  int  ( __MSCALL * Dot)( void *Instance, void *OtherBufferInstance );
  void ( __MSCALL * AndBuffer)( void *Instance, void *OtherBufferInstance );
  void ( __MSCALL * OrBuffer)( void *Instance, void *OtherBufferInstance );
  void ( __MSCALL * XorBuffer)( void *Instance, void *OtherBufferInstance );
};
//---------------------------------------------------------------------------
struct TOWImplRealComplex
{
  double Real;
  double Imaginary;
};
//---------------------------------------------------------------------------
struct TSLComplexVCBufferProxyMethods
{
  TSLUniMemoryVCBufferProxyMethods Iherited;

  void *( __MSCALL * GetReal)( void *Instance );
  void *( __MSCALL * GetImaginary)( void *Instance );
  void *( __MSCALL * Phase)( void *Instance );
  void *( __MSCALL * Magnitude)( void *Instance );
  void *( __MSCALL * PowerSpectrum)( void *Instance );
  void ( __MSCALL * SetBuffer)( void *Instance, void *RealValueInstance, void *ImagValueInstance );
  void ( __MSCALL * SetValue)( void *Instance, double Real, double Imaginary );
  void ( __MSCALL * Zero)( void *Instance );
  void ( __MSCALL * AddValue)( void *Instance, double Real, double Imaginary );
  void ( __MSCALL * SubValue)( void *Instance, double Real, double Imaginary );
  void ( __MSCALL * MulValue)( void *Instance, double Real, double Imaginary );
  void ( __MSCALL * DivValue)( void *Instance, double Real, double Imaginary );
  void ( __MSCALL * Add)( void *Instance, void *OtherInstance );
  void ( __MSCALL * Sub)( void *Instance, void *OtherInstance );
  void ( __MSCALL * Mul)( void *Instance, void *OtherInstance );
  void ( __MSCALL * Div)( void *Instance, void *OtherInstance );
  void ( __MSCALL * NormalizeFrom)( void *Instance, void *SrcInstance, TOWImplRealComplex Offset, double Factor );
  TOWImplRealComplex ( __MSCALL * Dot)( void *Instance, void *SrcInstance );
  void ( __MSCALL * Threshold)( void *Instance, double Threshold, TSLThresholdType Type );
  void ( __MSCALL * ThresholdFrom)( void *Instance, void *SrcInstance, double Threshold, TSLThresholdType Type );
  void ( __MSCALL * Sqr)( void *Instance );
  void ( __MSCALL * SqrFrom)( void *Instance, void *SrcInstance );
  void ( __MSCALL * Sqrt)( void *Instance );
  void ( __MSCALL * SqrtFrom)( void *Instance, void *SrcInstance );
  void ( __MSCALL * AutoCorr)( void *Instance, void *SrcInstance, TSLAutoCorrType type );
  void ( __MSCALL * CrossCorr)( void *Instance, void *SrcInstance1, void *SrcInstance2, int LoLag );
};
//---------------------------------------------------------------------------
struct TSLRealVCBufferProxyMethods
{
  TSLUniMemoryVCBufferProxyMethods Iherited;
  
  void ( __MSCALL * SetValue)( void *Instance, double value );
  void ( __MSCALL * AddValue)( void *Instance, double value );
  void ( __MSCALL * SubValue)( void *Instance, double value );
  void ( __MSCALL * MulValue)( void *Instance, double value );
  void ( __MSCALL * DivValue)( void *Instance, double value );

  void ( __MSCALL * ToInt)( void *Instance, int *OutBuffer, bool Round );
  void ( __MSCALL * ToSingle)( void *Instance, float *OutBuffer );
  void ( __MSCALL * FromShort)( void *Instance, const short *InBuffer);
  void ( __MSCALL * FromInt)( void *Instance, const int *InBuffer);
  void ( __MSCALL * FromSingle)( void *Instance, const float *InBuffer );

  void ( __MSCALL * Add)( void *Instance, void *OtherInstance );
  void ( __MSCALL * Sub)( void *Instance, void *OtherInstance );
  void ( __MSCALL * Mul)( void *Instance, void *OtherInstance );
  void ( __MSCALL * Div)( void *Instance, void *OtherInstance );

  void ( __MSCALL * Zero)( void *Instance );
  void ( __MSCALL * NormalizeFrom)( void *Instance, void *SrcInstance, double Offset, double Factor );
  double ( __MSCALL * Dot)( void *Instance, void *SrcInstance );
  void ( __MSCALL * Threshold)( void *Instance, double Threshold, TSLThresholdType Type );
  void ( __MSCALL * ThresholdFrom)( void *Instance, void *SrcInstance, double Threshold, TSLThresholdType Type);
  void ( __MSCALL * Abs)( void *Instance );
  void ( __MSCALL * AbsFrom)( void *Instance, void *SrcInstance );
  void ( __MSCALL * Sqr)( void *Instance );
  void ( __MSCALL * SqrFrom)( void *Instance, void *SrcInstance );
  void ( __MSCALL * Sqrt)( void *Instance );
  void ( __MSCALL * SqrtFrom)( void *Instance, void *SrcInstance );
  void ( __MSCALL * Exp)( void *Instance );
  void ( __MSCALL * ExpFrom)( void *Instance, void *SrcInstance );
  void ( __MSCALL * Ln)( void *Instance );
  void ( __MSCALL * LnFrom)( void *Instance, void *SrcInstance );
  double ( __MSCALL * GetMinValue)( void *Instance );
  double ( __MSCALL * GetMaxValue)( void *Instance );
  double ( __MSCALL * GetMinIndex)( void *Instance, int & index);
  double ( __MSCALL * GetMaxIndex)( void *Instance, int & index);
  double ( __MSCALL * Mean)( void *Instance );
  double ( __MSCALL * StdDev)( void *Instance );
  double ( __MSCALL * Norm)( void *Instance, void *SrcInstance, TSLNormType type );
  void ( __MSCALL * Convolve)( void *Instance, void *SrcInstance, void *HInstance );
  void ( __MSCALL * AutoCorr)( void *Instance, void *SrcInstance, TSLAutoCorrType type );
  void ( __MSCALL * CrossCorr)( void *Instance, void *SrcInstance1, void *SrcInstance2, int LoLag );
};
//---------------------------------------------------------------------------
#ifdef __CLR_VER
public
#endif
struct TSLUniVCBufferProxy
{
  void *Instance;
  void *Methods;
  bool  Destroy;
  _di_ISLDataBuffer RefInstance;
};
//---------------------------------------------------------------------------
#endif
