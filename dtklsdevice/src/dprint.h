#ifndef _PRINT_H_
#define _PRINT_H_

#include "../3rdparty/hw.h"
#include "dlsdevice.h"
#include "dtklsdevice_global.h"

using namespace hw;
DLSDEVICE_BEGIN_NAMESPACE

// void print(hwNode & node, bool html=true, int level = 0);
void addDeviceInfo(hwNode & node, QList < device_info > &ll);
// void printhwpath(hwNode & node);
void printbusinfo(hwNode & node);

void status(const char *);
// Dtk::lsDevice::devClass devClass(hw::hwClass cc);
// hw::hwClass  devClass(Dtk::lsDevice::devClass cc);

DLSDEVICE_END_NAMESPACE

#endif
