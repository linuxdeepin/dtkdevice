// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
#ifndef DCPUDEVICE_H
#define DCPUDEVICE_H

#include "dtklsdevice_global.h"
#include "dlsdevicetypes.h"

#include <qobject.h>

DLSDEVICE_BEGIN_NAMESPACE

class DCpuDevicePrivate;
class DCpuDevice : public QObject
{
public:
    explicit DCpuDevice(QObject *parent = nullptr);
    ~DCpuDevice();

    int physicalCount();
    int coreCount(const int &physicalID);
    int threadCount(const int &physicalID, const int &coreID);
    int physicalID(const int &processorID);
    int coreID(const int &processorID);
    QString architecture(const int &physicalID);
    QString vendor(const int &physicalID);
    QString model(const int &physicalID);
    QString minFreq(const int &processorID);
    QString maxFreq(const int &processorID);
    QString cache(const int &processorID, QString type);
    QString flags(const int &processorID);
    QString stepping(const int &processorID);
    QString family(const int &processorID);
    QString bogoMIPS(const int &processorID);

    QString currentFreq(const int &processorID);
    DCpuStat stat(const int &processorID);
    DCpuUsage usage(const int &processorID);

private:
    QScopedPointer<DCpuDevicePrivate> d_ptr;
    Q_DECLARE_PRIVATE(DCpuDevice)
};

DLSDEVICE_END_NAMESPACE

#endif // DCPUDEVICE_H


