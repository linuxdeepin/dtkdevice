// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DINPUTDEVICETABLET_P_H
#define DINPUTDEVICETABLET_P_H
#include "dinputdevicetablet.h"
#include "wacominterface.h"
DINPUTDEVICES_BEGIN_NAMESPACE
class DInputDeviceTabletPrivate : public QObject
{
    Q_OBJECT
public:
    DInputDeviceTabletPrivate(DInputDeviceTablet *q);
    ~DInputDeviceTabletPrivate() override;

private:
    DInputDeviceTablet *q_ptr;
    WacomInterface *m_wacomInter;
    Q_DECLARE_PUBLIC(DInputDeviceTablet)
};
DINPUTDEVICES_END_NAMESPACE
#endif  // DINPUTDEVICETABLET_P_H