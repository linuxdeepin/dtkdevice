// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dinputdevice.h"
#include "dinputdevice_p.h"

DINPUTDEVICES_BEGIN_NAMESPACE

DInputDevicePrivate::DInputDevicePrivate(DInputDevice *q)
    : q_ptr(q)
{
}

DInputDevice::DInputDevice(QObject *parent)
    : QObject(parent)
    , d_ptr(new DInputDevicePrivate(this))
{
}

DInputDevice::~DInputDevice() {}

quint32 DInputDevice::id() const
{
    // TODO Implement this
    return 10;
}

QString DInputDevice::name() const
{
    // TODO Implement this
    return "test";
}

DeviceType DInputDevice::type() const
{
    // TODO Implement this
    return DeviceType::Generic;
}

bool DInputDevice::enabled() const
{
    // TODO Implement this
    return true;
}

DExpected<void> DInputDevice::reset()
{
    // TODO Implement this
    return {};
}

DINPUTDEVICES_END_NAMESPACE