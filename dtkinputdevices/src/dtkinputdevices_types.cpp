// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dtkinputdevices_types.h"
#include "dtkinputdevices_converters.h"
#include "dtkinputdevices_global.h"
#include <QDebug>
DINPUTDEVICES_BEGIN_NAMESPACE
bool operator==(const DeviceInfo &lhs, const DeviceInfo &rhs)
{
    return lhs.id == rhs.id && lhs.name == rhs.name && lhs.type == rhs.type;
}

QDebug operator<<(QDebug debug, DeviceType type)
{
    debug << deviceTypeToString(type);
    return debug;
}

QDebug operator<<(QDebug debug, const DeviceInfo &info)
{
    debug << "{id: " << info.id << ", name: " << info.name << ", type: " << info.type << "}";
    return debug;
}
DINPUTDEVICES_END_NAMESPACE
