// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef MOUSESERVICE_H
#define MOUSESERVICE_H
#include "dtkinputdevices_global.h"
#include <QObject>
DINPUTDEVICES_BEGIN_NAMESPACE
class MouseAdaptor;
class TrackPointAdaptor;
class MouseService : public QObject
{
    Q_OBJECT
public:
    MouseService(const QString &service = QStringLiteral("org.deepin.dtk.InputDevices"),
                 const QString &path = QStringLiteral("/com/deepin/daemon/InputDevice/Mouse"),
                 QObject *parent = nullptr);
    ~MouseService() override;

private:
    bool registerService();
    void unregisterService();

private:
    QString m_service;
    QString m_path;
    MouseAdaptor *m_mouseAdaptor;
    TrackPointAdaptor *m_trackPointAdaptor;
};

DINPUTDEVICES_END_NAMESPACE
#endif  // MOUSESERVICE_H
