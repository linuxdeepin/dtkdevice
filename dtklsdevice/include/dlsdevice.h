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
     explicit DlsDevice(QObject *parent = nullptr);
      ~DlsDevice();

       QList< device_info >  devicesInfosAll();

       QStringList  deviceAttris(devClass etype);
       QList< device_info > deviceInfo(devClass etype);
       QList< device_info >  deviceInfo(devClass etype, const int idex);

      int devicesCount() ;
      int devicesCount(devClass devclass);


     QList< device_info >  deviceCPU();   //d_processor
     QList< device_info >  deviceStorage();  //d_storage //d_disk
     QList< device_info >  deviceGPU();      //display
     QList< device_info >  deviceMemory();  //d_memory
     QList< device_info >  deviceMonitor();
     QList< device_info >  deviceBios();
     QList< device_info >  deviceAudio();    //d_multimedia
     QList< device_info >  deviceNetwork();  //d_network
     QList< device_info >  deviceCamera();
     QList< device_info >  deviceKeyboard();  //d_input
     QList< device_info >  deviceComputer();  //d_system  d_generic

private:

    QScopedPointer<DlsDevicePrivate> d_ptr;
    Q_DECLARE_PRIVATE(DlsDevice)
};

DLSDEVICE_END_NAMESPACE


//-------------------------------------------------


#endif // DlsDevice_H


