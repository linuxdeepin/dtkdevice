// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DDEVICEETTING_P_H
#define DDEVICEETTING_P_H
#include "dinputdevicesetting.h"
DDEVICE_BEGIN_NAMESPACE
class InputDevicesInterface;
class KeyboardInterface;
class MouseInterface;
class WacomInterface;

class DInputDeviceSettingPrivate : public QObject
{
    Q_OBJECT
public:
    explicit DInputDeviceSettingPrivate(DInputDeviceSetting *q);
    ~DInputDeviceSettingPrivate() override;

private:
    InputDevicesInterface *m_inter;
    KeyboardInterface *m_keyboardInter;
    MouseInterface *m_mouseInter;
    WacomInterface *m_wacomInter;
    DInputDeviceSetting *q_ptr;
    Q_DECLARE_PUBLIC(DInputDeviceSetting)
};
DDEVICE_END_NAMESPACE
#endif
