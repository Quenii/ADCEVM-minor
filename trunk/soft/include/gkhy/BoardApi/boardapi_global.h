#ifndef BOARDAPI_GLOBAL_H
#define BOARDAPI_GLOBAL_H

#include <Qt/qglobal.h>

#ifdef BOARDAPI_LIB
# define BOARDAPI_EXPORT Q_DECL_EXPORT
#else
# define BOARDAPI_EXPORT Q_DECL_IMPORT
#endif

#endif // BOARDAPI_GLOBAL_H
