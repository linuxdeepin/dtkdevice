// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dinputdevicemouse.h"
#include "mouseservice.h"
#include <gtest/gtest.h>

DINPUTDEVICES_USE_NAMESPACE

class TestDInputDeviceMouse : public testing::Test
{
public:
    static void SetUpTestCase()
    {
        deviceMouse = new DInputDeviceMouse;
        mouseService = new MouseService;
    }
    static void TearDownTestCase()
    {
        delete deviceMouse;
        delete mouseService;
    }
    static DInputDeviceMouse *deviceMouse;
    static MouseService *mouseService;
};

DInputDeviceMouse *TestDInputDeviceMouse::deviceMouse = nullptr;
MouseService *TestDInputDeviceMouse::mouseService = nullptr;

TEST_F(TestDInputDeviceMouse, naturalScroll)
{
    mouseService->m_naturalScroll = false;
    ASSERT_EQ(false, mouseService->NaturalScroll());
    EXPECT_EQ(false, deviceMouse->naturalScroll());
    mouseService->m_naturalScroll = true;
    ASSERT_EQ(true, mouseService->NaturalScroll());
    EXPECT_EQ(true, deviceMouse->naturalScroll());
}

TEST_F(TestDInputDeviceMouse, setNaturalScroll)
{
    mouseService->m_naturalScroll = false;
    deviceMouse->setNaturalScroll(true);
    EXPECT_EQ(true, mouseService->m_naturalScroll);
}

TEST_F(TestDInputDeviceMouse, middleButtonEmulation)
{
    mouseService->m_middleButtonEmulation = false;
    ASSERT_EQ(false, mouseService->MiddleButtonEmulation());
    EXPECT_EQ(false, deviceMouse->middleButtonEmulation());
    mouseService->m_middleButtonEmulation = true;
    ASSERT_EQ(true, mouseService->MiddleButtonEmulation());
    EXPECT_EQ(true, deviceMouse->middleButtonEmulation());
}

TEST_F(TestDInputDeviceMouse, setMiddleButtonEmulation)
{
    mouseService->m_middleButtonEmulation = false;
    deviceMouse->setMiddleButtonEmulation(true);
    EXPECT_EQ(true, mouseService->m_middleButtonEmulation);
}

TEST_F(TestDInputDeviceMouse, leftHanded)
{
    mouseService->m_leftHanded = false;
    ASSERT_EQ(false, mouseService->LeftHanded());
    EXPECT_EQ(false, deviceMouse->leftHanded());
    mouseService->m_leftHanded = true;
    ASSERT_EQ(true, mouseService->LeftHanded());
    EXPECT_EQ(true, deviceMouse->leftHanded());
}

TEST_F(TestDInputDeviceMouse, setLeftHanded)
{
    mouseService->m_leftHanded = false;
    deviceMouse->setLeftHanded(true);
    EXPECT_EQ(true, mouseService->m_leftHanded);
}

TEST_F(TestDInputDeviceMouse, scrollMethod)
{
    EXPECT_EQ(ScrollMethod::ScrollOnButtonDown, deviceMouse->scrollMethod());
}

TEST_F(TestDInputDeviceMouse, setScrollMethod)
{
    deviceMouse->setScrollMethod(ScrollMethod::NoScroll);
    EXPECT_EQ(ScrollMethod::ScrollOnButtonDown, deviceMouse->scrollMethod());
}

TEST_F(TestDInputDeviceMouse, accelerationProfile)
{
    mouseService->m_adaptiveAccelProfile = false;
    ASSERT_EQ(false, mouseService->AdaptiveAccelProfile());
    EXPECT_EQ(AccelerationProfile::Flat, deviceMouse->accelerationProfile());
    mouseService->m_adaptiveAccelProfile = true;
    ASSERT_EQ(true, mouseService->AdaptiveAccelProfile());
    EXPECT_EQ(AccelerationProfile::Adaptive, deviceMouse->accelerationProfile());
}

TEST_F(TestDInputDeviceMouse, setAccelerationProfile)
{
    mouseService->m_adaptiveAccelProfile = false;
    deviceMouse->setAccelerationProfile(AccelerationProfile::Adaptive);
    EXPECT_EQ(true, mouseService->m_adaptiveAccelProfile);
}

TEST_F(TestDInputDeviceMouse, accelerationSpeed)
{
    mouseService->m_motionAcceleration = 123;
    ASSERT_EQ(123, mouseService->MotionAcceleration());
    EXPECT_EQ(123, deviceMouse->accelerationSpeed());
    mouseService->m_motionAcceleration = 456;
    ASSERT_EQ(456, mouseService->MotionAcceleration());
    EXPECT_EQ(456, deviceMouse->accelerationSpeed());
}

TEST_F(TestDInputDeviceMouse, setAccelerationSpeed)
{
    mouseService->m_motionAcceleration = 123;
    deviceMouse->setAccelerationSpeed(456);
    EXPECT_EQ(456, mouseService->m_motionAcceleration);
}

TEST_F(TestDInputDeviceMouse, reset)
{
    mouseService->m_adaptiveAccelProfile = !MouseService::AdaptiveAccelProfileDefault;
    mouseService->m_disableTpad = !MouseService::DisableTpadDefault;
    mouseService->m_exist = !MouseService::ExistDefault;
    mouseService->m_leftHanded = !MouseService::LeftHandedDefault;
    mouseService->m_middleButtonEmulation = !MouseService::MiddleButtonEmulationDefault;
    mouseService->m_naturalScroll = !MouseService::NaturalScrollDefault;
    mouseService->m_motionAcceleration = MouseService::MotionAccelerationDefault + 2;
    mouseService->m_doubleClick = MouseService::DoubleClickDefault + 100;
    mouseService->m_dragThreshold = MouseService::DragThresholdDefault + 100;
    mouseService->m_deviceList = "";
    auto result = deviceMouse->reset();
    EXPECT_TRUE(result.hasValue());
    EXPECT_EQ(mouseService->m_adaptiveAccelProfile, MouseService::AdaptiveAccelProfileDefault);
    EXPECT_EQ(mouseService->m_disableTpad, MouseService::DisableTpadDefault);
    EXPECT_EQ(mouseService->m_exist, MouseService::ExistDefault);
    EXPECT_EQ(mouseService->m_leftHanded, MouseService::LeftHandedDefault);
    EXPECT_EQ(mouseService->m_middleButtonEmulation, MouseService::MiddleButtonEmulationDefault);
    EXPECT_EQ(mouseService->m_naturalScroll, MouseService::NaturalScrollDefault);
    EXPECT_DOUBLE_EQ(mouseService->m_motionAcceleration, MouseService::MotionAccelerationDefault);
    EXPECT_EQ(mouseService->m_doubleClick, MouseService::DoubleClickDefault);
    EXPECT_EQ(mouseService->m_dragThreshold, MouseService::DragThresholdDefault);
    EXPECT_EQ(mouseService->m_deviceList, MouseService::DeviceListDefault);
}
