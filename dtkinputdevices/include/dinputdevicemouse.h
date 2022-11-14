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
    Q_PROPERTY(bool naturalScroll READ naturalScroll WRITE setNaturalScroll)
    Q_PROPERTY(bool middleButtonEmulation READ middleButtonEmulation WRITE setMiddleButtonEmulation)

public:
    explicit DInputDeviceMouse(QObject *parent = nullptr);
    ~DInputDeviceMouse() override;

    bool naturalScroll() const;
    bool middleButtonEmulation() const;

    void setNaturalScroll(bool naturalScroll);
    void setMiddleButtonEmulation(bool middleButtonEmulation);

public Q_SLOTS:
    DExpected<void> reset() override;

private:
    QScopedPointer<DInputDeviceMousePrivate> d_ptr;
    Q_DECLARE_PRIVATE(DInputDeviceMouse)
};

DINPUTDEVICES_END_NAMESPACE

#endif  // DINPUTDEVICEMOUSE_H
