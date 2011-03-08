#ifndef __AdcDynTest_h
#define __AdcDynTest_h

Mm AdcDynTest(Mm ADout, Mm fclk, Mm numbit, Mm NFFT, Mm V, Mm code);
Mm AdcDynTest(Mm ADout, Mm fclk, Mm numbit, Mm NFFT, Mm V, Mm code, i_o_t, Mm& SNR__o, Mm& SFDR__o);
Mm AdcDynTest(Mm ADout, Mm fclk, Mm numbit, Mm NFFT, Mm V, Mm code, i_o_t, Mm& SNR__o, Mm& SFDR__o, Mm& SNRFS__o);
Mm AdcDynTest(Mm ADout, Mm fclk, Mm numbit, Mm NFFT, Mm V, Mm code, i_o_t, Mm& SNR__o, Mm& SFDR__o, Mm& SNRFS__o, Mm& SINAD__o);
Mm AdcDynTest(Mm ADout, Mm fclk, Mm numbit, Mm NFFT, Mm V, Mm code, i_o_t, Mm& SNR__o, Mm& SFDR__o, Mm& SNRFS__o, Mm& SINAD__o, Mm& THD__o);
Mm AdcDynTest(Mm ADout, Mm fclk, Mm numbit, Mm NFFT, Mm V, Mm code, i_o_t, Mm& SNR__o, Mm& SFDR__o, Mm& SNRFS__o, Mm& SINAD__o, Mm& THD__o, Mm& HD__o);
Mm AdcDynTest(Mm ADout, Mm fclk, Mm numbit, Mm NFFT, Mm V, Mm code, i_o_t, Mm& SNR__o, Mm& SFDR__o, Mm& SNRFS__o, Mm& SINAD__o, Mm& THD__o, Mm& HD__o, Mm& ENOB__o);
Mm AdcDynTest(Mm ADout, Mm fclk, Mm numbit, Mm NFFT, Mm V, Mm code, i_o_t, Mm& SNR__o, Mm& SFDR__o, Mm& SNRFS__o, Mm& SINAD__o, Mm& THD__o, Mm& HD__o, Mm& ENOB__o, Mm& ENOBFS__o);
Mm AdcDynTest(Mm ADout, Mm fclk, Mm numbit, Mm NFFT, Mm V, Mm code, i_o_t, Mm& SNR__o, Mm& SFDR__o, Mm& SNRFS__o, Mm& SINAD__o, Mm& THD__o, Mm& HD__o, Mm& ENOB__o, Mm& ENOBFS__o, Mm& Pn_dB__o);

#endif // __AdcDynTest_h
