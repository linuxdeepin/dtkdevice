#ifndef DLSDEVICE_H
#define DLSDEVICE_H

#include "dtklsdevice_global.h"
#include "dlsdevicetypes.h"
#include "../3rdparty/hw.h"


#include <qobject.h>
//#include <qscopedpointer.h>



DLSDEVICE_BEGIN_NAMESPACE
class DlsDevicePrivate;
class DlsDevice : public QObject 
{

public:
     DlsDevice();
      ~DlsDevice();
      void init_system();
      void show();

      unsigned int devicesCount() const;            //返回存储 所有的设备个数
      QList< device_info >  getAllDevicesInfos();    //存储 所有的设备信息
      QList< device_info >  getDevicesInfoByClass(devClass etype) ;  //存储 所有的设备信息

    // explicit DlsDevice(QObject *parent = nullptr);
    // virtual ~DlsDevice();
    // // properties
    // Q_PROPERTY(bool canNTP READ canNTP);
    // // sync properties
    // Q_PROPERTY(QStringList fallbackNTPServers READ fallbackNTPServers);

    // slot
public slots:
   

private:
    hwNode m_hwNode;    
    QList< device_info >    m_ListDeviceInfo;

    //QScopedPointer<DlsDevicePrivate> d_ptr;
    Q_DECLARE_PRIVATE(DlsDevice)
};

DLSDEVICE_END_NAMESPACE


//-------------------------------------------------


#endif // DlsDevice_H


