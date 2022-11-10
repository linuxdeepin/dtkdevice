// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
#pragma once

#include "dinputdevicetouchpad.h"

DINPUTDEVICES_BEGIN_NAMESPACE

class DInputDeviceTouchPadPrivate : public QObject
{
    Q_OBJECT
public:
    explicit DInputDeviceTouchPadPrivate(DInputDeviceTouchPad *q = nullptr);

private:
    DInputDeviceTouchPad *q_ptr;
    Q_DECLARE_PUBLIC(DInputDeviceTouchPad)
};

DINPUTDEVICES_END_NAMESPACE
