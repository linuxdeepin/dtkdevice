// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
#include "scan.h"
#include "../3rdparty/hw.h"
#include "dlsdevicetypes.h"
#include "dcpudevice.h"

#include <QDebug>

DLSDEVICE_BEGIN_NAMESPACE

class DCpuDevicePrivate
{
public:
    explicit DCpuDevicePrivate(DCpuDevice *parent)
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
    Q_DECLARE_PUBLIC(DCpuDevice)
private:
    DCpuDevice *q_ptr = nullptr;
};

void DCpuDevicePrivate::addDeviceInfo(hwNode &node, QList<DDeviceInfo> &infoLst)
{
    struct DDeviceInfo entry;

    entry.deviceInfoLstMap.clear();
    entry.devClass = DtkCpu;

    entry.deviceBaseAttrisLst.append("Vendor");
    entry.deviceInfoLstMap.insert("Vendor", QString::fromStdString(node.getVendor()));
    entry.vendorName = QString::fromStdString(node.getVendor());

    entry.deviceBaseAttrisLst.append("Name");
    entry.deviceInfoLstMap.insert("Name", QString::fromStdString(node.getProduct()));
    entry.productName = QString::fromStdString(node.getProduct());

//--------------------------------ADD Children---------------------
    if (hw::processor == node.getClass())
        infoLst.append(entry);
    for (int i = 0; i < node.countChildren(); i++) {
        addDeviceInfo(*node.getChild(i), infoLst);
    }
}

DCpuDevice::DCpuDevice(QObject *parent)
    : QObject(parent)
    , d_ptr(new DCpuDevicePrivate(this))
{
}

DCpuDevice::~DCpuDevice()
{
}

int DCpuDevice::physicalCount()
{
    Q_D(DCpuDevice);
    return  d->m_listDeviceInfo.count();
}

int DCpuDevice::coreCount(int physicalID)
{
    return 0;
}

int DCpuDevice::threadCount(int physicalID, int coreID)
{
    return 0;
}

int DCpuDevice::physicalID(int processorID)
{
    return -1;
}

int DCpuDevice::coreID(int processorID)
{
    return -1;
}

QString DCpuDevice::architecture(int physicalID)
{
    return QString();
}

QString DCpuDevice::vendor(int physicalID)
{
    Q_D(DCpuDevice);
//    if (index < d->m_listDeviceInfo.count())
//    {
//        return  d->m_listDeviceInfo[index].vendorName;
//    } else
    return QString();
}

QString DCpuDevice::model(int physicalID)
{
    Q_D(DCpuDevice);
//    if (index < d->m_listDeviceInfo.count()) {
//        return  d->m_listDeviceInfo[index].productName;
//    } else
    return QString();
}

QString DCpuDevice::minFreq(int processorID)
{
    return QString();
}

QString DCpuDevice::maxFreq(int processorID)
{
    return QString();
}

QString DCpuDevice::cache(int processorID, QString type)
{
    return QString();
}

QString DCpuDevice::flags(int processorID)
{
    return QString();
}

QString DCpuDevice::stepping(int processorID)
{
    return QString();
}

QString DCpuDevice::family(int processorID)
{
    return QString();
}

QString DCpuDevice::bogoMIPS(int processorID)
{
    return QString();
}

QString DCpuDevice::temperature(int physicalID)
{
    return QString();
}

QString DCpuDevice::currentFreq(int processorID)
{
    return QString();
}

DCpuStat DCpuDevice::stat()
{

}

DCpuUsage DCpuDevice::usage()
{

}

DCpuStat DCpuDevice::stat(int processorID)
{
    return DCpuStat();
}

DCpuUsage DCpuDevice::usage(int processorID)
{
    return DCpuUsage();
}

DLSDEVICE_END_NAMESPACE
