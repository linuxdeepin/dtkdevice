// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DINPUTDEVICESETTING_H
#define DINPUTDEVICESETTING_H
#include "dtkinputdevices_global.h"
#include <QObject>
#include <QSharedPointer>

DINPUTDEVICES_BEGIN_NAMESPACE
class DInputDeviceSettingPrivate;
class DInputDeviceSetting : public QObject
{
    Q_OBJECT
public:
    explicit DInputDeviceSetting(QObject *parent = nullptr);
    using Ptr = QSharedPointer<DInputDeviceSetting>;

private:
    QScopedPointer<DInputDeviceSettingPrivate> d_ptr;
    Q_DECLARE_PRIVATE(DInputDeviceSetting)
};
DINPUTDEVICES_END_NAMESPACE

#endif