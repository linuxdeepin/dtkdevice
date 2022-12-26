// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
#include "dlsdevice.h"
#include "dlsdevice_p.h"


#include "scan.h"

#include "../3rdparty/hw.h"

#include "osutils.h"

#include <cstring>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <termios.h>

#include <QString>
#include <QVector>
#include <QMap>
#include <QFile>
#include <QDebug>

#define PROC_CPU_STAT_PATH "/proc/stat"
#define PROC_CPU_INFO_PATH "/proc/cpuinfo"

using namespace hw;
DLSDEVICE_BEGIN_NAMESPACE

DlsDevicePrivate::DlsDevicePrivate(DlsDevice *parent)
    : m_hwNode("computer", hw::sys_tem)
    , q_ptr(parent)
{
    // m_classAttrisLstMap.clear();
    m_listDeviceInfo.clear();
    scan_system(m_hwNode);
    addDeviceInfo(m_hwNode, m_listDeviceInfo);

    // mLastCpuStat record the Cpu status
    // init  all  mLastCpuStat
    mLastCpuStat["user"] = 0;
    mLastCpuStat["nice"] = 0;
    mLastCpuStat["sys"] = 0;
    mLastCpuStat["idle"] = 0;
    mLastCpuStat["iowait"] = 0;
    mLastCpuStat["hardqirq"] = 0;
    mLastCpuStat["softirq"] = 0;
    mLastCpuStat["steal"] = 0;
    mLastCpuStat["guest"] = 0;
    mLastCpuStat["guest_nice"] = 0;
    // total is sum of above items
    mLastCpuStat["total"] = 0;

    updateSystemCpuUsage();
}

double DlsDevicePrivate::updateSystemCpuUsage()
{
    double cpuUsage = 0.0;

    QFile file(PROC_CPU_STAT_PATH);
    if (file.exists() && file.open(QFile::ReadOnly)) {

        QByteArray lineData = file.readLine();
        file.close();

        QStringList cpuStatus =  QString(lineData).split(" ", QString::SkipEmptyParts);

        if (cpuStatus.size() < 11) {
            return cpuUsage;
        }

        QMap<QString, int> curCpuStat;
        {
            curCpuStat["user"] = cpuStatus.at(1).toInt();
            curCpuStat["nice"] = cpuStatus.at(2).toInt();
            curCpuStat["sys"] = cpuStatus.at(3).toInt();
            curCpuStat["idle"] = cpuStatus.at(4).toInt();
            curCpuStat["iowait"] = cpuStatus.at(5).toInt();
            curCpuStat["hardqirq"] = cpuStatus.at(6).toInt();
            curCpuStat["softirq"] = cpuStatus.at(7).toInt();
            curCpuStat["steal"] = cpuStatus.at(8).toInt();
            curCpuStat["guest"] = cpuStatus.at(9).toInt();
            curCpuStat["guest_nice"] = cpuStatus.at(10).toInt();
        }

        int curTotalCpu = 0;
        for (int i = 1; i <= 10; i++) {
            curTotalCpu = curTotalCpu + cpuStatus.at(i).toInt();
        }
        curCpuStat["total"] = curTotalCpu;

        double calcCpuTotal = curCpuStat["total"] - mLastCpuStat["total"];
        double calcCpuIdle =
            (curCpuStat["idle"] + curCpuStat["iowait"]) - (mLastCpuStat["idle"] + mLastCpuStat["iowait"]);

        if (calcCpuTotal == 0.0) {
            qWarning() << " cpu total usage calc result equal 0 ! cpu stat [" << curCpuStat << "]";
            return cpuUsage;
        }

        cpuUsage = (calcCpuTotal - calcCpuIdle) * 100.0 / calcCpuTotal;


        mCpuUsage = cpuUsage;

        mLastCpuStat = curCpuStat;
    } else {
        qWarning() << QString(" file %1 open fail !").arg(PROC_CPU_STAT_PATH);
    }

    return cpuUsage;
}

QMap<QString, int> DlsDevicePrivate::CpuStat()
{
    return mLastCpuStat;
}

double DlsDevicePrivate::getCpuUsage()
{
    return mCpuUsage;
}

