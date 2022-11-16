// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dinputdevicetouchpad.h"
#include "dinputdevicetouchpad_p.h"
#include "touchpadinterface.h"

DINPUTDEVICES_BEGIN_NAMESPACE

using DCORE_NAMESPACE::DError;
using DCORE_NAMESPACE::DExpected;
using DCORE_NAMESPACE::DUnexpected;

DInputDeviceTouchPadPrivate::DInputDeviceTouchPadPrivate(DInputDeviceTouchPad *q)
    : QObject(q)
    , q_ptr(q)
{
#ifdef USE_FAKE_INTERFACE
    const QString &Service = QStringLiteral("org.deepin.dtk.InputDevices");
#else
    const QString &Service = QStringLiteral("com.deepin.daemon.InputDevices");
#endif
    m_touchPadInter = new TouchPadInterface(Service);
    connect(m_touchPadInter, &TouchPadInterface::DisableIfTypingChanged, q, &DInputDeviceTouchPad::disableWhileTypingChanged);
    connect(m_touchPadInter, &TouchPadInterface::NaturalScrollChanged, q, &DInputDeviceTouchPad::naturalScrollChanged);
    connect(m_touchPadInter, &TouchPadInterface::TapClickChanged, q, &DInputDeviceTouchPad::tapToClickChanged);
}

DInputDeviceTouchPadPrivate::~DInputDeviceTouchPadPrivate()
{
    delete m_touchPadInter;
}

DInputDeviceTouchPad::DInputDeviceTouchPad(DInputDevicePointer *parent)
    : DInputDevicePointer(parent)
    , d_ptr(new DInputDeviceTouchPadPrivate(this))
{
}

DInputDeviceTouchPad::DInputDeviceTouchPad(const DeviceInfo &info, bool enabled)
    : DInputDevicePointer(info, enabled)
    , d_ptr(new DInputDeviceTouchPadPrivate(this))
{
}

DInputDeviceTouchPad::~DInputDeviceTouchPad() = default;

bool DInputDeviceTouchPad::disableWhileTyping() const
{
    Q_D(const DInputDeviceTouchPad);
    return d->m_touchPadInter->DisableIfTyping();
}

bool DInputDeviceTouchPad::naturalScroll() const
{
    Q_D(const DInputDeviceTouchPad);
    return d->m_touchPadInter->NaturalScroll();
}

bool DInputDeviceTouchPad::tapToClick() const
{
    Q_D(const DInputDeviceTouchPad);
    return d->m_touchPadInter->TapClick();
}

DExpected<void> DInputDeviceTouchPad::reset()
{
    Q_D(DInputDeviceTouchPad);
    auto result = d->m_touchPadInter->Reset();
    result.waitForFinished();
    if (!result.isValid()) {
        return DUnexpected{DError{result.error().type(), result.error().message()}};
    } else {
        return {};
    }
}

DExpected<void> DInputDeviceTouchPad::enable(bool enabled)
{
    setEnabled(enabled);
    Q_D(DInputDeviceTouchPad);
    d->m_touchPadInter->SetTPadEnable(enabled);
    return {};
}

void DInputDeviceTouchPad::setDisableWhileTyping(bool disabled)
{
    Q_D(DInputDeviceTouchPad);
    d->m_touchPadInter->SetDisableIfTyping(disabled);
}

void DInputDeviceTouchPad::setNaturalScroll(bool naturalScroll)
{
    Q_D(DInputDeviceTouchPad);
    d->m_touchPadInter->SetNaturalScroll(naturalScroll);
}

void DInputDeviceTouchPad::setTapToClick(bool tapToClick)
{
    Q_D(DInputDeviceTouchPad);
    d->m_touchPadInter->SetTapClick(tapToClick);
}

bool DInputDeviceTouchPad::leftHanded() const
{
    Q_D(const DInputDeviceTouchPad);
    return d->m_touchPadInter->LeftHanded();
}

void DInputDeviceTouchPad::setLeftHanded(bool leftHanded)
{
    Q_D(DInputDeviceTouchPad);
    d->m_touchPadInter->SetLeftHanded(leftHanded);
}

ScrollMethod DInputDeviceTouchPad::scrollMethod() const
{
    Q_D(const DInputDeviceTouchPad);
    if (d->m_touchPadInter->EdgeScroll()) {
        return ScrollMethod::ScrollEdge;
    } else if (d->m_touchPadInter->VertScroll()) {
        return ScrollMethod::ScrollTwoFinger;
    } else {
        return ScrollMethod::NoScroll;
    }
}

void DInputDeviceTouchPad::setScrollMethod(ScrollMethod method)
{
    Q_D(DInputDeviceTouchPad);
    switch (method) {
        case ScrollMethod::ScrollEdge:
            d->m_touchPadInter->SetEdgeScroll(true);
            d->m_touchPadInter->SetVertScroll(false);
            break;
        case ScrollMethod::ScrollTwoFinger:
            d->m_touchPadInter->SetEdgeScroll(false);
            d->m_touchPadInter->SetVertScroll(true);
            break;
        case ScrollMethod::ScrollOnButtonDown:
            break;
        case ScrollMethod::NoScroll:
            d->m_touchPadInter->SetEdgeScroll(false);
            d->m_touchPadInter->SetVertScroll(false);
        default:
            Q_UNREACHABLE();
    }
}

AccelerationProfile DInputDeviceTouchPad::accelerationProfile() const
{
    return AccelerationProfile::Na;
}

void DInputDeviceTouchPad::setAccelerationProfile(AccelerationProfile profile)
{
    Q_UNUSED(profile)
}

double DInputDeviceTouchPad::accelerationSpeed() const
{
    return 0;
}

void DInputDeviceTouchPad::setAccelerationSpeed(double speed)
{
    Q_UNUSED(speed)
}
DINPUTDEVICES_END_NAMESPACE
