// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DINPUTDEVICESETTING_P_H
#define DINPUTDEVICESETTING_P_H
#include "dinputdevicesetting.h"
DINPUTDEVICES_BEGIN_NAMESPACE
class DInputDeviceSettingPrivate : public QObject
{
    Q_OBJECT
public:
    explicit DInputDeviceSettingPrivate(DInputDeviceSetting *q);
    ~DInputDeviceSettingPrivate() override;

private:
    DInputDeviceSetting *q_ptr;
    Q_DECLARE_PUBLIC(DInputDeviceSetting)
};
DINPUTDEVICES_END_NAMESPACE
#endif