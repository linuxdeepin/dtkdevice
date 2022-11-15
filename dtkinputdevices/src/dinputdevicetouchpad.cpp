// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dinputdevicetouchpad.h"
#include "dinputdevicetouchpad_p.h"

DINPUTDEVICES_BEGIN_NAMESPACE

using DCORE_NAMESPACE::DExpected;

DInputDeviceTouchPadPrivate::DInputDeviceTouchPadPrivate(DInputDeviceTouchPad *q)
    : q_ptr(q)
{
}

DInputDeviceTouchPad::DInputDeviceTouchPad(DInputDevicePointer *parent)
    : DInputDevicePointer(parent)
    , d_ptr(new DInputDeviceTouchPadPrivate(this))
{
}

DInputDeviceTouchPad::DInputDeviceTouchPad(const DeviceInfo &info, bool enabled)
    : DInputDevicePointer(info, enabled)
    , d_ptr(new DInputDeviceTouchPadPrivate(this))
{
}

DInputDeviceTouchPad::~DInputDeviceTouchPad() = default;

bool DInputDeviceTouchPad::disableWhileTyping() const
{
    // TODO Implement this
    return true;
}

bool DInputDeviceTouchPad::naturalScroll() const
{
    // TODO Implement this
    return true;
}

bool DInputDeviceTouchPad::tapToClick() const
{
    // TODO Implement this
    return true;
}

DExpected<void> DInputDeviceTouchPad::reset()
{
    // TODO Implement this
    return {};
}

DExpected<void> DInputDeviceTouchPad::enable(bool enabled)
{
    // TODO Implement this
    return {};
}

void DInputDeviceTouchPad::setDisableWhileTyping(bool disableWhileTyping)
{
    // TODO Implement this
    return;
}

void DInputDeviceTouchPad::setNaturalScroll(bool naturalScroll)
{
    // TODO Implement this
    return;
}

void DInputDeviceTouchPad::setTapToClick(bool tapToClick)
{
    // TODO Implement this
    return;
}

DINPUTDEVICES_END_NAMESPACE
