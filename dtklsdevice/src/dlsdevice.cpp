#include "dlsdevice.h"
#include "../3rdparty/hw.h"
#include "../3rdparty/scan.h"
#include "../3rdparty/options.h"
#include "../3rdparty/osutils.h"
#include "../3rdparty/config.h"
#include "daddInfo.h"

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

#ifndef NONLS
#include <locale.h>
#endif
DLSDEVICE_BEGIN_NAMESPACE


QList< device_info > m_ListDeviceMouse;
QList< device_info > m_ListDeviceCPU;
QList< device_info > m_ListDeviceStorage;
QList< device_info > m_ListDeviceGPU;
QList< device_info > m_ListDeviceMemory;
QList< device_info > m_ListDeviceBios;
QList< device_info > m_ListDeviceBluetooth;
QList< device_info > m_ListDeviceAudio;
QList< device_info > m_ListDeviceNetwork;
QList< device_info > m_ListDeviceImage;
QList< device_info > m_ListDeviceKeyboard;
QList< device_info > m_ListDeviceComputer;
QList< device_info > m_ListDeviceOthers;

DlsDevice::DlsDevice()
    : m_hwNode("computer", hw::sys_tem)
{
    scan_system(m_hwNode);
    addDeviceInfo(m_hwNode, m_ListDeviceInfo);
}


DlsDevice::~DlsDevice()
{

}

void DlsDevice::init_system()
{

#ifndef NONLS
  setlocale (LC_ALL, "");
  bindtextdomain (PACKAGE, LOCALEDIR);
  bind_textdomain_codeset (PACKAGE, "UTF-8");
  textdomain (PACKAGE);
#endif
}


QList<device_info> DlsDevice::dAllDevicesInfos()
{
    return m_ListDeviceInfo;
}

QList<device_info> DlsDevice::dDevicesInfoByClass(devClass etype)
{
    QList< device_info >  tmp;

   for (int it = 0; it < m_ListDeviceInfo.count(); it++) {
       if(m_ListDeviceInfo.at(it).deviceclass == etype)
           tmp.append(m_ListDeviceInfo.at(it));
   }
   return tmp;
}


unsigned int DlsDevice::ddevicesCount() const
{
    return  m_hwNode.countChildren();
}



DLSDEVICE_END_NAMESPACE
