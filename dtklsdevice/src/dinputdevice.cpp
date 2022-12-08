// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dinputdevice.h"

#include <QDebug>

DLSDEVICE_BEGIN_NAMESPACE

class DInputDevicePrivate
{
public:
    explicit DInputDevicePrivate(DInputDevice *parent)
        : q_ptr(parent)
    {

    }

private:
    DInputDevice *q_ptr = nullptr;
};

DInputDevice::DInputDevice(QObject *parent)
    : QObject(parent)
    , d_ptr(new DInputDevicePrivate(this))
{
}

DInputDevice::~DInputDevice()
{
}

int DInputDevice::count()
{
    return 0;
}

QString DInputDevice::vendor(int index)
{
    return QString();
}

QString DInputDevice::model(int index)
{
    return QString();
}

QString DInputDevice::interface(int index)
{
    return QString();
}

QString DInputDevice::driver(int index)
{
    return QString();
}

DLSDEVICE_END_NAMESPACE
