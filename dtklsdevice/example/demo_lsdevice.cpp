// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

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

int main(int argc, char **argv)
{

    DlsDevice *computer = new DlsDevice();

    QList< device_info >  tmpLst1 = computer -> devicesInfosAll();
    for (auto value : tmpLst1) {

        qInfo() << "设备 --------- " << value.deviceInfoLstMap["sysID"];
        qInfo() << "BusInfo: " <<  value.deviceInfoLstMap["sysID"];
        qInfo() << "Description: " << value.deviceInfoLstMap["Description"];
        qInfo() << "Product Name: " <<  value.deviceInfoLstMap["Name"];
        qInfo() << "Vendor Name: " <<  value.deviceInfoLstMap["Vendor"];
        qInfo() << "Class Name: " <<  value.deviceInfoLstMap["ClassName"];
        qInfo() << "VID:PID " <<  value.deviceInfoLstMap["VID:PID"];
        qInfo() << "LogicalName: " <<  value.deviceInfoLstMap["LogicalName"];
        qInfo() << "Resources: " <<  value.deviceInfoLstMap["Resources"];
        qInfo() << "Configuration: " <<  value.deviceInfoLstMap["Configuration"];
    }

    devClass tmpClass ;
    QList< device_info >  tmpLst2;
    QStringList  tmpStringList1;
    QString tmpstr;

    tmpClass = DtkDisk;
    tmpStringList1 =  computer -> deviceAttris(tmpClass);
    qInfo() << tmpClass;
    for (auto value : tmpStringList1) {
        qInfo() << value;
    }
    tmpLst2 = computer ->deviceInfo(tmpClass);
    qInfo() << "---device  Attris---:";
    for (auto value2 : tmpLst2) {
        qInfo() << "--------\n:";
        for (auto value1 : tmpStringList1) {
            qInfo() << value1 << value2.deviceInfoLstMap[value1];
        }
    }

    tmpClass = DtkCpu;
    tmpStringList1 =  computer -> deviceAttris(tmpClass);
    qInfo() << tmpClass;
    for (auto value : tmpStringList1) {
        tmpstr.append(value + ", ");
    }
    qInfo() << tmpstr;
    qInfo() << "--------:\n";
    tmpLst2 = computer->deviceCPU();
    for (auto value2 : tmpLst2) {
        for (auto value1 : tmpStringList1) {
            qInfo() << value1 << value2.deviceInfoLstMap[value1];
        }
        qInfo() << "\n";
    }

    tmpClass = DtkDisplayGPU;
    tmpStringList1 =  computer -> deviceAttris(tmpClass);
    qInfo() << tmpClass;
    for (auto value : tmpStringList1) {
        tmpstr.append(value + ", ");
    }
    qInfo() << tmpstr;
    qInfo() << "--------:\n";
    tmpLst2 = computer->deviceGPU();
    for (auto value2 : tmpLst2) {
        for (auto value1 : tmpStringList1) {
            qInfo() << value1 << value2.deviceInfoLstMap[value1];
        }
        qInfo() << "\n";
    }

    tmpClass = DtkSoundAudio;
    tmpStringList1 =  computer -> deviceAttris(tmpClass);
    qInfo() << tmpClass;
    for (auto value : tmpStringList1) {
        tmpstr.append(value + ", ");
    }
    qInfo() << tmpstr;
    qInfo() << "--------:\n";
    tmpLst2 = computer->deviceCamera();
    for (auto value2 : tmpLst2) {
        for (auto value1 : tmpStringList1) {
            qInfo() << value1 << value2.deviceInfoLstMap[value1];
        }
        qInfo() << "\n";
    }

    delete computer;

    return 0;
}


