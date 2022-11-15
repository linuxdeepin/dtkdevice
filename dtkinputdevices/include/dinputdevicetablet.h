// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DINPUTDEVICETABLET_H
#define DINPUTDEVICETABLET_H
#include "dinputdevicepointer.h"
#include "dtkinputdevices_global.h"
#include <DExpected>
#include <QScopedPointer>

DINPUTDEVICES_BEGIN_NAMESPACE
using DCORE_NAMESPACE::DExpected;
class DInputDeviceTabletPrivate;
class DInputDeviceTablet : public DInputDevicePointer
{
    Q_OBJECT
    Q_PROPERTY(bool cursorMode READ cursorMode WRITE setCursorMode NOTIFY cursorModeChanged)

public:
    bool cursorMode() const;
    void setCursorMode(bool cursorMode);
    ~DInputDeviceTablet() override;

Q_SIGNALS:
    void cursorModeChanged(bool cursorMode);

public Q_SLOTS:
    DExpected<void> reset() override;

protected:
    explicit DInputDeviceTablet(QObject *parent = nullptr);
    DInputDeviceTablet(const DeviceInfo &info, bool enabled = true);

private:
    friend class DInputDeviceManager;
    QScopedPointer<DInputDeviceTabletPrivate> d_ptr;
    Q_DECLARE_PRIVATE(DInputDeviceTablet);
};
DINPUTDEVICES_END_NAMESPACE
#endif  // DINPUTDEVICETABLET_H