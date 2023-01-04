// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dinputdevicepointer.h"
#include "dinputdevicepointer_p.h"

DDEVICE_BEGIN_NAMESPACE

DInputDevicePointerPrivate::DInputDevicePointerPrivate(DInputDevicePointer *q)
    : q_ptr(q)
{
}

DInputDevicePointer::DInputDevicePointer(QObject *parent)
    : DInputDeviceGeneric(parent)
    , d_ptr(new DInputDevicePointerPrivate(this))
{
}

DInputDevicePointer::DInputDevicePointer(const DeviceInfo &info, bool enabled)
    : DInputDeviceGeneric(info, enabled)
    , d_ptr(new DInputDevicePointerPrivate(this))
{
}

DInputDevicePointer::~DInputDevicePointer() = default;

DDEVICE_END_NAMESPACE
