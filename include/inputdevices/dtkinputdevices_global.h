// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
#ifndef DTKINPUTDEVICES_GLOBAL_H
#define DTKINPUTDEVICES_GLOBAL_H

#ifndef DTK_NAMESPACE
#    define DTK_NAMESPACE Dtk
#endif
#define DDEVICE_NAMESPACE InputDevices
#define DTK_DEVICE_NAMESPACE DTK_NAMESPACE::DDEVICE_NAMESPACE
#define DDEVICE_USE_NAMESPACE using namespace DTK_DEVICE_NAMESPACE;

#define DDEVICE_BEGIN_NAMESPACE                                                                                                  \
    namespace DTK_NAMESPACE {                                                                                                    \
    namespace DDEVICE_NAMESPACE {
#define DDEVICE_END_NAMESPACE                                                                                                    \
    }                                                                                                                            \
    }

#endif  // DTKINPUTDEVICES_GLOBAL_H
