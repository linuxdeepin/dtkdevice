// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dcpudevice.h"

#include <QDebug>

DLSDEVICE_BEGIN_NAMESPACE

class DCpuDevicePrivate
{
public:
    explicit DCpuDevicePrivate(DCpuDevice *parent)
        : q_ptr(parent)
    {

    }

private:
    DCpuDevice *q_ptr = nullptr;
};

DCpuDevice::DCpuDevice(QObject *parent)
    : QObject(parent)
    , d_ptr(new DCpuDevicePrivate(this))
{
}

DCpuDevice::~DCpuDevice()
{
}

int DCpuDevice::physicalCount()
{
    return 0;
}

int DCpuDevice::coreCount(int physicalID)
{
    return 0;
}

int DCpuDevice::threadCount(int physicalID, int coreID)
{
    return 0;
}

int DCpuDevice::physicalID(int processorID)
{
    return -1;
}

int DCpuDevice::coreID(int processorID)
{
    return -1;
}

QString DCpuDevice::architecture(int physicalID)
{
    return QString();
}

QString DCpuDevice::vendor(int physicalID)
{
    return QString();
}

QString DCpuDevice::model(int physicalID)
{
    return QString();
}

QString DCpuDevice::minFreq(int processorID)
{
    return QString();
}

QString DCpuDevice::maxFreq(int processorID)
{
    return QString();
}

QString DCpuDevice::cache(int processorID, QString type)
{
    return QString();
}

QString DCpuDevice::flags(int processorID)
{
    return QString();
}

QString DCpuDevice::stepping(int processorID)
{
    return QString();
}

QString DCpuDevice::family(int processorID)
{
    return QString();
}

QString DCpuDevice::bogoMIPS(int processorID)
{
    return QString();
}

QString DCpuDevice::temperature(int physicalID)
{
    return QString();
}

QString DCpuDevice::currentFreq(int processorID)
{
    return QString();
}

DCpuStat DCpuDevice::stat()
{

}

DCpuUsage DCpuDevice::usage()
{

}

DCpuStat DCpuDevice::stat(int processorID)
{
    return DCpuStat();
}

DCpuUsage DCpuDevice::usage(int processorID)
{
    return DCpuUsage();
}

DLSDEVICE_END_NAMESPACE
