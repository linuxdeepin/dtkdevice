// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DLSDEVICETYPES_H
#define DLSDEVICETYPES_H

#include <qobject.h>
#include <QMap>
#include "dtklsdevice_global.h"

DLSDEVICE_BEGIN_NAMESPACE
typedef enum
  {
    d_unkown = 0,
    d_system, d_bridge,    d_memory,    d_processor,    d_address,
    d_storage,    d_disk,    d_tape,    d_bus,    d_network,
    d_display,    d_input,    d_printer,    d_multimedia,
    d_communication,    d_power,    d_volume,    d_generic,
    d_max = 100
  } devClass;



struct device_info
{
    devClass deviceclass;
    QStringList deviceAttrisLst;
    QMap<QString, QString>        deviceInfoLstMap;
};

//struct device_info
//{
//  devClass deviceclass;
//  QString id, vendor, product, version, date, serial, slot, handle, description,
//    businfo, physid, dev, modalias, subvendor, subproduct;
//  QString vendor_id,product_id,subvendor_id, subproduct_id,class_id,vid_pid;
//  QString vendor_name,product_name,subvendor_name, subproduct_name,class_name;
//  bool enabled;
//  bool claimed;
//  unsigned long long start;
//  unsigned long long size;
//  unsigned long long capacity;
//  unsigned long long clock;
//  unsigned int width;


//};

//QStringList  deviceAttris;


DLSDEVICE_END_NAMESPACE

#endif
