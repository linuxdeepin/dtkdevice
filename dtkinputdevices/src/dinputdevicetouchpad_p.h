// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
#pragma once

#include "dinputdevicetouchpad.h"
#include "touchpadinterface.h"

DINPUTDEVICES_BEGIN_NAMESPACE

class DInputDeviceTouchPadPrivate : public QObject
{
    Q_OBJECT
public:
    explicit DInputDeviceTouchPadPrivate(DInputDeviceTouchPad *q);
    ~DInputDeviceTouchPadPrivate();

private:
    TouchPadInterface *m_touchPadInter;
    DInputDeviceTouchPad *q_ptr;
    Q_DECLARE_PUBLIC(DInputDeviceTouchPad)
};

DINPUTDEVICES_END_NAMESPACE
