// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DINPUTDEVICEMANAGER_H
#define DINPUTDEVICEMANAGER_H

#include "dtkinputdevices_global.h"
#include <DExpected>
#include <QObject>
#include <QScopedPointer>

#include "dtkinputdevices_types.h"

DINPUTDEVICES_BEGIN_NAMESPACE
class DInputDevice;
class DInputDeviceSetting;
DINPUTDEVICES_END_NAMESPACE
using DInputDevicePtr = QSharedPointer<DTK_INPUTDEVICES_NAMESPACE::DInputDevice>;
using DInputSettingPtr = QSharedPointer<DTK_INPUTDEVICES_NAMESPACE::DInputDeviceSetting>;
using DInputDeviceInfoList = QList<DTK_INPUTDEVICES_NAMESPACE::DeviceInfo>;
DINPUTDEVICES_BEGIN_NAMESPACE
using DCORE_NAMESPACE::DExpected;

class DInputDeviceManagerPrivate;
class DInputDeviceManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(DInputDeviceInfoList deviceInfos READ deviceInfos)

public:
    explicit DInputDeviceManager(QObject *parent = nullptr);
    ~DInputDeviceManager() override;
    DInputDeviceInfoList deviceInfos() const;

Q_SIGNALS:
    void deviceAdded(const DeviceInfo &device);
    void deviceRemoved(const DeviceInfo &device);

public Q_SLOTS:
    DExpected<DInputDevicePtr> createDevice(const DeviceInfo &info);
    DExpected<DInputSettingPtr> setting();

private:
    QScopedPointer<DInputDeviceManagerPrivate> d_ptr;
    Q_DECLARE_PRIVATE(DInputDeviceManager)
};

DINPUTDEVICES_END_NAMESPACE
#endif
