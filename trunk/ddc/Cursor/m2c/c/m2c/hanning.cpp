  #include "matlib.h"
  #pragma hdrstop
  
  #include "hanning.h"
  #include "sym_hanning.h"
  #include "check_order.h"
  
  
  
  Mm hanning(Mm varargin) {
    begin_scope
    varargin.setname("varargin"); 
    dMm(w); dMm(n); dMm(trivialwin); dMm(sflag); dMm(allsflags); dMm(sflagindex); 
    
    call_stack_begin;
    // nargin, nargout entry code
    double old_nargin=nargin_val; if (!nargin_set) nargin_val=0+varargin.size();
    nargin_set=0;
    double old_nargout=nargout_val; if (!nargout_set) nargout_val=1.0;
    nargout_set=0;
    
    // translated code
    
    //HANNING   Hanning window.
    //   HANNING(N) returns the N-point symmetric Hanning window in a column
    //   vector.  Note that the first and last zero-weighted window samples
    //   are not included.
    //
    //   HANNING(N,'symmetric') returns the same result as HANNING(N).
    //
    //   HANNING(N,'periodic') returns the N-point periodic Hanning window,
    //   and includes the first zero-weighted window sample.
    //
    //   NOTE: Use the HANN function to get a Hanning window which has the 
    //          first and last zero-weighted samples. 
    //
    //   See also BARTLETT, BLACKMAN, BOXCAR, CHEBWIN, HAMMING, HANN, KAISER
    //   and TRIANG.
    
    //   Copyright 1988-2002 The MathWorks, Inc.
    //   $Revision: 1.11 $  $Date: 2002/03/28 17:28:19 $
    
    // Check number of inputs
    error(nargchk(1.0,2.0,nargin()));
    
    // Check for trivial order
    /*[n,w,trivialwin] = */check_order(varargin.br(1.0),i_o,n,w,trivialwin);
    if (istrue(trivialwin)) {
      goto return_from_hanning;
    }
    
    // Select the sampling option
    if (istrue(nargin()==1.0)) {
      sflag = TM("symmetric");
    } else {
      
      sflag = lower(varargin.br(2.0));
    }
    
    // Allow partial strings for sampling options
    allsflags = (CL(TM("symmetric")),TM("periodic"));
    sflagindex = strmatch(sflag,allsflags);
    if (istrue(length(sflagindex)!=1.0)) {
      // catch 0 or 2 matches
      error(TM("Sampling flag must be either 'symmetric' or 'periodic'."));
    }
    sflag = allsflags.br(sflagindex);
    
    // Evaluate the window
    mswitch (sflag) {
      beginmswitch {
        break;
      }
      mcase (TM("periodic")) {
        // Includes the first zero sample
        w = (BR(0.0),semi,
        sym_hanning(n-1.0));
        break;
      }
      mcase (TM("symmetric")) {
        // Does not include the first and last zero sample
        w = sym_hanning(n);
      }
    } endmswitch;
    
    //---------------------------------------------------------------------
    
    return_from_hanning: call_stack_end;
    
    // nargin, nargout exit code
    nargin_val=old_nargin; nargout_val=old_nargout;
    
    // function exit code
    varargin.setname(NULL); 
    return w;
    end_scope
  }
  
  
  Mm hanning() {
    begin_scope
    double old_nargin=nargin_val; nargin_val=0.0; nargin_set=1;
    dMm(varargin); varargin=cell(0); 
    dMm(ret1a);
    ret1a=hanning(varargin);
    nargin_val=old_nargin;
    return ret1a;
    end_scope
  }
  
  #include "hanning.h"
  #include "calc_hanning.h"
  
  
  
  static Mm sym_hanning(Mm n) {
    begin_scope
    n.setname("n"); 
    dMm(w); dMm(half); 
    
    call_stack_begin;
    // nargin, nargout entry code
    double old_nargin=nargin_val; if (!nargin_set) nargin_val=1.0;
    nargin_set=0;
    double old_nargout=nargout_val; if (!nargout_set) nargout_val=1.0;
    nargout_set=0;
    
    // translated code
    
    //SYM_HANNING   Symmetric Hanning window. 
    //   SYM_HANNING Returns an exactly symmetric N point window by evaluating
    //   the first half and then flipping the same samples over the other half.
    
    if (istrue(!rem(n,2.0))) {
      // Even length window
      half = n/2.0;
      w = calc_hanning(half,n);
      w = (BR(w),semi,
      w(colon(w.size(),-1.0,1.0)));
    } else {
      
      // Odd length window
      half = (n+1.0)/2.0;
      w = calc_hanning(half,n);
      w = (BR(w),semi,
      w(colon(w.size()-1.0,-1.0,1.0)));
    }
    
    //---------------------------------------------------------------------
    
    call_stack_end;
    
    // nargin, nargout exit code
    nargin_val=old_nargin; nargout_val=old_nargout;
    
    // function exit code
    n.setname(NULL); 
    return w;
    end_scope
  }
  
  
  #include "hanning.h"
  
  
  static Mm calc_hanning(Mm m, Mm n) {
    begin_scope
    m.setname("m"); n.setname("n"); 
    dMm(w); 
    
    call_stack_begin;
    // nargin, nargout entry code
    double old_nargin=nargin_val; if (!nargin_set) nargin_val=2.0;
    nargin_set=0;
    double old_nargout=nargout_val; if (!nargout_set) nargout_val=1.0;
    nargout_set=0;
    
    // translated code
    
    //CALC_HANNING   Calculates Hanning window samples.
    //   CALC_HANNING Calculates and returns the first M points of an N point
    //   Hanning window.
    
    w = 0.5*(1.0-cos(2.0*pi*ctranspose((colon(1.0,1.0,m)))/(n+1.0)));
    
    
    // [EOF] hanning.m
    
    call_stack_end;
    
    // nargin, nargout exit code
    nargin_val=old_nargin; nargout_val=old_nargout;
    
    // function exit code
    m.setname(NULL); n.setname(NULL); 
    return w;
    end_scope
  }
  
  
