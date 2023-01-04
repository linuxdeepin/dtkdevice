// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DINPUTDEVICETRACKPOINT_P_H
#define DINPUTDEVICETRACKPOINT_P_H
#include "dinputdevicetrackpoint.h"
#include "trackpointinterface.h"
DDEVICE_BEGIN_NAMESPACE
class DInputDeviceTrackPointPrivate : public QObject
{
    Q_OBJECT

public:
    DInputDeviceTrackPointPrivate(DInputDeviceTrackPoint *q);
    ~DInputDeviceTrackPointPrivate() override;

    void initSignals();

private:
    DInputDeviceTrackPoint *q_ptr;
    TrackPointInterface *m_trackPointInter;
    Q_DECLARE_PUBLIC(DInputDeviceTrackPoint)
};

DDEVICE_END_NAMESPACE

#endif  // DINPUTDEVICETRACKPOINT_P_H
