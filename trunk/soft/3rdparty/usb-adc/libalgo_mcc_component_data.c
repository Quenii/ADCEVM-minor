//
// MATLAB Compiler: 4.8 (R2008a)
// Date: Sat Jun 19 22:45:32 2010
// Arguments: "-B" "macro_default" "-W" "cpplib:libalgo" "-T" "link:lib"
// "myfft" "calc_dynam_params" 
//

#include "mclmcrrt.h"

#ifdef __cplusplus
extern "C" {
#endif
extern const unsigned char __MCC_libalgo_session_key[] = {
    '0', '8', '1', 'E', 'D', 'A', '9', '3', '8', '4', 'B', 'D', '6', '5', '1',
    'B', '7', 'F', 'E', '9', 'A', '6', '0', 'D', '4', 'F', 'D', '1', 'E', '1',
    '4', '2', '8', 'C', '3', '4', '1', '3', '0', '3', '6', '9', 'D', '6', '7',
    '4', '9', '0', 'F', '9', 'D', '6', '7', 'F', '8', 'E', '6', '0', '4', 'B',
    'B', '8', '8', '4', '1', '7', '1', 'D', 'D', 'F', '1', 'A', 'D', '1', 'D',
    'C', 'F', '4', '5', '8', 'B', 'B', 'C', '2', 'E', 'B', '6', '9', '4', 'E',
    '2', '4', '4', '9', 'E', '1', '0', 'A', '4', '9', '2', 'F', '1', '5', '3',
    '3', 'B', 'A', '6', 'A', '8', 'A', '0', '3', 'E', '6', '1', '2', '5', 'B',
    '9', 'E', 'E', 'A', '7', '3', 'F', 'C', '6', 'C', '1', 'B', 'D', '7', '7',
    '6', '7', 'A', '0', '5', '1', '1', 'E', '5', 'F', 'B', '1', '4', 'B', 'F',
    'C', '3', '4', 'E', '8', '4', '3', 'C', '3', 'A', 'C', '3', 'E', 'F', '1',
    'A', '4', 'D', 'D', '0', '5', '9', '3', '5', '0', '6', '3', 'C', 'E', 'A',
    'C', 'D', '8', '5', '3', '0', '2', 'D', 'C', 'E', '7', '0', '8', 'C', '2',
    '3', '4', '5', 'E', 'D', '9', 'C', '1', '4', '6', '6', '5', '6', '1', '6',
    'D', '0', '6', '9', '5', '4', 'B', '6', '6', '7', 'B', 'A', '9', 'B', '0',
    '3', 'E', '7', '7', 'E', '2', '9', '7', 'F', 'B', 'A', 'C', 'C', '9', '0',
    '9', 'B', '7', '4', 'C', '7', '2', '7', '3', 'D', '9', 'E', '8', '6', '4',
    'C', '\0'};

extern const unsigned char __MCC_libalgo_public_key[] = {
    '3', '0', '8', '1', '9', 'D', '3', '0', '0', 'D', '0', '6', '0', '9', '2',
    'A', '8', '6', '4', '8', '8', '6', 'F', '7', '0', 'D', '0', '1', '0', '1',
    '0', '1', '0', '5', '0', '0', '0', '3', '8', '1', '8', 'B', '0', '0', '3',
    '0', '8', '1', '8', '7', '0', '2', '8', '1', '8', '1', '0', '0', 'C', '4',
    '9', 'C', 'A', 'C', '3', '4', 'E', 'D', '1', '3', 'A', '5', '2', '0', '6',
    '5', '8', 'F', '6', 'F', '8', 'E', '0', '1', '3', '8', 'C', '4', '3', '1',
    '5', 'B', '4', '3', '1', '5', '2', '7', '7', 'E', 'D', '3', 'F', '7', 'D',
    'A', 'E', '5', '3', '0', '9', '9', 'D', 'B', '0', '8', 'E', 'E', '5', '8',
    '9', 'F', '8', '0', '4', 'D', '4', 'B', '9', '8', '1', '3', '2', '6', 'A',
    '5', '2', 'C', 'C', 'E', '4', '3', '8', '2', 'E', '9', 'F', '2', 'B', '4',
    'D', '0', '8', '5', 'E', 'B', '9', '5', '0', 'C', '7', 'A', 'B', '1', '2',
    'E', 'D', 'E', '2', 'D', '4', '1', '2', '9', '7', '8', '2', '0', 'E', '6',
    '3', '7', '7', 'A', '5', 'F', 'E', 'B', '5', '6', '8', '9', 'D', '4', 'E',
    '6', '0', '3', '2', 'F', '6', '0', 'C', '4', '3', '0', '7', '4', 'A', '0',
    '4', 'C', '2', '6', 'A', 'B', '7', '2', 'F', '5', '4', 'B', '5', '1', 'B',
    'B', '4', '6', '0', '5', '7', '8', '7', '8', '5', 'B', '1', '9', '9', '0',
    '1', '4', '3', '1', '4', 'A', '6', '5', 'F', '0', '9', '0', 'B', '6', '1',
    'F', 'C', '2', '0', '1', '6', '9', '4', '5', '3', 'B', '5', '8', 'F', 'C',
    '8', 'B', 'A', '4', '3', 'E', '6', '7', '7', '6', 'E', 'B', '7', 'E', 'C',
    'D', '3', '1', '7', '8', 'B', '5', '6', 'A', 'B', '0', 'F', 'A', '0', '6',
    'D', 'D', '6', '4', '9', '6', '7', 'C', 'B', '1', '4', '9', 'E', '5', '0',
    '2', '0', '1', '1', '1', '\0'};

static const char * MCC_libalgo_matlabpath_data[] = 
  { "libalgo/", "toolbox/compiler/deploy/", "$TOOLBOXMATLABDIR/general/",
    "$TOOLBOXMATLABDIR/ops/", "$TOOLBOXMATLABDIR/lang/",
    "$TOOLBOXMATLABDIR/elmat/", "$TOOLBOXMATLABDIR/elfun/",
    "$TOOLBOXMATLABDIR/specfun/", "$TOOLBOXMATLABDIR/matfun/",
    "$TOOLBOXMATLABDIR/datafun/", "$TOOLBOXMATLABDIR/polyfun/",
    "$TOOLBOXMATLABDIR/funfun/", "$TOOLBOXMATLABDIR/sparfun/",
    "$TOOLBOXMATLABDIR/scribe/", "$TOOLBOXMATLABDIR/graph2d/",
    "$TOOLBOXMATLABDIR/graph3d/", "$TOOLBOXMATLABDIR/specgraph/",
    "$TOOLBOXMATLABDIR/graphics/", "$TOOLBOXMATLABDIR/uitools/",
    "$TOOLBOXMATLABDIR/strfun/", "$TOOLBOXMATLABDIR/imagesci/",
    "$TOOLBOXMATLABDIR/iofun/", "$TOOLBOXMATLABDIR/audiovideo/",
    "$TOOLBOXMATLABDIR/timefun/", "$TOOLBOXMATLABDIR/datatypes/",
    "$TOOLBOXMATLABDIR/verctrl/", "$TOOLBOXMATLABDIR/codetools/",
    "$TOOLBOXMATLABDIR/helptools/", "$TOOLBOXMATLABDIR/winfun/",
    "$TOOLBOXMATLABDIR/demos/", "$TOOLBOXMATLABDIR/timeseries/",
    "$TOOLBOXMATLABDIR/hds/", "$TOOLBOXMATLABDIR/guide/",
    "$TOOLBOXMATLABDIR/plottools/", "toolbox/local/",
    "toolbox/shared/dastudio/", "$TOOLBOXMATLABDIR/datamanager/",
    "toolbox/compiler/", "toolbox/signal/signal/", "toolbox/shared/spcuilib/" };

static const char * MCC_libalgo_classpath_data[] = 
  { "" };

static const char * MCC_libalgo_libpath_data[] = 
  { "" };

static const char * MCC_libalgo_app_opts_data[] = 
  { "" };

static const char * MCC_libalgo_run_opts_data[] = 
  { "" };

static const char * MCC_libalgo_warning_state_data[] = 
  { "off:MATLAB:dispatcher:nameConflict" };


mclComponentData __MCC_libalgo_component_data = { 

  /* Public key data */
  __MCC_libalgo_public_key,

  /* Component name */
  "libalgo",

  /* Component Root */
  "",

  /* Application key data */
  __MCC_libalgo_session_key,

  /* Component's MATLAB Path */
  MCC_libalgo_matlabpath_data,

  /* Number of directories in the MATLAB Path */
  40,

  /* Component's Java class path */
  MCC_libalgo_classpath_data,
  /* Number of directories in the Java class path */
  0,

  /* Component's load library path (for extra shared libraries) */
  MCC_libalgo_libpath_data,
  /* Number of directories in the load library path */
  0,

  /* MCR instance-specific runtime options */
  MCC_libalgo_app_opts_data,
  /* Number of MCR instance-specific runtime options */
  0,

  /* MCR global runtime options */
  MCC_libalgo_run_opts_data,
  /* Number of MCR global runtime options */
  0,
  
  /* Component preferences directory */
  "libalgo_CFC32A60AB40F4EFB79FB8B4E033F1EC",

  /* MCR warning status data */
  MCC_libalgo_warning_state_data,
  /* Number of MCR warning status modifiers */
  1,

  /* Path to component - evaluated at runtime */
  NULL

};

#ifdef __cplusplus
}
#endif


