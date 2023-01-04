// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DINPUTDEVICEGENERIC_H
#define DINPUTDEVICEGENERIC_H

#include "dtkdevice_global.h"

#include <DExpected>
#include <QObject>
#include <QScopedPointer>
#include <QSharedPointer>

#include "dtkinputdevices_types.h"

DDEVICE_BEGIN_NAMESPACE
using DCORE_NAMESPACE::DExpected;
class DInputDeviceGenericPrivate;
class DInputDeviceGeneric : public QObject
{
    Q_OBJECT
    Q_PROPERTY(quint32 id READ id CONSTANT)
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(DeviceType type READ type CONSTANT)
    Q_PROPERTY(bool enabled READ enabled NOTIFY enabledChanged)

public:
    virtual quint32 id() const;
    virtual QString name() const;
    virtual DeviceType type() const;
    virtual bool enabled() const;

    using Ptr = QSharedPointer<DInputDeviceGeneric>;
    ~DInputDeviceGeneric() override;

Q_SIGNALS:
    void enabledChanged(bool enabled);

public Q_SLOTS:
    virtual DExpected<void> reset();

protected:
    explicit DInputDeviceGeneric(QObject *parent = nullptr);
    DInputDeviceGeneric(const DeviceInfo &info, bool enabled = true);
    virtual void setId(quint32 id);
    virtual void setName(const QString &name);
    virtual void setType(DeviceType type);
    virtual void setEnabled(bool enabled);
    virtual void setDeviceInfo(const DeviceInfo &info);

private:
    friend class DInputDeviceManager;
    QScopedPointer<DInputDeviceGenericPrivate> d_ptr;
    Q_DECLARE_PRIVATE(DInputDeviceGeneric)
};

DDEVICE_END_NAMESPACE

#endif
