// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dmemorydevice.h"

#include <QDebug>

DLSDEVICE_BEGIN_NAMESPACE

class DMemoryDevicePrivate
{
public:
    explicit DMemoryDevicePrivate(DMemoryDevice *parent)
        : q_ptr(parent)
    {

    }

private:
    DMemoryDevice *q_ptr = nullptr;
};

DMemoryDevice::DMemoryDevice(QObject *parent)
    : QObject(parent)
    , d_ptr(new DMemoryDevicePrivate(this))
{
}

DMemoryDevice::~DMemoryDevice()
{
}

int DMemoryDevice::count()
{
    return 0;
}

QString DMemoryDevice::vendor(int index)
{
    return QString();
}

QString DMemoryDevice::model(int index)
{
    return QString();
}

QString DMemoryDevice::totalWidth(int index)
{
    return QString();
}

QString DMemoryDevice::dataWidth(int index)
{
    return QString();
}

QString DMemoryDevice::type(int index)
{
    return QString();
}

QString DMemoryDevice::speed(int index)
{
    return QString();
}

QString DMemoryDevice::serialNumber(int index)
{
    return QString();
}

QString DMemoryDevice::size(int index)
{
    return QString();
}

QString DMemoryDevice::swapSize()
{
    return QString();
}

QString DMemoryDevice::available()
{
    return QString();
}

QString DMemoryDevice::buffers()
{
    return QString();
}

QString DMemoryDevice::cached()
{
    return QString();
}

QString DMemoryDevice::active()
{
    return QString();
}

QString DMemoryDevice::inactive()
{
    return QString();
}

QString DMemoryDevice::sharedSize()
{
    return QString();
}

QString DMemoryDevice::swapFree()
{
    return QString();
}

QString DMemoryDevice::swapCached()
{
    return QString();
}

QString DMemoryDevice::slab()
{
    return QString();
}

QString DMemoryDevice::dirty()
{
    return QString();
}

QString DMemoryDevice::mapped()
{
    return QString();
}

DLSDEVICE_END_NAMESPACE
