// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
#ifndef DTKINPUTDEVICES_GLOBAL_H
#define DTKINPUTDEVICES_GLOBAL_H

#ifndef DTK_NAMESPACE
#    define DTK_NAMESPACE Dtk
#endif
#define DINPUTDEVICES_NAMESPACE InputDevices
#define DTK_INPUTDEVICES_NAMESPACE DTK_NAMESPACE::DINPUTDEVICES_NAMESPACE
#define DINPUTDEVICES_USE_NAMESPACE using namespace DTK_INPUTDEVICES_NAMESPACE;

#define DINPUTDEVICES_BEGIN_NAMESPACE                                                                                            \
    namespace DTK_NAMESPACE {                                                                                                    \
    namespace DINPUTDEVICES_NAMESPACE {
#define DINPUTDEVICES_END_NAMESPACE                                                                                              \
    }                                                                                                                            \
    }

#endif  // DTKINPUTDEVICES_GLOBAL_H
