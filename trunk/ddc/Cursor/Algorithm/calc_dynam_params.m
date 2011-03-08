function [SNR, SFDR, SNRFS, SINAD, THD, HD, ENOB, ENOBFS, Pn_dB] = calc_dynam_params(fclk, numbit, NFFT, V, TPY, TPX, code)
% Pn_dB为底噪声，fclk为采样频率，numbit为采样精度，NFFT为FFT的深度，V为峰峰值，TPY和TPX分别为时域图的Y和X轴，code
% 为1：补码，2：偏移码，3：格雷码。
%例子：若采样时钟80MHZ，精度16为，峰峰值2v，时域图显示Y轴＋－1V和X轴0－0.01ms，码源为补码
%[SNR, SFDR, SNRFS,SINAD, THD, HD, ENOB, ENOBFS, Pn_dB] = calc_dynam_params(80e6, 16, 32768, 2, 1, 0.01, 1)
% clear all
% close all
% format long
% fclk = 80e6;
% numbit = 14;
% V = 2;
% NFFT = 32768;
% TPY = 1;
% TPX = 0.01;
% code = 1;
% fid = fopen('adc_0dbm.txt');%;
% fid = fopen('SNR测试_A通道_20090105053713.txt');
fid = fopen('adc_0dbm.txt');
ADout = fscanf(fid,'%d');
if code == 1
    if numbit < 16
        ADout = fix(ADout/2^(16-numbit));
    end
        ADout = ADout / 2^(numbit-1); 
elseif code == 2
    if numbit < 16
        ADout = fix(ADout/2^(16-numbit));
    end        
    ADout = ADout / 2^(numbit-1) - 1;
else
        if numbit < 16
        ADout = fix(ADout/2^(16-numbit));
    end  
    ADout = gray2bin(ADout) / 2^(numbit-1) - 1;
end
    
ADout = V/2*ADout;        
% ADout=input('the number of bits is');
% ADout=ADout/2^(numbit-1);
ad_len_N = length(ADout);
%ref_dB = 74.666;%0dbm时候的计算值。75.25

maxADout = max(abs(ADout));
[AmpMax t1]=max(ADout);
[AmpMin t2]=min(ADout);
Vpp = AmpMax - AmpMin;


ADout_w=ADout.*chebwin(ad_len_N,200);
%ADout_w=ADout.*chebwin(ad_len);
AA = zeros(NFFT-ad_len_N,1);
 ADout_w = [ADout_w;AA];
 ad_len = length(ADout_w);
ADout_spect=fft(ADout_w,NFFT);
ADout_dB=20*log10(abs(ADout_spect));

%Display the results in the frequency domain with an FFT plot 
%figure; 
maxdB=max(ADout_dB(1:ad_len/2));
fin=find(ADout_dB(1:ad_len/2)==maxdB); 
freq_fin = (fin*fclk/ad_len);

%refdB
data_ref = zeros(ad_len_N,1);
for n = 1:ad_len_N;    
    data_ref(n) = V/2*sin((n-1) * (freq_fin) / fclk * 2 * pi) ;
end
data_ref_w=data_ref.*chebwin(ad_len_N,200);

 data_ref_w = [data_ref_w;AA];
data_ref_spect=fft(data_ref_w,NFFT);
data_ref_dB=20*log10(abs(data_ref_spect));
ref_dB=max(data_ref_dB(1:ad_len/2));
figure(1)
plot([0:round(ad_len/2)-1].*fclk/ad_len,-20,'-k');
hold on;
plot([0:50:round(ad_len/2)-1].*fclk/ad_len,-40,'--k');
hold on;
plot([0:round(ad_len/2)-1].*fclk/ad_len,-60,'-k');
hold on;
plot([0:50:round(ad_len/2)-1].*fclk/ad_len,-80,'--k');
hold on;
plot([0:round(ad_len/2)-1].*fclk/ad_len,-100,'-k');
hold on;
plot([0:50:round(ad_len/2)-1].*fclk/ad_len,-120,'--k');
hold on;
plot([0:round(ad_len/2)-1].*fclk/ad_len,ADout_dB(1:round(ad_len/2))-ref_dB);


title('FFT PLOT'); 
xlabel('ANALOG INPUT FREQUENCY (MHz)');
ylabel('AMPLITUDE (dBFs)');
a1=axis; axis([a1(1) a1(2) -140 0]); 

%Calculate SNR, SINAD, THD and SFDR values
%Find the signal bin number, DC = bin 1

%Span of the DC on each side
span=max(11); 

%Searching span for peak harmonics amp on each side  
spanh_har = 4;
%Span of the signal on each side
span_s = 19;%8
%Determine power spectrum
spectP=(abs(ADout_spect)).*(abs(ADout_spect)); 
%Find DC offset power 
Pdc=sum(spectP(1:span)); 
Pdc_dB=sum(ADout_dB(1:span));
%Extract overall signal power 
Ps=sum(spectP(fin-span_s:fin+span_s));
Ps_dB=sum(ADout_dB(fin-span_s:fin+span_s));
%Vector/matrix to store both frequency and power of signal and harmonics
Fh=[]; 

