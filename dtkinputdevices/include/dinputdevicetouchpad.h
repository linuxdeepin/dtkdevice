// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DINPUTDEVICETOUCHPAD_H
#define DINPUTDEVICETOUCHPAD_H

#include "dtkinputdevices_global.h"

#include <DExpected>
#include <QObject>
#include <QScopedPointer>

#include "dinputdevicetypes.h"
#include "dinputdevicepointer.h"

DINPUTDEVICES_BEGIN_NAMESPACE

using DCORE_NAMESPACE::DExpected;
class DInputDeviceTouchPadPrivate;
class DInputDeviceTouchPad : public DInputDevicePointer
{
    Q_OBJECT
    Q_PROPERTY(bool disableWhileTyping READ disableWhileTyping WRITE setDisableWhileTyping)
    Q_PROPERTY(bool naturalScroll READ naturalScroll WRITE setNaturalScroll)
    Q_PROPERTY(bool tapToClick READ tapToClick WRITE setTapToClick)

public:
    explicit DInputDeviceTouchPad(DInputDevicePointer *parent = nullptr);
    ~DInputDeviceTouchPad() override;

    bool disableWhileTyping() const;
    bool naturalScroll() const;
    bool tapToClick() const;


    void setDisableWhileTyping(bool disableWhileTyping);
    void setNaturalScroll(bool naturalScroll);
    void setTapToClick(bool tapToClick);

public Q_SLOTS:
    virtual DExpected<void> reset();
    DExpected<void> enable(bool enabled);

private:
    QScopedPointer<DInputDeviceTouchPadPrivate> d_ptr;
    Q_DECLARE_PRIVATE(DInputDeviceTouchPad)
};



DINPUTDEVICES_END_NAMESPACE


#endif // DINPUTDEVICETOUCHPAD_H
