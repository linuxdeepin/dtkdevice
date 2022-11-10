// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "dtkinputdevices_global.h"

#include <QObject>

DINPUTDEVICES_BEGIN_NAMESPACE

class DInputDevicePointer;
class DInputDevicePointerPrivate : public QObject
{
    Q_OBJECT
public:
    explicit DInputDevicePointerPrivate(DInputDevicePointer *q = nullptr);

private:
    DInputDevicePointer *q_ptr;
    Q_DECLARE_PUBLIC(DInputDevicePointer)

};

DINPUTDEVICES_END_NAMESPACE

