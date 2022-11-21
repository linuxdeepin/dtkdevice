// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dinputdevicetrackpoint.h"
#include "dinputdevicetrackpoint_p.h"

DINPUTDEVICES_BEGIN_NAMESPACE
using DCORE_NAMESPACE::DError;
using DCORE_NAMESPACE::DUnexpected;
DInputDeviceTrackPoint::DInputDeviceTrackPoint(QObject *parent)
    : DInputDevicePointer(parent)
    , d_ptr(new DInputDeviceTrackPointPrivate(this))
{
    Q_D(DInputDeviceTrackPoint);
    d->initSignals();
}

DInputDeviceTrackPoint::DInputDeviceTrackPoint(const DeviceInfo &info, bool enabled)
    : DInputDevicePointer(info, enabled)
    , d_ptr(new DInputDeviceTrackPointPrivate(this))
{
    Q_D(DInputDeviceTrackPoint);
    d->initSignals();
}

DInputDeviceTrackPoint::~DInputDeviceTrackPoint() = default;

DInputDeviceTrackPointPrivate::DInputDeviceTrackPointPrivate(DInputDeviceTrackPoint *q)
    : QObject(q)
    , q_ptr(q)
{
#ifdef USE_FAKE_INTERFACE
    const QString &Service = QStringLiteral("org.deepin.dtk.InputDevices");
#else
    const QString &Service = QStringLiteral("com.deepin.daemon.InputDevices");
#endif
    m_trackPointInter = new TrackPointInterface(Service);
}

void DInputDeviceTrackPointPrivate::initSignals()
{
    Q_Q(DInputDeviceTrackPoint);
    connect(m_trackPointInter,
            &TrackPointInterface::MiddleButtonEnabledChanged,
            q,
            &DInputDeviceTrackPoint::middleButtonEnabledChanged);
    connect(m_trackPointInter,
            &TrackPointInterface::MiddleButtonTimeoutChanged,
            q,
            &DInputDeviceTrackPoint::middleButtonTimeoutChanged);
    connect(m_trackPointInter, &TrackPointInterface::WheelEmulationChanged, q, &DInputDeviceTrackPoint::wheelEmulationChanged);
    connect(m_trackPointInter,
            &TrackPointInterface::WheelEmulationButtonChanged,
            q,
            &DInputDeviceTrackPoint::wheelEmulationButtonChanged);
    connect(m_trackPointInter,
            &TrackPointInterface::WheelEmulationTimeoutChanged,
            q,
            &DInputDeviceTrackPoint::wheelEmulationTimeoutChanged);
    connect(m_trackPointInter,
            &TrackPointInterface::WheelHorizScrollChanged,
            q,
            &DInputDeviceTrackPoint::wheelHorizontalScrollChanged);
}

DInputDeviceTrackPointPrivate::~DInputDeviceTrackPointPrivate()
{
    delete m_trackPointInter;
}

bool DInputDeviceTrackPoint::middleButtonEnabled() const
{
    Q_D(const DInputDeviceTrackPoint);
    return d->m_trackPointInter->MiddleButtonEnabled();
}

qint32 DInputDeviceTrackPoint::middleButtonTimeout() const
{
    Q_D(const DInputDeviceTrackPoint);
    return d->m_trackPointInter->MiddleButtonTimeout();
}

bool DInputDeviceTrackPoint::wheelEmulation() const
{
    Q_D(const DInputDeviceTrackPoint);
    return d->m_trackPointInter->WheelEmulation();
}

qint32 DInputDeviceTrackPoint::wheelEmulationButton() const
{
    Q_D(const DInputDeviceTrackPoint);
    return d->m_trackPointInter->WheelEmulationButton();
}

qint32 DInputDeviceTrackPoint::wheelEmulationTimeout() const
{
    Q_D(const DInputDeviceTrackPoint);
    return d->m_trackPointInter->WheelEmulationTimeout();
}

bool DInputDeviceTrackPoint::wheelHorizontalScroll() const
{
    Q_D(const DInputDeviceTrackPoint);
    return d->m_trackPointInter->WheelHorizScroll();
}

void DInputDeviceTrackPoint::setMiddleButtonEnabled(bool enabled)
{
    Q_D(DInputDeviceTrackPoint);
    d->m_trackPointInter->SetMiddleButtonEnabled(enabled);
}

void DInputDeviceTrackPoint::setMiddleButtonTimeout(qint32 timeout)
{
    Q_D(DInputDeviceTrackPoint);
    d->m_trackPointInter->SetMiddleButtonTimeout(timeout);
}

void DInputDeviceTrackPoint::setWheelEmulation(bool emulation)
{
    Q_D(DInputDeviceTrackPoint);
    d->m_trackPointInter->SetWheelEmulation(emulation);
}

void DInputDeviceTrackPoint::setWheelEmulationButton(qint32 emulationButton)
{
    Q_D(DInputDeviceTrackPoint);
    d->m_trackPointInter->SetWheelEmulationButton(emulationButton);
}

void DInputDeviceTrackPoint::setWheelEmulationTimeout(qint32 timeout)
{
    Q_D(DInputDeviceTrackPoint);
    d->m_trackPointInter->SetWheelEmulationTimeout(timeout);
}

void DInputDeviceTrackPoint::setWheelHorizontalScroll(bool horizontal)
{
    Q_D(DInputDeviceTrackPoint);
    d->m_trackPointInter->SetWheelHorizScroll(horizontal);
}

DExpected<void> DInputDeviceTrackPoint::reset()
{
    Q_D(DInputDeviceTrackPoint);
    auto reply = d->m_trackPointInter->Reset();
    reply.waitForFinished();
    if (!reply.isValid()) {
        return DUnexpected{DError{reply.error().type(), reply.error().message()}};
    } else {
        return {};
    }
}

bool DInputDeviceTrackPoint::leftHanded() const
{
    Q_D(const DInputDeviceTrackPoint);
    return d->m_trackPointInter->LeftHanded();
}

void DInputDeviceTrackPoint::setLeftHanded(bool leftHanded)
{
    Q_D(DInputDeviceTrackPoint);
    d->m_trackPointInter->SetLeftHanded(leftHanded);
}

AccelerationProfile DInputDeviceTrackPoint::accelerationProfile() const
{
    // TODO(asterwyx): Here we cannot acquire the profile using dde-daemon
    return AccelerationProfile::Adaptive;
}

void DInputDeviceTrackPoint::setAccelerationProfile(AccelerationProfile profile)
{
    Q_UNUSED(profile)
}

ScrollMethod DInputDeviceTrackPoint::scrollMethod() const
{
    return ScrollMethod::ScrollOnButtonDown;
}

void DInputDeviceTrackPoint::setScrollMethod(ScrollMethod method)
{
    Q_UNUSED(method)
}

double DInputDeviceTrackPoint::accelerationSpeed() const
{
    Q_D(const DInputDeviceTrackPoint);
    return d->m_trackPointInter->MotionAcceleration();
}

void DInputDeviceTrackPoint::setAccelerationSpeed(double speed)
{
    Q_D(DInputDeviceTrackPoint);
    d->m_trackPointInter->SetMotionAcceleration(speed);
}
DINPUTDEVICES_END_NAMESPACE
