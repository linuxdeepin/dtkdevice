// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dinputdevicemouse.h"
#include "dinputdevicemouse_p.h"

DINPUTDEVICES_BEGIN_NAMESPACE

using DCORE_NAMESPACE::DExpected;
using DCORE_NAMESPACE::DUnexpected;
using DCORE_NAMESPACE::DError;

DInputDeviceMousePrivate::DInputDeviceMousePrivate(DInputDeviceMouse *q):
    q_ptr(q)
{

}

DInputDeviceMouse::DInputDeviceMouse(QObject *parent):
    DInputDevicePointer(parent),
    d_ptr(new DInputDeviceMousePrivate(this))
{

}

DInputDeviceMouse::~DInputDeviceMouse() = default;

bool DInputDeviceMouse::naturalScroll() const
{
    //TODO Implement this
    return true;
}

bool DInputDeviceMouse::middleButtonEmulation() const
{
    //TODO Implement this
    return true;
}

DExpected<void> DInputDeviceMouse::reset()
{
    //TODO Implement this
    return {};
}

void DInputDeviceMouse::setNaturalScroll(bool naturalScroll)
{
    //TODO Implement this
    return ;
}

void DInputDeviceMouse::setMiddleButtonEmulation(bool middleButtonEmulation)
{
    //TODO Implement this
    return ;
}

DINPUTDEVICES_END_NAMESPACE
