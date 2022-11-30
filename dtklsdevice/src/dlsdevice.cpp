// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dlsdevice.h"
#include "dlsdevice_p.h"

#include <qdebug.h>
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

QList<DDeviceInfo > DlsDevice::devicesInfosAll()
{
    Q_D(const DlsDevice);
    return d->m_listDeviceInfo;
}

QStringList DlsDevice::deviceAttris(DevClass etype)
{

    Q_D(const DlsDevice);
    QStringList  tmpInfoLst;
    tmpInfoLst.clear();

    for (int it = 0; it < d->m_listDeviceInfo.count(); it++) {
        if (d->m_listDeviceInfo.at(it).devClass == etype)
            return d->m_listDeviceInfo.at(it).deviceBaseAttrisLst;
    }
    return tmpInfoLst;
}

QList<DDeviceInfo > DlsDevice::deviceInfo(DevClass etype)
{
    Q_D(const DlsDevice);
    QList<DDeviceInfo >  infoList;

    for (int it = 0; it < d->m_listDeviceInfo.count(); it++) {
        if (d->m_listDeviceInfo.at(it).devClass == etype)
            infoList.append(d->m_listDeviceInfo.at(it));
    }
    return infoList;
}

QList< DDeviceInfo > DlsDevice::deviceInfo(DevClass etype, const int idex)
{
    Q_D(const DlsDevice);
    QList<DDeviceInfo >  infoList;
    int cnt = 0;
    infoList.clear();

    for (int it = 0; it < d->m_listDeviceInfo.count(); it++) {
        if (d->m_listDeviceInfo.at(it).devClass == etype)
            if (cnt++ == idex) {
                infoList.append(d->m_listDeviceInfo.at(it));
                break;
            }
    }
    return infoList;
}

int DlsDevice::devicesCount()
{
    Q_D(const DlsDevice);
    return  d->m_hwNode.countChildren();
}

int DlsDevice::devicesCount(DevClass devclass)
{
    Q_D(DlsDevice);
    return  d->m_hwNode.countChildren(d->convertClass(devclass));
}

double DlsDevice::updateSystemCpuUsage()
{
    Q_D(DlsDevice);
    return  d->updateSystemCpuUsage();
}

QMap<QString, int> DlsDevice::CpuStat()
{
    Q_D(DlsDevice);
    return   d->CpuStat();
}

double DlsDevice::getCpuUsage()
{
    Q_D(DlsDevice);
    return  d->getCpuUsage();
}

QList<DDeviceInfo> DlsDevice::deviceCPU()
{
    Q_D(DlsDevice);
    return  d->deviceCPU();
}

QList<DDeviceInfo> DlsDevice::deviceStorage()
{
    Q_D(DlsDevice);
    return  d->deviceStorage();
}

QList<DDeviceInfo> DlsDevice::deviceGPU()
{
    Q_D(DlsDevice);
    return  d->deviceGPU();
}

QList<DDeviceInfo> DlsDevice::deviceMemory()
{
    Q_D(DlsDevice);
    return  d->deviceMemory();
}

QList<DDeviceInfo> DlsDevice::deviceMonitor()
{
    Q_D(DlsDevice);
    return  d->deviceMonitor();
}

QList<DDeviceInfo> DlsDevice::deviceAudio()
{
    Q_D(DlsDevice);
    return  d->deviceAudio();
}

QList<DDeviceInfo> DlsDevice::deviceNetwork()
{
    Q_D(DlsDevice);
    return  d->deviceNetwork();
}

QList<DDeviceInfo> DlsDevice::deviceCamera()
{
    Q_D(DlsDevice);
    return  d->deviceCamera();
}

QList<DDeviceInfo> DlsDevice::deviceKeyboard()
{
    Q_D(DlsDevice);
    return  d->deviceKeyboard();
}

QList<DDeviceInfo> DlsDevice::deviceMouse()
{
    Q_D(DlsDevice);
    return  d->deviceMouse();
}

QList<DDeviceInfo> DlsDevice::deviceComputer()
{
    Q_D(DlsDevice);
    return  d->deviceComputer();
}

DLSDEVICE_END_NAMESPACE
