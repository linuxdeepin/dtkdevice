// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dinputdevicesetting.h"
#include "dinputdevicesetting_p.h"

DINPUTDEVICES_BEGIN_NAMESPACE
DInputDeviceSettingPrivate::DInputDeviceSettingPrivate(DInputDeviceSetting *q)
    : QObject(q)
    , q_ptr(q)
{
}

DInputDeviceSettingPrivate::~DInputDeviceSettingPrivate() {}

DInputDeviceSetting::DInputDeviceSetting(QObject *parent)
    : QObject(parent)
    , d_ptr(new DInputDeviceSettingPrivate(this))
{
}

DInputDeviceSetting::~DInputDeviceSetting() {}
DINPUTDEVICES_END_NAMESPACE