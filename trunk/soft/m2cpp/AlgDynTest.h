#ifndef __AlgDynTest_h
#define __AlgDynTest_h

Mm AlgDynTest(Mm data1, Mm data2, Mm numpt, Mm fclk, Mm numbit, Mm r);
Mm AlgDynTest(Mm data1, Mm data2, Mm numpt, Mm fclk, Mm numbit, Mm r, i_o_t, Mm& SNR__o, Mm& SINAD__o);
Mm AlgDynTest(Mm data1, Mm data2, Mm numpt, Mm fclk, Mm numbit, Mm r, i_o_t, Mm& SNR__o, Mm& SINAD__o, Mm& SFDR__o);
Mm AlgDynTest(Mm data1, Mm data2, Mm numpt, Mm fclk, Mm numbit, Mm r, i_o_t, Mm& SNR__o, Mm& SINAD__o, Mm& SFDR__o, Mm& ENOB__o);
Mm AlgDynTest(Mm data1, Mm data2, Mm numpt, Mm fclk, Mm numbit, Mm r, i_o_t, Mm& SNR__o, Mm& SINAD__o, Mm& SFDR__o, Mm& ENOB__o, Mm& y__o);

#endif // __AlgDynTest_h
