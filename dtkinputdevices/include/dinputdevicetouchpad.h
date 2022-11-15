// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DINPUTDEVICETOUCHPAD_H
#define DINPUTDEVICETOUCHPAD_H

#include "dtkinputdevices_global.h"

#include <DExpected>
#include <QObject>
#include <QScopedPointer>

#include "dinputdevicepointer.h"

DINPUTDEVICES_BEGIN_NAMESPACE

using DCORE_NAMESPACE::DExpected;
class DInputDeviceTouchPadPrivate;
class DInputDeviceTouchPad : public DInputDevicePointer
{
    Q_OBJECT
    Q_PROPERTY(bool disableWhileTyping READ disableWhileTyping WRITE setDisableWhileTyping NOTIFY disableWhileTypingChanged)
    Q_PROPERTY(bool naturalScroll READ naturalScroll WRITE setNaturalScroll NOTIFY naturalScrollChanged)
    Q_PROPERTY(bool tapToClick READ tapToClick WRITE setTapToClick NOTIFY tapToClickChanged)

public:
    ~DInputDeviceTouchPad() override;

    bool disableWhileTyping() const;
    bool naturalScroll() const;
    bool tapToClick() const;

    void setDisableWhileTyping(bool disableWhileTyping);
    void setNaturalScroll(bool naturalScroll);
    void setTapToClick(bool tapToClick);

public Q_SLOTS:
    DExpected<void> reset() override;
    DExpected<void> enable(bool enabled = true);

Q_SIGNALS:
    void disableWhileTypingChanged(bool disableWhileTyping);
    void naturalScrollChanged(bool naturalScroll);
    void tapToClickChanged(bool tapToClick);

protected:
    explicit DInputDeviceTouchPad(DInputDevicePointer *parent = nullptr);
    DInputDeviceTouchPad(const DeviceInfo &info, bool enabled = true);

private:
    friend class DInputDeviceManager;
    QScopedPointer<DInputDeviceTouchPadPrivate> d_ptr;
    Q_DECLARE_PRIVATE(DInputDeviceTouchPad)
};

DINPUTDEVICES_END_NAMESPACE

#endif  // DINPUTDEVICETOUCHPAD_H
