// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dinputdevice.h"
#include "dinputdevice_p.h"
#include <gtest/gtest.h>

DINPUTDEVICES_USE_NAMESPACE

class TestDInputDevice : public testing::Test
{
public:
    static void SetUpTestCase() { device = new DInputDevice; }
    static void TearDownTestCase() { delete device; }
    static DInputDevice *device;
};

DInputDevice *TestDInputDevice::device = nullptr;

TEST_F(TestDInputDevice, id)
{
    device->d_ptr->m_id = 10;
    EXPECT_EQ(10, device->id());
}

TEST_F(TestDInputDevice, name)
{
    device->d_ptr->m_name = "Test";
    EXPECT_EQ("Test", device->name());
}

TEST_F(TestDInputDevice, type)
{
    device->d_ptr->m_type = DeviceType::Mouse;
    EXPECT_EQ(DeviceType::Mouse, device->type());
}

TEST_F(TestDInputDevice, enabled)
{
    device->d_ptr->m_enabled = true;
    EXPECT_EQ(true, device->enabled());
    device->d_ptr->m_enabled = false;
    EXPECT_EQ(false, device->enabled());
}

TEST_F(TestDInputDevice, reset)
{
    auto result = device->reset();
    ASSERT_FALSE(result.hasValue());
    EXPECT_EQ(ErrorCode::InvalidCall, result.error().getErrorCode());
    EXPECT_EQ("Generic device does not have a reset method!", result.error().getErrorMessage());
}

TEST_F(TestDInputDevice, setDeviceInfo)
{
    DeviceInfo info{100, "test", DeviceType::Keyboard};
    device->setDeviceInfo(info);
    EXPECT_EQ(100, device->d_ptr->m_id);
    EXPECT_EQ("test", device->d_ptr->m_name);
    EXPECT_EQ(DeviceType::Keyboard, device->d_ptr->m_type);
}

TEST_F(TestDInputDevice, setEnabled)
{
    device->d_ptr->m_enabled = false;
    device->setEnabled(true);
    EXPECT_EQ(true, device->d_ptr->m_enabled);
}

TEST_F(TestDInputDevice, setId)
{
    device->d_ptr->m_id = 0;
    device->setId(12345);
    EXPECT_EQ(12345, device->d_ptr->m_id);
}

TEST_F(TestDInputDevice, setName)
{
    device->d_ptr->m_name = "";
    device->setName("Test");
    EXPECT_EQ("Test", device->d_ptr->m_name);
}

TEST_F(TestDInputDevice, setType)
{
    device->d_ptr->m_type = DeviceType::Generic;
    device->setType(DeviceType::Mouse);
    EXPECT_EQ(DeviceType::Mouse, device->d_ptr->m_type);
}
