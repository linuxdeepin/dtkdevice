// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
#include "scan.h"
#include "../3rdparty/hw.h"
#include "dlsdevicetypes.h"
#include "dnetdevice.h"

#include <QDebug>

DLSDEVICE_BEGIN_NAMESPACE

class DNetDevicePrivate
{
public:
    explicit DNetDevicePrivate(DNetDevice *parent)
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
    Q_DECLARE_PUBLIC(DNetDevice)

private:
    DNetDevice *q_ptr = nullptr;
};


void DNetDevicePrivate::addDeviceInfo(hwNode &node, QList<DDeviceInfo> &infoLst)
{
    struct DDeviceInfo entry;

    entry.deviceInfoLstMap.clear();
    entry.devClass = DtkNetwork;

    if (node.getBusInfo() != "") {
        entry.deviceBaseAttrisLst.append("SysFs_PATH");
        entry.deviceInfoLstMap["SysFs_PATH"] = QString::fromStdString(node.getBusInfo());
    }

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

    if (! node.getVendor_id().empty()) {
        entry.deviceBaseAttrisLst.append("Vendor_ID");
        entry.deviceInfoLstMap.insert("Vendor_ID", QString::fromStdString(node.getVendor_id()));
        entry.vendorID = QString::fromStdString(node.getVendor_id());
    }

    if (! node.getProduct_id().empty()) {
        entry.deviceBaseAttrisLst.append("Product_ID");
        entry.deviceInfoLstMap.insert("Product_ID", QString::fromStdString(node.getProduct_id()));
        entry.productID = QString::fromStdString(node.getProduct_id());
    }

    if (! node.getConfig("vid:pid").empty()) {
        entry.deviceBaseAttrisLst.append("VID:PID");
        entry.deviceInfoLstMap.insert("VID:PID", QString::fromStdString(node.getConfig("vid:pid")));
    }

    if (node.getModalias().length() > 53) {
        entry.deviceBaseAttrisLst.append("Modalias");
        entry.deviceInfoLstMap.insert("Modalias", QString::fromStdString(node.getModalias().substr(0, 53)));
    } else {
        entry.deviceBaseAttrisLst.append("Modalias");
        entry.deviceInfoLstMap.insert("Modalias", QString::fromStdString(node.getModalias()));
    }

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

    if (! node.getConfig("driver").empty()) {
        entry.deviceBaseAttrisLst.append("driver");
        entry.deviceInfoLstMap.insert("driver", QString::fromStdString(node.getConfig("driver")));
    }

    if (! node.getConfig("driverversion").empty()) {
        entry.deviceBaseAttrisLst.append("driverversion");
        entry.deviceInfoLstMap.insert("driverversion", QString::fromStdString(node.getConfig("driverversion")));
    }
    if (! node.getSerial().empty()) {
        entry.deviceBaseAttrisLst.append("macAddress");
        entry.deviceInfoLstMap.insert("macAddress", QString::fromStdString(node.getSerial()));
    }

    if (! node.getConfig("proc_net_dev_data").empty()) {
        entry.deviceBaseAttrisLst.append("proc_net_dev_data");
        entry.deviceInfoLstMap.insert("proc_net_dev_data", QString::fromStdString(node.getConfig("proc_net_dev_data")));
    }
//------- ADD Children-------
    if ((hw::disk == node.getClass()) || (hw::storage == node.getClass()))
        infoLst.append(entry);
    for (int i = 0; i < node.countChildren(); i++) {
        addDeviceInfo(*node.getChild(i), infoLst);
    }
}

/*
$ sudo ./lshw -c network
请输入密码:
验证成功
  [ network----network ]
       description = Ethernet interface
       vid:pid = 8086:0D55
       Modalias = pci:v00008086d00000D55sv00001849sd00000D55bc02sc00i00
       vendor = Intel Corporation [8086]
       product = Ethernet Connection (12) I219-V [8086:0D55]
       physical id = 1f.6
       bus_info = pci@0000:00:1f.6
       sysfs_path = /sys/devices/pci0000:00/0000:00:1f.6
       logical name = eno1 ,
       version = 00
       serial = a8:a1:59:2e:f4:78
       size = 1Gbit/s
       capacity = 1Gbit/s
       width = 32 bits
       clock = 33MHz
       capabilities = pm msi bus_master cap_list ethernet physical tp 10bt 10bt-fd 100bt 100bt-fd 1000bt-fd autonegotiation
       configuration: Product_ID=0D55 Vendor_ID=8086 autonegotiation=on broadcast=yes class:vid:pid=0200:8086:0D55 driver=e1000e driverversion=5.15.34-amd64-desktop duplex=full firmware=0.2-4 ip=10.8.11.89 latency=0 link=yes multicast=yes port=twisted pair speed=1Gbit/s vid:pid=8086:0D55
       resources: irq = 126 memory = a0300000-a031ffff

*/

