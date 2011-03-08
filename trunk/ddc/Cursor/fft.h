#ifndef __FFT_H__
#define __FFT_H__

/**
 *  Pi for fft, float type.
 */
#define PI 3.14159265358979323846

/*  Complex type.
 */
typedef struct {
    double rex, imx;
} Complex;

class CFFT
{
public:
	/**
	 *  Decimation-in-Time Complex FFT Algorithm with Radix-2.
	 *  Note:
	 *    L   : exponent value of 2, N = 2^L.
	 *    cin : input complex array.
	 *    cout: output complex array.
	 */
	static void cfftr2( const int L, 
				 const Complex *cin, Complex *cout);
	/**
	 *  in reverse FFT.
	 */
	static void cifftr2(const int L,
				 const Complex *cin, Complex *cout);
	/**
	 *  DFT Algorithm, with arbitrary N point.
	 *  Note: slow but sample, useful in verify other FFT algorithm.
	 */
	static void dft(const int N, 
			 const Complex cin[], Complex cout[]);

	/**
	 *  Bit reverse sort, use reverse addition.
	 */
	static void revsort(const int N, 
				 const Complex cin[], Complex cout[]);

	/**
	 *  Calculate the module and Normalize by LEVER.
	 */
	static void module(const Complex cin[], 
				double pout[], const int N, const int LEVER);
};


#endif //__FFT_H__
