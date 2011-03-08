  #include "matlib.h"
  #pragma hdrstop
  
  #include "hamming.h"
  #include "gencoswin.h"
  #include "check_order.h"
  
  
  
  Mm hamming(Mm varargin) {
    begin_scope
    varargin.setname("varargin"); 
    dMm(w); dMm(msg); 
    
    call_stack_begin;
    // nargin, nargout entry code
    double old_nargin=nargin_val; if (!nargin_set) nargin_val=0+varargin.size();
    nargin_set=0;
    double old_nargout=nargout_val; if (!nargout_set) nargout_val=1.0;
    nargout_set=0;
    
    // translated code
    
    //HAMMING   Hamming window.
    //   HAMMING(N) returns the N-point symmetric Hamming window in a column vector.
    // 
    //   HAMMING(N,SFLAG) generates the N-point Hamming window using SFLAG window
    //   sampling. SFLAG may be either 'symmetric' or 'periodic'. By default, a 
    //   symmetric window is returned. 
    //
    //   See also BLACKMAN, HANN, WINDOW.
    
    //   Copyright 1988-2002 The MathWorks, Inc.
    //   $Revision: 1.14 $  $Date: 2002/11/21 15:46:43 $
    
    // Check number of inputs
    error(nargchk(1.0,2.0,nargin()));
    
    /*[w,msg] = */gencoswin((CL(TM("hamming")),varargin),i_o,w,msg);
    error(msg);
    
    
    // [EOF] hamming.m
    
    call_stack_end;
    
    // nargin, nargout exit code
    nargin_val=old_nargin; nargout_val=old_nargout;
    
    // function exit code
    varargin.setname(NULL); 
    return w;
    end_scope
  }
  
  
  Mm hamming() {
    begin_scope
    double old_nargin=nargin_val; nargin_val=0.0; nargin_set=1;
    dMm(varargin); varargin=cell(0); 
    dMm(ret1a);
    ret1a=hamming(varargin);
    nargin_val=old_nargin;
    return ret1a;
    end_scope
  }
  
