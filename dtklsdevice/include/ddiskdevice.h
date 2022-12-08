// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
#ifndef DDISKDEVICE_H
#define DDISKDEVICE_H

#include "dtklsdevice_global.h"
#include "dlsdevicetypes.h"

#include <QObject>

DLSDEVICE_BEGIN_NAMESPACE

class DDiskDevicePrivate;
class DDiskDevice : public QObject
{
public:
    explicit DDiskDevice(QObject *parent = nullptr);
    ~DDiskDevice();

    int count();
    QString vendor(int index);
    QString model(int index);
    QString mediaType(int index);
    QString size(int index);
    QString interface(int index);
    QString serialNumber(int index);
    QString deviceFile(int index);
    QString rotationRate(int index);
    QString firmwareVersion(int index);
    QString sectorSize(int index);

    QString temperature(int index);
    DDiskIoStat diskIoStat(int index);

private:
    QScopedPointer<DDiskDevicePrivate> d_ptr;
    Q_DECLARE_PRIVATE(DDiskDevice)
};

DLSDEVICE_END_NAMESPACE

#endif // DDISKDEVICE_H
