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

private:
    DInputDeviceManager *q_ptr;
    MouseInterface *m_mouseInter;
    TouchPadInterface *m_touchPadInter;
    TrackPointInterface *m_trackPointInter;
    WacomInterface *m_wacomInter;
    Q_DECLARE_PUBLIC(DInputDeviceManager)
};

DINPUTDEVICES_END_NAMESPACE
#endif