void DlsDevicePrivate::addDeviceInfo(hwNode &node, QList<DDeviceInfo > &ll)
{
    struct DDeviceInfo entry;

    entry.deviceInfoLstMap.clear();
    entry.deviceInfoLstMap.clear();
    entry.devClass = DtkUnkown;

    if (node.getBusInfo() != "") {
        entry.deviceBaseAttrisLst.append("SysFs_PATH");
        entry.deviceInfoLstMap["SysFs_PATH"] = QString::fromStdString(node.getBusInfo());
    }

    entry.devClass = convertClass(node.getClass());
    entry.subClassName = QString::fromStdString(node.getsubClassName());

    entry.deviceBaseAttrisLst.append("Description");
    entry.deviceInfoLstMap.insert("Description", QString::fromStdString(node.getDescription()));

    entry.deviceBaseAttrisLst.append("sysID");
    entry.deviceInfoLstMap.insert("sysID", QString::fromStdString(node.getId()));

    entry.deviceBaseAttrisLst.append("Vendor");
    entry.deviceInfoLstMap.insert("Vendor", QString::fromStdString(node.getVendor()));


    entry.deviceBaseAttrisLst.append("Name");
    entry.deviceInfoLstMap.insert("Name", QString::fromStdString(node.getProduct()));

    if (! node.getVendor_id().empty()) {
        entry.deviceBaseAttrisLst.append("Vendor_ID");
        entry.deviceInfoLstMap.insert("Vendor_ID", QString::fromStdString(node.getVendor_id()));
    }

    if (! node.getProduct_id().empty()) {
        entry.deviceBaseAttrisLst.append("Product_ID");
        entry.deviceInfoLstMap.insert("Product_ID", QString::fromStdString(node.getProduct_id()));
    }

    if (! node.getConfig("vid:pid").empty()) {
        entry.deviceBaseAttrisLst.append("VID:PID");
        entry.deviceInfoLstMap.insert("VID:PID", QString::fromStdString(node.getConfig("vid:pid")));
    }

    if (node.getModalias().length() > 53) {
        entry.deviceBaseAttrisLst.append("Modalias");
        entry.deviceInfoLstMap.insert("Modalias", QString::fromStdString(node.getModalias().substr(0, 53)));
    }

    else {
        entry.deviceBaseAttrisLst.append("Modalias");
        entry.deviceInfoLstMap.insert("Modalias", QString::fromStdString(node.getModalias()));
    }

    entry.deviceBaseAttrisLst.append("ClassName");
    entry.deviceInfoLstMap.insert("ClassName", QString::fromStdString(node.getClassName()));


    if (node.getLogicalName() != "") {
        vector<string> logicalnames = node.getLogicalNames();
        QString  tmps = "";

        for (unsigned int i = 0; i < logicalnames.size(); i++) {
            tmps.append(QString::fromStdString(logicalnames[i]));
            if (i >= logicalnames.size())
                break;
            tmps.append(" ");
        }
        entry.deviceBaseAttrisLst.append("LogicalName");
        entry.deviceInfoLstMap.insert("LogicalName", tmps);
    }

    vector < string > config;
    config = node.getConfigValues("=");

    if (config.size() > 0) {
        QString  tmps = "";
        for (unsigned int i = 0; i < config.size(); i++) {
            tmps.append(QString::fromStdString(config[i]));
            if (i >= config.size())
                break;
            tmps.append(" ");
        }
        entry.deviceBaseAttrisLst.append("Configuration");
        entry.deviceInfoLstMap.insert("Configuration", tmps);
    }

    vector < string > resources;
    resources = node.getResources(":");
    if (resources.size() > 0) {
        QString  tmps = "";
        for (unsigned int i = 0; i < resources.size(); i++) {
            tmps.append(QString::fromStdString(resources[i]));
            if (i >= resources.size())
                break;
            tmps.append(" ");
        }
        entry.deviceBaseAttrisLst.append("Resources");
        entry.deviceInfoLstMap.insert("Resources", tmps);
    }
    if (node.getSize() > 0) {
        string tmpstr = "";

        switch (node.getClass()) {
        case hw::disk:
            tmpstr = kilobytes(node.getSize()) + " (" + decimalkilos(node.getSize()) + "B)";
            break;
        case hw::display:
        case hw::memory:
        case hw::address:
        case hw::storage:
        case hw::volume:
            tmpstr =  kilobytes(node.getSize());
            break;
        case hw::processor:
        case hw::bus:
        case hw::sys_tem:
            tmpstr =  decimalkilos(node.getSize()) + "Hz";
            break;
        case hw::network:
            tmpstr =  decimalkilos(node.getSize()) + "bit/s";
            break;
        case hw::power:
            tmpstr =  node.getSize() + "mWh";
            break;
        default:
            tmpstr =   node.getSize();
        }
        entry.deviceBaseAttrisLst.append("Size");
        entry.deviceInfoLstMap.insert("Size", QString::fromStdString(tmpstr));
    }
//--------------------------------ADD Children---------------------
    ll.append(entry);
    for (int i = 0; i < node.countChildren(); i++) {
        addDeviceInfo(*node.getChild(i), ll);
    }
}

DevClass DlsDevicePrivate::convertClass(hw::hwClass cc)
{
    switch (cc) {
    case bridge:  return DtkBridge;
    case sys_tem:  return DtkProductSystem;
    case memory:  return DtkMemory;
    case processor: return DtkCpu;
    case address:   return   DtkAddress;
    case storage:   return   DtkStorage;
    case disk:      return   DtkDisk;
    case tape:      return   DtkTape;
    case bus:       return   DtkBus;
    case network:   return   DtkNetwork;
    case display:   return   DtkDisplayGPU;
    case input:     return   DtkInput;
    case printer:   return   DtkPrinter;
    case multimedia: return   DtkSoundAudio;
    case communication: return DtkCommunication;
    case power:       return  DtkPower;
    case volume:      return  DtkVolume;
    case generic:     return  DtkGeneric;
    default:          return  DtkUnkown;
    }
}

