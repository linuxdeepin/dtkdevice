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
    connect(d->m_trackPointInter,
            &TrackPointInterface::MiddleButtonEnabledChanged,
            this,
            &DInputDeviceTrackPoint::middleButtonEnabledChanged);
    connect(d->m_trackPointInter,
            &TrackPointInterface::MiddleButtonTimeoutChanged,
            this,
            &DInputDeviceTrackPoint::middleButtonTimeoutChanged);
    connect(
        d->m_trackPointInter, &TrackPointInterface::WheelEmulationChanged, this, &DInputDeviceTrackPoint::wheelEmulationChanged);
    connect(d->m_trackPointInter,
            &TrackPointInterface::WheelEmulationButtonChanged,
            this,
            &DInputDeviceTrackPoint::wheelEmulationButtonChanged);
    connect(d->m_trackPointInter,
            &TrackPointInterface::WheelEmulationTimeoutChanged,
            this,
            &DInputDeviceTrackPoint::wheelEmulationTimeoutChanged);
    connect(d->m_trackPointInter,
            &TrackPointInterface::WheelHorizScrollChanged,
            this,
            &DInputDeviceTrackPoint::wheelHorizontalScrollChanged);
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

void DInputDeviceTrackPoint::enableMiddleButton(bool enabled)
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

DINPUTDEVICES_END_NAMESPACE