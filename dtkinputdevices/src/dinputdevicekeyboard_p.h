// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DINPUTDEVICEKEYBOARD_P_H
#define DINPUTDEVICEKEYBOARD_P_H
#include "dinputdevicekeyboard.h"
DINPUTDEVICES_BEGIN_NAMESPACE
class DInputDeviceKeyboardPrivate : public QObject
{
    Q_OBJECT
public:
    DInputDeviceKeyboardPrivate(DInputDeviceKeyboard *q);
    ~DInputDeviceKeyboardPrivate() override;

private:
    DInputDeviceKeyboard *q_ptr;
    Q_DECLARE_PUBLIC(DInputDeviceKeyboard)
};
DINPUTDEVICES_END_NAMESPACE

#endif  // DINPUTDEVICEKEYBOARD_P_H
