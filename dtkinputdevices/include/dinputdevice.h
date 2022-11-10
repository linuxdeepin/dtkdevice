// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DINPUTDEVICE_H
#define DINPUTDEVICE_H

#include "dtkinputdevices_global.h"

#include <DExpected>
#include <QObject>
#include <QScopedPointer>
#include <QSharedPointer>

#include "dinputdevicetypes.h"

DINPUTDEVICES_BEGIN_NAMESPACE
using DCORE_NAMESPACE::DExpected;
class DInputDevicePrivate;
class DInputDevice : public QObject
{
    Q_OBJECT
    Q_PROPERTY(quint32 id READ id)
    Q_PROPERTY(QString name READ name)
    Q_PROPERTY(DeviceType type READ type)
    Q_PROPERTY(bool enabled READ enabled)

public:
    explicit DInputDevice(QObject *parent = nullptr);
    ~DInputDevice() override;
    using Ptr = QSharedPointer<DInputDevice>;

    quint32 id() const;
    QString name() const;
    DeviceType type() const;
    bool enabled() const;

public Q_SLOTS:

    virtual DExpected<void> reset();

private:
    QScopedPointer<DInputDevicePrivate> d_ptr;
    Q_DECLARE_PRIVATE(DInputDevice)
};

DINPUTDEVICES_END_NAMESPACE

#endif
