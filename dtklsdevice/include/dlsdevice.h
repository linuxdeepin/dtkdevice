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

      unsigned int devicesCount() const;            
      QList< device_info >  getAllDevicesInfos();   
      QList< device_info >  getDevicesInfoByClass(devClass etype) ; 


public slots:
   

private:
    hwNode m_hwNode;    
    QList< device_info >    m_ListDeviceInfo;

    Q_DECLARE_PRIVATE(DlsDevice)
};

DLSDEVICE_END_NAMESPACE


//-------------------------------------------------


#endif // DlsDevice_H


