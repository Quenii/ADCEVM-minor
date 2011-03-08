function [ret] = myfft(x)
    f = abs(fft(x));
    f = f(1 : length(f) / 2);
    f = f / max(f);
    f = log10(f);
    ret = f;