// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dinputdevicemouse.h"
#include "dinputdevicemouse_p.h"
#include "dtkinputdevices_types.h"

DDEVICE_BEGIN_NAMESPACE

using DCORE_NAMESPACE::DError;
using DCORE_NAMESPACE::DExpected;
using DCORE_NAMESPACE::DUnexpected;

DInputDeviceMousePrivate::DInputDeviceMousePrivate(DInputDeviceMouse *q)
    : QObject(q)
    , q_ptr(q)
{
#ifdef USE_FAKE_INTERFACE
    const QString &Service = QStringLiteral("org.deepin.dtk.InputDevices");
#else
    const QString &Service = QStringLiteral("com.deepin.daemon.InputDevices");
#endif
    m_mouseInter = new MouseInterface(Service);
    connect(m_mouseInter, &MouseInterface::NaturalScrollChanged, q, &DInputDeviceMouse::naturalScrollChanged);
    connect(m_mouseInter, &MouseInterface::MiddleButtonEmulationChanged, q, &DInputDeviceMouse::middleButtonEmulationChanged);
}

DInputDeviceMousePrivate::~DInputDeviceMousePrivate()
{
    delete m_mouseInter;
}

DInputDeviceMouse::DInputDeviceMouse(QObject *parent)
    : DInputDevicePointer(parent)
    , d_ptr(new DInputDeviceMousePrivate(this))
{
}

DInputDeviceMouse::DInputDeviceMouse(const DeviceInfo &info, bool enabled)
    : DInputDevicePointer(info, enabled)
    , d_ptr(new DInputDeviceMousePrivate(this))
{
}

DInputDeviceMouse::~DInputDeviceMouse() = default;

bool DInputDeviceMouse::leftHanded() const
{
    Q_D(const DInputDeviceMouse);
    return d->m_mouseInter->LeftHanded();
}

void DInputDeviceMouse::setLeftHanded(bool leftHanded)
{
    Q_D(DInputDeviceMouse);
    d->m_mouseInter->SetLeftHanded(leftHanded);
}

ScrollMethod DInputDeviceMouse::scrollMethod() const
{
    return ScrollMethod::ScrollOnButtonDown;
}

void DInputDeviceMouse::setScrollMethod(ScrollMethod method)
{
    Q_UNUSED(method)
}

AccelerationProfile DInputDeviceMouse::accelerationProfile() const
{
    Q_D(const DInputDeviceMouse);
    if (d->m_mouseInter->AdaptiveAccelProfile()) {
        return AccelerationProfile::Adaptive;
    } else {
        return AccelerationProfile::Flat;
    }
}

void DInputDeviceMouse::setAccelerationProfile(AccelerationProfile profile)
{
    Q_D(DInputDeviceMouse);
    if (profile == AccelerationProfile::Adaptive) {
        d->m_mouseInter->SetAdaptiveAccelProfile(true);
    } else if (profile == AccelerationProfile::Flat) {
        d->m_mouseInter->SetAdaptiveAccelProfile(false);
    } else {
        qWarning() << "Cannot apply acceleration profile none to mouse.";
    }
}

double DInputDeviceMouse::accelerationSpeed() const
{
    Q_D(const DInputDeviceMouse);
    return d->m_mouseInter->MotionAcceleration();
}

void DInputDeviceMouse::setAccelerationSpeed(double speed)
{
    Q_D(DInputDeviceMouse);
    d->m_mouseInter->SetMotionAcceleration(speed);
}

bool DInputDeviceMouse::naturalScroll() const
{
    Q_D(const DInputDeviceMouse);
    return d->m_mouseInter->NaturalScroll();
}

bool DInputDeviceMouse::middleButtonEmulation() const
{
    Q_D(const DInputDeviceMouse);
    return d->m_mouseInter->MiddleButtonEmulation();
}

DExpected<void> DInputDeviceMouse::reset()
{
    Q_D(DInputDeviceMouse);
    auto result = d->m_mouseInter->Reset();
    if (!result.isValid()) {
        return DUnexpected<>{DError{result.error().type(), result.error().message()}};
    } else {
        return {};
    }
}

void DInputDeviceMouse::setNaturalScroll(bool naturalScroll)
{
    Q_D(DInputDeviceMouse);
    d->m_mouseInter->SetNaturalScroll(naturalScroll);
}

void DInputDeviceMouse::setMiddleButtonEmulation(bool middleButtonEmulation)
{
    Q_D(DInputDeviceMouse);
    d->m_mouseInter->SetMiddleButtonEmulation(middleButtonEmulation);
}

DDEVICE_END_NAMESPACE
