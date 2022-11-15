// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DINPUTDEVICEMANAGER_P_H
#define DINPUTDEVICEMANAGER_P_H

#include "dinputdevicemanager.h"
#include "mouseinterface.h"
#include "touchpadinterface.h"
#include "trackpointinterface.h"
#include "wacominterface.h"

DINPUTDEVICES_BEGIN_NAMESPACE
class DInputDeviceManagerPrivate : public QObject
{
    Q_OBJECT
public:
    explicit DInputDeviceManagerPrivate(DInputDeviceManager *q);
    ~DInputDeviceManagerPrivate() override;
    void initialize();
    void initializeDeviceInfos();
    void initializeSignals();
    void addDevice(const DeviceInfo &info);
    void removeDevice(const DeviceInfo &info);
    void removeDeviceById(quint32 id);
    template <DeviceType deviceType> void handleDeviceChanged(const QString &deviceList);

Q_SIGNALS:
    void deviceAdded(const DeviceInfo &device);
    void deviceRemoved(const DeviceInfo &device);

private:
    MouseInterface *m_mouseInter;
    TouchPadInterface *m_touchPadInter;
    TrackPointInterface *m_trackPointInter;
    WacomInterface *m_wacomInter;
    QList<DeviceInfo> m_deviceInfos;
    QMap<DeviceType, QList<quint32>> m_idMap;
    DInputDeviceManager *q_ptr;
    Q_DECLARE_PUBLIC(DInputDeviceManager)
};

DINPUTDEVICES_END_NAMESPACE
#endif
