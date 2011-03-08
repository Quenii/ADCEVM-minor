  #include "matlib.h"
  #pragma hdrstop
  
  #include "AdcDynTest.h"
  #include "chebwin.h"
  
  
  
  Mm AdcDynTest(Mm ADout, Mm fclk, Mm numbit, Mm NFFT, Mm V, Mm code, i_o_t, Mm& SNR__o, Mm& SINAD__o, Mm& SFDR__o, \
     Mm& ENOB__o, Mm& HD__o, Mm& y__o) {
    begin_scope
    ADout.setname("ADout"); fclk.setname("fclk"); numbit.setname("numbit"); NFFT.setname("NFFT"); V.setname("V");  \
      code.setname("code"); 
    dMm(SNR); dMm(SINAD); dMm(SFDR); dMm(ENOB); dMm(HD); dMm(y); dMm(ad_len_N); dMm(maxADout); dMm(AmpMax); dMm(t1) \
      ; dMm(AmpMin); dMm(t2); dMm(Vpp); dMm(ADout_w); dMm(AA); dMm(ad_len); dMm(ADout_spect); dMm(ADout_dB); dMm(maxdB) \
      ; dMm(fin_v); dMm(fin); dMm(freq_fin); dMm(data_ref); dMm(n); dMm(n_AdcDynTest_v0); dMm(data_ref_w); dMm(data_ref_spect) \
      ; dMm(data_ref_dB); dMm(ref_dB); dMm(span); dMm(spanh_har); dMm(span_s); dMm(spectP); dMm(Pdc); dMm(Pdc_dB);  \
      dMm(l); dMm(u); dMm(Ps); dMm(Ps_dB); dMm(Fh); dMm(Ph); dMm(Harbin); dMm(Ph_dB); dMm(har_num); dMm(har_num_AdcDynTest_v1) \
      ; dMm(tone); dMm(har_peak); dMm(har_bin); dMm(spectP_temp); dMm(i_); dMm(i_AdcDynTest_v2); dMm(disturb_len);  \
      dMm(spectP_disturb); dMm(Harbin_disturb); dMm(findSpac); dMm(findSpan); dMm(findStart); dMm(i_AdcDynTest_v3);  \
      dMm(spectP_disturb_peak); dMm(num); dMm(array_flag); dMm(jj); dMm(jj_AdcDynTest_v4); dMm(k); dMm(k_AdcDynTest_v5) \
      ; dMm(spectP_disturb_temp); dMm(Harbin_disturb_temp); dMm(Ph_disturb); dMm(Ph_disturb_dB); dMm(Fn_disturb); dMm( \
      i_AdcDynTest_v6); dMm(Pd_disturb); dMm(Pd_disturb_dB); dMm(Pd); dMm(Pd_dB); dMm(Pn); dMm(Pn_dB); dMm(Vin); dMm( \
      THD); dMm(SNRFS); dMm(ENOBFS); 
    
    call_stack_begin;
    // nargin, nargout entry code
    double old_nargin=nargin_val; if (!nargin_set) nargin_val=6.0;
    nargin_set=0;
    double old_nargout=nargout_val; if (!nargout_set) nargout_val=6.0;
    nargout_set=0;
    
    // translated code
    
    // function [SNR, SFDR, SNRFS, SINAD, y, THD, HD, ENOB, ENOBFS, Pn_dB] = AdcDynTest( ADout, fclk, numbit, NFFT, V, code )
    // Pn_dB为底噪声，fclk为采样频率，numbit为采样精度，NFFT为FFT的深度，V为峰峰值，TPY和TPX分别为时域图的Y和X轴，code
    // 为1：补码，2：偏移码，3：格雷码。
    //例子：若采样时钟80MHZ，精度16为，峰峰值2v，时域图显示Y轴＋－1V和X轴0－0.01ms，码源为补码
    //[SNR, SFDR, SNRFS, SINAD, THD, HD, ENOB, ENOBFS, Pn_dB] = calc_dynam_params( 80e6, 16, 32768, 2, 1, 0.01, 1 )
    
    if (istrue(code==1.0)) {
      if (istrue(numbit<16.0)) {
        ADout = fix(ADout/mpower(2.0,(16.0-numbit)));
      }
      ADout = ADout/mpower(2.0,(numbit-1.0));
      
    } else
    if (istrue(code==2.0)) {
      if (istrue(numbit<16.0)) {
        ADout = fix(ADout/mpower(2.0,(16.0-numbit)));
      }
      ADout = ADout/mpower(2.0,(numbit-1.0))-1.0;
    } else {
      
      if (istrue(numbit<16.0)) {
        ADout = fix(ADout/mpower(2.0,(16.0-numbit)));
      }
    }
    
    ADout = V/2.0*ADout;
    
    ad_len_N = length(ADout);
    
    maxADout = max(abs(ADout));
    /*[AmpMax,t1] = */max(ADout,i_o,AmpMax,t1);
    /*[AmpMin,t2] = */min(ADout,i_o,AmpMin,t2);
    Vpp = AmpMax-AmpMin;
    
    
    ADout_w = times(ADout,chebwin(ad_len_N,200.0));
    AA = zeros(NFFT-ad_len_N,1.0);
    ADout_w = (BR(ADout_w),semi,
    AA);
    ad_len = length(ADout_w);
    ADout_spect = fft(ADout_w,NFFT);
    ADout_dB = 20.0*log10(abs(ADout_spect));
    
    maxdB = max(ADout_dB(colon(1.0,1.0,ad_len/2.0)));
    fin_v = find(ADout_dB(colon(1.0,1.0,ad_len/2.0))==maxdB);
    
    fin = fin_v(1.0);
    freq_fin = (fin*fclk/ad_len);
    
    data_ref = zeros(ad_len_N,1.0);
    n_AdcDynTest_v0 = colon(1.0,1.0,ad_len_N); int n_AdcDynTest_i0;
    for (n_AdcDynTest_i0=0;n_AdcDynTest_i0<n_AdcDynTest_v0.cols();n_AdcDynTest_i0++) {
      forelem(n,n_AdcDynTest_v0,n_AdcDynTest_i0);
      
      data_ref(n) = V/2.0*sin((n-1.0)*(freq_fin)/fclk*2.0*pi);
    }
    data_ref_w = times(data_ref,chebwin(ad_len_N,200.0));
    
    data_ref_w = (BR(data_ref_w),semi,
    AA);
    data_ref_spect = fft(data_ref_w,NFFT);
    data_ref_dB = 20.0*log10(abs(data_ref_spect));
    ref_dB = max(data_ref_dB(colon(1.0,1.0,ad_len/2.0)));
    
    // $$$ figure( 1 )
    // $$$ plot( [0:round( ad_len / 2 ) - 1].*fclk / ad_len, - 20, ' - k' );
    // $$$ hold on;
    // $$$ plot( [0:50:round( ad_len / 2 ) - 1].*fclk / ad_len, - 40, ' - - k' );
    // $$$ hold on;
    // $$$ plot( [0:round( ad_len / 2 ) - 1].*fclk / ad_len, - 60, ' - k' );
    // $$$ hold on;
    // $$$ plot( [0:50:round( ad_len / 2 ) - 1].*fclk / ad_len, - 80, ' - - k' );
    // $$$ hold on;
    // $$$ plot( [0:round( ad_len / 2 ) - 1].*fclk / ad_len, - 100, ' - k' );
    // $$$ hold on;
    // $$$ plot( [0:50:round( ad_len / 2 ) - 1].*fclk / ad_len, - 120, ' - - k' );
    // $$$ hold on;
    // $$$ plot( [0:round( ad_len / 2 ) - 1].*fclk / ad_len, ADout_dB( 1:round( ad_len / 2 ) ) - ref_dB );
    // $$$ 
    // $$$ 
    // $$$ title( 'FFT PLOT' ); 
    // $$$ xlabel( 'ANALOG INPUT FREQUENCY ( MHz )' );
    // $$$ ylabel( 'AMPLITUDE ( dBFs )' );
    // $$$ a1 = axis; axis( [a1( 1 ) a1( 2 ) - 140 0] ); 
    
    //Calculate SNR, SINAD, THD and SFDR values
    //Find the signal bin number, DC = bin 1
    
    //Span of the DC on each side
    span = max(11.0);
    
    
    //Searching span for peak harmonics amp on each side 
    spanh_har = 4.0;
    //Span of the signal on each side
    span_s = 19.0;
    //8
    //Determine power spectrum
    spectP = times((abs(ADout_spect)),(abs(ADout_spect)));
    
    //Find DC offset power 
    Pdc = sum(spectP(colon(1.0,1.0,span)));
    
    Pdc_dB = sum(ADout_dB(colon(1.0,1.0,span)));
    //Extract overall signal power
    
    l = max(fin-span_s,1.0);
    u = min(fin+span_s,ad_len/2.0);
    Ps = sum(spectP(colon(l,1.0,u)));
    Ps_dB = sum(ADout_dB(colon(l,1.0,u)));
    //Vector / matrix to store both frequency and power of signal and harmonics
    Fh = nop_M;
    
    
    //The 1st element in the vector / matrix represents the signal, the next element represents
    //the 2nd harmonic, etc.
    Ph = nop_M;
    
    Harbin = nop_M;
    Ph_dB = nop_M;
    
    har_num_AdcDynTest_v1 = colon(1.0,1.0,11.0); int har_num_AdcDynTest_i1;
    for (har_num_AdcDynTest_i1=0;har_num_AdcDynTest_i1<har_num_AdcDynTest_v1.cols();har_num_AdcDynTest_i1++) {
      forelem(har_num,har_num_AdcDynTest_v1,har_num_AdcDynTest_i1);
      
      tone = rem((har_num*(fin-1.0)+1.0)/ad_len,1.0);
      
      if (istrue(tone>0.5)) {
        
        tone = 1.0-tone;
        
      }
      
      Fh = (BR(Fh),tone);
      
      
      l = max(1.0,round(tone*ad_len)-spanh_har);
      u = min(ad_len/2.0,round(tone*ad_len)+spanh_har);
      har_peak = max(spectP(colon(l,1.0,u)));
      
      har_bin = find(spectP(colon(l,1.0,u))==har_peak);
      har_bin = har_bin+round(tone*ad_len)-spanh_har-1.0;
      
      l = max(1.0,har_bin-spanh_har);
      u = min(ad_len/2.0,har_bin+spanh_har);
      Ph = (BR(Ph),sum(spectP(colon(l,1.0,u))));
      
      Ph_dB = (BR(Ph_dB),sum(ADout_dB(colon(l,1.0,u))));
      Harbin = (BR(Harbin),har_bin);
    }
    
    spectP_temp = spectP;
    
    i_AdcDynTest_v2 = colon(2.0,1.0,10.0); int i_AdcDynTest_i2;
    for (i_AdcDynTest_i2=0;i_AdcDynTest_i2<i_AdcDynTest_v2.cols();i_AdcDynTest_i2++) {
      forelem(i_,i_AdcDynTest_v2,i_AdcDynTest_i2);
      l = max(1.0,Harbin(i_)-spanh_har);
      u = min(ad_len/2.0,Harbin(i_)+spanh_har);
      spectP_temp(colon(l,1.0,u)) = 0.0;
    }
    l = max(1.0,fin-span_s);
    u = min(ad_len/2.0,fin+span_s);
    spectP_temp(colon(l,1.0,u)) = 0.0;
    spectP_temp(colon(1.0,1.0,span)) = 0.0;
    
    
    disturb_len = 19.0;
    spectP_disturb = zeros(1.0,disturb_len);
    Harbin_disturb = zeros(1.0,disturb_len);
    findSpac = 30.0;
    findSpan = (findSpac-1.0)/2.0;
    findStart = findSpan+1.0;
    
    i_AdcDynTest_v3 = colon(findStart,findSpac,ad_len/2.0); int i_AdcDynTest_i3;
    for (i_AdcDynTest_i3=0;i_AdcDynTest_i3<i_AdcDynTest_v3.cols();i_AdcDynTest_i3++) {
      forelem(i_,i_AdcDynTest_v3,i_AdcDynTest_i3);
      l = max(1.0,i_-findSpan);
      u = min(ad_len/2.0,i_+findSpan);
      /*[spectP_disturb_peak,num] = */max(spectP_temp(colon(l,1.0,u)),i_o,spectP_disturb_peak,num);
      
      if (istrue(spectP_disturb_peak>spectP_disturb(1.0))) {
        spectP_disturb(1.0) = spectP_disturb_peak;
        Harbin_disturb(1.0) = i_-findStart+num;
        array_flag = 1.0;
      } else {
        
        array_flag = 0.0;
      }
      if (istrue(array_flag==1.0)) {
        jj_AdcDynTest_v4 = colon(1.0,1.0,disturb_len-2.0); int jj_AdcDynTest_i4;
        for (jj_AdcDynTest_i4=0;jj_AdcDynTest_i4<jj_AdcDynTest_v4.cols();jj_AdcDynTest_i4++) {
          forelem(jj,jj_AdcDynTest_v4,jj_AdcDynTest_i4);
          k_AdcDynTest_v5 = colon(1.0,1.0,(disturb_len-jj)); int k_AdcDynTest_i5;
          for (k_AdcDynTest_i5=0;k_AdcDynTest_i5<k_AdcDynTest_v5.cols();k_AdcDynTest_i5++) {
            forelem(k,k_AdcDynTest_v5,k_AdcDynTest_i5);
            if (istrue(spectP_disturb(k)>spectP_disturb(k+1.0))) {
              spectP_disturb_temp = spectP_disturb(k);
              spectP_disturb(k) = spectP_disturb(k+1.0);
              spectP_disturb(k+1.0) = spectP_disturb_temp;
              Harbin_disturb_temp = Harbin_disturb(k);
              Harbin_disturb(k) = Harbin_disturb(k+1.0);
              Harbin_disturb(k+1.0) = Harbin_disturb_temp;
              
            }
          }
        }
      }
    }
    Ph_disturb = nop_M;
    Ph_disturb_dB = nop_M;
    Fn_disturb = Harbin_disturb/(ad_len);
    i_AdcDynTest_v6 = colon(1.0,1.0,disturb_len); int i_AdcDynTest_i6;
    for (i_AdcDynTest_i6=0;i_AdcDynTest_i6<i_AdcDynTest_v6.cols();i_AdcDynTest_i6++) {
      forelem(i_,i_AdcDynTest_v6,i_AdcDynTest_i6);
      l = max(1.0,Harbin_disturb(i_)-spanh_har);
      u = min(ad_len/2.0,Harbin_disturb(i_)+spanh_har);
      Ph_disturb = (BR(Ph_disturb),sum(spectP(colon(l,1.0,u))));
      Ph_disturb_dB = (BR(Ph_disturb_dB),sum(ADout_dB(colon(l,1.0,u))));
    }
    Pd_disturb = sum(Ph_disturb(colon(1.0,1.0,disturb_len)));
    Pd_disturb_dB = sum(Ph_disturb_dB(colon(1.0,1.0,disturb_len)));
    
    Pd = sum(Ph(colon(2.0,1.0,10.0)));
    Pd_dB = sum(Ph_dB(colon(2.0,1.0,10.0)));
    
    
    Pn = (sum(spectP(colon(1.0,1.0,ad_len/2.0)))-Pdc-Ps-Pd);
    Pn_dB = (sum(ADout_dB(colon(1.0,1.0,ad_len/2.0)))-Pdc_dB-Ps_dB-Pd_dB-Pd_disturb_dB)*2.0/ad_len-ref_dB;
    // Vin = 20*log10( Vpp / 2 );
    Vin = maxdB-ref_dB;
    SINAD = 10.0*log10(Ps/(Pn+Pd));
    SNR = 10.0*log10(Ps/Pn);
    
    // $$$ disp( 'THD is calculated from 2nd through 5th order harmonics' );
    THD = 10.0*log10(Pd/Ph(1.0));
    SFDR = 10.0*log10(Ph(1.0)/max(max(Ph(colon(2.0,1.0,10.0)),max(Ph_disturb(colon(1.0,1.0,disturb_len))))));
    
    // $$$ disp( 'Signal & Harmonic Power Components:' );
    HD = 10.0*log10(Ph(colon(1.0,1.0,10.0))/Ph(1.0));
    
    
    
    
    // $$$ hold on; 
    // $$$ 
    // $$$ plot( Fh( 2 )*fclk, ADout_dB( Harbin( 2 ) ) - ref_dB, 'rv', Fh( 3 )*fclk, ADout_dB( Harbin( 3 ) ) - ref_dB, 'rv', Fh( 4 )*fclk, ADout_dB( Harbin( 4 ) ) - ref_dB, 'rv', Fh( 5 )*fclk, ADout_dB( Harbin( 5 ) ) - ref_dB, 'rv', Fh( 6 )*fclk, ADout_dB( Harbin( 6 ) ) - ref_dB, 'rv', Fh( 7 )*fclk, ADout_dB( Harbin( 7 ) ) - ref_dB, 'rv', Fh( 8 )*fclk, ADout_dB( Harbin( 8 ) ) - ref_dB, 'rv', Fh( 9 )*fclk, ADout_dB( Harbin( 9 ) ) - ref_dB, 'rv', Fh( 10 )*fclk, ADout_dB( Harbin( 10 ) ) - ref_dB, 'rv' );
    // $$$ hold on;
    // $$$ plot( [0:round( ad_len / 2 ) - 1].*fclk / ad_len, Pn_dB, 'm - ' );
    // $$$ switch ( NFFT )
    // $$$  case 16384
    // $$$   NFFT_txt = '16K';
    // $$$  case 32768
    // $$$   NFFT_txt = '32K';
    // $$$  case 65536
    // $$$   NFFT_txt = '64K'; 
    // $$$ end
    // $$$ FRQ_txt = num2str( freq_fin / 1e6, '%2.1f' );
    // $$$ FRQ_txt = strcat( FRQ_txt, 'MHz' );
    // $$$ FFT_txt = strcat( NFFT_txt, ' FFT' );
    // $$$ FREQ_txt = strcat( num2str( fclk / 1e6, '%2d' ), 'MSPS' );
    // $$$ DBFS_txt = strcat( FRQ_txt, '@', num2str( maxdB - ref_dB, '%2.1f' ), 'dBFs' );
    // $$$ SNR_txt = strcat( 'SNR =', num2str( SNR, '% 2.3f' ), ' dBc' );
    // $$$ SFDR_txt = strcat( 'SFDR = ', num2str( SFDR, '% 2.3f' ), ' dBc' );
    // $$$ text( fclk*5.6 / 16, - 5, FFT_txt, 'HorizontalAlignment', 'left', 'Color', 'r' );
    // $$$ text( fclk*5.6 / 16, - 13, FREQ_txt, 'HorizontalAlignment', 'left', 'Color', 'r' );
    // $$$ text( fclk*5.6 / 16, - 21, DBFS_txt, 'HorizontalAlignment', 'left', 'Color', 'r' );
    // $$$ text( fclk*5.6 / 16, - 29, SNR_txt, 'HorizontalAlignment', 'left', 'Color', 'r' );
    // $$$ text( fclk*5.6 / 16, - 37, SFDR_txt, 'HorizontalAlignment', 'left', 'Color', 'r' );
    // $$$ text( Fh( 2 )*fclk, ADout_dB( Harbin( 2 ) ) - ref_dB + 2, '2', 'VerticalAlignmen', 'bottom', 'Color', 'r' );
    // $$$ text( Fh( 3 )*fclk, ADout_dB( Harbin( 3 ) ) - ref_dB + 2, '3', 'VerticalAlignmen', 'bottom', 'Color', 'r' );
    // $$$ text( Fh( 4 )*fclk, ADout_dB( Harbin( 4 ) ) - ref_dB + 2, '4', 'VerticalAlignmen', 'bottom', 'Color', 'r' );
    // $$$ text( Fh( 5 )*fclk, ADout_dB( Harbin( 5 ) ) - ref_dB + 2, '5', 'VerticalAlignmen', 'bottom', 'Color', 'r' );
    // $$$ text( Fh( 6 )*fclk, ADout_dB( Harbin( 6 ) ) - ref_dB + 2, '6', 'VerticalAlignmen', 'bottom', 'Color', 'r' );
    // $$$ text( Fh( 7 )*fclk, ADout_dB( Harbin( 7 ) ) - ref_dB + 2, '7', 'VerticalAlignmen', 'bottom', 'Color', 'r' );
    // $$$ text( Fh( 8 )*fclk, ADout_dB( Harbin( 8 ) ) - ref_dB + 2, '8', 'VerticalAlignmen', 'bottom', 'Color', 'r' );
    // $$$ text( Fh( 9 )*fclk, ADout_dB( Harbin( 9 ) ) - ref_dB + 2, '9', 'VerticalAlignmen', 'bottom', 'Color', 'r' );
    // $$$ text( Fh( 10 )*fclk, ADout_dB( Harbin( 10 ) ) - ref_dB + 2, '10', 'VerticalAlignmen', 'bottom', 'Color', 'r' );
    // $$$ hold on;
    // $$$ for i = 0:disturb_len / 2
    // $$$  hold on;
    // $$$  plot( Fn_disturb( disturb_len - i )*fclk, ADout_dB( Harbin_disturb( disturb_len - i ) ) - ref_dB, 'g*' );
    // $$$ end
    // $$$ hold off;
    // $$$ 
    // $$$ 
    // $$$ VPP_txt = strcat( num2str( Vpp, '%2.3f' ), ' Vpp' );
    // $$$ figure( 2 )
    // $$$ 
    // $$$ plot( [1:ad_len_N].*1e3 / fclk, ADout( 1:ad_len_N ) );
    // $$$ title( 'Time PLOT' ); 
    // $$$ xlabel( 'TIME ( ms )' );
    // $$$ ylabel( 'AMPLITUDE ( V )' );
    // $$$ hold on
    
    SNRFS = SNR+abs(maxdB-ref_dB);
    ENOB = (SINAD-1.76)/6.02;
    ENOBFS = ENOB+abs(maxdB-ref_dB)/6.02;
    HD = (BR(ADout_dB(max(Harbin(2.0),1.0))-ref_dB),ADout_dB(max(Harbin(2.0),1.0))-ref_dB,ADout_dB(max(Harbin(3.0) \
      ,1.0))-ref_dB,ADout_dB(max(Harbin(4.0),1.0))-ref_dB,ADout_dB(max(Harbin(5.0),1.0))-ref_dB,ADout_dB(max(Harbin( \
      6.0),1.0))-ref_dB,ADout_dB(max(Harbin(7.0),1.0))-ref_dB,ADout_dB(max(Harbin(8.0),1.0))-ref_dB,ADout_dB(max(Harbin( \
      9.0),1.0))-ref_dB,ADout_dB(max(Harbin(10.0),1.0))-ref_dB);
    
    y = ADout_dB-ref_dB;
    
    call_stack_end;
    
    // nargin, nargout exit code
    nargin_val=old_nargin; nargout_val=old_nargout;
    
    // function exit code
    ADout.setname(NULL); fclk.setname(NULL); numbit.setname(NULL); NFFT.setname(NULL); V.setname(NULL); code.setname( \
      NULL); 
    SNR__o=SNR; SINAD__o=SINAD; SFDR__o=SFDR; ENOB__o=ENOB; HD__o=HD; y__o=y; 
    return x_M;
    end_scope
  }
  
  
  Mm AdcDynTest(Mm ADout, Mm fclk, Mm numbit, Mm NFFT, Mm V, Mm code) {
    begin_scope
    double old_nargin=nargin_val; nargin_val=6.0; nargin_set=1;
    double old_nargout=nargout_val; nargout_val=1.0; nargout_set=1;
    dMm(SNR__o); dMm(SINAD__o); dMm(SFDR__o); dMm(ENOB__o); dMm(HD__o); dMm(y__o); 
    AdcDynTest(ADout, fclk, numbit, NFFT, V, code, i_o, SNR__o, SINAD__o, SFDR__o, ENOB__o, HD__o, y__o);
    nargout_val=old_nargout;
    nargin_val=old_nargin;
    return(SNR__o);
    end_scope
  }
  
  Mm AdcDynTest(Mm ADout, Mm fclk, Mm numbit, Mm NFFT, Mm V, Mm code, i_o_t, Mm& SNR__o, Mm& SINAD__o) {
    begin_scope
    double old_nargin=nargin_val; nargin_val=6.0; nargin_set=1;
    double old_nargout=nargout_val; nargout_val=2.0; nargout_set=1;
    dMm(SFDR__o); dMm(ENOB__o); dMm(HD__o); dMm(y__o); 
    AdcDynTest(ADout, fclk, numbit, NFFT, V, code, i_o, SNR__o, SINAD__o, SFDR__o, ENOB__o, HD__o, y__o);
    nargout_val=old_nargout;
    nargin_val=old_nargin;
    return x_M;
    end_scope
  }
  
  Mm AdcDynTest(Mm ADout, Mm fclk, Mm numbit, Mm NFFT, Mm V, Mm code, i_o_t, Mm& SNR__o, Mm& SINAD__o, Mm& SFDR__o) \
     {
    begin_scope
    double old_nargin=nargin_val; nargin_val=6.0; nargin_set=1;
    double old_nargout=nargout_val; nargout_val=3.0; nargout_set=1;
    dMm(ENOB__o); dMm(HD__o); dMm(y__o); 
    AdcDynTest(ADout, fclk, numbit, NFFT, V, code, i_o, SNR__o, SINAD__o, SFDR__o, ENOB__o, HD__o, y__o);
    nargout_val=old_nargout;
    nargin_val=old_nargin;
    return x_M;
    end_scope
  }
  
  Mm AdcDynTest(Mm ADout, Mm fclk, Mm numbit, Mm NFFT, Mm V, Mm code, i_o_t, Mm& SNR__o, Mm& SINAD__o, Mm& SFDR__o, \
     Mm& ENOB__o) {
    begin_scope
    double old_nargin=nargin_val; nargin_val=6.0; nargin_set=1;
    double old_nargout=nargout_val; nargout_val=4.0; nargout_set=1;
    dMm(HD__o); dMm(y__o); 
    AdcDynTest(ADout, fclk, numbit, NFFT, V, code, i_o, SNR__o, SINAD__o, SFDR__o, ENOB__o, HD__o, y__o);
    nargout_val=old_nargout;
    nargin_val=old_nargin;
    return x_M;
    end_scope
  }
  
  Mm AdcDynTest(Mm ADout, Mm fclk, Mm numbit, Mm NFFT, Mm V, Mm code, i_o_t, Mm& SNR__o, Mm& SINAD__o, Mm& SFDR__o, \
     Mm& ENOB__o, Mm& HD__o) {
    begin_scope
    double old_nargin=nargin_val; nargin_val=6.0; nargin_set=1;
    double old_nargout=nargout_val; nargout_val=5.0; nargout_set=1;
    dMm(y__o); 
    AdcDynTest(ADout, fclk, numbit, NFFT, V, code, i_o, SNR__o, SINAD__o, SFDR__o, ENOB__o, HD__o, y__o);
    nargout_val=old_nargout;
    nargin_val=old_nargin;
    return x_M;
    end_scope
  }
  
