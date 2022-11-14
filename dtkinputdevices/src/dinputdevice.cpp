// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dinputdevice.h"
#include "dinputdevice_p.h"
#include "dtkinputdevices_types.h"

DINPUTDEVICES_BEGIN_NAMESPACE
using DCORE_NAMESPACE::DError;
using DCORE_NAMESPACE::DUnexpected;
DInputDevicePrivate::DInputDevicePrivate(DInputDevice *q)
    : m_id(0)
    , m_name("Generic device")
    , m_type(DeviceType::Generic)
    , m_enabled(true)
    , q_ptr(q)
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
    Q_D(const DInputDevice);
    return d->m_id;
}

QString DInputDevice::name() const
{
    Q_D(const DInputDevice);
    return d->m_name;
}

DeviceType DInputDevice::type() const
{
    Q_D(const DInputDevice);
    return d->m_type;
}

bool DInputDevice::enabled() const
{
    Q_D(const DInputDevice);
    return d->m_enabled;
}

DExpected<void> DInputDevice::reset()
{
    return DUnexpected{DError{ErrorCode::InvalidCall, "Generic device does not have a reset method!"}};
}

DINPUTDEVICES_END_NAMESPACE
