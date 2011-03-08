#include "stdafx.h"
#include <stdlib.h>
#include <math.h>

#include <assert.h>

#include "fft.h"

/**
 *  Decimation-in-Time Complex FFT Algorithm with Radix-2.
 *  Note:
 *    L   : exponent value of 2, N = 2^L.
 *    cin : input complex array.
 *    cout: output complex array.
 */
void CFFT::cfftr2(const int L, 
            const Complex cin[], Complex cout[])
{
    assert(cin);
    assert(cout);
    assert(L>0);
    const int N = 1<<L;
       
    /* Bit reverse sort, use reverse addition.
     */
    revsort(N, cin, cout);

    /* Butterfly calculate start.
     */
    int sep = 1;       /* seprate of butterfly, sep*2 every stage. */
    int len_sd = N/2;  /* number of sub-DFT, len_sd/2 every stage. */
    int len_cl = 1;    /* number of butterfly calculation in a sub-DFT.
                          len_cl*2 every stage. */
    const double WN = (2*PI/N);  /* %omiga, exponent value of Wn.  */

    /* Loop for each stage */
    int st;
    for (st=0; st<L; st++)
    {
        /* start position */
        int pos = 0;

        /* Loop for each sub-DFT */
        int sd;
        for (sd=0; sd<len_sd; sd++)
        {
            int k = 0;  /* {W_N}^k */
            
            /* Loop for each butterfly calculation */
            int cl;
            for (cl=0; cl<len_cl; cl++)
            {
                double w = WN * k;
                double cosx = cos(w);
                double sinx = sin(w);
                
                /* butterfly calculation.
                 */
                int nxt = pos+sep;  /* next point */

                double tr = cout[nxt].rex*cosx + cout[nxt].imx*sinx;
                double ti = cout[nxt].imx*cosx - cout[nxt].rex*sinx;
                cout[nxt].rex = cout[pos].rex - tr;
                cout[nxt].imx = cout[pos].imx - ti;
                cout[pos].rex = cout[pos].rex + tr;
                cout[pos].imx = cout[pos].imx + ti;
                
                k += (1<<(L-st-1));
                pos++;
            }
            
            /* position delta */
            pos += (1<<st);
        }

        sep <<= 1;     /* sep *= 2    */
        len_sd >>= 1;  /* len_sd /= 2 */
        len_cl <<= 1;  /* len_cl *= 2 */
    }
}

/**
 *  in reverse FFT. see cfftr2();
 */
void CFFT::cifftr2(const int L,
             const Complex *cin, Complex *cout)
{
    assert(cin);
    assert(cout);
    assert(L>0);
    
    const int N = 1<<L;
    int i;
    double tmp1, tmp2;
    for (i=0; i<N; i++)
    {
        tmp1 = cin[i].rex;
        tmp2 = cin[i].imx;
        cout[i].rex = tmp2;
        cout[i].imx = tmp1;
    }
    cfftr2(L, cout, cout);
    for (i=0; i<N; i++)
    {
        tmp1 = cout[i].rex;
        cout[i].rex = cout[i].imx;
        cout[i].imx = tmp1;
        cout[i].rex /= N;
        cout[i].imx /= N;
    }
}


/**
 *  DFT Algorithm, with arbitrary N point.
 *  Note: slow but sample, useful in verify other FFT algorithm.
 */
void CFFT::dft(const int N, 
         const Complex cin[], Complex cout[])
{
    assert(cin);
    assert(cout);
    assert(N>0);
    
    /* Loop for each X(k).
     */
    int k;
    for (k=0; k<N; k++)
    {
        double tr=0, ti=0;
        double wn = 2*PI/N*k;
        int n;
        /* sum x(n) */
        for (n=0; n<N; n++)
        {
            double w = wn*n;
            tr += ( cin[n].rex*cos(w) + cin[n].imx*sin(w) );
            ti += ( cin[n].imx*cos(w) - cin[n].rex*sin(w) );
        }
        cout[k].rex = tr;
        cout[k].imx = ti;
    }    
}

/**
 *  Calculate the module and Normalize by LEVER.
 */
void CFFT::module(const Complex cin[], 
            double pout[], const int N, const int LEVER)
{
    assert(cin);
    assert(pout);
    assert(N>0);

    /* Reconstruct data for output.
     */
    double gmax = 1;
    int i;
    for (i=0; i<N; i++) 
    {
        pout[i] = sqrt( cin[i].rex*cin[i].rex + cin[i].imx*cin[i].imx );
        if (pout[i] > gmax) 
        {
            gmax = pout[i];
        }
    }
/*
	// 不进行归一化，防止误差产生
    // Normalize data.    
    for (i=0; i<N; i++)
    {
        pout[i] = (int)(LEVER * pout[i]/gmax);
    }
*/
}

/**
 *  Bit reverse sort, use reverse addition.
 */
void CFFT::revsort(const int N, 
             const Complex cin[], Complex cout[])
{
    assert(cin);
    assert(cout);
    assert(N>0);
    
    int ri = 0, i;
    const int N2 = N/2, N1=N-1;
    /* copy data to cout */
    for (i=0; i<N; i++)
    {
        cout[i].rex = cin[i].rex;
        cout[i].imx = cin[i].imx;
    }
    
    /* bit reverse addition */
    for (i=0; i<N1; i++)
    {
        /* change i to revers i ( ri ). */
        if (i<ri)
        {
            /* switch data */
            double tmp;
            tmp = cout[ri].rex;
            cout[ri].rex = cout[i].rex;
            cout[i].rex  = tmp;
            tmp = cout[ri].imx;
            cout[ri].imx = cout[i].imx;
            cout[i].imx  = tmp;
        }
        /* calc ri here */
        int k = N2;
        while ( (k-ri) < 1 )
        {
            ri = ri - k;
            k /= 2;
        }
        ri += k;
    }
}
