// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dinputdevicepointer.h"
#include "dinputdevicepointer_p.h"

DINPUTDEVICES_BEGIN_NAMESPACE

DInputDevicePointerPrivate::DInputDevicePointerPrivate(DInputDevicePointer *q)
    : q_ptr(q)
{
}

DInputDevicePointer::DInputDevicePointer(QObject *parent)
    : DInputDevice(parent)
    , d_ptr(new DInputDevicePointerPrivate(this))
{
}

DInputDevicePointer::DInputDevicePointer(const DeviceInfo &info, bool enabled)
    : DInputDevice(info, enabled)
    , d_ptr(new DInputDevicePointerPrivate(this))
{
}

DInputDevicePointer::~DInputDevicePointer() = default;

DINPUTDEVICES_END_NAMESPACE