%The 1st element in the vector/matrix represents the signal, the next element represents
%the 2nd harmonic, etc.
Ph=[]; 
Harbin = [];
Ph_dB = [];

for har_num=1:11

tone=rem((har_num*(fin-1)+1)/ad_len,1);

if tone>0.5 

tone=1-tone;

end 

Fh=[Fh tone]; 

har_peak=max(spectP(round(tone*ad_len)-spanh_har:round(tone*ad_len)+spanh_har)); 
har_bin=find(spectP(round(tone*ad_len)-spanh_har:round(tone*ad_len)+spanh_har)==har_peak);
har_bin=har_bin+round(tone*ad_len)-spanh_har-1;
Ph=[Ph sum(spectP(har_bin-spanh_har:har_bin+spanh_har))]; 
Ph_dB=[Ph_dB sum(ADout_dB(har_bin-spanh_har:har_bin+spanh_har))];
Harbin = [Harbin har_bin];
end


spectP_temp = spectP;

for i = 2:10
    spectP_temp(Harbin(i)-spanh_har:Harbin(i)+spanh_har) = 0;
end
spectP_temp(fin-span_s:fin+span_s) = 0;
spectP_temp(1:span) = 0;   


disturb_len = 19;
spectP_disturb = zeros(1,disturb_len);
Harbin_disturb = zeros(1,disturb_len);
findSpac = 30;
findSpan = (findSpac-1)/2;
findStart = findSpan + 1;

for i = findStart:findSpac:ad_len/2
    [spectP_disturb_peak, num]=max(spectP_temp(i-findSpan:i+findSpan)); 
    if (spectP_disturb_peak > spectP_disturb(1))
        spectP_disturb(1) = spectP_disturb_peak;
        Harbin_disturb(1) = i-findStart+num;
        array_flag = 1;
    else
        array_flag = 0;
    end
    if (array_flag == 1)
        for jj = 1:disturb_len - 2
            for k = 1:(disturb_len-jj)
                if spectP_disturb(k) > spectP_disturb(k+1)
                   spectP_disturb_temp = spectP_disturb(k);
                   spectP_disturb(k) = spectP_disturb(k+1);
                   spectP_disturb(k+1) = spectP_disturb_temp;
                   Harbin_disturb_temp = Harbin_disturb(k);
                   Harbin_disturb(k) = Harbin_disturb(k+1);
                   Harbin_disturb(k+1) = Harbin_disturb_temp;                  
                end
            end
        end
    end
end
Ph_disturb=[];
Ph_disturb_dB = [];
Fn_disturb = Harbin_disturb/(ad_len);
for i = 1:disturb_len
 Ph_disturb=[Ph_disturb sum(spectP(Harbin_disturb(i)-spanh_har:Harbin_disturb(i)+spanh_har))];
 Ph_disturb_dB = [Ph_disturb_dB sum(ADout_dB(Harbin_disturb(i)-spanh_har:Harbin_disturb(i)+spanh_har))];
end
 Pd_disturb = sum(Ph_disturb(1:disturb_len));
 Pd_disturb_dB = sum(Ph_disturb_dB(1:disturb_len));

Pd=sum(Ph(2:10));
Pd_dB = sum(Ph_dB(2:10));


Pn=(sum(spectP(1:ad_len/2))-Pdc-Ps-Pd);
Pn_dB = (sum(ADout_dB(1:ad_len/2))-Pdc_dB-Ps_dB-Pd_dB - Pd_disturb_dB)*2/ad_len - ref_dB;
% Vin = 20*log10(Vpp/2);
Vin = maxdB - ref_dB;
SINAD=10*log10(Ps/(Pn+Pd));
SNR=10*log10(Ps/Pn); 
disp('THD is calculated from 2nd through 5th order harmonics');
THD=10*log10(Pd/Ph(1));
SFDR=10*log10(Ph(1)/max(max(Ph(2:10),max(Ph_disturb(1:disturb_len))))); 
disp('Signal & Harmonic Power Components:');
HD=10*log10(Ph(1:10)/Ph(1));




hold on; 

plot(Fh(2)*fclk,ADout_dB(Harbin(2))-ref_dB,'rv',Fh(3)*fclk,ADout_dB(Harbin(3))-ref_dB,'rv',Fh(4)*fclk,ADout_dB(Harbin(4))-ref_dB,'rv',Fh(5)*fclk,ADout_dB(Harbin(5))-ref_dB,'rv', Fh(6)*fclk,ADout_dB(Harbin(6))-ref_dB,'rv',Fh(7)*fclk,ADout_dB(Harbin(7))-ref_dB,'rv',Fh(8)*fclk,ADout_dB(Harbin(8))-ref_dB,'rv',Fh(9)*fclk,ADout_dB(Harbin(9))-ref_dB,'rv',Fh(10)*fclk,ADout_dB(Harbin(10))-ref_dB,'rv');
hold on;
plot([0:round(ad_len/2)-1].*fclk/ad_len,Pn_dB,'m-');
switch (NFFT)
   case 16384
     NFFT_txt = '16K';
   case 32768
      NFFT_txt = '32K';
   case 65536
      NFFT_txt = '64K'; 
