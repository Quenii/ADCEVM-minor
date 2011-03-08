function ret = myfft(x, n)
    x = x .* hamming(n);
    d = 20*log10(abs(fft(x, n)));
    ret = d - max(d(3 : n / 2));    