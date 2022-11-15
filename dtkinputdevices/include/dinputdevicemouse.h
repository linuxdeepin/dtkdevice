// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DINPUTDEVICEMOUSE_H
#define DINPUTDEVICEMOUSE_H

#include "dtkinputdevices_global.h"

#include <DExpected>
#include <QObject>
#include <QScopedPointer>

#include "dinputdevicepointer.h"

DINPUTDEVICES_BEGIN_NAMESPACE

using DCORE_NAMESPACE::DExpected;
class DInputDeviceMousePrivate;
class DInputDeviceMouse : public DInputDevicePointer
{
    Q_OBJECT
    Q_PROPERTY(bool naturalScroll READ naturalScroll WRITE setNaturalScroll NOTIFY naturalScrollChanged)
    Q_PROPERTY(
        bool middleButtonEmulation READ middleButtonEmulation WRITE setMiddleButtonEmulation NOTIFY middleButtonEmulationChanged)

public:
    ~DInputDeviceMouse() override;
    bool naturalScroll() const;
    bool middleButtonEmulation() const;

    void setNaturalScroll(bool naturalScroll);
    void setMiddleButtonEmulation(bool middleButtonEmulation);

Q_SIGNALS:
    void naturalScrollChanged(bool naturalScroll);
    void middleButtonEmulationChanged(bool emulation);

public Q_SLOTS:
    DExpected<void> reset() override;

protected:
    explicit DInputDeviceMouse(QObject *parent = nullptr);
    DInputDeviceMouse(const DeviceInfo &info, bool enabled = true);

private:
    friend class DInputDeviceManager;
    QScopedPointer<DInputDeviceMousePrivate> d_ptr;
    Q_DECLARE_PRIVATE(DInputDeviceMouse)
};

DINPUTDEVICES_END_NAMESPACE

#endif  // DINPUTDEVICEMOUSE_H
