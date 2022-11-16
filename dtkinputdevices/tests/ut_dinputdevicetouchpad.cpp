// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dinputdevicetouchpad.h"
#include <gtest/gtest.h>

DINPUTDEVICES_USE_NAMESPACE

class TestDInputDeviceTouchPad : public testing::Test
{
public:
    TestDInputDeviceTouchPad()
        : m_deviceTouchPad(new DInputDeviceTouchPad)
    {
    }

    virtual ~TestDInputDeviceTouchPad() { delete m_deviceTouchPad; }

protected:
    DInputDeviceTouchPad *m_deviceTouchPad;
};
