/*
 * print.cpp
 *
 * This module prints out the hardware tree depending on options passed
 * Output can be plain text (good for human beings), HTML (good for web brow-
 * sers), XML (good for programs) or "hardware path" (ioscan-like).
 *
 */
#include "../3rdparty/hw.h"
#include "dprint.h"
#include "dlsdevice.h"
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

devClass convertClass(hw::hwClass cc)
{
  switch (cc)
  {
    // 
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
    default:          return  d_generic;
  }
}


void addDeviceInfo(hwNode & node, QList < device_info > &ll)
{
  device_info entry;

  entry.businfo = "";
  if (node.getBusInfo() != "")
    entry.businfo = QString::fromStdString( node.getBusInfo());

  entry.deviceclass = convertClass(node.getClass());
  entry.id = QString::fromStdString( node.getId());

  entry.description = QString::fromStdString( node.getDescription());
  entry.class_name = QString::fromStdString( node.getClassName());
  entry.vendor_name = QString::fromStdString( node.getVendor());
  entry.product_name = QString::fromStdString( node.getProduct());
  if (node.getSize() > 0)
    entry.size = ( node.getSize());

  entry.vid_pid = QString::fromStdString( node.getConfig("vid:pid") );
  
  if( node.getModalias().length() > 53 )
     entry.modalias = QString::fromStdString( node.getModalias().substr(0, 53));
  else 
    entry.modalias = QString::fromStdString( node.getModalias());
  
  // ll.push_back(entry); 
  ll.append(entry);
  for (unsigned int i = 0; i < node.countChildren(); i++)
  { 
    addDeviceInfo(*node.getChild(i), ll);
  }
}


DLSDEVICE_END_NAMESPACE