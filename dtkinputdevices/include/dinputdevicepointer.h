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

    bool leftHanded() const;
    ScrollMethod scrollMethod() const;
    AccelerationProfile accelerationProfile() const;
    double accelerationSpeed() const;

    void setLeftHanded(bool leftHanded);
    void setScrollMethod(ScrollMethod scrollMethod);
    void setAccelerationProfile(AccelerationProfile accelerationProfile);
    void setAccelerationSpeed(double accelerationSpeed);

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
