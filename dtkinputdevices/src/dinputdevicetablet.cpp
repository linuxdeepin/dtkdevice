// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dinputdevicetablet.h"
#include "dinputdevicetablet_p.h"
DINPUTDEVICES_BEGIN_NAMESPACE
using DCORE_NAMESPACE::DError;
using DCORE_NAMESPACE::DUnexpected;
DInputDeviceTabletPrivate::DInputDeviceTabletPrivate(DInputDeviceTablet *q)
    : QObject(q)
    , q_ptr(q)
{
#ifdef USE_FAKE_INTERFACE
    const QString &Service = QStringLiteral("org.deepin.dtk.InputDevices");
#else
    const QString &Service = QStringLiteral("com.deepin.daemon.InputDevices");
#endif
    m_wacomInter = new WacomInterface(Service);
}

DInputDeviceTabletPrivate::~DInputDeviceTabletPrivate()
{
    delete m_wacomInter;
}

DInputDeviceTablet::DInputDeviceTablet(QObject *parent)
    : DInputDevicePointer(parent)
    , d_ptr(new DInputDeviceTabletPrivate(this))
{
}

DExpected<void> DInputDeviceTablet::reset()
{
    Q_D(DInputDeviceTablet);
    auto result = d->m_wacomInter->Reset();
    result.waitForFinished();
    if (!result.isValid()) {
        return DUnexpected{DError{result.error().type(), result.error().message()}};
    } else {
        return {};
    }
}

bool DInputDeviceTablet::cursorMode() const
{
    Q_D(const DInputDeviceTablet);
    return d->m_wacomInter->CursorMode();
}

void DInputDeviceTablet::setCursorMode(bool cursorMode)
{
    Q_D(DInputDeviceTablet);
    d->m_wacomInter->SetCursorMode(cursorMode);
}

DINPUTDEVICES_END_NAMESPACE