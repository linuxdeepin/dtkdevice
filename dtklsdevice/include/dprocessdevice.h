// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
#ifndef DPROCESSDEVICE_H
#define DPROCESSDEVICE_H

#include "dtklsdevice_global.h"
#include "dlsdevicetypes.h"

#include <QObject>

DLSDEVICE_BEGIN_NAMESPACE

class DProcessDevicePrivate;
class DProcessDevice : public QObject
{
public:
    explicit DProcessDevice(QObject *parent = nullptr);
    ~DProcessDevice();

    QList<pid_t> allPids();
    QHash<QString, QString> environment(pid_t pid);
    QString groupName(const gid_t &gid);
    DProcessBaseInfo baseInfo(pid_t pid);
    DProcessMemoryInfo memoryInfo(pid_t pid);
    DProcessIOInfo ioInfo(pid_t pid);
    DProcessNetworkInfo networkInfo(pid_t pid);
    DProcessStatus status(pid_t pid);

private:
    QScopedPointer<DProcessDevicePrivate> d_ptr;
    Q_DECLARE_PRIVATE(DProcessDevice)
};

DLSDEVICE_END_NAMESPACE

#endif // DPROCESSDEVICE_H
