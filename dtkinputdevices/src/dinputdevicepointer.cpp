// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dinputdevicepointer.h"
#include "dinputdevicepointer_p.h"

DINPUTDEVICES_BEGIN_NAMESPACE

DInputDevicePointerPrivate::DInputDevicePointerPrivate(DInputDevicePointer *q)
    : q_ptr(q)
{
}

DInputDevicePointer::DInputDevicePointer(QObject *parent)
    : DInputDevice(parent)
    , d_ptr(new DInputDevicePointerPrivate(this))
{
}

DInputDevicePointer::DInputDevicePointer(const DeviceInfo &info, bool enabled)
    : DInputDevice(info, enabled)
    , d_ptr(new DInputDevicePointerPrivate(this))
{
}

DInputDevicePointer::~DInputDevicePointer() = default;

bool DInputDevicePointer::leftHanded() const
{
    // TODO Implement this
    return true;
}

ScrollMethod DInputDevicePointer::scrollMethod() const
{
    // TODO Implement this
    return ScrollMethod::NoScroll;
}

AccelerationProfile DInputDevicePointer::accelerationProfile() const
{
    // TODO Implement this
    return AccelerationProfile::Adaptive;
}

double DInputDevicePointer::accelerationSpeed() const
{
    // TODO Implement this
    return 1;
}

void DInputDevicePointer::setLeftHanded(bool leftHanded)
{
    // TODO Implement this
    return;
}

void DInputDevicePointer::setScrollMethod(ScrollMethod scrollMethod)
{
    // TODO Implement this
    return;
}

void DInputDevicePointer::setAccelerationProfile(AccelerationProfile accelerationProfile)
{
    // TODO Implement this
    return;
}

void DInputDevicePointer::setAccelerationSpeed(double accelerationSpeed)
{
    // TODO Implement this
    return;
}

DINPUTDEVICES_END_NAMESPACE
