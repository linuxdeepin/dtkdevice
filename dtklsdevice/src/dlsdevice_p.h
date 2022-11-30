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

    void addDeviceInfo(hwNode &node, QList< DDeviceInfo >   &ll);
    DevClass convertClass(hw::hwClass cc);
    hw::hwClass convertClass(DevClass cc);

    QList< DDeviceInfo >  deviceCPU();
    QList< DDeviceInfo >  deviceStorage();
    QList< DDeviceInfo >  deviceGPU();
    QList< DDeviceInfo >  deviceMemory();
    QList< DDeviceInfo >  deviceMonitor();
    QList< DDeviceInfo >  deviceAudio();
    QList< DDeviceInfo >  deviceNetwork();
    QList< DDeviceInfo >  deviceCamera();
    QList< DDeviceInfo >  deviceKeyboard();
    QList< DDeviceInfo >  deviceMouse();
    QList< DDeviceInfo >  deviceComputer();

    double updateSystemCpuUsage();
    QMap<QString, int> CpuStat();
    double getCpuUsage();

public:
    QList< DDeviceInfo >      m_listDeviceInfo;
    hwNode                    m_hwNode ;
    DlsDevice                *q_ptr = nullptr;

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
    QStringList  attrisCameraImage;
    QStringList  attrisKeyboard;
    QStringList  attrisComputer;
    QStringList  attrisOthers;

};

DLSDEVICE_END_NAMESPACE

#endif
