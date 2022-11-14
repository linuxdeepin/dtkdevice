// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DINPUTDEVICEKEYBOARD_P_H
#define DINPUTDEVICEKEYBOARD_P_H
#include "dinputdevicekeyboard.h"
#include "keyboardinterface.h"
DINPUTDEVICES_BEGIN_NAMESPACE
class DInputDeviceKeyboardPrivate : public QObject
{
    Q_OBJECT
public:
    DInputDeviceKeyboardPrivate(DInputDeviceKeyboard *q);
    ~DInputDeviceKeyboardPrivate() override;

private:
    DInputDeviceKeyboard *q_ptr;
    KeyboardInterface *m_keyboardInter;
    Q_DECLARE_PUBLIC(DInputDeviceKeyboard)
};
DINPUTDEVICES_END_NAMESPACE

#endif  // DINPUTDEVICEKEYBOARD_P_H
