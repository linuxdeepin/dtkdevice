// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dinputdevicepointer.h"
#include "dinputdevicetypes.h"
#include <gtest/gtest.h>

DINPUTDEVICES_USE_NAMESPACE

class TestDInputDevicePointer : public testing::Test
{
public:
    TestDInputDevicePointer():
        m_devicePointer(new DInputDevicePointer)
    {
    }

    virtual ~TestDInputDevicePointer() { delete m_devicePointer; }

protected:
    DInputDevicePointer *m_devicePointer;
};

TEST_F(TestDInputDevicePointer, leftHanded)
{
    EXPECT_EQ(true, m_devicePointer->leftHanded());
}

TEST_F(TestDInputDevicePointer, scrollMethod)
{
    EXPECT_EQ(ScrollMethod::NoScroll, m_devicePointer->scrollMethod());
}
