// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dprocessdevice.h"

#include <QDebug>

DLSDEVICE_BEGIN_NAMESPACE

class DProcessDevicePrivate
{
public:
    explicit DProcessDevicePrivate(DProcessDevice *parent)
        : q_ptr(parent)
    {

    }

private:
    DProcessDevice *q_ptr = nullptr;
};

DProcessDevice::DProcessDevice(QObject *parent)
    : QObject(parent)
    , d_ptr(new DProcessDevicePrivate(this))
{
}

DProcessDevice::~DProcessDevice()
{
}

QList<pid_t> DProcessDevice::allPids()
{
    return QList<pid_t>();
}

QHash<QString, QString> DProcessDevice::environment(pid_t pid)
{
    return QHash<QString, QString>();
}

QString DProcessDevice::groupName(const gid_t &gid)
{
    return QString();
}

DProcessBaseInfo DProcessDevice::baseInfo(pid_t pid)
{
    return DProcessBaseInfo();
}

DProcessMemoryInfo DProcessDevice::memoryInfo(pid_t pid)
{
    return DProcessMemoryInfo();
}

DProcessIOInfo DProcessDevice::ioInfo(pid_t pid)
{
    return DProcessIOInfo();
}

DProcessNetworkInfo DProcessDevice::networkInfo(pid_t pid)
{
    return DProcessNetworkInfo();
}

DProcessStatus DProcessDevice::status(pid_t pid)
{
    return DProcessStatus();
}

DLSDEVICE_END_NAMESPACE
