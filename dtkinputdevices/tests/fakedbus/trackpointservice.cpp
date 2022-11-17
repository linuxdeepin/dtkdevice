// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "trackpointservice.h"
#include <QtDBus>

DINPUTDEVICES_BEGIN_NAMESPACE

TrackPointService::TrackPointService(const QString &service, const QString &path, QObject *parent)
    : QObject(parent)
    , m_exist(ExistDefault)
    , m_leftHanded(LeftHandedDefault)
    , m_middleButtonEnabled(MiddleButtonEnabledDefault)
    , m_wheelEmulation(WheelEmulationDefault)
    , m_wheelHorizScroll(WheelHorizScrollDefault)
    , m_motionAcceleration(MotionAccelerationDefault)
    , m_middleButtonTimeout(MiddleButtonTimeoutDefault)
    , m_wheelEmulationButton(WheelEmulationButtonDefault)
    , m_wheelEmulationTimeout(WheelEmulationTimeoutDefault)
    , m_deviceList(DeviceListDefault)
    , m_service(service)
    , m_path(path)
{
    registerService(m_service, m_path);
}

TrackPointService::~TrackPointService()
{
    unregisterService();
}

bool TrackPointService::registerService(const QString &service, const QString &path)
{
    QDBusConnection connection = QDBusConnection::sessionBus();
    if (!connection.registerService(service)) {
        QString errorMsg = connection.lastError().message();
        if (errorMsg.isEmpty())
            errorMsg = "maybe it's running";

        qWarning() << QString("Can't register the %1 service, %2.").arg(service).arg(errorMsg);
        return false;
    }
    if (!connection.registerObject(path, this, QDBusConnection::ExportAllContents)) {
        qWarning() << QString("Can't register %1 the D-Bus object.").arg(path);
        return false;
    }
    return true;
}

void TrackPointService::unregisterService()
{
    QDBusConnection connection = QDBusConnection::sessionBus();
    connection.unregisterObject(m_path);
    connection.unregisterService(m_service);
}

bool TrackPointService::Exist() const
{
    return m_exist;
}

bool TrackPointService::LeftHanded() const
{
    return m_leftHanded;
}

bool TrackPointService::MiddleButtonEnabled() const
{
    return m_middleButtonEnabled;
}

bool TrackPointService::WheelEmulation() const
{
    return m_wheelEmulation;
}

bool TrackPointService::WheelHorizScroll() const
{
    return m_wheelHorizScroll;
}

double TrackPointService::MotionAcceleration() const
{
    return m_motionAcceleration;
}

qint32 TrackPointService::MiddleButtonTimeout() const
{
    return m_middleButtonTimeout;
}

qint32 TrackPointService::WheelEmulationButton() const
{
    return m_wheelEmulationButton;
}

qint32 TrackPointService::WheelEmulationTimeout() const
{
    return m_wheelEmulationTimeout;
}

QString TrackPointService::DeviceList() const
{
    return m_deviceList;
}

void TrackPointService::SetLeftHanded(bool leftHanded)
{
    m_leftHanded = leftHanded;
    Q_EMIT this->LeftHandedChanged(leftHanded);
}

void TrackPointService::SetMiddleButtonEnabled(bool enabled)
{
    m_middleButtonEnabled = enabled;
    Q_EMIT this->MiddleButtonEnabledChanged(enabled);
}

void TrackPointService::SetWheelEmulation(bool emulation)
{
    m_wheelEmulation = emulation;
    Q_EMIT this->WheelEmulationChanged(emulation);
}

void TrackPointService::SetWheelHorizScroll(bool horizScroll)
{
    m_wheelHorizScroll = horizScroll;
    Q_EMIT this->WheelHorizScrollChanged(horizScroll);
}

void TrackPointService::SetMotionAcceleration(double acceleration)
{
    m_motionAcceleration = acceleration;
    Q_EMIT this->MotionAccelerationChanged(acceleration);
}

void TrackPointService::SetMiddleButtonTimeout(qint32 timeout)
{
    m_middleButtonTimeout = timeout;
    Q_EMIT this->MiddleButtonTimeoutChanged(timeout);
}

void TrackPointService::SetWheelEmulationButton(qint32 button)
{
    m_wheelEmulationButton = button;
    Q_EMIT this->WheelEmulationButtonChanged(button);
}

void TrackPointService::SetWheelEmulationTimeout(qint32 timeout)
{
    m_wheelEmulationTimeout = timeout;
    Q_EMIT this->WheelEmulationTimeoutChanged(timeout);
}

void TrackPointService::Reset()
{
    m_exist = ExistDefault;
    m_leftHanded = LeftHandedDefault;
    m_middleButtonEnabled = MiddleButtonEnabledDefault;
    m_wheelEmulation = WheelEmulationDefault;
    m_wheelHorizScroll = WheelHorizScrollDefault;
    m_motionAcceleration = MotionAccelerationDefault;
    m_middleButtonTimeout = MiddleButtonTimeoutDefault;
    m_wheelEmulationButton = WheelEmulationButtonDefault;
    m_wheelEmulationTimeout = WheelEmulationTimeoutDefault;
    m_deviceList = DeviceListDefault;
}

DINPUTDEVICES_END_NAMESPACE
