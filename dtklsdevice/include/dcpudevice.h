// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
#ifndef DCPUDEVICE_H
#define DCPUDEVICE_H

#include "dtklsdevice_global.h"
#include "dlsdevicetypes.h"

#include <QObject>

DLSDEVICE_BEGIN_NAMESPACE

class DCpuDevicePrivate;
class DCpuDevice : public QObject
{
public:
    explicit DCpuDevice(QObject *parent = nullptr);
    ~DCpuDevice();

    int physicalCount();
    int coreCount(int physicalID);
    int threadCount(int physicalID, int coreID);
    int physicalID(int processorID);
    int coreID(int processorID);
    QString architecture(int physicalID);
    QString vendor(int physicalID);
    QString model(int physicalID);
    QString minFreq(int processorID);
    QString maxFreq(int processorID);
    QString cache(int processorID, QString type);
    QString flags(int processorID);
    QString stepping(int processorID);
    QString family(int processorID);
    QString bogoMIPS(int processorID);

    QString temperature(int physicalID);
    QString currentFreq(int processorID);
    DCpuStat stat();
    DCpuUsage usage();
    DCpuStat stat(int processorID);
    DCpuUsage usage(int processorID);

private:
    QScopedPointer<DCpuDevicePrivate> d_ptr;
    Q_DECLARE_PRIVATE(DCpuDevice)
};

DLSDEVICE_END_NAMESPACE

#endif // DCPUDEVICE_H
