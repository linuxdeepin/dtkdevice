// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dinputdevicegeneric.h"
#include "dinputdevicegeneric_p.h"
#include "dtkinputdevices_types.h"

DDEVICE_BEGIN_NAMESPACE
using DCORE_NAMESPACE::DError;
using DCORE_NAMESPACE::DUnexpected;
DInputDeviceGenericPrivate::DInputDeviceGenericPrivate(DInputDeviceGeneric *q)
    : m_id(0xffffffff)
    , m_name("Generic device")
    , m_type(DeviceType::Generic)
    , m_enabled(true)
    , q_ptr(q)
{
}

DInputDeviceGeneric::DInputDeviceGeneric(QObject *parent)
    : QObject(parent)
    , d_ptr(new DInputDeviceGenericPrivate(this))
{
}

DInputDeviceGeneric::DInputDeviceGeneric(const DeviceInfo &info, bool enabled)
    : DInputDeviceGeneric()
{
    setDeviceInfo(info);
    setEnabled(enabled);
}

DInputDeviceGeneric::~DInputDeviceGeneric() = default;

quint32 DInputDeviceGeneric::id() const
{
    Q_D(const DInputDeviceGeneric);
    return d->m_id;
}

QString DInputDeviceGeneric::name() const
{
    Q_D(const DInputDeviceGeneric);
    return d->m_name;
}

DeviceType DInputDeviceGeneric::type() const
{
    Q_D(const DInputDeviceGeneric);
    return d->m_type;
}

bool DInputDeviceGeneric::enabled() const
{
    Q_D(const DInputDeviceGeneric);
    return d->m_enabled;
}

DExpected<void> DInputDeviceGeneric::reset()
{
    return DUnexpected<>{DError{ErrorCode::InvalidCall, "Generic device does not have a reset method!"}};
}

void DInputDeviceGeneric::setDeviceInfo(const DeviceInfo &info)
{
    setId(info.id);
    setName(info.name);
    setType(info.type);
}

void DInputDeviceGeneric::setEnabled(bool enabled)
{
    Q_D(DInputDeviceGeneric);
    d->m_enabled = enabled;
    Q_EMIT this->enabledChanged(enabled);
}

void DInputDeviceGeneric::setId(quint32 id)
{
    Q_D(DInputDeviceGeneric);
    d->m_id = id;
}

void DInputDeviceGeneric::setName(const QString &name)
{
    Q_D(DInputDeviceGeneric);
    d->m_name = name;
}

void DInputDeviceGeneric::setType(DeviceType type)
{
    Q_D(DInputDeviceGeneric);
    d->m_type = type;
}
DDEVICE_END_NAMESPACE
