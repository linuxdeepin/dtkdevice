// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "ddiskdevice.h"

#include <QDebug>

DLSDEVICE_BEGIN_NAMESPACE

class DDiskDevicePrivate
{
public:
    explicit DDiskDevicePrivate(DDiskDevice *parent)
        : q_ptr(parent)
    {

    }

private:
    DDiskDevice *q_ptr = nullptr;
};

DDiskDevice::DDiskDevice(QObject *parent)
    : QObject(parent)
    , d_ptr(new DDiskDevicePrivate(this))
{
}

DDiskDevice::~DDiskDevice()
{
}

int DDiskDevice::count()
{
    return 0;
}

QString DDiskDevice::vendor(int index)
{
    return QString();
}

QString DDiskDevice::model(int index)
{
    return QString();
}

QString DDiskDevice::mediaType(int index)
{
    return QString();
}

QString DDiskDevice::size(int index)
{
    return QString();
}

QString DDiskDevice::interface(int index)
{
    return QString();
}

QString DDiskDevice::serialNumber(int index)
{
    return QString();
}

QString DDiskDevice::deviceFile(int index)
{
    return QString();
}

QString DDiskDevice::rotationRate(int index)
{
    return QString();
}

QString DDiskDevice::firmwareVersion(int index)
{
    return QString();
}

QString DDiskDevice::sectorSize(int index)
{
    return QString();
}

QString DDiskDevice::temperature(int index)
{
    return QString();
}

DDiskIoStat DDiskDevice::diskIoStat(int index)
{
    return DDiskIoStat();
}

DLSDEVICE_END_NAMESPACE
