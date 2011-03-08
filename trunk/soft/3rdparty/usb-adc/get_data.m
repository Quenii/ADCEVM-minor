 function [s] = get_data()
filename='13@80-6.csv';
if isempty(filename)
filename = 'listing'; 
end
fid=fopen(filename,'r');

numpt = 32768; 
fclk = 250; 
numbit = 16; 
%Discard first 13 lines from the data file, which do not contain data
for i=1:9,
fgetl(fid); 
end 
[v2,count]=fscanf(fid,'%f,',[1 inf]); 
fclose(fid); 

v1=v2'; 
if numpt> count
    numpt = count;
end

code = v1(1:numpt);

%code = code .* blackman(length(code));

code = code / max(code);
s = code;
