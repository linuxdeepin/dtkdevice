#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>


#include <QDebug>
#include <QString>
#include "dtklsdevice_global.h"
#include "dlsdevice.h"
#include "dlsdevicetypes.h"
#ifndef NONLS
#include <locale.h>
#endif

DLSDEVICE_USE_NAMESPACE

// int main_getjobinfo(int argc, char *argv[]);
// int main_ddesysinfo(int argc, char *argv[]);



int main(int argc,char **argv)
{

  DlsDevice *computer = new DlsDevice();

  computer->init_system();
//  computer->show();
   QList< device_info >  tmp = computer -> dAllDevicesInfos();

  for (auto it = tmp.begin(); it != tmp.end(); ++it) {
      qInfo() << "设备 --------- " << it->id;
      qInfo() << "hwclass: " << it->deviceclass;   //设备枚举值

      qInfo() << "businfo: " << it->businfo;
      qInfo() << "description: " << it->description;
      qInfo() << "product_name: " << it->product_name;
      qInfo() << "vendor_name: " << it->vendor_name;
      qInfo() << "class_name: " << it->class_name;
      qInfo() << "vid_pid: " << it->vid_pid;
      qInfo() << "modalias: " << it->modalias;    //获取设备  Modalias  即硬件ID号

  }

devClass lsclass = d_memory;
 tmp = computer -> dDevicesInfoByClass(lsclass);
 for (auto it = tmp.begin(); it != tmp.end(); ++it) {
     qInfo() << "设备设备枚举值 --------- " << it->deviceclass;  //设备枚举值
     qInfo() << "hwclass: " << it->id;
     qInfo() << "businfo: " << it->businfo;
     qInfo() << "description: " << it->description;
     qInfo() << "product_name: " << it->product_name;
     qInfo() << "vendor_name: " << it->vendor_name;
     qInfo() << "class_name: " << it->class_name;
     qInfo() << "vid_pid: " << it->vid_pid;
     qInfo() << "modalias: " << it->modalias;    //获取设备  Modalias  即硬件ID号
 }

 delete computer;

  // main_getjobinfo(argc, argv);
  // main_ddesysinfo(argc, argv);

  return 0;
}


