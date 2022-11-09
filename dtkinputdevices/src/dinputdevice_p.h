// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DINPUTDEVICE_P_H
#define DINPUTDEVICE_P_H
#include "dinputdevice.h"

DINPUTDEVICES_BEGIN_NAMESPACE

class DInputDevicePrivate : public QObject
{
    Q_OBJECT
public:
    explicit DInputDevicePrivate(DInputDevice *q);

private:
    quint32 m_id;
    QString m_name;
    DeviceType m_type;
    bool m_enabled;
    DInputDevice *q_ptr;
    Q_DECLARE_PUBLIC(DInputDevice)
};
DINPUTDEVICES_END_NAMESPACE

#endif