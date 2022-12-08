// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
#ifndef DLSDEVICE_H
#define DLSDEVICE_H

#include "dtklsdevice_global.h"
#include "dlsdevicetypes.h"

#include <QObject>

DLSDEVICE_BEGIN_NAMESPACE
class DlsDevicePrivate;

class DlsDevice : public QObject
{

public:
    explicit DlsDevice(QObject *parent = nullptr);
    ~DlsDevice();

    QList< DDeviceInfo >  devicesInfosAll();

    QStringList  deviceAttris(DevClass etype);
    QList< DDeviceInfo > deviceInfo(DevClass etype);
    QList< DDeviceInfo >  deviceInfo(DevClass etype, const int idex);

    int devicesCount() ;
    int devicesCount(DevClass devclass);
    double updateSystemCpuUsage();
    QMap<QString, int> CpuStat();
    double getCpuUsage();


    QList< DDeviceInfo >  deviceCPU();
    QList< DDeviceInfo >  deviceStorage();
    QList< DDeviceInfo >  deviceGPU();
    QList< DDeviceInfo >  deviceMemory();
    QList< DDeviceInfo >  deviceMonitor(); //todo
    QList< DDeviceInfo >  deviceAudio();
    QList< DDeviceInfo >  deviceNetwork();
    QList< DDeviceInfo >  deviceCamera();
    QList< DDeviceInfo >  deviceKeyboard();
    QList< DDeviceInfo >  deviceMouse();
    QList< DDeviceInfo >  deviceComputer();

private:
    QScopedPointer<DlsDevicePrivate> d_ptr;
    Q_DECLARE_PRIVATE(DlsDevice)
};

DLSDEVICE_END_NAMESPACE

#endif


