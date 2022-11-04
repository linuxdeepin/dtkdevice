// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
#ifndef DLSDEVICE_H
#define DLSDEVICE_H

#include "dtklsdevice_global.h"
#include "dlsdevicetypes.h"

#include <qobject.h>

DLSDEVICE_BEGIN_NAMESPACE
class DlsDevicePrivate;

class DlsDevice : public QObject
{

public:
    explicit DlsDevice(QObject *parent = nullptr);
    ~DlsDevice();

    QList< device_info >  devicesInfosAll();

    QStringList  deviceAttris(devClass etype);
    QList< device_info > deviceInfo(devClass etype);
    QList< device_info >  deviceInfo(devClass etype, const int idex);

    int devicesCount() ;
    int devicesCount(devClass devclass);
    double updateSystemCpuUsage();
    QMap<QString, int> cpuStat();
    double getCpuUsage();

// TODO:
    QList< device_info >  deviceCPU();
    QList< device_info >  deviceStorage();
    QList< device_info >  deviceGPU();
    QList< device_info >  deviceMemory();
    QList< device_info >  deviceMonitor();
    QList< device_info >  deviceBios();
    QList< device_info >  deviceAudio();
    QList< device_info >  deviceNetwork();
    QList< device_info >  deviceCamera();
    QList< device_info >  deviceKeyboard();
    QList< device_info >  deviceComputer();

private:
    QScopedPointer<DlsDevicePrivate> d_ptr;
    Q_DECLARE_PRIVATE(DlsDevice)
};

DLSDEVICE_END_NAMESPACE

#endif


