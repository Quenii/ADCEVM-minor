#ifndef QPLOTLAB_GLOBAL_HPP
#define QPLOTLAB_GLOBAL_HPP

#include <Qt/qglobal.h>

#ifdef QPLOTLAB_LIB
# define QPLOTLAB_EXPORT Q_DECL_EXPORT
#else
# define QPLOTLAB_EXPORT Q_DECL_IMPORT
#endif

#endif // QPLOTLAB_GLOBAL_HPP