DNetDevice::DNetDevice(QObject *parent)
    : QObject(parent)
    , d_ptr(new DNetDevicePrivate(this))
{
}

DNetDevice::~DNetDevice()
{
}

int DNetDevice::count()
{
    Q_D(DNetDevice);
    return  d->m_listDeviceInfo.count();
}

QString DNetDevice::vendor(int index)
{
    Q_D(DNetDevice);
    if (index < d->m_listDeviceInfo.count()) {
        return  d->m_listDeviceInfo[index].vendorName;
    } else
        return QString();
}

QString DNetDevice::model(int index)
{
    Q_D(DNetDevice);
    if (index < d->m_listDeviceInfo.count()) {
        return  d->m_listDeviceInfo[index].productName;
    } else
        return QString();
}

QString DNetDevice::type(int index)
{
    Q_D(DNetDevice);
    if (index < d->m_listDeviceInfo.count())  {
        return  d->m_listDeviceInfo[index].deviceInfoLstMap.value("type");
    } else
        return QString();
}

QString DNetDevice::macAddress(int index)
{
    Q_D(DNetDevice);
    if (index < d->m_listDeviceInfo.count())  {
        return  d->m_listDeviceInfo[index].deviceInfoLstMap.value("macAddress");
    } else
        return QString();
}

QString DNetDevice::driver(int index)
{
    Q_D(DNetDevice);
    if (index < d->m_listDeviceInfo.count())  {
        return  d->m_listDeviceInfo[index].deviceInfoLstMap.value("driver");
    } else
        return QString();
}

QString DNetDevice::speed(int index)
{
    Q_D(DNetDevice);
    if (index < d->m_listDeviceInfo.count())  {
        return  d->m_listDeviceInfo[index].deviceInfoLstMap.value("speed");
    } else
        return QString();
}

QString DNetDevice::status(int index)
{
    Q_D(DNetDevice);
    if (index < d->m_listDeviceInfo.count())  {
        return  d->m_listDeviceInfo[index].deviceInfoLstMap.value("status");
    } else
        return QString();
}

DInetAddr4 DNetDevice::inetAddr4(int index)
{
    return DInetAddr4();
}

DInetAddr6 DNetDevice::inetAddr6(int index)
{
    return DInetAddr6();
}

DNetifInfo DNetDevice::netifInfo(int index)
{
    //net/core/net-procfs.c  net/core/dev.c
    Q_D(DNetDevice);
    if (index < d->m_listDeviceInfo.count())  {
        struct DNetifInfo result =  DNetifInfo();

        QString line =  d->m_listDeviceInfo[index].deviceInfoLstMap.value("proc_net_dev_data");
        if (!line.isNull()) {
            QStringList deviceInfo = line.split(" ", QString::SkipEmptyParts);
            if (deviceInfo.size() > 16) { //1-17
                result.rxBytes      =   deviceInfo[1].toULongLong();     // total bytes received
                result.rxPackets    =   deviceInfo[2].toULongLong();   // total packets received
                result.rxErrors     =   deviceInfo[3].toULongLong();    // bad packets received
                result.rxDropped    =   deviceInfo[4].toULongLong();   // no space in linux buffers
                result.rxFifo       =   deviceInfo[5].toULongLong();      // FIFO overruns
                result.rxFrame      =   deviceInfo[6].toULongLong();     // frame alignment error
                // 7  compressed  //  8 multicast
                result.txBytes      =   deviceInfo[9].toULongLong();     // total bytes transmitted
                result.txPackets    =   deviceInfo[10].toULongLong();   // total packets transmitted
                result.txErrors     =   deviceInfo[11].toULongLong();    // packet transmit problems
                result.txDropped    =   deviceInfo[12].toULongLong();   // no space available in linux
                result.txFifo       =   deviceInfo[13].toULongLong();      // FIFO overruns
                // 14 collisions
                result.txCarrier    =   deviceInfo[15].toULongLong();   // loss of link pulse
            }
        }
        return result;
    } else
        return DNetifInfo();
}

QString DNetDevice::portStatus(int index, int port)
{
    return QString();
}

QList<int> DNetDevice::applicationPorts(int pid)
{
    return QList<int>();
}


DLSDEVICE_END_NAMESPACE
