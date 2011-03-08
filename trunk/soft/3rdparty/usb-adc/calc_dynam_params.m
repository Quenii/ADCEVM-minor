function [A, AdB,SINAD,SNR,THD,SFDR,ENOB,HD, Spectrum] = calc_dynam_params(samples, numbit)

v1 = samples';
numpt = length(v1);
%numpt = floor(numpt/2)*2;

code = double(v1(1:numpt));
% code = code/max(code);
% code = sin(2*pi*13e6*[4e-9 1: 32 8 1024])
% code = sin(2*pi*52e-3*[ 1: 32 * 1024]);
%code=v1(:,1); 

%Display a warning, when the input generates a code greater than full-scale
% if (max(code)==2^numbit-1) | (min(code)==0)
% disp('Warning: ADC may be clipping!!!'); 
% end 

%Recenter the digital sine wave 
%Dout=code-(2^numbit-1)/2; 
Dout = code/max(code);

%If no window function is used, the input tone must be chosen to be unique and with 
%regard to the sampling frequency. To achieve this prime numbers are introduced and the
%input tone is determined by fIN = fSAMPLE * (Prime Number / Data Record Size). 
%To relax this requirement, window functions such as HANNING and HAMING
%(see below) can
%be introduced, however the fundamental in the resulting FFT spectrum appears 'sharper'
%without the use of window functions. 
%Doutw=Dout;
%Doutw=Dout.*hanning(numpt);
%Doutw=Dout.*hamming(numpt); 
Doutw=Dout.*blackman(numpt); 

%Performing the Fast Fourier Transform 
Dout_spect=fft(Doutw)/numpt; 

%Recalculate to dB 
Dout_dB=20*log10(abs(Dout_spect)); 
maxdB=max(Dout_dB(1:numpt/2)); 
Spectrum = Dout_dB - maxdB;
%Calculate SNR, SINAD, THD and SFDR values
%Find the signal bin number, DC = bin 1
fin=find(Dout_dB(1:numpt/2)==maxdB); 
%Span of the input frequency on each side 
span=max(round(numpt/200),5); 

if fin > span
%Approximate search span for harmonics on each side 
spanh=2;
%Determine power spectrum
spectP=(abs(Dout_spect)).*(abs(Dout_spect)); 
%Find DC offset power 
Pdc=sum(spectP(1:span)); 
%Extract overall signal power 
Ps=sum(spectP(fin-span:fin+span));
%Vector/matrix to store both frequency and power of signal and harmonics
Fh=[]; 
%The 1st element in the vector/matrix represents the signal, the next element represents
%the 2nd harmonic, etc.
Ph=[]; 

%Find harmonic frequencies and power components in the FFT spectrum 
for har_num=1:10
%Input tones greater than fSAMPLE are aliased back into the spectrum
tone=rem((har_num*(fin-1)+1)/numpt,1); 
if tone>0.5 
%Input tones greater than 0.5*fSAMPLE (after aliasing) are reflected
tone=1-tone;
end 
Fh=[Fh tone]; 
%For this procedure to work, ensure the folded back high order harmonics do not overlap 
%with DC or signal or lower order harmonics 
har_peak=max(spectP(round(tone*numpt)-spanh:round(tone*numpt)+spanh)); 
har_bin=find(spectP(round(tone*numpt)-spanh:round(tone*numpt)+spanh)==har_peak);
har_bin=har_bin+round(tone*numpt)-spanh-1;
Ph=[Ph sum(spectP(har_bin-1:har_bin+1))]; 
end 

%Determine the total distortion power 
Pd=sum(Ph(2:5)); 
%Determine the noise power 
Pn=sum(spectP(1:numpt/2))-Pdc-Ps-Pd;

format;
A=(max(code)-min(code)); 
AdB=20*log10(A/sqrt(2));
SINAD=10*log10(Ps/(Pn+Pd));
SNR=10*log10(Ps/Pn) ;
THD=10*log10(Pd/Ph(1));
SFDR=10*log10(Ph(1)/max(Ph(2:10))); 
ENOB=(SINAD-1.763)/6.02;
HD=10*log10(Ph(1:10)/Ph(1)); 
else
    A=(max(code)-min(code)); 
    AdB=20*log10(A/sqrt(2));
    SINAD=-1;
    SNR=-1;
    THD=-1;
    SFDR=-1; 
    ENOB=-1;
    HD=-1; 
end




