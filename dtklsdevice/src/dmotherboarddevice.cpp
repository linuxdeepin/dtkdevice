// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
#include "scan.h"
#include "../3rdparty/hw.h"
#include "dlsdevicetypes.h"
#include "dmotherboarddevice.h"

#include <QDebug>

DLSDEVICE_BEGIN_NAMESPACE

class DMotherboardDevicePrivate
{
public:
    explicit DMotherboardDevicePrivate(DMotherboardDevice *parent)
        : q_ptr(parent)
        , m_hwNode("computer", hw::sys_tem)
    {

        m_listsystemInfo.clear();
        scan_system(m_hwNode);
        addDeviceInfo(m_hwNode, m_listsystemInfo, hw::sys_tem);
        addDeviceInfo(m_hwNode, m_listMotherboardInfo, hw::motherboard);
        addDeviceInfo(m_hwNode, m_listbiosInfo, hw::bios);
    }
    hwNode                    m_hwNode ;

    void addDeviceInfo(hwNode &node, QList< DDeviceInfo >  &infoLst, hw::hwClass);
    Q_DECLARE_PUBLIC(DMotherboardDevice)

private:
    DMotherboardDevice *q_ptr = nullptr;
    QList< DDeviceInfo >      m_listsystemInfo;
    QList< DDeviceInfo >      m_listMotherboardInfo;
    QList< DDeviceInfo >      m_listbiosInfo;
};

/*
computer----system ]
    description = Desktop Computer
    vendor = TSINGHUA TONGFANG COMPUTER
    product = E500 (800017761)
    serial = 2200980001776100571
    width = 64 bits
    capabilities = smbios-3.2.0 dmi-3.2.0 smp
    configuration: boot=normal chassis=desktop family=ChaoYue sku=800017761 uuid=2e59a1a8-78f4-2020-0927-141409000000
  [ motherboard----Motherboard ]
       description = Motherboard
       vendor = TSINGHUA TONGFANG COMPUTER
       product = B460M-HDV(RD)
       physical id = 0
       version = 1.00
       serial = M80-D5014000249
     [ firmware----bios ]
          description = BIOS
          vendor = American Megatrends Inc.
          physical id = 0
          version = P008NJ0
          date = 08/21/2020
          size = 65536
          capacity = 16777216
          capabilities = pci upgrade shadowing cdboot bootselect socketedrom edd int13floppy1200 int13floppy720 int13floppy2880 int5printscreen int9keyboard int14serial int17printer acpi usb biosbootspecification uefi

*/
void DMotherboardDevicePrivate::addDeviceInfo(hwNode &node, QList<DDeviceInfo> &infoLst, hw::hwClass cls)
{
    struct DDeviceInfo entry;

    entry.deviceInfoLstMap.clear();
    entry.devClass = DtkProductSystem;

    entry.deviceBaseAttrisLst.append("Vendor");
    entry.deviceInfoLstMap.insert("Vendor", QString::fromStdString(node.getVendor()));
    entry.vendorName = QString::fromStdString(node.getVendor());

    entry.deviceBaseAttrisLst.append("Name");
    entry.deviceInfoLstMap.insert("Name", QString::fromStdString(node.getProduct()));
    entry.productName = QString::fromStdString(node.getProduct());

    entry.deviceBaseAttrisLst.append("data");
    entry.deviceInfoLstMap.insert("data", QString::fromStdString(node.getDate()));

    if (! node.getConfig("chassis").empty()) {
        entry.deviceBaseAttrisLst.append("chassis");
        entry.deviceInfoLstMap.insert("chassis", QString::fromStdString(node.getConfig("chassis")));
    }

//--------------------------------ADD Children---------------------
    if (cls == node.getClass())
        infoLst.append(entry);

    for (int i = 0; i < node.countChildren(); i++) {
        addDeviceInfo(*node.getChild(i), infoLst, cls);
    }
}

DMotherboardDevice::DMotherboardDevice(QObject *parent)
    : QObject(parent)
    , d_ptr(new DMotherboardDevicePrivate(this))
{
}

DMotherboardDevice::~DMotherboardDevice()
{
}

QString DMotherboardDevice::vendor()
{
    Q_D(DMotherboardDevice);
    if (d->m_listMotherboardInfo.count() > 0)
        return  d->m_listMotherboardInfo[0].vendorName;

    return QString();
}

QString DMotherboardDevice::model()
{
    Q_D(DMotherboardDevice);
    if (d->m_listMotherboardInfo.count() > 0)
        return  d->m_listMotherboardInfo[0].productName;

    return QString();
}

QString DMotherboardDevice::date()
{
    Q_D(DMotherboardDevice);
    if (d->m_listbiosInfo.count() > 0)
        return  d->m_listbiosInfo[0].deviceInfoLstMap.value("data");
    return QString();
}

QString DMotherboardDevice::biosInformation()
{
    Q_D(DMotherboardDevice);
    if (d->m_listbiosInfo.count() > 0)
        return  d->m_listbiosInfo[0].vendorName + d->m_listbiosInfo[0].productName;
    return QString();
}

QString DMotherboardDevice::chassisInformation()
{
    Q_D(DMotherboardDevice);
    if (d->m_listsystemInfo.count() > 0)
        return  d->m_listsystemInfo[0].deviceInfoLstMap.value("chassis");
    return QString();
}

QString DMotherboardDevice::PhysicalMemoryArrayInformation()
{
    return QString();
}

QString DMotherboardDevice::temperature()
{
    return QString();
}

DLSDEVICE_END_NAMESPACE
