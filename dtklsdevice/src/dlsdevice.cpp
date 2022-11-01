#include "dlsdevice.h"
#include "../3rdparty/hw.h"
#include "../3rdparty/scan.h"
#include "../3rdparty/options.h"
#include "../3rdparty/osutils.h"
#include "../3rdparty/config.h"
#include "dprint.h"

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

#ifndef NONLS
#include <locale.h>
#endif
DLSDEVICE_BEGIN_NAMESPACE

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


void DlsDevice::show()
{
    // print(m_hwNode, 0);
}

QList<device_info> DlsDevice::getAllDevicesInfos()
{
    return m_ListDeviceInfo;
}

QList<device_info> DlsDevice::getDevicesInfoByClass(devClass etype)
{
    QList< device_info >  tmp;

   for (int it = 0; it < m_ListDeviceInfo.count(); it++) {
       if(m_ListDeviceInfo.at(it).deviceclass == etype)
           tmp.append(m_ListDeviceInfo.at(it));
   }
   return tmp;
}


unsigned int DlsDevice::devicesCount() const
{
    return  m_hwNode.countChildren();
}



DLSDEVICE_END_NAMESPACE
