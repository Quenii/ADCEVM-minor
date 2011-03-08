  #include "matlib.h"
  #pragma hdrstop
  
  #include "check_order.h"
  
  
  Mm check_order(Mm n_in, i_o_t, Mm& n_out__o, Mm& w__o, Mm& trivalwin__o) {
    begin_scope
    n_in.setname("n_in"); 
    dMm(n_out); dMm(w); dMm(trivalwin); 
    
    call_stack_begin;
    // nargin, nargout entry code
    double old_nargin=nargin_val; if (!nargin_set) nargin_val=1.0;
    nargin_set=0;
    double old_nargout=nargout_val; if (!nargout_set) nargout_val=3.0;
    nargout_set=0;
    
    // translated code
    
    //CHECK_ORDER Checks the order passed to the window functions.
    // [N,W,TRIVALWIN] = CHECK_ORDER(N_ESTIMATE) will round N_ESTIMATE to the
    // nearest integer if it is not alreay an integer. In special cases (N is [],
    // 0, or 1), TRIVALWIN will be set to flag that W has been modified.
    
    //   Copyright 1988-2002 The MathWorks, Inc.
    //   $Revision: 1.6 $  $Date: 2002/04/15 01:07:36 $
    
    w = nop_M;
    trivalwin = 0.0;
    
    // Special case of negative orders:
    if (istrue(n_in<0.0)) {
      error(TM("Order cannot be less than zero."));
    }
    
    // Check if order is already an integer or empty
    // If not, round to nearest integer.
    if (istrue(isempty(n_in))||istrue(n_in==floor(n_in))) {
      n_out = n_in;
    } else {
      
      n_out = round(n_in);
      warning(TM("Rounding order to nearest integer."));
    }
    
    // Special cases:
    if (istrue(isempty(n_out))||istrue(n_out==0.0)) {
      w = zeros(0.0,1.0);
      // Empty matrix: 0-by-1
      trivalwin = 1.0;
      
    } else
    if (istrue(n_out==1.0)) {
      w = 1.0;
      trivalwin = 1.0;
      
    }
    
    call_stack_end;
    
    // nargin, nargout exit code
    nargin_val=old_nargin; nargout_val=old_nargout;
    
    // function exit code
    n_in.setname(NULL); 
    n_out__o=n_out; w__o=w; trivalwin__o=trivalwin; 
    return x_M;
    end_scope
  }
  
  
  Mm check_order(Mm n_in) {
    begin_scope
    double old_nargin=nargin_val; nargin_val=1.0; nargin_set=1;
    double old_nargout=nargout_val; nargout_val=1.0; nargout_set=1;
    dMm(n_out__o); dMm(w__o); dMm(trivalwin__o); 
    check_order(n_in, i_o, n_out__o, w__o, trivalwin__o);
    nargout_val=old_nargout;
    nargin_val=old_nargin;
    return(n_out__o);
    end_scope
  }
  
  Mm check_order(Mm n_in, i_o_t, Mm& n_out__o, Mm& w__o) {
    begin_scope
    double old_nargin=nargin_val; nargin_val=1.0; nargin_set=1;
    double old_nargout=nargout_val; nargout_val=2.0; nargout_set=1;
    dMm(trivalwin__o); 
    check_order(n_in, i_o, n_out__o, w__o, trivalwin__o);
    nargout_val=old_nargout;
    nargin_val=old_nargin;
    return x_M;
    end_scope
  }
  
