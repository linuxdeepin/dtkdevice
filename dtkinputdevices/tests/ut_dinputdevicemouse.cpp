// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dinputdevicemouse.h"
#include <gtest/gtest.h>

DINPUTDEVICES_USE_NAMESPACE

class TestDInputDeviceMouse : public testing::Test
{
public:
    TestDInputDeviceMouse()
        : m_deviceMouse(new DInputDeviceMouse)
    {
    }

    virtual ~TestDInputDeviceMouse() { delete m_deviceMouse; }

protected:
    DInputDeviceMouse *m_deviceMouse;
};
