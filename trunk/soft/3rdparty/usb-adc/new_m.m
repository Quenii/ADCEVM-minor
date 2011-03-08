clear;
close all;
clc;

filename=input('Type a:\filename:  ');
if isempty(filename)
filename = 'listing'; 
end
fid=fopen(filename,'r');
numpt=input('Data Record Size (Number of Points?, 32k by defalt)   ');
if isempty(numpt)
numpt = 32768; 
end
fclk=input('Sampling Frequency in MHz? (250M)  '); 
if isempty(fclk)
fclk = 250; 
end
numbit=input('Bitwidth of ADC, 16b defalt?  '); 
if isempty(numbit)
numbit = 16; 
end

%Discard first 13 lines from the data file, which do not contain data
for i=1:9,
fgetl(fid); 
end 
[v2,count]=fscanf(fid,'%f,',[1 inf]); 
fclose(fid); 
%for i=1:count
%    v1(i) = v2(i);
%end
%v2 =  sin(2*pi*52e-3*[ 1: 32 * 1024]);
v1=v2'; 
if numpt> count
    numpt = count;
end
code = v1(1:numpt);

f = 1;
fs = 5.1;
t = 5000;
code = sin(2 * pi * f * [0:1/fs:t]);
%code = code / max(code);

code_fft = 20 * log10(abs(fft(code)) / length(code));
code_fft = (abs(fft(code)) / length(code)) .^2;
code_fft = code_fft([1:length(code_fft)/2]) * 2;
figure 
plot(code_fft);