end
FRQ_txt = num2str(freq_fin/1e6,'%2.1f');
FRQ_txt = strcat(FRQ_txt,'MHz');
FFT_txt = strcat(NFFT_txt,' FFT');
FREQ_txt = strcat(num2str(fclk/1e6,'%2d'),'MSPS');
DBFS_txt = strcat(FRQ_txt,'@', num2str(maxdB-ref_dB,'%2.1f'),'dBFs');
SNR_txt = strcat('SNR =',num2str(SNR,'% 2.3f'),' dBc');
SFDR_txt = strcat('SFDR =  ',num2str(SFDR,'% 2.3f'),' dBc');
% SINAD_txt = strcat('SINAD: ',num2str(SINAD,'%2.3f'),' dB');
% THD_txt = strcat('THD: ',num2str(THD,'%2.3f'),' dB');
text(fclk*5.6/16,-5,FFT_txt,'HorizontalAlignment','left','Color','r');
text(fclk*5.6/16,-13,FREQ_txt,'HorizontalAlignment','left','Color','r');
text(fclk*5.6/16,-21,DBFS_txt,'HorizontalAlignment','left','Color','r');
text(fclk*5.6/16,-29,SNR_txt,'HorizontalAlignment','left','Color','r');
text(fclk*5.6/16,-37,SFDR_txt,'HorizontalAlignment','left','Color','r');
%text(fclk*6/16,-55,THD_txt,'HorizontalAlignment','left','Color','r');
text(Fh(2)*fclk,ADout_dB(Harbin(2))-ref_dB+2,'2','VerticalAlignmen','bottom','Color','r');
text(Fh(3)*fclk,ADout_dB(Harbin(3))-ref_dB+2,'3','VerticalAlignmen','bottom','Color','r');
text(Fh(4)*fclk,ADout_dB(Harbin(4))-ref_dB+2,'4','VerticalAlignmen','bottom','Color','r');
text(Fh(5)*fclk,ADout_dB(Harbin(5))-ref_dB+2,'5','VerticalAlignmen','bottom','Color','r');
text(Fh(6)*fclk,ADout_dB(Harbin(6))-ref_dB+2,'6','VerticalAlignmen','bottom','Color','r');
text(Fh(7)*fclk,ADout_dB(Harbin(7))-ref_dB+2,'7','VerticalAlignmen','bottom','Color','r');
text(Fh(8)*fclk,ADout_dB(Harbin(8))-ref_dB+2,'8','VerticalAlignmen','bottom','Color','r');
text(Fh(9)*fclk,ADout_dB(Harbin(9))-ref_dB+2,'9','VerticalAlignmen','bottom','Color','r');
text(Fh(10)*fclk,ADout_dB(Harbin(10))-ref_dB+2,'10','VerticalAlignmen','bottom','Color','r');
hold on;
for i = 0:disturb_len/2
    hold on;
    plot(Fn_disturb(disturb_len - i)*fclk,ADout_dB(Harbin_disturb(disturb_len - i))-ref_dB,'g*');
end
hold off;


VPP_txt = strcat(num2str(Vpp,'%2.3f'),' Vpp');
figure(2)

plot([1:ad_len_N].*1e3/fclk,ADout(1:ad_len_N));
title('Time PLOT'); 
xlabel('TIME (ms)');
ylabel('AMPLITUDE (V)');
hold on
axis([0 TPX -TPY TPY]);
% text(t1,AmpMax,num2str(AmpMax),'VerticalAlignmen','bottom');
% text(t1,AmpMin,num2str(AmpMin),'VerticalAlignmen','top')
text(TPX*0.85,0.9*TPY,VPP_txt,'HorizontalAlignment','left','Color','r')
text(TPX*0.85,0.8*TPY,FRQ_txt,'HorizontalAlignment','left','Color','r')
SNRFS = SNR + abs(maxdB-ref_dB);
ENOB = (SINAD - 1.76)/6.02;
ENOBFS = ENOB+abs(maxdB-ref_dB)/6.02;
% A = [AmpMax,AmpMin];
% AdB = Vin;
HD = [ADout_dB(Harbin(2))-ref_dB,ADout_dB(Harbin(2))-ref_dB,ADout_dB(Harbin(3))-ref_dB,ADout_dB(Harbin(4))-ref_dB,ADout_dB(Harbin(5))-ref_dB,ADout_dB(Harbin(6))-ref_dB,ADout_dB(Harbin(7))-ref_dB,ADout_dB(Harbin(8))-ref_dB,ADout_dB(Harbin(9))-ref_dB,ADout_dB(Harbin(10))-ref_dB]; 
%Spectrum = ADout_dB - ref_dB;