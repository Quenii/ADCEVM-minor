function ret = myfft_complex(r, i, n)    
%    r = r .* hamming(n);
%    i = i .* hamming(n);
    x = r + j * i;
    w = x.*hanning(n)';
    d = 20*log10(abs(fft(w, n)));
    ret = d - max(d(3 : n / 2));    