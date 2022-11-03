#include "dlsdevice.h"
#include "dlsdevice_p.h"

//#include <qdbusreply.h>
#include <qdebug.h>
//#include <qdatetime.h>


#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

#ifndef NONLS
#include <locale.h>
#endif
DLSDEVICE_BEGIN_NAMESPACE



DlsDevice::DlsDevice(QObject *parent)
    : QObject(parent)
    , d_ptr(new DlsDevicePrivate(this))

{

}


DlsDevice::~DlsDevice()
{

}

QList<device_info > DlsDevice::devicesInfosAll()
{
    Q_D(const DlsDevice);
    return d->m_ListDeviceInfo;
}

QStringList DlsDevice::deviceAttris(devClass etype)
{

       Q_D(const DlsDevice);
       QStringList  tmp;
       tmp.clear();
       

      for (int it = 0; it < d->m_ListDeviceInfo.count(); it++) {
          if(d->m_ListDeviceInfo.at(it).deviceclass == etype)
            return d->m_ListDeviceInfo.at(it).deviceAttrisLst;
      }
      return tmp;

}

QList<device_info > DlsDevice::deviceInfo(devClass etype)
{
   Q_D(const DlsDevice);
       QList<device_info >  tmp;

      for (int it = 0; it < d->m_ListDeviceInfo.count(); it++) {
          if(d->m_ListDeviceInfo.at(it).deviceclass == etype)
              tmp.append(d->m_ListDeviceInfo.at(it));
      }
      return tmp;
}

QList< device_info > DlsDevice::deviceInfo(devClass etype, const int idex)
{
    Q_D(const DlsDevice);
        QList<device_info >  tmp;
        int cnt = 0;
        tmp.clear();

       for (int it = 0; it < d->m_ListDeviceInfo.count(); it++) {
           if(d->m_ListDeviceInfo.at(it).deviceclass == etype)
               if(cnt++ == idex)
               {
                    tmp.append(d->m_ListDeviceInfo.at(it));
                    break;
               }
       }
       return tmp;
}

int DlsDevice::devicesCount()
{
    Q_D(const DlsDevice);
    return  d->m_hwNode.countChildren();
}

int DlsDevice::devicesCount(devClass devclass)
{
    Q_D(DlsDevice);

    return  d->m_hwNode.countChildren(d->convertClass(devclass));
}

//void DlsDevice::init_system()
//{

//#ifndef NONLS
//  setlocale (LC_ALL, "");
//  bindtextdomain (PACKAGE, LOCALEDIR);
//  bind_textdomain_codeset (PACKAGE, "UTF-8");
//  textdomain (PACKAGE);
//#endif
//  deviceAttris << "VID" << "PID" << "l1"
//}


//QList< device_info > m_ListDeviceMouse;
//QList< device_info > m_ListDeviceCPU;
//QList< device_info > m_ListDeviceStorage;
//QList< device_info > m_ListDeviceGPU;
//QList< device_info > m_ListDeviceMemory;
//QList< device_info > m_ListDeviceBios;
//QList< device_info > m_ListDeviceBluetooth;
//QList< device_info > m_ListDeviceAudio;
//QList< device_info > m_ListDeviceNetwork;
//QList< device_info > m_ListDeviceImage;
//QList< device_info > m_ListDeviceKeyboard;
//QList< device_info > m_ListDeviceComputer;
//QList< device_info > m_ListDeviceOthers;

DLSDEVICE_END_NAMESPACE
