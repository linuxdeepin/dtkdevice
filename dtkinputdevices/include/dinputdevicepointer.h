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


using DCORE_NAMESPACE::DExpected;

class DInputDevicePointerPrivate;
class DInputDevicePointer : public DInputDevice
{
    Q_OBJECT
    Q_PROPERTY(bool leftHanded READ leftHanded WRITE setLeftHanded)
    Q_PROPERTY(ScrollMethod scrollMethod READ scrollMethod WRITE setScrollMethod)
    Q_PROPERTY(AccelerationProfile accelerationProfile READ accelerationProfile WRITE setAccelerationProfile)
    Q_PROPERTY(double accelerationSpeed READ accelerationSpeed WRITE setAccelerationSpeed)

public:
    explicit DInputDevicePointer(QObject *parent = nullptr);
    ~DInputDevicePointer() override;

    bool leftHanded() const;
    ScrollMethod scrollMethod() const;
    AccelerationProfile accelerationProfile() const;
    double accelerationSpeed() const;

    void setLeftHanded(bool leftHanded);
    void setScrollMethod(ScrollMethod scrollMethod);
    void setAccelerationProfile(AccelerationProfile accelerationProfile);
    void setAccelerationSpeed(double accelerationSpeed);

private:
    QScopedPointer<DInputDevicePointerPrivate> d_ptr;
    Q_DECLARE_PRIVATE(DInputDevicePointer)
};


DINPUTDEVICES_END_NAMESPACE
#endif
