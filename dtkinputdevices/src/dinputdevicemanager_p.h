// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DINPUTDEVICEMANAGER_P_H
#define DINPUTDEVICEMANAGER_P_H

#include "dinputdevicemanager.h"

DINPUTDEVICES_BEGIN_NAMESPACE
class DInputDeviceManagerPrivate : public QObject
{
    explicit DInputDeviceManagerPrivate(DInputDeviceManager *q);

private:
    DInputDeviceManager *q_ptr;
    Q_DECLARE_PUBLIC(DInputDeviceManager)
};

DINPUTDEVICES_END_NAMESPACE
#endif