// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
#include "dnetdevice.h"
#include "dlsdevice.h"

#include "scan.h"
#include "hw.h"

#include <QDebug>

DDEVICE_BEGIN_NAMESPACE

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
    QList< DlsDevice::DDeviceInfo >      m_listDeviceInfo;
    void addDeviceInfo(hwNode &node, QList< DlsDevice::DDeviceInfo >  &infoLst);
    Q_DECLARE_PUBLIC(DNetDevice)

private:
    DNetDevice *q_ptr = nullptr;
};


void DNetDevicePrivate::addDeviceInfo(hwNode &node, QList<DlsDevice::DDeviceInfo> &infoLst)
{
    struct DlsDevice::DDeviceInfo entry;

    entry.deviceInfoLstMap.clear();
    entry.devClass = DlsDevice::DtkNetwork;

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

    if (! node.getConfig("Vendor_ID").empty()) {
        entry.deviceBaseAttrisLst.append("Vendor_ID");
        entry.deviceInfoLstMap.insert("Vendor_ID", QString::fromStdString(node.getConfig("Vendor_ID")));
        entry.vendorID = QString::fromStdString(node.getConfig("Vendor_ID"));
    }

    if (! node.getConfig("Product_ID").empty()) {
        entry.deviceBaseAttrisLst.append("Product_ID");
        entry.deviceInfoLstMap.insert("Product_ID", QString::fromStdString(node.getConfig("Product_ID")));
        entry.productID = QString::fromStdString(node.getConfig("Product_ID"));
    }

    if (! node.getConfig("VID:PID").empty()) {
        entry.deviceBaseAttrisLst.append("VID:PID");
        entry.deviceInfoLstMap.insert("VID:PID", QString::fromStdString(node.getConfig("VID:PID")));
    }

    if (node.getModalias().length() > 53) {
        entry.deviceBaseAttrisLst.append("Modalias");
        entry.deviceInfoLstMap.insert("Modalias", QString::fromStdString(node.getModalias().substr(0, 53)));
    } else {
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

    if (! node.getConfig("driver").empty()) {
        entry.deviceBaseAttrisLst.append("Driver");
        entry.deviceInfoLstMap.insert("Driver", QString::fromStdString(node.getConfig("driver")));
    }

    if (! node.getConfig("Revison").empty()) {
        entry.deviceBaseAttrisLst.append("Revison");
        entry.deviceInfoLstMap.insert("Revison", QString::fromStdString(node.getConfig("Revison")));
    }

//------- ADD Children-------
    if ((hw::disk == node.getClass()) || (hw::storage == node.getClass()))
        infoLst.append(entry);
    for (int i = 0; i < node.countChildren(); i++) {
        addDeviceInfo(*node.getChild(i), infoLst);
    }
}

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
        return  d->m_listDeviceInfo[index].deviceInfoLstMap.value("macaddress");
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

DNetDevice::DInetAddr4 DNetDevice::inetAddr4(int index)
{
    return DInetAddr4();
}

DNetDevice::DInetAddr6 DNetDevice::inetAddr6(int index)
{
    return DInetAddr6();
}

DNetDevice::DNetifInfo DNetDevice::netifInfo(int index)
{
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


DDEVICE_END_NAMESPACE
