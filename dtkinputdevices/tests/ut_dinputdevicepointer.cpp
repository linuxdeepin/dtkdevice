// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dinputdevicemouse.h"
#include "dinputdevicepointer.h"
#include <gtest/gtest.h>

DINPUTDEVICES_USE_NAMESPACE

class TestDInputDevicePointer : public testing::Test
{
public:
    TestDInputDevicePointer()
        : m_devicePointer(new DInputDeviceMouse)
    {
    }

    virtual ~TestDInputDevicePointer() { delete m_devicePointer; }

protected:
    DInputDevicePointer *m_devicePointer;
};
