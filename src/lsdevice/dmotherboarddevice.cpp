// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
#include "dmotherboarddevice.h"
#include "dlsdevice.h"

#include "scan.h"
#include "hw.h"

#include <QDebug>

DDEVICE_BEGIN_NAMESPACE

class DMotherboardDevicePrivate
{
public:
    explicit DMotherboardDevicePrivate(DMotherboardDevice *parent)
        : q_ptr(parent)
        , m_hwNode("computer", hw::sys_tem)
    {

        m_listDeviceInfo.clear();
        scan_system(m_hwNode);
        addDeviceInfo(m_hwNode, m_listDeviceInfo);
    }
    hwNode                    m_hwNode ;
    QList< DlsDevice::DDeviceInfo >      m_listDeviceInfo;
    void addDeviceInfo(hwNode &node, QList< DlsDevice::DDeviceInfo >  &infoLst);
    Q_DECLARE_PUBLIC(DMotherboardDevice)

private:
    DMotherboardDevice *q_ptr = nullptr;
};

void DMotherboardDevicePrivate::addDeviceInfo(hwNode &node, QList<DlsDevice::DDeviceInfo> &infoLst)
{
    struct DlsDevice::DDeviceInfo entry;

    entry.deviceInfoLstMap.clear();
    entry.devClass = DlsDevice::DtkProductSystem;

    entry.deviceBaseAttrisLst.append("Vendor");
    entry.deviceInfoLstMap.insert("Vendor", QString::fromStdString(node.getVendor()));
    entry.vendorName = QString::fromStdString(node.getVendor());

    entry.deviceBaseAttrisLst.append("Name");
    entry.deviceInfoLstMap.insert("Name", QString::fromStdString(node.getProduct()));
    entry.productName = QString::fromStdString(node.getProduct());

//--------------------------------ADD Children---------------------
    if (hw::sys_tem == node.getClass())
        infoLst.append(entry);
    for (int i = 0; i < node.countChildren(); i++) {
        addDeviceInfo(*node.getChild(i), infoLst);
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
//    return  d->m_listDeviceInfo[index].vendorName;

    return QString();
}

QString DMotherboardDevice::model()
{
    Q_D(DMotherboardDevice);
//    return  d->m_listDeviceInfo[index].productName;

    return QString();
}

QString DMotherboardDevice::date()
{
    return QString();
}

QString DMotherboardDevice::biosInformation()
{
    return QString();
}

QString DMotherboardDevice::chassisInformation()
{
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

DDEVICE_END_NAMESPACE
