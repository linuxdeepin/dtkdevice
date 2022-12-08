// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dnetdevice.h"

#include <QDebug>

DLSDEVICE_BEGIN_NAMESPACE

class DNetDevicePrivate
{
public:
    explicit DNetDevicePrivate(DNetDevice *parent)
        : q_ptr(parent)
    {

    }

private:
    DNetDevice *q_ptr = nullptr;
};

DNetDevice::DNetDevice(QObject *parent)
    : QObject(parent)
    , d_ptr(new DNetDevicePrivate(this))
{
}

DNetDevice::~DNetDevice()
{
}

int DNetDevice::count()
{
    return 0;
}

QString DNetDevice::vendor(int index)
{
    return QString();
}

QString DNetDevice::model(int index)
{
    return QString();
}

QString DNetDevice::type(int index)
{
    return QString();
}

QString DNetDevice::macAddress(int index)
{
    return QString();
}

QString DNetDevice::driver(int index)
{
    return QString();
}

QString DNetDevice::speed(int index)
{
    return QString();
}

QString DNetDevice::status(int index)
{
    return QString();
}

DInetAddr4 DNetDevice::inetAddr4(int index)
{
    return DInetAddr4();
}

DInetAddr6 DNetDevice::inetAddr6(int index)
{
    return DInetAddr6();
}

DNetifInfo DNetDevice::netifInfo(int index)
{
    return DNetifInfo();
}

QString DNetDevice::portStatus(int index, int port)
{
    return QString();
}

QList<int> DNetDevice::applicationPorts(int pid)
{
    return QList<int>();
}


DLSDEVICE_END_NAMESPACE
