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


      unsigned int ddevicesCount() const;
      QList< device_info >  dAllDevicesInfos();
      QList< device_info >  dDevicesInfoByClass(devClass etype) ;

      QList< device_info > dDeviceMouse();
      QList< device_info > dDeviceCPU();   //d_processor
      QList< device_info > dDeviceStorage();  //d_storage //d_disk
      QList< device_info > dDeviceGPU();      //display
      QList< device_info > dDeviceMemory();  //d_memory
      QList< device_info > dDeviceMonitor();
      QList< device_info > dDeviceBios();
      QList< device_info > dDeviceAudio();    //d_multimedia
      QList< device_info > dDeviceNetwork();  //d_network
      QList< device_info > dDeviceCamera();
      QList< device_info > dDeviceKeyboard();  //d_input
      QList< device_info > dDeviceComputer();  //d_system  d_generic



      QString  dMouseVendor(const int id);
      QString  dMouseProduct(const int id);
      QString  dMouseVID(const int id);
      QString  dMousePID(const int id);
      QString  dMouseModalias(const int id);

      QString  dGPUVendor(const int id);
      QString  dGPUseProduct(const int id);
      QString  dGPUVID(const int id);
      QString  dGPUPID();
      QString  dGPUModalias(const int id);

   

private:
    hwNode m_hwNode;    
    QList< device_info >    m_ListDeviceInfo;

    Q_DECLARE_PRIVATE(DlsDevice)
};

DLSDEVICE_END_NAMESPACE


//-------------------------------------------------


#endif // DlsDevice_H


