// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DINPUTDEVICEMANAGER_H
#define DINPUTDEVICEMANAGER_H

#include "dtkinputdevices_global.h"
#include <DExpected>
#include <QObject>
#include <QScopedPointer>

#include "dinputdevice.h"
#include "dinputdevicesetting.h"
#include "dinputdevicetypes.h"
DINPUTDEVICES_BEGIN_NAMESPACE
using DevicePtr = DInputDevice::Ptr;
using SettingPtr = DInputDeviceSetting::Ptr;

class DInputDeviceManagerPrivate;
class DInputDeviceManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<DeviceInfo> deviceInfos READ deviceInfos)
public:
    explicit DInputDeviceManager(QObject *parent = nullptr);
    ~DInputDeviceManager() override;
    QList<DeviceInfo> deviceInfos() const;

Q_SIGNALS:
    void deviceAdded(const DeviceInfo &device);
    void deviceRemoved(const DeviceInfo &device);

public Q_SLOTS:
    DExpected<DevicePtr> createDevice(const DeviceInfo &info);
    DExpected<SettingPtr> setting();

private:
    QScopedPointer<DInputDeviceManagerPrivate> d_ptr;
    Q_DECLARE_PRIVATE(DInputDeviceManager)
};

DINPUTDEVICES_END_NAMESPACE
#endif