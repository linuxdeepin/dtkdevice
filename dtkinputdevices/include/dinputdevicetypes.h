// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DINPUTDEVICETYPES_H
#define DINPUTDEVICETYPES_H
#include "dtkinputdevices_global.h"
#include <QString>

enum class DeviceType { Mouse, TrackPoint, TouchPad, Tablet, Keyboard, Generic };

struct DeviceInfo
{
    quint32 id;
    QString name;
    DeviceType type;
};

enum class AccelerationProfile { Flat, Adaptive, Na };

enum class Key { KeyUp, KeyDown };

enum class KeyAction { LeftClick, MiddleClick, RightClick, PageUp, PageDown };

enum class ScrollMethod { NoScroll, ScrollTwoFinger, ScrollEdge, ScrollOnButtonDown };

#endif