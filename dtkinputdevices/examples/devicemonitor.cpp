// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dinputdevicemanager.h"
#include <QCoreApplication>
#include <QObject>

DINPUTDEVICES_USE_NAMESPACE
int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    DInputDeviceManager manager;
    qDebug() << manager.deviceInfos();
    QObject::connect(&manager, &DInputDeviceManager::deviceAdded, &app, [=](const DeviceInfo &info) {
        qDebug() << "Device added.";
        qDebug() << info;
    });
    QObject::connect(&manager, &DInputDeviceManager::deviceRemoved, &app, [=](const DeviceInfo &info) {
        qDebug() << "Device removed.";
        qDebug() << info;
    });
    return app.exec();
}
