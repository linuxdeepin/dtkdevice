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

    QStringList  tmpStringList1 =  computer -> deviceAttris(d_memory);
    qInfo() << "memory Attris:";
    for (auto value: tmpStringList1){
      qInfo() << value;


    }
      
  
   QList< device_info >  tmpLst1 = computer -> devicesInfosAll();
   for (auto value:tmpLst1) {

       qInfo() << "设备 --------- " << value.deviceInfoLstMap["sysID"];
        qInfo() << "businfo: " <<  value.deviceInfoLstMap["sysID"];
        qInfo() << "description: " << value.deviceInfoLstMap["Description"];
        qInfo() << "product_name: " <<  value.deviceInfoLstMap["Name"];
        qInfo() << "vendor_name: " <<  value.deviceInfoLstMap["Vendor"];
        qInfo() << "class_name: " <<  value.deviceInfoLstMap["ClassName"];
        qInfo() << "vid_pid: " <<  value.deviceInfoLstMap["vid:pid"];
        qInfo() << "modalias: " <<  value.deviceInfoLstMap["Modalias"];
   }


    QStringList  tmpStringList2 =  computer -> deviceAttris(d_memory);
    QList< device_info >  tmpLst2 = computer ->deviceInfo(d_memory);
    qInfo() << "memory Attris:";
    for (auto value2:tmpLst2){
      qInfo() << "---memory Attris---:";
      for (auto value1: tmpStringList2){
          qInfo() << value1 << value2.deviceInfoLstMap[value1];  
      }      
    }

    delete computer;

    return 0;
}


