// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
#ifndef DLSDEVICE_P_H
#define DLSDEVICE_P_H

#include "../3rdparty/hw.h"
#include "dlsdevice.h"
#include <QMap>

DLSDEVICE_BEGIN_NAMESPACE


class DlsDevicePrivate : public QObject
{
    // Q_OBJECT
    Q_DECLARE_PUBLIC(DlsDevice)

public:
    explicit DlsDevicePrivate(DlsDevice *parent);
    virtual ~DlsDevicePrivate()
    {
    }

    void addDeviceInfo(hwNode &node, QList< device_info >   &ll);
    devClass convertClass(hw::hwClass cc);
    hw::hwClass convertClass(devClass cc);

    double updateSystemCpuUsage();
    QMap<QString, int> cpuStat();
    double getCpuUsage();

public:

    QList< device_info >      m_ListDeviceInfo;

    hwNode m_hwNode ;
    DlsDevice *q_ptr = nullptr;

private:
    QMap<QString, int> mLastCpuStat;
    double mCpuUsage;

    QStringList  attrisMouse;
    QStringList  attrisCPU;
    QStringList  attrisStorage;
    QStringList  attrisGPU;
    QStringList  attrisMemory;
    QStringList  attrisBios;
    QStringList  attrisBluetooth;
    QStringList  attrisAudio;
    QStringList  attrisNetwork;
    QStringList  attrisImage;
    QStringList  attrisKeyboard;
    QStringList  attrisComputer;
    QStringList  attrisOthers;

};

DLSDEVICE_END_NAMESPACE

#endif
