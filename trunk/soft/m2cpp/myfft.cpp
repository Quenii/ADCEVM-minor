  #include "matlib.h"
  #pragma hdrstop
  
  #include "myfft.h"
  #include "hamming.h"
  #include "gencoswin.h"
  #include "check_order.h"
  
  
  
  Mm myfft(Mm x, Mm n) {
    begin_scope
    x.setname("x"); n.setname("n"); 
    dMm(ret); dMm(d); 
    
    call_stack_begin;
    // nargin, nargout entry code
    double old_nargin=nargin_val; if (!nargin_set) nargin_val=2.0;
    nargin_set=0;
    double old_nargout=nargout_val; if (!nargout_set) nargout_val=1.0;
    nargout_set=0;
    
    // translated code
    
    x = times(x,hamming((CL(n))));
    d = 20.0*log10(abs(fft(x,n)));
    ret = d-max(d(colon(3.0,1.0,n/2.0)));
    
    call_stack_end;
    
    // nargin, nargout exit code
    nargin_val=old_nargin; nargout_val=old_nargout;
    
    // function exit code
    x.setname(NULL); n.setname(NULL); 
    return ret;
    end_scope
  }
  
  
