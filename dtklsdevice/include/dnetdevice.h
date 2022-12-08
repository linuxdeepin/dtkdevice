// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
#ifndef DNETDEVICE_H
#define DNETDEVICE_H

#include "dtklsdevice_global.h"
#include "dlsdevicetypes.h"

#include <QObject>

DLSDEVICE_BEGIN_NAMESPACE

class DNetDevicePrivate;
class DNetDevice : public QObject
{
public:
    explicit DNetDevice(QObject *parent = nullptr);
    ~DNetDevice();

    int count();
    QString name(int index);
    QString vendor(int index);
    QString model(int index);
    QString type(int index);
    QString macAddress(int index);
    QString driver(int index);
    QString speed(int index);

    QString status(int index);
    DInetAddr4 inetAddr4(int index);
    DInetAddr6 inetAddr6(int index);
    DNetifInfo netifInfo(int index);
    QString portStatus(int index, int port);
    QList<int> applicationPorts(int pid);

private:
    QScopedPointer<DNetDevicePrivate> d_ptr;
    Q_DECLARE_PRIVATE(DNetDevice)
};

DLSDEVICE_END_NAMESPACE

#endif // DDISKDEVICE_H
