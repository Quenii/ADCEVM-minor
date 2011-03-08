  #include "matlib.h"
  #pragma hdrstop
  
  #include "gencoswin.h"
  #include "sym_window.h"
  #include "check_order.h"
  
  
  
  Mm gencoswin(Mm varargin, i_o_t, Mm& w__o, Mm& msg__o) {
    begin_scope
    varargin.setname("varargin"); 
    dMm(w); dMm(msg); dMm(window); dMm(n); dMm(trivialwin); dMm(sflag); dMm(allsflags); dMm(sflagindex); 
    
    call_stack_begin;
    // nargin, nargout entry code
    double old_nargin=nargin_val; if (!nargin_set) nargin_val=0+varargin.size();
    nargin_set=0;
    double old_nargout=nargout_val; if (!nargout_set) nargout_val=2.0;
    nargout_set=0;
    
    // translated code
    
    //GENCOSWIN   Returns one of the generalized cosine windows.
    //   GENCOSWIN returns the generalized cosine window specified by the 
    //   first string argument. Its inputs can be
    //     Window name    - a string, any of 'hamming', 'hann', 'blackman'.
    //     N              - length of the window desired.
    //     Sampling flag  - optional string, one of 'symmetric', 'periodic'. 
    
    //   Copyright 1988-2002 The MathWorks, Inc.
    //   $Revision: 1.7 $  $Date: 2002/04/15 01:09:14 $ 
    
    // Parse the inputs
    window = varargin.br(1.0);
    n = varargin.br(2.0);
    msg = TM("");
    
    // Check for trivial orders
    /*[n,w,trivialwin] = */check_order(n,i_o,n,w,trivialwin);
    if (istrue(trivialwin)) {
      goto return_from_gencoswin;
    }
    
    // Select the sampling option
    if (istrue(nargin()==2.0)) {
      // no sampling flag specified, use default. 
      sflag = TM("symmetric");
    } else {
      
      sflag = lower(varargin.br(3.0));
    }
    
    // Allow partial strings for sampling options
    allsflags = (CL(TM("symmetric")),TM("periodic"));
    sflagindex = strmatch(sflag,allsflags);
    if (istrue(length(sflagindex)!=1.0)) {
      // catch 0 or 2 matches
      msg = TM("Sampling flag must be either 'symmetric' or 'periodic'.");
      goto return_from_gencoswin;
    } else {
      
      sflag = allsflags.br(sflagindex);
    }
    
    // Evaluate the window
    mswitch (sflag) {
      beginmswitch {
        break;
      }
      mcase (TM("periodic")) {
        w = sym_window(n+1.0,window);
        w(w.size()) = nop_M;
        break;
      }
      mcase (TM("symmetric")) {
        w = sym_window(n,window);
      }
    } endmswitch;
    
    //---------------------------------------------------------------------
    
    return_from_gencoswin: call_stack_end;
    
    // nargin, nargout exit code
    nargin_val=old_nargin; nargout_val=old_nargout;
    
    // function exit code
    varargin.setname(NULL); 
    w__o=w; msg__o=msg; 
    return x_M;
    end_scope
  }
  
  
  Mm gencoswin() {
    begin_scope
    double old_nargin=nargin_val; nargin_val=0.0; nargin_set=1;
    double old_nargout=nargout_val; nargout_val=1.0; nargout_set=1;
    dMm(varargin); varargin=cell(0); dMm(w__o); dMm(msg__o); 
    gencoswin(varargin, i_o, w__o, msg__o);
    nargout_val=old_nargout;
    nargin_val=old_nargin;
    return(w__o);
    end_scope
  }
  
  Mm gencoswin(Mm varargin) {
    begin_scope
    double old_nargin=nargin_val; nargin_val=1.0+varargin.size()-1; nargin_set=1;
    double old_nargout=nargout_val; nargout_val=1.0; nargout_set=1;
    dMm(w__o); dMm(msg__o); 
    gencoswin(varargin, i_o, w__o, msg__o);
    nargout_val=old_nargout;
    nargin_val=old_nargin;
    return(w__o);
    end_scope
  }
  
  Mm gencoswin(i_o_t, Mm& w__o, Mm& msg__o) {
    begin_scope
    double old_nargin=nargin_val; nargin_val=0.0; nargin_set=1;
    double old_nargout=nargout_val; nargout_val=2.0; nargout_set=1;
    dMm(varargin); varargin=cell(0); 
    gencoswin(varargin, i_o, w__o, msg__o);
    nargout_val=old_nargout;
    nargin_val=old_nargin;
    return x_M;
    end_scope
  }
  
  #include "gencoswin.h"
  #include "calc_window.h"
  
  
  
  static Mm sym_window(Mm n, Mm window) {
    begin_scope
    n.setname("n"); window.setname("window"); 
    dMm(w); dMm(half); 
    
    call_stack_begin;
    // nargin, nargout entry code
    double old_nargin=nargin_val; if (!nargin_set) nargin_val=2.0;
    nargin_set=0;
    double old_nargout=nargout_val; if (!nargout_set) nargout_val=1.0;
    nargout_set=0;
    
    // translated code
    
    //SYM_WINDOW   Symmetric generalized cosine window.
    //   SYM_WINDOW Returns an exactly symmetric N point generalized cosine 
    //   window by evaluating the first half and then flipping the same samples
    //   over the other half.
    
    if (istrue(!rem(n,2.0))) {
      // Even length window
      half = n/2.0;
      w = calc_window(half,n,window);
      w = (BR(w),semi,
      w(colon(w.size(),-1.0,1.0)));
    } else {
      
      // Odd length window
      half = (n+1.0)/2.0;
      w = calc_window(half,n,window);
      w = (BR(w),semi,
      w(colon(w.size()-1.0,-1.0,1.0)));
    }
    
    //---------------------------------------------------------------------
    
    call_stack_end;
    
    // nargin, nargout exit code
    nargin_val=old_nargin; nargout_val=old_nargout;
    
    // function exit code
    n.setname(NULL); window.setname(NULL); 
    return w;
    end_scope
  }
  
  
  #include "gencoswin.h"
  
  
  static Mm calc_window(Mm m, Mm n, Mm window) {
    begin_scope
    m.setname("m"); n.setname("n"); window.setname("window"); 
    dMm(w); dMm(a0); dMm(a1); dMm(a2); dMm(a3); dMm(a4); dMm(x); 
    
    call_stack_begin;
    // nargin, nargout entry code
    double old_nargin=nargin_val; if (!nargin_set) nargin_val=3.0;
    nargin_set=0;
    double old_nargout=nargout_val; if (!nargout_set) nargout_val=1.0;
    nargout_set=0;
    
    // translated code
    
    //CALC_WINDOW   Calculate the generalized cosine window samples.
    //   CALC_WINDOW Calculates and returns the first M points of an N point
    //   generalized cosine window determined by the 'window' string.
    
    // For the hamming and blackman windows we force rounding in order to achieve
    // better numerical properties.  For example, the end points of the hamming 
    // window should be exactly 0.08.
    
    mswitch (window) {
      beginmswitch {
        break;
      }
      mcase (TM("hann")) {
        // Hann window
        //    w = 0.5 * (1 - cos(2*pi*(0:m-1)'/(n-1))); 
        a0 = 0.5;
        a1 = 0.5;
        a2 = 0.0;
        a3 = 0.0;
        a4 = 0.0;
        break;
      }
      mcase (TM("hamming")) {
        // Hamming window
        //    w = (54 - 46*cos(2*pi*(0:m-1)'/(n-1)))/100;
        a0 = 0.54;
        a1 = 0.46;
        a2 = 0.0;
        a3 = 0.0;
        a4 = 0.0;
        break;
      }
      mcase (TM("blackman")) {
        // Blackman window
        //    w = (42 - 50*cos(2*pi*(0:m-1)/(n-1)) + 8*cos(4*pi*(0:m-1)/(n-1)))'/100;
        a0 = 0.42;
        a1 = 0.5;
        a2 = 0.08;
        a3 = 0.0;
        a4 = 0.0;
        break;
      }
      mcase (TM("flattopwin")) {
        // Flattop window
        // Original coefficients as defined in the reference (see flattopwin.m);
        // a0 = 1;
        // a1 = 1.93;
        // a2 = 1.29;
        // a3 = 0.388;
        // a4 = 0.032;
        //
        // Scaled by (a0+a1+a2+a3+a4)
        a0 = 0.2156;
        a1 = 0.416;
        a2 = 0.2781;
        a3 = 0.08359999999999999;
        a4 = 0.0069;
      }
    } endmswitch;
    
    x = ctranspose((colon(0.0,1.0,m-1.0)))/(n-1.0);
    w = a0-a1*cos(2.0*pi*x)+a2*cos(4.0*pi*x)-a3*cos(6.0*pi*x)+a4*cos(8.0*pi*x);
    
    // [EOF] gencoswin.m
    
    call_stack_end;
    
    // nargin, nargout exit code
    nargin_val=old_nargin; nargout_val=old_nargout;
    
    // function exit code
    m.setname(NULL); n.setname(NULL); window.setname(NULL); 
    return w;
    end_scope
  }
  
  
