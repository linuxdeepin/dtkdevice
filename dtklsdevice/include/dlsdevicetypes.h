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
    DtkUnkown = 0,
    DtkBridge,   DtkController, DtkHub,
    DtkBios,     DtkBus,        DtkAddress, DtkVolume,  
    DtkVirtual,
    DtkGeneric,
    DtkProductSystem,
    DtkMainboard,
    DtkCpu,
    DtkMemory,
    DtkStorage,  DtkDisk,
    DtkDvd,      DtkTape,
    DtkNetwork,  Dtkwlan,   DtkCommunication,
    DtkDisplayGPU,         DtkMonitor,
    DtkInput,   
    DtkMouse,  
    DtkKeyboard, 
    DtkFingerprint,
    DtkCamera,
    DtkSoundAudio,
    DtkTouchscreen,
    DtkTouchpad, 
    DtkBluetooth,
    DtkPrinter,
    DtkPower,    DtkBattery,
    DtkSensor,
    DtkLed,
    DtkSwitchbuttion,
    DtkScanner,
    DtkChipcard,

    DtkOther,
    DtkRevers1,
    DtkRevers2,

    DtkMax = 100
  } devClass;


struct device_info
{
    QMap<QString, QString>  deviceInfoLstMap;
                
    QString VendorName;
    QString ProductName;
    QString Modalias;
    QString Vendor_ID;
    QString Product_ID;    
    QString SysFs_PATH;
    QString baseClassName;
    QString subClassName;
    QString Description;
    QStringList deviceBaseAttrisLst;
    QStringList deviceOtherAttrisLst;
    devClass eDevClass;  
};

DLSDEVICE_END_NAMESPACE

#endif
