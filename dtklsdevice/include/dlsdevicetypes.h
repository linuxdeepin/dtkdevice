// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DLSDEVICETYPES_H
#define DLSDEVICETYPES_H

#include <qobject.h>
#include <QMap>
#include "dtklsdevice_global.h"

DLSDEVICE_BEGIN_NAMESPACE
enum DevClass {
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
};


struct DDeviceInfo {
    QMap<QString, QString>  deviceInfoLstMap;

    QString vendorName;
    QString productName;
    QString modalias;
    QString vendorID;
    QString productID;
    QString sysFsPath;
    QString baseClassName;
    QString subClassName;
    QString description;
    QStringList deviceBaseAttrisLst;
    QStringList deviceOtherAttrisLst;
    DevClass devClass;
};

struct DCpuStat {
    unsigned long long user {0}; // user time
    unsigned long long nice {0}; // user time with low priority
    unsigned long long sys {0}; // system time
    unsigned long long idle {0}; // idle time
    unsigned long long iowait {0}; // io wait time
    unsigned long long hardirq {0}; // interrupt time
    unsigned long long softirq {0}; // soft interrupt time
    unsigned long long steal {0}; // stolen time
    unsigned long long guest {0}; // guest time
    unsigned long long guestNice {0}; // guest time (niced)
};

struct DCpuUsage {
    unsigned long long total {0};
    unsigned long long idle {0};
};

DLSDEVICE_END_NAMESPACE

#endif
