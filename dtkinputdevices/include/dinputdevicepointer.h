// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DINPUTDEVICEPOINTER_H
#define DINPUTDEVICEPOINTER_H

#include "dtkinputdevices_global.h"

#include <DExpected>
#include <QObject>
#include <QScopedPointer>

#include "dinputdevice.h"
#include "dtkinputdevices_types.h"

DINPUTDEVICES_BEGIN_NAMESPACE

class DInputDevicePointerPrivate;
class DInputDevicePointer : public DInputDevice
{
    Q_OBJECT
    Q_PROPERTY(bool leftHanded READ leftHanded WRITE setLeftHanded NOTIFY leftHandedChanged)
    Q_PROPERTY(ScrollMethod scrollMethod READ scrollMethod WRITE setScrollMethod NOTIFY scrollMethodChanged)
    Q_PROPERTY(AccelerationProfile accelerationProfile READ accelerationProfile WRITE setAccelerationProfile NOTIFY
                   accelerationProfileChanged)
    Q_PROPERTY(double accelerationSpeed READ accelerationSpeed WRITE setAccelerationSpeed NOTIFY accelerationSpeedChanged)

public:
    ~DInputDevicePointer() override;

    virtual bool leftHanded() const = 0;
    virtual ScrollMethod scrollMethod() const = 0;
    virtual AccelerationProfile accelerationProfile() const = 0;
    virtual double accelerationSpeed() const = 0;

    virtual void setLeftHanded(bool leftHanded) = 0;
    virtual void setScrollMethod(ScrollMethod scrollMethod) = 0;
    virtual void setAccelerationProfile(AccelerationProfile accelerationProfile) = 0;
    virtual void setAccelerationSpeed(double accelerationSpeed) = 0;

Q_SIGNALS:
    void leftHandedChanged(bool leftHanded);
    void scrollMethodChanged(ScrollMethod method);
    void accelerationProfileChanged(AccelerationProfile profile);
    void accelerationSpeedChanged(double speed);

protected:
    explicit DInputDevicePointer(QObject *parent = nullptr);
    DInputDevicePointer(const DeviceInfo &info, bool enabled = true);

private:
    QScopedPointer<DInputDevicePointerPrivate> d_ptr;
    Q_DECLARE_PRIVATE(DInputDevicePointer)
};

DINPUTDEVICES_END_NAMESPACE
#endif
