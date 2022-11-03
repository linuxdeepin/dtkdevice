

#include "dlsdevice.h"
#include "dlsdevice_p.h"


#include "scan.h"

#include "../3rdparty/hw.h"


#include "options.h"
#include "version.h"
#include "osutils.h"
#include "config.h"
#include <cstring>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <termios.h>

#include <QString>
#include <QVector>
#include <QMap>

using namespace hw;
DLSDEVICE_BEGIN_NAMESPACE


DlsDevicePrivate::DlsDevicePrivate(DlsDevice *parent)
    : m_hwNode("computer", hw::sys_tem)
    ,q_ptr(parent)
{
        // m_classAttrisLstMap.clear();
        m_ListDeviceInfo.clear();
        scan_system(m_hwNode);
        addDeviceInfo(m_hwNode, m_ListDeviceInfo);
}

void DlsDevicePrivate::addDeviceInfo(hwNode &node, QList<device_info > &ll)
{

    struct device_info entry;

     entry.deviceInfoLstMap.clear();
     entry.deviceInfoLstMap.clear();
     entry.deviceclass = d_unkown;

     if (node.getBusInfo() != "")
     {
        entry.deviceAttrisLst.append("SysFs_PATH");
        entry.deviceInfoLstMap["SysFs_PATH"] = QString::fromStdString( node.getBusInfo());
     }

     entry.deviceclass = convertClass(node.getClass());

     entry.deviceAttrisLst.append("sysID");
     entry.deviceInfoLstMap.insert("sysID",QString::fromStdString( node.getId()));

     entry.deviceAttrisLst.append("Description");
     entry.deviceInfoLstMap.insert("Description",QString::fromStdString( node.getDescription()));

     entry.deviceAttrisLst.append("sysID");
     entry.deviceInfoLstMap.insert("sysID",QString::fromStdString( node.getId()));

     entry.deviceAttrisLst.append("Vendor");
     entry.deviceInfoLstMap.insert("Vendor",QString::fromStdString( node.getVendor()));


     entry.deviceAttrisLst.append("Name");
     entry.deviceInfoLstMap.insert("Name",QString::fromStdString( node.getProduct()));


      if (node.getSize() > 0)
      {
          entry.deviceAttrisLst.append("Size");
          entry.deviceInfoLstMap.insert("Size", QString::fromStdString( std::to_string(node.getSize())));
      }

      if (! node.getConfig("Vendor_ID").empty())
      {
          entry.deviceAttrisLst.append("Vendor_ID");
          entry.deviceInfoLstMap.insert("Vendor_ID", QString::fromStdString( node.getConfig("Vendor_ID") ) );
      }

      if (! node.getConfig("Product_ID").empty())
      {
          entry.deviceAttrisLst.append("Product_ID");
          entry.deviceInfoLstMap.insert("Product_ID", QString::fromStdString( node.getConfig("Product_ID") ) );
      }

      if (! node.getConfig("vid:pid").empty())
      {
          entry.deviceAttrisLst.append("vid:pid");
          entry.deviceInfoLstMap.insert("vid:pid", QString::fromStdString( node.getConfig("vid:pid") ) );
      }

      if( node.getModalias().length() > 53 )
      {
          entry.deviceAttrisLst.append("Modalias");
          entry.deviceInfoLstMap.insert("Modalias", QString::fromStdString( node.getModalias().substr(0, 53)) );
      }

      else
      {
          entry.deviceAttrisLst.append("Modalias");
          entry.deviceInfoLstMap.insert("Modalias", QString::fromStdString( node.getModalias()) );
      }

//capabilities: pm msi bus_master cap_list ethernet physical tp 10bt 10bt-fd 100bt 100bt-fd 1000bt-fd autonegotiation
//configuration: autonegotiation=on broadcast=yes driver=e1000e driverversion=5.15.34-amd64-desktop duplex=full firmware=0.2-4 ip=10.8.11.89 latency=0 link=yes multicast=yes port=twisted pair speed=1Gbit/s
//resources: irq:126 memory:a0300000-a031ffff

      entry.deviceAttrisLst.append("ClassName");
      entry.deviceInfoLstMap.insert("ClassName",QString::fromStdString( node.getClassName()));

      ll.append(entry);
      for (unsigned int i = 0; i < node.countChildren(); i++)
      {
        addDeviceInfo(*node.getChild(i), ll);
      }
}


devClass DlsDevicePrivate::convertClass(hw::hwClass cc)
{
  switch (cc)
  {

    case bridge:  return d_bridge;
    case sys_tem:  return d_system;
    case memory:  return d_memory;
    case processor: return d_processor;
    case address:   return   d_address;
    case storage:   return   d_storage;
    case disk:      return   d_disk;
    case tape:      return   d_tape;
    case bus:       return   d_bus;
    case network:   return   d_network;
    case display:   return   d_display;
    case input:     return   d_input;
    case printer:   return   d_printer;
    case multimedia: return   d_multimedia;
    case communication: return d_communication;
    case power:       return  d_power;
    case volume:      return  d_volume;
    case generic:     return  d_generic;
    default:          return  d_unkown;
  }
}

hwClass DlsDevicePrivate::convertClass(devClass cc)
{
    switch (cc)
    {

      case d_bridge:  return bridge;
      case d_system:  return sys_tem;
      case d_memory:  return memory;
      case d_processor: return processor;
      case d_address:   return   address;
      case d_storage:   return   storage;
      case d_disk:      return   disk;
      case d_tape:      return   tape;
      case d_bus:       return   bus;
      case d_network:   return   network;
      case d_display:   return   display;
      case d_input:     return   input;
      case d_printer:   return   printer;
      case d_multimedia: return   multimedia;
      case d_communication: return communication;
      case d_power:       return  power;
      case d_volume:      return  volume;
      case d_generic:     return  generic;
      default:          return  generic;
    }

}


DLSDEVICE_END_NAMESPACE
