// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dinputdevicekeyboard.h"
#include "dinputdevicekeyboard_p.h"
#include "dtkdevice_global.h"
DDEVICE_BEGIN_NAMESPACE

DInputDeviceKeyboardPrivate::DInputDeviceKeyboardPrivate(DInputDeviceKeyboard *q)
    : QObject(q)
    , q_ptr(q)
{
}

DInputDeviceKeyboardPrivate::~DInputDeviceKeyboardPrivate() = default;

DInputDeviceKeyboard::DInputDeviceKeyboard(QObject *parent)
    : DInputDeviceGeneric(parent)
    , d_ptr(new DInputDeviceKeyboardPrivate(this))
{
}

DInputDeviceKeyboard::DInputDeviceKeyboard(const DeviceInfo &info, bool enabled)
    : DInputDeviceGeneric(info, enabled)
    , d_ptr(new DInputDeviceKeyboardPrivate(this))
{
}

DExpected<void> DInputDeviceKeyboard::reset()
{
    return {};
}

DInputDeviceKeyboard::~DInputDeviceKeyboard() = default;
DDEVICE_END_NAMESPACE
