// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dinputdevicemanager.h"
#include "dinputdevicemanager_p.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include "dinputdevicemouse.h"
#include "dinputdevicesetting.h"
#include "dinputdevicetouchpad.h"

DINPUTDEVICES_BEGIN_NAMESPACE
DInputDeviceManagerPrivate::DInputDeviceManagerPrivate(DInputDeviceManager *q)
    : q_ptr(q)
{
#ifdef USE_FAKE_INTERFACE
    const QString &Service = QStringLiteral("org.deepin.dtk.InputDevices");
#else
    const QString &Service = QStringLiteral("com.deepin.daemon.InputDevices");
#endif
    m_mouseInter = new MouseInterface(Service);
    m_touchPadInter = new TouchPadInterface(Service);
    m_trackPointInter = new TrackPointInterface(Service);
    m_wacomInter = new WacomInterface(Service);
}

DInputDeviceManagerPrivate::~DInputDeviceManagerPrivate()
{
    delete m_mouseInter;
    delete m_touchPadInter;
    delete m_trackPointInter;
    delete m_wacomInter;
}

DInputDeviceManager::DInputDeviceManager(QObject *parent)
    : QObject(parent)
    , d_ptr(new DInputDeviceManagerPrivate(this))
{
}

QList<DeviceInfo> DInputDeviceManager::deviceInfos() const
{
    Q_D(const DInputDeviceManager);
    QList<DeviceInfo> infos;
    DeviceInfo info;
    if (d->m_mouseInter->Exist()) {
        info.type = DeviceType::Mouse;
        QString deviceList = d->m_mouseInter->DeviceList();
        QJsonParseError parseErr;
        auto rootDoc = QJsonDocument::fromJson(deviceList.toLocal8Bit(), &parseErr);
        if (parseErr.error != QJsonParseError::NoError) {
            qWarning() << "Can't parse deviceList!";
        } else {
            auto array = rootDoc.array();
            foreach (const auto &device, array) {
                info.id = device.toObject().value("id").toInt();
                info.name = device.toObject().value("name").toString();
                infos << info;
            }
        }
    }
    if (d->m_touchPadInter->Exist()) {
        info.type = DeviceType::TouchPad;
        QString deviceList = d->m_touchPadInter->DeviceList();
        QJsonParseError parseErr;
        auto rootDoc = QJsonDocument::fromJson(deviceList.toLocal8Bit(), &parseErr);
        if (parseErr.error != QJsonParseError::NoError) {
            qWarning() << "Can't parse deviceList!";
        } else {
            auto array = rootDoc.array();
            foreach (const auto &device, array) {
                info.id = device.toObject().value("id").toInt();
                info.name = device.toObject().value("name").toString();
                infos << info;
            }
        }
    }
    if (d->m_trackPointInter->Exist()) {
        info.type = DeviceType::TrackPoint;
        QString deviceList = d->m_trackPointInter->DeviceList();
        QJsonParseError parseErr;
        auto rootDoc = QJsonDocument::fromJson(deviceList.toLocal8Bit(), &parseErr);
        if (parseErr.error != QJsonParseError::NoError) {
            qWarning() << "Can't parse deviceList!";
        } else {
            auto array = rootDoc.array();
            foreach (const auto &device, array) {
                info.id = device.toObject().value("id").toInt();
                info.name = device.toObject().value("name").toString();
                infos << info;
            }
        }
    }
    if (d->m_wacomInter->Exist()) {
        info.type = DeviceType::Tablet;
        QString deviceList = d->m_wacomInter->DeviceList();
        QJsonParseError parseErr;
        auto rootDoc = QJsonDocument::fromJson(deviceList.toLocal8Bit(), &parseErr);
        if (parseErr.error != QJsonParseError::NoError) {
            qWarning() << "Can't parse deviceList!";
        } else {
            auto array = rootDoc.array();
            foreach (const auto &device, array) {
                info.id = device.toObject().value("id").toInt();
                info.name = device.toObject().value("name").toString();
                infos << info;
            }
        }
    }
    return infos;
}

DExpected<DInputDevicePtr> DInputDeviceManager::createDevice(const DeviceInfo &info)
{
    switch (info.type) {
        case DeviceType::Mouse:
            return DInputDevicePtr{new DInputDeviceMouse};
        case DeviceType::TouchPad:
            return DInputDevicePtr{new DInputDeviceTouchPad};
        case DeviceType::Tablet:
        case DeviceType::TrackPoint:
        case DeviceType::Keyboard:
        case DeviceType::Generic:
            return DInputDevicePtr{new DInputDevice};
        default:
            return {};
    }
}
DExpected<DInputSettingPtr> DInputDeviceManager::setting()
{
    return DInputSettingPtr{new DInputDeviceSetting};
}
DINPUTDEVICES_END_NAMESPACE