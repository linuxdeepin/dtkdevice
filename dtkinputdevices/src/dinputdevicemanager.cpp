// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dinputdevicemanager.h"
#include "dinputdevicemanager_p.h"

DINPUTDEVICES_BEGIN_NAMESPACE
DInputDeviceManagerPrivate::DInputDeviceManagerPrivate(DInputDeviceManager *q)
    : q_ptr(q)
{
}

DInputDeviceManager::DInputDeviceManager(QObject *parent)
    : QObject(parent)
    , d_ptr(new DInputDeviceManagerPrivate(this))
{
}

DInputDeviceManager::~DInputDeviceManager() {}

QList<DeviceInfo> DInputDeviceManager::deviceInfos() const
{
    // TODO Implement this
    return {};
}

DExpected<DevicePtr> DInputDeviceManager::createDevice(const DeviceInfo &info)
{
    // TODO Implement this
    return {};
}
DExpected<SettingPtr> DInputDeviceManager::setting()
{
    // TODO Implement this
    return {};
}
DINPUTDEVICES_END_NAMESPACE