// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
#include "scan.h"
#include "../3rdparty/hw.h"
#include "ddiskdevice.h"
#include "dlsdevicetypes.h"

#include "dmemorydevice.h"
//#include "DMemoryDevice.h"
#include <QDebug>

DLSDEVICE_BEGIN_NAMESPACE

class DMemoryDevicePrivate
{
public:
    explicit DMemoryDevicePrivate(DMemoryDevice *parent)
        : q_ptr(parent)
        , m_hwNode("computer", hw::sys_tem)
    {
        m_listDeviceInfo.clear();
        scan_system(m_hwNode);
        addDeviceInfo(m_hwNode, m_listDeviceInfo);
    }
    hwNode                    m_hwNode ;
    QList< DDeviceInfo >      m_listDeviceInfo;
    void addDeviceInfo(hwNode &node, QList< DDeviceInfo >  &infoLst);
    Q_DECLARE_PUBLIC(DMemoryDevice)

private:
    DMemoryDevice *q_ptr = nullptr;
};
/*
     [ ddr----ddr ]
          description = DIMM DDR4 Synchronous 2667 MHz (0.4 ns)
          vendor = Hitachi
          product = TMKU8G68AHFHC-26V
          physical id = b
          serial = 00002791
          slot = ChannelA-DIMM0
          size = 8589934592
          width = 64 bits
          clock = 2667MHz
          configuration: MemAvailable=2817952 kB MemFree=563700 kB MemTotal=8068476 kB MemUsage=65 %
*/
void DMemoryDevicePrivate::addDeviceInfo(hwNode &node, QList<DDeviceInfo> &infoLst)
{
    struct DDeviceInfo entry;

    entry.deviceInfoLstMap.clear();
    entry.devClass = DtkMemory;

    if (node.getBusInfo() != "") {
        entry.deviceBaseAttrisLst.append("SysFs_PATH");
        entry.deviceInfoLstMap["SysFs_PATH"] = QString::fromStdString(node.getBusInfo());
    }

    entry.subClassName = QString::fromStdString(node.getsubClassName());

    entry.deviceBaseAttrisLst.append("Description");
    entry.deviceInfoLstMap.insert("Description", QString::fromStdString(node.getDescription()));

    entry.deviceBaseAttrisLst.append("sysID");
    entry.deviceInfoLstMap.insert("sysID", QString::fromStdString(node.getId()));

    entry.deviceBaseAttrisLst.append("Vendor");
    entry.deviceInfoLstMap.insert("Vendor", QString::fromStdString(node.getVendor()));
    entry.vendorName = QString::fromStdString(node.getVendor());

    entry.deviceBaseAttrisLst.append("Name");
    entry.deviceInfoLstMap.insert("Name", QString::fromStdString(node.getProduct()));
    entry.productName = QString::fromStdString(node.getProduct());

    if (node.getSize() > 0) {
        string size = to_string(node.getSize());
        entry.deviceBaseAttrisLst.append("size");
        entry.deviceInfoLstMap.insert("size",  QString::fromStdString(size));
    }

//    entry.deviceInfoLstMap.insert("speed", QString::fromStdString(node.getClock()));
    entry.deviceInfoLstMap.insert("serial", QString::fromStdString(node.getSerial()));
//    entry.deviceInfoLstMap.insert("width", QString::fromStdString(node.getWidth()));
    entry.deviceInfoLstMap.insert("type", QString::fromStdString(node.getDescription()));
    entry.deviceInfoLstMap.insert("MemAvailable", QString::fromStdString(node.getConfig("MemAvailable")));

//--------------------------------ADD Children---------------------
    if (hw::ddr == node.getClass())
        infoLst.append(entry);
    for (int i = 0; i < node.countChildren(); i++) {
        addDeviceInfo(*node.getChild(i), infoLst);
    }
}

DMemoryDevice::DMemoryDevice(QObject *parent)
    : QObject(parent)
    , d_ptr(new DMemoryDevicePrivate(this))
{
}

DMemoryDevice::~DMemoryDevice()
{
}

int DMemoryDevice::count()
{
    Q_D(DMemoryDevice);
    return  d->m_listDeviceInfo.count();
}

QString DMemoryDevice::vendor(int index)
{
    Q_D(DMemoryDevice);
    if (index < d->m_listDeviceInfo.count()) {
        return  d->m_listDeviceInfo[index].vendorName;
    } else
        return QString();
}

QString DMemoryDevice::model(int index)
{
    Q_D(DMemoryDevice);
    if (index < d->m_listDeviceInfo.count()) {
        return  d->m_listDeviceInfo[index].productName;
    } else
        return QString();
}


QString DMemoryDevice::totalWidth(int index)
{
    return QString();
}

QString DMemoryDevice::dataWidth(int index)
{
    return QString();
}

/*
     [ ddr----ddr ]
          description = DIMM DDR4 Synchronous 2667 MHz (0.4 ns)
          vendor = Hitachi
          product = TMKU8G68AHFHC-26V
          physical id = b
          serial = 00002791
          slot = ChannelA-DIMM0
          size = 8589934592
          width = 64 bits
          clock = 2667MHz
          configuration: MemAvailable=2817952 kB MemFree=563700 kB MemTotal=8068476 kB MemUsage=65 %
*/
QString DMemoryDevice::type(int index)
{
    Q_D(DMemoryDevice);
    if (index < d->m_listDeviceInfo.count())  {
        return  d->m_listDeviceInfo[index].deviceInfoLstMap.value("type");
    } else
        return QString();
}

QString DMemoryDevice::speed(int index)
{
    Q_D(DMemoryDevice);
    if (index < d->m_listDeviceInfo.count())  {
        return  d->m_listDeviceInfo[index].deviceInfoLstMap.value("speed");
    } else
        return QString();
}

QString DMemoryDevice::serialNumber(int index)
{
    Q_D(DMemoryDevice);
    if (index < d->m_listDeviceInfo.count())  {
        return  d->m_listDeviceInfo[index].deviceInfoLstMap.value("serial");
    } else
        return QString();
}

QString DMemoryDevice::size(int index)
{
    Q_D(DMemoryDevice);
    if (index < d->m_listDeviceInfo.count()) {
        return  d->m_listDeviceInfo[index].deviceInfoLstMap.value("size");
    } else
        return QString();
}

QString DMemoryDevice::swapSize()
{
    return QString();
}

QString DMemoryDevice::available()
{
    Q_D(DMemoryDevice);
    return QString(); //return  d->m_listDeviceInfo.deviceInfoLstMap.value("MemAvailable");
}

QString DMemoryDevice::buffers()
{
    return QString();
}

QString DMemoryDevice::cached()
{
    return QString();
}

QString DMemoryDevice::active()
{
    return QString();
}

QString DMemoryDevice::inactive()
{
    return QString();
}

QString DMemoryDevice::sharedSize()
{
    return QString();
}

QString DMemoryDevice::swapFree()
{
    return QString();
}

QString DMemoryDevice::swapCached()
{
    return QString();
}

QString DMemoryDevice::slab()
{
    return QString();
}

QString DMemoryDevice::dirty()
{
    return QString();
}

QString DMemoryDevice::mapped()
{
    return QString();
}

DLSDEVICE_END_NAMESPACE
