// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DTKINPUTDEVICES_CONVERTERS_H
#define DTKINPUTDEVICES_CONVERTERS_H
#include "dtkinputdevices_global.h"
#include "dtkinputdevices_types.h"
#include <QString>

DINPUTDEVICES_BEGIN_NAMESPACE
QString deviceTypeToString(DeviceType type);
QString keyActionToString(KeyAction action);
KeyAction stringToKeyAction(const QString &action);
QString profileToString(AccelerationProfile profile);
DINPUTDEVICES_END_NAMESPACE
#endif  // DTKINPUTDEVICES_CONVERTERS_H
