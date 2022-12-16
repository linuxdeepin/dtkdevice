// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dmotherboarddevice.h"

#include <QDebug>

DLSDEVICE_BEGIN_NAMESPACE

class DMotherboardDevicePrivate
{
public:
    explicit DMotherboardDevicePrivate(DMotherboardDevice *parent)
        : q_ptr(parent)
    {

    }

private:
    DMotherboardDevice *q_ptr = nullptr;
};

DMotherboardDevice::DMotherboardDevice(QObject *parent)
    : QObject(parent)
    , d_ptr(new DMotherboardDevicePrivate(this))
{
}

DMotherboardDevice::~DMotherboardDevice()
{
}

QString DMotherboardDevice::vendor()
{
    return QString();
}

QString DMotherboardDevice::model()
{
    return QString();
}

QString DMotherboardDevice::date()
{
    return QString();
}

QString DMotherboardDevice::biosInformation()
{
    return QString();
}

QString DMotherboardDevice::chassisInformation()
{
    return QString();
}

QString DMotherboardDevice::PhysicalMemoryArrayInformation()
{
    return QString();
}

QString DMotherboardDevice::temperature()
{
    return QString();
}

DLSDEVICE_END_NAMESPACE
