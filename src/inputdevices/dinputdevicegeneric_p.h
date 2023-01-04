// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DINPUTDEVICEGENERIC_P_H
#define DINPUTDEVICEGENERIC_P_H
#include "dinputdevicegeneric.h"

DDEVICE_BEGIN_NAMESPACE

class DInputDeviceGenericPrivate : public QObject
{
    Q_OBJECT
public:
    explicit DInputDeviceGenericPrivate(DInputDeviceGeneric *q);

private:
    quint32 m_id;
    QString m_name;
    DeviceType m_type;
    bool m_enabled;
    DInputDeviceGeneric *q_ptr;
    Q_DECLARE_PUBLIC(DInputDeviceGeneric)
};
DDEVICE_END_NAMESPACE

#endif
