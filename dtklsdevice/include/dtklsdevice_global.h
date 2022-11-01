#ifndef DTKLSDEVICE_GLOBAL_H
#define DTKLSDEVICE_GLOBAL_H
// #include <QString>
// #include <QVector>
// #include <QList>

// #include <QtCore/qglobal.h>

// #if defined(DLSDEVICE_LIBRARY)
// #  define DLSDEVICESHARED_EXPORT Q_DECL_EXPORT
// #else
// #  define DLSDEVICESHARED_EXPORT Q_DECL_IMPORT
// #endif



#define DLSDEVICE_NAMESPACE Dtk::lsDevice
#define DLSDEVICE_USE_NAMESPACE using namespace DLSDEVICE_NAMESPACE;

#define DLSDEVICE_BEGIN_NAMESPACE                                                                                              \
    namespace Dtk {                                                                                                              \
      namespace lsDevice {
#define DLSDEVICE_END_NAMESPACE                                                                                                \
      }                                                                                                                            \
    }                                                                                         \




#endif // DTKLSDEVICE_GLOBAL_H