hwClass DlsDevicePrivate::convertClass(DevClass cc)
{
    switch (cc) {
    case DtkBridge:  return bridge;
    case DtkProductSystem:  return sys_tem;
    case DtkMemory:  return memory;
    case DtkCpu: return processor;
    case DtkAddress:   return   address;
    case DtkStorage:   return   storage;
    case DtkDisk:      return   disk;
    case DtkTape:      return   tape;
    case DtkBus:       return   bus;
    case DtkNetwork:   return   network;
    case DtkDisplayGPU:   return   display;
    case DtkInput:     return   input;
    case DtkPrinter:   return   printer;
    case DtkSoundAudio: return   multimedia;
    case DtkCommunication: return communication;
    case DtkPower:       return  power;
    case DtkVolume:      return  volume;
    case DtkGeneric:     return  generic;
    default:          return  generic;
    }
}

QList<DDeviceInfo> DlsDevicePrivate::deviceCPU()
{
    QList<DDeviceInfo >  infoList;
    for (int it = 0; it < m_listDeviceInfo.count(); it++) {
        if ((m_listDeviceInfo.at(it).devClass == DtkCpu))
            infoList.append(m_listDeviceInfo.at(it));
    }
    return infoList;
}

QList<DDeviceInfo> DlsDevicePrivate::deviceStorage()
{
    QList<DDeviceInfo >  infoList;
    for (int it = 0; it < m_listDeviceInfo.count(); it++) {
        if ((m_listDeviceInfo.at(it).devClass == DtkDisk) \
                || (m_listDeviceInfo.at(it).devClass == DtkStorage))
            infoList.append(m_listDeviceInfo.at(it));
    }
    return infoList;
}

QList<DDeviceInfo> DlsDevicePrivate::deviceGPU()
{
    QList<DDeviceInfo >  infoList;
    for (int it = 0; it < m_listDeviceInfo.count(); it++) {
        if ((m_listDeviceInfo.at(it).devClass == DtkDisplayGPU))
            infoList.append(m_listDeviceInfo.at(it));
    }
    return infoList;
}

QList<DDeviceInfo> DlsDevicePrivate::deviceMemory()
{
    QList<DDeviceInfo >  infoList;
    for (int it = 0; it < m_listDeviceInfo.count(); it++) {
        if ((m_listDeviceInfo.at(it).devClass == DtkMemory))
            infoList.append(m_listDeviceInfo.at(it));
    }
    return infoList;
}

QList<DDeviceInfo> DlsDevicePrivate::deviceMonitor()
{
//todo
}


QList<DDeviceInfo> DlsDevicePrivate::deviceAudio()
{
    QList<DDeviceInfo >  infoList;
    for (int it = 0; it < m_listDeviceInfo.count(); it++) {
        if ((m_listDeviceInfo.at(it).devClass == DtkSoundAudio))
            infoList.append(m_listDeviceInfo.at(it));
    }
    return infoList;
}

QList<DDeviceInfo> DlsDevicePrivate::deviceNetwork()
{
    QList<DDeviceInfo >  infoList;
    for (int it = 0; it < m_listDeviceInfo.count(); it++) {
        if ((m_listDeviceInfo.at(it).devClass == DtkNetwork))
            infoList.append(m_listDeviceInfo.at(it));
    }
    return infoList;
}

QList<DDeviceInfo> DlsDevicePrivate::deviceCamera()
{
    QList<DDeviceInfo >  infoList;
    for (int it = 0; it < m_listDeviceInfo.count(); it++) {
        //if (m_ListDeviceInfo.at(it).eDevClass == DtkInput)
        if (m_listDeviceInfo.at(it).subClassName == "camera")
            infoList.append(m_listDeviceInfo.at(it));
    }
    return infoList;
}

QList<DDeviceInfo> DlsDevicePrivate::deviceKeyboard()
{
    QList<DDeviceInfo >  infoList;
    for (int it = 0; it < m_listDeviceInfo.count(); it++) {
        if (m_listDeviceInfo.at(it).devClass == DtkInput)
            if (m_listDeviceInfo.at(it).subClassName == "keyboard")
                infoList.append(m_listDeviceInfo.at(it));
    }
    return infoList;
}

QList<DDeviceInfo> DlsDevicePrivate::deviceMouse()
{
    QList<DDeviceInfo >  infoList;
    for (int it = 0; it < m_listDeviceInfo.count(); it++) {
        if (m_listDeviceInfo.at(it).devClass == DtkInput)
            if (m_listDeviceInfo.at(it).subClassName == "mouse")
                infoList.append(m_listDeviceInfo.at(it));
    }
    return infoList;
}

QList<DDeviceInfo> DlsDevicePrivate::deviceComputer()
{
    QList<DDeviceInfo >  infoList;
    for (int it = 0; it < m_listDeviceInfo.count(); it++) {
        if ((m_listDeviceInfo.at(it).devClass == DtkProductSystem))
            infoList.append(m_listDeviceInfo.at(it));
    }
    return infoList;
}

DLSDEVICE_END_NAMESPACE
