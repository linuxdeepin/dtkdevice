// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DINPUTDEVICESETTING_P_H
#define DINPUTDEVICESETTING_P_H
#include "dinputdevicesetting.h"
DINPUTDEVICES_BEGIN_NAMESPACE
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
DINPUTDEVICES_END_NAMESPACE
#endif
