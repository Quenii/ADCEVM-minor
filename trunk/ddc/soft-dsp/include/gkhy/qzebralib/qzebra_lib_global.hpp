#ifndef QZEBRA_LIB_GLOBAL_H
#define QZEBRA_LIB_GLOBAL_H

#include <Qt/qglobal.h>

#ifdef QZEBRA_LIB_LIB
# define QZEBRA_LIB_EXPORT Q_DECL_EXPORT
#else
# define QZEBRA_LIB_EXPORT Q_DECL_IMPORT
#endif

#endif // QZEBRA-LIB_GLOBAL_H
