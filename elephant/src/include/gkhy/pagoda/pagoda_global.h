#ifndef PAGODA_GLOBAL_H
#define PAGODA_GLOBAL_H

#include <QtGlobal>

#ifdef PAGODA_LIB
# define PAGODA_EXPORT Q_DECL_EXPORT
#else
# define PAGODA_EXPORT Q_DECL_IMPORT
#endif

#endif // PAGODA_GLOBAL_H
