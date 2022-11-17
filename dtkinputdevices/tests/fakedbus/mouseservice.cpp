// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "mouseservice.h"
#include <QtDBus>
DINPUTDEVICES_BEGIN_NAMESPACE

MouseService::MouseService(const QString &service, const QString &path, QObject *parent)
    : QObject(parent)
    , m_adaptiveAccelProfile(AdaptiveAccelProfileDefault)
    , m_disableTpad(DisableTpadDefault)
    , m_exist(ExistDefault)
    , m_leftHanded(LeftHandedDefault)
    , m_middleButtonEmulation(MiddleButtonEmulationDefault)
    , m_naturalScroll(NaturalScrollDefault)
    , m_motionAcceleration(MotionAccelerationDefault)
    , m_doubleClick(DoubleClickDefault)
    , m_dragThreshold(DragThresholdDefault)
    , m_deviceList(DeviceListDefault)
    , m_service(service)
    , m_path(path)
{
    registerService(m_service, m_path);
}

MouseService::~MouseService()
{
    unregisterService();
}

bool MouseService::registerService(const QString &service, const QString &path)
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

void MouseService::unregisterService()
{
    QDBusConnection connection = QDBusConnection::sessionBus();
    connection.unregisterObject(m_path);
    connection.unregisterService(m_service);
}

bool MouseService::AdaptiveAccelProfile() const
{
    return m_adaptiveAccelProfile;
}

bool MouseService::DisableTpad() const
{
    return m_disableTpad;
}

bool MouseService::Exist() const
{
    return m_exist;
}

bool MouseService::LeftHanded() const
{
    return m_leftHanded;
}

bool MouseService::MiddleButtonEmulation() const
{
    return m_middleButtonEmulation;
}

bool MouseService::NaturalScroll() const
{
    return m_naturalScroll;
}

double MouseService::MotionAcceleration() const
{
    return m_motionAcceleration;
}

qint32 MouseService::DoubleClick() const
{
    return m_doubleClick;
}

qint32 MouseService::DragThreshold() const
{
    return m_dragThreshold;
}

QString MouseService::DeviceList() const
{
    return m_deviceList;
}

void MouseService::SetAdaptiveAccelProfile(bool adaptive)
{
    m_adaptiveAccelProfile = adaptive;
    Q_EMIT this->AdaptiveAccelProfileChanged(adaptive);
}

void MouseService::SetDisableTpad(bool disable)
{
    m_disableTpad = disable;
    Q_EMIT this->DisableTpadChanged(disable);
}

void MouseService::SetLeftHanded(bool leftHanded)
{
    m_leftHanded = leftHanded;
    Q_EMIT this->LeftHandedChanged(leftHanded);
}

void MouseService::SetMiddleButtonEmulation(bool emulation)
{
    m_middleButtonEmulation = emulation;
    Q_EMIT this->MiddleButtonEmulationChanged(emulation);
}

void MouseService::SetNaturalScroll(bool naturalScroll)
{
    m_naturalScroll = naturalScroll;
    Q_EMIT this->NaturalScrollChanged(naturalScroll);
}

void MouseService::SetMotionAcceleration(double acceleration)
{
    m_motionAcceleration = acceleration;
    Q_EMIT this->MotionAccelerationChanged(acceleration);
}

void MouseService::SetDoubleClick(qint32 interval)
{
    m_doubleClick = interval;
    Q_EMIT this->DoubleClickChanged(interval);
}

void MouseService::SetDragThreshold(qint32 threshold)
{
    m_dragThreshold = threshold;
    Q_EMIT this->DragThresholdChanged(threshold);
}

void MouseService::Reset()
{
    m_adaptiveAccelProfile = AdaptiveAccelProfileDefault;
    m_disableTpad = DisableTpadDefault;
    m_exist = ExistDefault;
    m_leftHanded = LeftHandedDefault;
    m_middleButtonEmulation = MiddleButtonEmulationDefault;
    m_naturalScroll = NaturalScrollDefault;
    m_motionAcceleration = MotionAccelerationDefault;
    m_doubleClick = DoubleClickDefault;
    m_dragThreshold = DragThresholdDefault;
    m_deviceList = DeviceListDefault;
}

DINPUTDEVICES_END_NAMESPACE
