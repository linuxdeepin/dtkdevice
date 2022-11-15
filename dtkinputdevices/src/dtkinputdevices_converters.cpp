// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dtkinputdevices_converters.h"
#include <QMap>

DINPUTDEVICES_BEGIN_NAMESPACE

QString deviceTypeToString(DeviceType type)
{
    const QMap<DeviceType, QString> &typeMap = {{DeviceType::Generic, "Generic"},
                                                {DeviceType::Keyboard, "Keyboard"},
                                                {DeviceType::Mouse, "Mouse"},
                                                {DeviceType::Tablet, "Tablet"},
                                                {DeviceType::TouchPad, "TouchPad"},
                                                {DeviceType::TrackPoint, "TrackPoint"}};
    return typeMap[type];
}
DINPUTDEVICES_END_NAMESPACE
