// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dinputdevicekeyboard.h"
#include "dinputdevicekeyboard_p.h"
#include "dtkinputdevices_global.h"
DINPUTDEVICES_BEGIN_NAMESPACE
using DCORE_NAMESPACE::DError;
using DCORE_NAMESPACE::DUnexpected;

DInputDeviceKeyboardPrivate::DInputDeviceKeyboardPrivate(DInputDeviceKeyboard *q)
    : QObject(q)
    , q_ptr(q)
{
#ifdef USE_FAKE_INTERFACE
    const QString &Service = QStringLiteral("org.deepin.dtk.InputDevices");
#else
    const QString &Service = QStringLiteral("com.deepin.daemon.InputDevices");
#endif
    m_keyboardInter = new KeyboardInterface(Service);
}

DInputDeviceKeyboardPrivate::~DInputDeviceKeyboardPrivate()
{
    delete m_keyboardInter;
}

DInputDeviceKeyboard::DInputDeviceKeyboard(QObject *parent)
    : DInputDevice(parent)
    , d_ptr(new DInputDeviceKeyboardPrivate(this))
{
}

DExpected<void> DInputDeviceKeyboard::reset()
{
    Q_D(DInputDeviceKeyboard);
    auto result = d->m_keyboardInter->Reset();
    result.waitForFinished();
    if (!result.isValid()) {
        return DUnexpected{DError{result.error().type(), result.error().message()}};
    } else {
        return {};
    }
}
DINPUTDEVICES_END_NAMESPACE