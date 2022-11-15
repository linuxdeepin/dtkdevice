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

#include "dtkinputdevices_types.h"

DINPUTDEVICES_BEGIN_NAMESPACE
using DCORE_NAMESPACE::DExpected;
class DInputDevicePrivate;
class DInputDevice : public QObject
{
    Q_OBJECT
    Q_PROPERTY(quint32 id READ id CONSTANT)
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(DeviceType type READ type CONSTANT)
    Q_PROPERTY(bool enabled READ enabled NOTIFY enabledChanged)

public:
    quint32 id() const;
    QString name() const;
    DeviceType type() const;
    bool enabled() const;

    using Ptr = QSharedPointer<DInputDevice>;
    ~DInputDevice() override;

Q_SIGNALS:
    void enabledChanged(bool enabled);

public Q_SLOTS:
    virtual DExpected<void> reset();

protected:
    explicit DInputDevice(QObject *parent = nullptr);
    DInputDevice(const DeviceInfo &info, bool enabled = true);
    void setDeviceInfo(const DeviceInfo &info);
    void setEnabled(bool enabled);
    void setId(quint32 id);
    void setType(DeviceType type);
    void setName(const QString &name);

private:
    friend class DInputDeviceManager;
    QScopedPointer<DInputDevicePrivate> d_ptr;
    Q_DECLARE_PRIVATE(DInputDevice)
};

DINPUTDEVICES_END_NAMESPACE

#endif
