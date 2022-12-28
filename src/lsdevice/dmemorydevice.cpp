// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
#include "dmemorydevice.h"
#include "dlsdevice.h"

#include "scan.h"
#include "hw.h"

#include <QDebug>

DDEVICE_BEGIN_NAMESPACE

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
    QList< DlsDevice::DDeviceInfo >      m_listDeviceInfo;
    void addDeviceInfo(hwNode &node, QList< DlsDevice::DDeviceInfo >  &infoLst);
    Q_DECLARE_PUBLIC(DMemoryDevice)

private:
    DMemoryDevice *q_ptr = nullptr;
};

void DMemoryDevicePrivate::addDeviceInfo(hwNode &node, QList<DlsDevice::DDeviceInfo> &infoLst)
{
    struct DlsDevice::DDeviceInfo entry;

    entry.deviceInfoLstMap.clear();
    entry.devClass = DlsDevice::DtkMemory;

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

//--------------------------------ADD Children---------------------
    if (hw::memory == node.getClass())
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
        return  d->m_listDeviceInfo[index].deviceInfoLstMap.value("serialnumber");
    } else
        return QString();
}

QString DMemoryDevice::size(int index)
{
    return QString();
}

QString DMemoryDevice::swapSize()
{
    return QString();
}

QString DMemoryDevice::available()
{
    return QString();
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

DDEVICE_END_NAMESPACE
