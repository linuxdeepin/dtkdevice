// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dinputdevicemouse.h"
#include "dinputdevicepointer.h"
#include "mouseservice.h"
#include <gtest/gtest.h>

DINPUTDEVICES_USE_NAMESPACE

class TestDInputDevicePointer : public testing::Test
{
public:
    static void SetUpTestCase()
    {
        devicePointer = new DInputDeviceMouse;
        mouseService = new MouseService;
    }
    static void TearDownTestCase()
    {
        delete devicePointer;
        delete mouseService;
    }

    static DInputDevicePointer *devicePointer;
    static MouseService *mouseService;
};

DInputDevicePointer *TestDInputDevicePointer::devicePointer = nullptr;
MouseService *TestDInputDevicePointer::mouseService = nullptr;

TEST_F(TestDInputDevicePointer, leftHanded)
{
    mouseService->m_leftHanded = false;
    ASSERT_EQ(false, mouseService->LeftHanded());
    EXPECT_EQ(false, devicePointer->leftHanded());
    mouseService->m_leftHanded = true;
    ASSERT_EQ(true, mouseService->LeftHanded());
    EXPECT_EQ(true, devicePointer->leftHanded());
}

TEST_F(TestDInputDevicePointer, setLeftHanded)
{
    mouseService->m_leftHanded = false;
    devicePointer->setLeftHanded(true);
    EXPECT_EQ(true, mouseService->m_leftHanded);
}

TEST_F(TestDInputDevicePointer, scrollMethod)
{
    EXPECT_EQ(ScrollMethod::ScrollOnButtonDown, devicePointer->scrollMethod());
}

TEST_F(TestDInputDevicePointer, setScrollMethod)
{
    devicePointer->setScrollMethod(ScrollMethod::NoScroll);
    EXPECT_EQ(ScrollMethod::ScrollOnButtonDown, devicePointer->scrollMethod());
}

TEST_F(TestDInputDevicePointer, accelerationProfile)
{
    mouseService->m_adaptiveAccelProfile = false;
    ASSERT_EQ(false, mouseService->AdaptiveAccelProfile());
    EXPECT_EQ(AccelerationProfile::Flat, devicePointer->accelerationProfile());
    mouseService->m_adaptiveAccelProfile = true;
    ASSERT_EQ(true, mouseService->AdaptiveAccelProfile());
    EXPECT_EQ(AccelerationProfile::Adaptive, devicePointer->accelerationProfile());
}

TEST_F(TestDInputDevicePointer, setAccelerationProfile)
{
    mouseService->m_adaptiveAccelProfile = false;
    devicePointer->setAccelerationProfile(AccelerationProfile::Adaptive);
    EXPECT_EQ(true, mouseService->m_adaptiveAccelProfile);
}

TEST_F(TestDInputDevicePointer, accelerationSpeed)
{
    mouseService->m_motionAcceleration = 123;
    ASSERT_EQ(123, mouseService->MotionAcceleration());
    EXPECT_EQ(123, devicePointer->accelerationSpeed());
    mouseService->m_motionAcceleration = 456;
    ASSERT_EQ(456, mouseService->MotionAcceleration());
    EXPECT_EQ(456, devicePointer->accelerationSpeed());
}

TEST_F(TestDInputDevicePointer, setAccelerationSpeed)
{
    mouseService->m_motionAcceleration = 123;
    devicePointer->setAccelerationSpeed(456);
    EXPECT_EQ(456, mouseService->m_motionAcceleration);
}

TEST_F(TestDInputDevicePointer, reset)
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
    auto result = devicePointer->reset();
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
