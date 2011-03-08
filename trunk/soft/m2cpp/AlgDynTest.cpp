  #include "matlib.h"
  #pragma hdrstop
  
  #include "AlgDynTest.h"
  #include "chebwin.h"
  
  
  
  Mm AlgDynTest(Mm data1, Mm data2, Mm numpt, Mm fclk, Mm numbit, Mm r, i_o_t, Mm& SNR__o, Mm& SINAD__o, Mm& SFDR__o, \
     Mm& ENOB__o, Mm& y__o) {
    begin_scope
    data1.setname("data1"); data2.setname("data2"); numpt.setname("numpt"); fclk.setname("fclk"); numbit.setname( \
      "numbit"); r.setname("r"); 
    dMm(SNR); dMm(SINAD); dMm(SFDR); dMm(ENOB); dMm(y); dMm(all_); dMm(fpga_i); dMm(fpga_q); dMm(V); dMm(NFFT); dMm( \
      TPY); dMm(TPX); dMm(code); dMm(fpga_len); dMm(ADout); dMm(ad_len_N); dMm(maxADout); dMm(real_ADout); dMm(AmpMax) \
      ; dMm(t1); dMm(AmpMin); dMm(t2); dMm(Vpp); dMm(ADout_w); dMm(ad_len); dMm(ADout_spect); dMm(abs_ADout_spect);  \
      dMm(ADout_dB); dMm(maxdB_1); dMm(maxdB_2); dMm(maxdB); dMm(fin_v); dMm(fin); dMm(fin_1); dMm(fin_lsb); dMm(freq_fin) \
      ; dMm(data_ref_iq); dMm(n); dMm(n_AlgDynTest_v0); dMm(fin_angle); dMm(data_ref_w); dMm(data_ref_spect); dMm(data_ref_dB) \
      ; dMm(ref_dB); dMm(BW); dMm(BW_len); dMm(X_FREQ); dMm(X_FREQ1); dMm(span); dMm(spanh_har); dMm(span_s); dMm(spectP) \
      ; dMm(l); dMm(u); dMm(Pdc); dMm(Pdc_dB); dMm(Ps); dMm(Ps_dB); dMm(Fh); dMm(Ph); dMm(Ph_1); dMm(Harbin); dMm(Harbin_1) \
      ; dMm(Ph_dB); dMm(Ph_dB_1); dMm(har_num); dMm(har_num_AlgDynTest_v1); dMm(tone); dMm(har_peak); dMm(har_bin);  \
      dMm(har_peak_1); dMm(har_bin_1); dMm(spectP_temp); dMm(i_); dMm(i_AlgDynTest_v2); dMm(disturb_len); dMm(spectP_disturb) \
      ; dMm(Harbin_disturb); dMm(findSpac); dMm(findSpan); dMm(findStart); dMm(i_AlgDynTest_v3); dMm(spectP_disturb_peak) \
      ; dMm(num); dMm(array_flag); dMm(jj); dMm(jj_AlgDynTest_v4); dMm(k); dMm(k_AlgDynTest_v5); dMm(spectP_disturb_temp) \
      ; dMm(Harbin_disturb_temp); dMm(Ph_disturb); dMm(Ph_disturb_dB); dMm(Fn_disturb); dMm(i_AlgDynTest_v6); dMm(Pd_disturb) \
      ; dMm(Pd_disturb_dB); dMm(Pd); dMm(Pd_dB); dMm(Pd_dB_1); dMm(Pd_dB_2); dMm(Pn); dMm(Pn_dB); dMm(Vin); dMm(THD) \
      ; dMm(HD); dMm(SNRFS); dMm(ENOBFS); 
    
    call_stack_begin;
    // nargin, nargout entry code
    double old_nargin=nargin_val; if (!nargin_set) nargin_val=6.0;
    nargin_set=0;
    double old_nargout=nargout_val; if (!nargout_set) nargout_val=5.0;
    nargout_set=0;
    
    // translated code
    
    clear((CL(all_)));
    figure_close(TM("all"));
    format(TM("long"));
    
    // y = ADout_dB
    fpga_i = data1/mpower(2.0,(numbit-1.0));
    fpga_q = data2/mpower(2.0,(numbit-1.0));
    
    // fclk = 80e6;
    // r=20;
    // numbit = 16;
    
    V = 2.0;
    NFFT = min(32768.0,length(data1));
    NFFT = floor(NFFT/2.0)*2.0;
    TPY = 1.0;
    TPX = 0.2;
    code = 1.0;
    fclk = fclk/r;
    
    
    fpga_len = length(fpga_i);
    
    ADout = V/2.0*(fpga_i+j*fpga_q);
    //-负频带 +正频带
    ad_len_N = length(ADout);
    //ref_dB = 74.666;%0dbm时候的计算值。75.25
    
    maxADout = max(abs(ADout));
    real_ADout = real(ADout);
    
    /*[AmpMax,t1] = */max(real_ADout,i_o,AmpMax,t1);
    /*[AmpMin,t2] = */min(real_ADout,i_o,AmpMin,t2);
    Vpp = AmpMax-AmpMin;
    
    ADout_w = times(ADout,chebwin(ad_len_N,200.0));
    // ADout_w=ADout.*chebchebwin(ad_len_N,200);
    //ADout_w=ADout.*chebchebwin(ad_len);
    // AA = zeros(NFFT-ad_len_N,1);
    //  ADout_w = [ADout_w;AA];
    ad_len = length(ADout_w);
    ADout_spect = fftshift(fft(ADout_w,NFFT));
    abs_ADout_spect = abs(ADout_spect);
    ADout_dB = 20.0*log10(abs_ADout_spect);
    
    //Display the results in the frequency domain with an FFT plot 
    //figure;  
    maxdB_1 = max(ADout_dB(colon(1.0,1.0,ad_len/2.0-6.0)));
    maxdB_2 = max(ADout_dB(colon(ad_len/2.0+6.0,1.0,ad_len)));
    //直流点数与采样深度是否有关？ 后面定义了直流点位5个！
    maxdB = max(maxdB_1,maxdB_2);
    fin_v = find(ADout_dB(colon(1.0,1.0,ad_len))==maxdB);
    //排除直流点数以外的最大值
    fin = fin_v(1.0);
    if (istrue(fin<ad_len/2.0)) {
      fin_1 = ad_len/2.0-fin;
    } else {
      
      fin_1 = fin-ad_len/2.0;
    }
    
    fin_lsb = fin_1/ad_len;
    freq_fin = fin_lsb*fclk;
    
    //refdB
    data_ref_iq = zeros(ad_len_N,1.0);
    n_AlgDynTest_v0 = colon(1.0,1.0,ad_len_N); int n_AlgDynTest_i0;
    for (n_AlgDynTest_i0=0;n_AlgDynTest_i0<n_AlgDynTest_v0.cols();n_AlgDynTest_i0++) {
      forelem(n,n_AlgDynTest_v0,n_AlgDynTest_i0);
      
      fin_angle = 2.0*(n-1.0)*fin_lsb*pi;
      data_ref_iq(n) = V/2.0*(cos(fin_angle)+j*sin(fin_angle));
    }
    
    data_ref_w = times(data_ref_iq,chebwin(ad_len_N,200.0));
    // data_ref_w=data_ref_iq .* chebwin(ad_len_N, 200);
    
    //  data_ref_w = [data_ref_w;AA];
    data_ref_spect = fft(data_ref_w,NFFT);
    data_ref_dB = 20.0*log10(abs(data_ref_spect));
    ref_dB = max(data_ref_dB(colon(1.0,1.0,ad_len/2.0)));
    BW = fclk/4.0;
    BW_len = (BW/fclk)*ad_len;
    
    X_FREQ = (BR(colon(-ad_len/2.0,1.0,ad_len/2.0-1.0)));
    //频率X轴由负-0-正排序
    //AD_freq_all = fftshift(ADout_dB);                                                        %dB值按频率排序，与上面相对应
    //AD_freq_all_spect = 
    X_FREQ1 = (BR(colon(-ad_len/2.0,200.0,ad_len/2.0-1.0)));
    
    
    //Calculate SNR, SINAD, THD and SFDR valuess
    //Find the signal bin number, DC = bin 1
    
    //Span of the DC on each side
    span = max(6.0);
    
    //Searching span for peak harmonics amp on each side  
    spanh_har = 4.0;
    //Span of the signal on each side
    span_s = 19.0;
    //Determine power spectrum
    spectP = (power(abs_ADout_spect,2.0));
    // spectP = (abs(ADout_spect)) .* (abs(ADout_spect)); 
    //Find DC offset power 
    
    l = max(ad_len/2.0-span,1.0);
    
    u = min(ad_len/2.0+span,length(spectP));
    
    Pdc = sum(spectP(colon(l,1.0,u)));
    
    
    l = max(ad_len/2.0-span,1.0);
    
    u = min(ad_len/2.0+span,length(ADout_dB));
    
    Pdc_dB = sum(ADout_dB(colon(l,1.0,u)));
    
    //Extract overall signal power 
    l = max(fin-span_s,1.0);
    
    u = min(fin+span_s,length(spectP));
    
    Ps = sum(spectP(colon(l,1.0,u)));
    
    l = max(fin-span_s,1.0);
    
    u = min(fin+span_s,length(ADout_dB));
    
    Ps_dB = sum(ADout_dB(colon(l,1.0,u)));
    //Vector/matrix to store both frequency and power of signal and harmonics
    Fh = nop_M;
    
    
    //The 1st element in the vector/matrix represents the signal, the next element represents
    //the 2nd harmonic, etc.
    Ph = nop_M;
    
    Ph_1 = nop_M;
    Harbin = nop_M;
    Harbin_1 = nop_M;
    Ph_dB = nop_M;
    Ph_dB_1 = nop_M;
    
    har_num_AlgDynTest_v1 = colon(1.0,1.0,11.0); int har_num_AlgDynTest_i1;
    for (har_num_AlgDynTest_i1=0;har_num_AlgDynTest_i1<har_num_AlgDynTest_v1.cols();har_num_AlgDynTest_i1++) {
      forelem(har_num,har_num_AlgDynTest_v1,har_num_AlgDynTest_i1);
      
      tone = rem((har_num*(fin_1-1.0)+1.0)/ad_len,1.0);
      
      if (istrue(tone>0.5)) {
        
        tone = 1.0-tone;
        
      }
      
      Fh = (BR(Fh),tone);
      
      
      l = max(round((tone+1.0/2.0)*ad_len)-spanh_har,1.0);
      
      u = min(round((tone+1.0/2.0)*ad_len)+spanh_har,length(spectP));
      
      har_peak = max(spectP(colon(l,1.0,u)));
      
      
      l = max(round((tone+1.0/2.0)*ad_len)-spanh_har,1.0);
      
      u = min(round((tone+1.0/2.0)*ad_len)+spanh_har,length(spectP));
      
      har_bin = find(spectP(colon(l,1.0,u))==har_peak);
      
      har_bin = har_bin+round((tone+1.0/2.0)*ad_len)-spanh_har-1.0;
      
      l = max(har_bin-spanh_har,1.0);
      
      u = min(har_bin+spanh_har,length(spectP));
      
      Ph = (BR(Ph),sum(spectP(colon(l,1.0,u))));
      
      
      l = max(har_bin-spanh_har,1.0);
      
      u = min(har_bin+spanh_har,length(spectP));
      
      Ph_dB = (BR(Ph_dB),sum(ADout_dB(colon(l,1.0,u))));
      
      Harbin = (BR(Harbin),har_bin);
      
      l = max(round((1.0/2.0-tone)*ad_len)-spanh_har,1.0);
      
      u = min(round((1.0/2.0-tone)*ad_len)+spanh_har,length(spectP));
      
      har_peak_1 = max(spectP(colon(l,1.0,u)));
      
      
      l = max(round((1.0/2.0-tone)*ad_len)-spanh_har,1.0);
      
      u = min(round((1.0/2.0-tone)*ad_len)+spanh_har,length(spectP));
      
      har_bin_1 = find(spectP(colon(l,1.0,u))==har_peak_1);
      
      har_bin_1 = har_bin_1+round((1.0/2.0-tone)*ad_len)-spanh_har-1.0;
      
      l = max(har_bin_1-spanh_har,1.0);
      
      u = min(har_bin_1+spanh_har,length(spectP));
      
      Ph_1 = (BR(Ph_1),sum(spectP(colon(l,1.0,u))));
      
      l = max(har_bin_1-spanh_har,1.0);
      
      u = min(har_bin_1+spanh_har,length(spectP));
      
      Ph_dB_1 = (BR(Ph_dB_1),sum(ADout_dB(colon(l,1.0,u))));
      
      Harbin_1 = (BR(Harbin_1),har_bin_1);
    }
    
    
    spectP_temp = spectP;
    
    i_AlgDynTest_v2 = colon(2.0,1.0,10.0); int i_AlgDynTest_i2;
    for (i_AlgDynTest_i2=0;i_AlgDynTest_i2<i_AlgDynTest_v2.cols();i_AlgDynTest_i2++) {
      forelem(i_,i_AlgDynTest_v2,i_AlgDynTest_i2);
      l = max(Harbin(i_)-spanh_har,1.0);
      
      u = min(Harbin(i_)+spanh_har,length(spectP_temp));
      spectP_temp(colon(l,1.0,u)) = 0.0;
    }
    
    l = max(fin-span_s,1.0);
    
    u = min(fin+span_s,length(spectP_temp));
    
    spectP_temp(colon(l,1.0,u)) = 0.0;
    
    l = max(ad_len/2.0-span,1.0);
    
    u = min(ad_len/2.0+span,length(spectP_temp));
    
    spectP_temp(colon(l,1.0,u)) = 0.0;
    
    
    
    disturb_len = 20.0;
    spectP_disturb = zeros(1.0,disturb_len);
    Harbin_disturb = zeros(1.0,disturb_len);
    findSpac = 60.0;
    findSpan = (findSpac-1.0)/2.0;
    findStart = findSpan+1.0;
    
    i_AlgDynTest_v3 = colon(findStart,findSpac,ad_len); int i_AlgDynTest_i3;
    for (i_AlgDynTest_i3=0;i_AlgDynTest_i3<i_AlgDynTest_v3.cols();i_AlgDynTest_i3++) {
      forelem(i_,i_AlgDynTest_v3,i_AlgDynTest_i3);
      l = max(i_-findSpan,1.0);
      
      u = min(i_+findSpan,length(spectP_temp));
      /*[spectP_disturb_peak,num] = */max(spectP_temp(colon(l,1.0,u)),i_o,spectP_disturb_peak,num);
      
      if (istrue(spectP_disturb_peak>spectP_disturb(1.0))) {
        spectP_disturb(1.0) = spectP_disturb_peak;
        Harbin_disturb(1.0) = i_-findStart+num;
        array_flag = 1.0;
      } else {
        
        array_flag = 0.0;
      }
      if (istrue(array_flag==1.0)) {
        jj_AlgDynTest_v4 = colon(1.0,1.0,disturb_len-2.0); int jj_AlgDynTest_i4;
        for (jj_AlgDynTest_i4=0;jj_AlgDynTest_i4<jj_AlgDynTest_v4.cols();jj_AlgDynTest_i4++) {
          forelem(jj,jj_AlgDynTest_v4,jj_AlgDynTest_i4);
          k_AlgDynTest_v5 = colon(1.0,1.0,(disturb_len-jj)); int k_AlgDynTest_i5;
          for (k_AlgDynTest_i5=0;k_AlgDynTest_i5<k_AlgDynTest_v5.cols();k_AlgDynTest_i5++) {
            forelem(k,k_AlgDynTest_v5,k_AlgDynTest_i5);
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
    Fn_disturb = (Harbin_disturb-ad_len/2.0)/(ad_len);
    i_AlgDynTest_v6 = colon(1.0,1.0,disturb_len); int i_AlgDynTest_i6;
    for (i_AlgDynTest_i6=0;i_AlgDynTest_i6<i_AlgDynTest_v6.cols();i_AlgDynTest_i6++) {
      forelem(i_,i_AlgDynTest_v6,i_AlgDynTest_i6);
      l = max(Harbin_disturb(i_)-spanh_har,1.0);
      
      
      u = min(Harbin_disturb(i_)+spanh_har,length(spectP));
      
      Ph_disturb = (BR(Ph_disturb),sum(spectP(colon(l,1.0,u))));
      
      l = max(Harbin_disturb(i_)-spanh_har,1.0);
      
      
      u = min(Harbin_disturb(i_)+spanh_har,length(ADout_dB));
      
      Ph_disturb_dB = (BR(Ph_disturb_dB),sum(ADout_dB(colon(l,1.0,u))));
      
    }
    Pd_disturb = sum(Ph_disturb(colon(1.0,1.0,disturb_len)));
    Pd_disturb_dB = sum(Ph_disturb_dB(colon(1.0,1.0,disturb_len)));
    
    Pd = sum(Ph(colon(2.0,1.0,10.0)));
    Pd_dB = sum(Ph_dB(colon(2.0,1.0,10.0)));
    Pd_dB_1 = sum(Ph_dB_1(colon(2.0,1.0,10.0)));
    Pd_dB_2 = Pd_dB+Pd_dB_1;
    
    
    Pn = (sum(spectP(colon(1.0,1.0,ad_len)))-Pdc-Ps-Pd);
    
    l = max((ad_len/2.0-BW_len),1.0);
    
    
    u = min(ad_len/2.0+BW_len,length(ADout_dB));
    
    Pn_dB = (sum(ADout_dB(colon(l,1.0,u)))-Pdc_dB-Ps_dB-Pd_dB_2-Pd_disturb_dB)/(2.0*BW_len)-ref_dB;
    // Vin = 20*log10(Vpp/2);
    Vin = maxdB-ref_dB;
    SINAD = 10.0*log10(Ps/(Pn+Pd));
    SNR = 10.0*log10(Ps/Pn);
    
    THD = 10.0*log10(Pd/Ps);
    SFDR = 10.0*log10(Ps/max(max(Ph(colon(2.0,1.0,10.0)),max(Ph_disturb(colon(1.0,1.0,disturb_len))))));
    
    HD = 10.0*log10(Ph(colon(1.0,1.0,10.0))/Ph(1.0));
    
    
    SNRFS = SNR+abs(maxdB-ref_dB);
    ENOB = (SINAD-1.76)/6.02;
    ENOBFS = ENOB+abs(maxdB-ref_dB)/6.02;
    // A = [AmpMax,AmpMin];
    // AdB = Vin;
    HD = (BR(ADout_dB(max(Harbin(2.0),1.0))-ref_dB),ADout_dB(max(Harbin(2.0),1.0))-ref_dB,ADout_dB(max(Harbin(3.0) \
      ,1.0))-ref_dB,ADout_dB(max(Harbin(4.0),1.0))-ref_dB,ADout_dB(max(Harbin(5.0),1.0))-ref_dB,ADout_dB(max(Harbin( \
      6.0),1.0))-ref_dB,ADout_dB(max(Harbin(7.0),1.0))-ref_dB,ADout_dB(max(Harbin(8.0),1.0))-ref_dB,ADout_dB(max(Harbin( \
      9.0),1.0))-ref_dB,ADout_dB(max(Harbin(10.0),1.0))-ref_dB);
    
    y = ADout_dB-ref_dB;
    
    call_stack_end;
    
    // nargin, nargout exit code
    nargin_val=old_nargin; nargout_val=old_nargout;
    
    // function exit code
    data1.setname(NULL); data2.setname(NULL); numpt.setname(NULL); fclk.setname(NULL); numbit.setname(NULL); r.setname( \
      NULL); 
    SNR__o=SNR; SINAD__o=SINAD; SFDR__o=SFDR; ENOB__o=ENOB; y__o=y; 
    return x_M;
    end_scope
  }
  
  
  Mm AlgDynTest(Mm data1, Mm data2, Mm numpt, Mm fclk, Mm numbit, Mm r) {
    begin_scope
    double old_nargin=nargin_val; nargin_val=6.0; nargin_set=1;
    double old_nargout=nargout_val; nargout_val=1.0; nargout_set=1;
    dMm(SNR__o); dMm(SINAD__o); dMm(SFDR__o); dMm(ENOB__o); dMm(y__o); 
    AlgDynTest(data1, data2, numpt, fclk, numbit, r, i_o, SNR__o, SINAD__o, SFDR__o, ENOB__o, y__o);
    nargout_val=old_nargout;
    nargin_val=old_nargin;
    return(SNR__o);
    end_scope
  }
  
  Mm AlgDynTest(Mm data1, Mm data2, Mm numpt, Mm fclk, Mm numbit, Mm r, i_o_t, Mm& SNR__o, Mm& SINAD__o) {
    begin_scope
    double old_nargin=nargin_val; nargin_val=6.0; nargin_set=1;
    double old_nargout=nargout_val; nargout_val=2.0; nargout_set=1;
    dMm(SFDR__o); dMm(ENOB__o); dMm(y__o); 
    AlgDynTest(data1, data2, numpt, fclk, numbit, r, i_o, SNR__o, SINAD__o, SFDR__o, ENOB__o, y__o);
    nargout_val=old_nargout;
    nargin_val=old_nargin;
    return x_M;
    end_scope
  }
  
  Mm AlgDynTest(Mm data1, Mm data2, Mm numpt, Mm fclk, Mm numbit, Mm r, i_o_t, Mm& SNR__o, Mm& SINAD__o, Mm& SFDR__o) \
     {
    begin_scope
    double old_nargin=nargin_val; nargin_val=6.0; nargin_set=1;
    double old_nargout=nargout_val; nargout_val=3.0; nargout_set=1;
    dMm(ENOB__o); dMm(y__o); 
    AlgDynTest(data1, data2, numpt, fclk, numbit, r, i_o, SNR__o, SINAD__o, SFDR__o, ENOB__o, y__o);
    nargout_val=old_nargout;
    nargin_val=old_nargin;
    return x_M;
    end_scope
  }
  
  Mm AlgDynTest(Mm data1, Mm data2, Mm numpt, Mm fclk, Mm numbit, Mm r, i_o_t, Mm& SNR__o, Mm& SINAD__o, Mm& SFDR__o, \
     Mm& ENOB__o) {
    begin_scope
    double old_nargin=nargin_val; nargin_val=6.0; nargin_set=1;
    double old_nargout=nargout_val; nargout_val=4.0; nargout_set=1;
    dMm(y__o); 
    AlgDynTest(data1, data2, numpt, fclk, numbit, r, i_o, SNR__o, SINAD__o, SFDR__o, ENOB__o, y__o);
    nargout_val=old_nargout;
    nargin_val=old_nargin;
    return x_M;
    end_scope
  }
  
