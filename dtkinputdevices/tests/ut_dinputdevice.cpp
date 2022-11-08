// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dinputdevice.h"
#include <gtest/gtest.h>

DINPUTDEVICES_USE_NAMESPACE

class TestDInputDevice : public testing::Test
{
public:
    TestDInputDevice()
        : m_device(new DInputDevice)
    {
    }

    virtual ~TestDInputDevice() { delete m_device; }

protected:
    DInputDevice *m_device;
};

TEST_F(TestDInputDevice, id)
{
    EXPECT_EQ(10, m_device->id());
}