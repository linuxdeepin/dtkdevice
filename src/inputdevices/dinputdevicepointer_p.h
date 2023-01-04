// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "dtkdevice_global.h"

#include <QObject>

DDEVICE_BEGIN_NAMESPACE

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

DDEVICE_END_NAMESPACE
