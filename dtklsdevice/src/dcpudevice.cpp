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

int DCpuDevice::coreCount(const int &physicalID)
{
    return 0;
}

int DCpuDevice::threadCount(const int &physicalID, const int &coreID)
{
    return 0;
}

int DCpuDevice::physicalID(const int &processorID)
{
    return -1;
}

int DCpuDevice::coreID(const int &processorID)
{
    return -1;
}

QString DCpuDevice::architecture(const int &physicalID)
{
    return QString();
}

QString DCpuDevice::vendor(const int &physicalID)
{
    return QString();
}

QString DCpuDevice::model(const int &physicalID)
{
    return QString();
}

QString DCpuDevice::minFreq(const int &processorID)
{
    return QString();
}

QString DCpuDevice::maxFreq(const int &processorID)
{
    return QString();
}

QString DCpuDevice::currentFreq(const int &processorID)
{
    return QString();
}

DCpuStat DCpuDevice::stat(const int &processorID)
{
    return DCpuStat();
}

DCpuUsage DCpuDevice::usage(const int &processorID)
{
    return DCpuUsage();
}

QString DCpuDevice::cache(const int &processorID, QString type)
{
    return QString();
}

QString DCpuDevice::flags(const int &processorID)
{
    return QString();
}

QString DCpuDevice::stepping(const int &processorID)
{
    return QString();
}

QString DCpuDevice::family(const int &processorID)
{
    return QString();
}

QString DCpuDevice::bogoMIPS(const int &processorID)
{
    return QString();
}

DLSDEVICE_END_NAMESPACE
