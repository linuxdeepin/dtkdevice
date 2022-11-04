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

QList<device_info > DlsDevice::devicesInfosAll()
{
    Q_D(const DlsDevice);
    return d->m_ListDeviceInfo;
}

QStringList DlsDevice::deviceAttris(devClass etype)
{

    Q_D(const DlsDevice);
    QStringList  tmpInfoLst;
    tmpInfoLst.clear();


    for (int it = 0; it < d->m_ListDeviceInfo.count(); it++) {
        if (d->m_ListDeviceInfo.at(it).eDevClass == etype)
            return d->m_ListDeviceInfo.at(it).deviceBaseAttrisLst;
    }
    return tmpInfoLst;
}

QList<device_info > DlsDevice::deviceInfo(devClass etype)
{
    Q_D(const DlsDevice);
    QList<device_info >  infoList;

    for (int it = 0; it < d->m_ListDeviceInfo.count(); it++) {
        if (d->m_ListDeviceInfo.at(it).eDevClass == etype)
            infoList.append(d->m_ListDeviceInfo.at(it));
    }
    return infoList;
}

QList< device_info > DlsDevice::deviceInfo(devClass etype, const int idex)
{
    Q_D(const DlsDevice);
    QList<device_info >  infoList;
    int cnt = 0;
    infoList.clear();

    for (int it = 0; it < d->m_ListDeviceInfo.count(); it++) {
        if (d->m_ListDeviceInfo.at(it).eDevClass == etype)
            if (cnt++ == idex) {
                infoList.append(d->m_ListDeviceInfo.at(it));
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

int DlsDevice::devicesCount(devClass devclass)
{
    Q_D(DlsDevice);
    return  d->m_hwNode.countChildren(d->convertClass(devclass));
}

double DlsDevice::updateSystemCpuUsage()
{
    Q_D(DlsDevice);
    return  d->updateSystemCpuUsage();
}

QMap<QString, int> DlsDevice::cpuStat()
{
    Q_D(DlsDevice);
    return   d->cpuStat();
}

double DlsDevice::getCpuUsage()
{
    Q_D(DlsDevice);
    return  d->getCpuUsage();
}

DLSDEVICE_END_NAMESPACE
