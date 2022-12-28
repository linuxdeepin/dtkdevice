// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
#include "ddiskdevice.h"
#include "dlsdevice_p.h"

#include "scan.h"
#include "hw.h"

#include <QDebug>

DDEVICE_BEGIN_NAMESPACE

class DDiskDevicePrivate
{

public:
    explicit DDiskDevicePrivate(DDiskDevice *parent)
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
    Q_DECLARE_PUBLIC(DDiskDevice)

private:
    DDiskDevice *q_ptr = nullptr;
};

void DDiskDevicePrivate::addDeviceInfo(hwNode &node, QList<DlsDevice::DDeviceInfo> &infoLst)
{
    struct DlsDevice::DDeviceInfo entry;

    entry.deviceInfoLstMap.clear();
    entry.devClass = DlsDevice::DtkDisk;

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

    if (! node.getConfig("interface").empty()) {
        entry.deviceBaseAttrisLst.append("interface");
        entry.deviceInfoLstMap.insert("interface", QString::fromStdString(node.getConfig("interface")));
    }

    if (! node.getConfig("serialNumber").empty()) {
        entry.deviceBaseAttrisLst.append("serialNumber");
        entry.deviceInfoLstMap.insert("serialNumber", QString::fromStdString(node.getConfig("serialNumber")));
    }

    if (! node.getConfig("Revison").empty()) {
        entry.deviceBaseAttrisLst.append("Revison");
        entry.deviceInfoLstMap.insert("Revison", QString::fromStdString(node.getConfig("Revison")));
    }

    if (! node.getConfig("SectorSize").empty()) {
        entry.deviceBaseAttrisLst.append("SectorSize");
        entry.deviceInfoLstMap.insert("SectorSize", QString::fromStdString(node.getConfig("SectorSize")));
    }

    if (! node.getConfig("Temperature").empty()) {
        entry.deviceBaseAttrisLst.append("Temperature");
        entry.deviceInfoLstMap.insert("Temperature", QString::fromStdString(node.getConfig("Temperature")));
    }


    if (! node.getConfig("RotationRate").empty()) {
        entry.deviceBaseAttrisLst.append("RotationRate");
        entry.deviceInfoLstMap.insert("RotationRate", QString::fromStdString(node.getConfig("RotationRate")));
    }
//    if (node.getSize() > 0) {
//        string tmpstr = "";

//        entry.deviceBaseAttrisLst.append("Size");
//        entry.deviceInfoLstMap.insert("Size", QString::fromStdString(tmpstr));
//    }
//--------------------------------ADD Children---------------------
    if ((hw::disk == node.getClass()) || (hw::storage == node.getClass()))
        infoLst.append(entry);
    for (int i = 0; i < node.countChildren(); i++) {
        addDeviceInfo(*node.getChild(i), infoLst);
    }
}

DDiskDevice::DDiskDevice(QObject *parent)
    : QObject(parent)
    , d_ptr(new DDiskDevicePrivate(this))
{
}

DDiskDevice::~DDiskDevice()
{
}

int DDiskDevice::count()
{
    Q_D(DDiskDevice);
    return  d->m_listDeviceInfo.count();
}

QString DDiskDevice::vendor(int index)
{
    Q_D(DDiskDevice);
    if (index < d->m_listDeviceInfo.count()) {
        return  d->m_listDeviceInfo[index].vendorName;
    } else
        return QString();
}

QString DDiskDevice::model(int index)
{
    Q_D(DDiskDevice);
    if (index < d->m_listDeviceInfo.count()) {
        return  d->m_listDeviceInfo[index].productName;
    } else
        return QString();
}

QString DDiskDevice::mediaType(int index)
{
    Q_D(DDiskDevice);
    if (index < d->m_listDeviceInfo.count())  {
        return  d->m_listDeviceInfo[index].deviceInfoLstMap.value("mediaType");
    } else
        return QString();
}

QString DDiskDevice::size(int index)
{
    Q_D(DDiskDevice);
    if (index < d->m_listDeviceInfo.count()) {
        return  d->m_listDeviceInfo[index].deviceInfoLstMap.value("Size");
    } else
        return QString();
}

QString DDiskDevice::interface(int index)
{
    Q_D(DDiskDevice);
    if (index < d->m_listDeviceInfo.count())  {
        return  d->m_listDeviceInfo[index].deviceInfoLstMap.value("interface");
    } else
        return QString();
}

QString DDiskDevice::serialNumber(int index)
{
    Q_D(DDiskDevice);
    if (index < d->m_listDeviceInfo.count()) {
        return  d->m_listDeviceInfo[index].deviceInfoLstMap.value("serialNumber");
    } else
        return QString();
}

QString DDiskDevice::deviceFile(int index)
{
    Q_D(DDiskDevice);
    if (index < d->m_listDeviceInfo.count()) {
        return  d->m_listDeviceInfo[index].deviceInfoLstMap.value("LogicalName");
    } else
        return QString();
}

QString DDiskDevice::rotationRate(int index)
{
    Q_D(DDiskDevice);
    if (index < d->m_listDeviceInfo.count())  {
        return  d->m_listDeviceInfo[index].deviceInfoLstMap.value("RotationRate");
    } else
        return QString();
}

QString DDiskDevice::firmwareVersion(int index)
{
    Q_D(DDiskDevice);
    if (index < d->m_listDeviceInfo.count()) {
        return  d->m_listDeviceInfo[index].deviceInfoLstMap.value("Revison");
    } else
        return QString();
}

QString DDiskDevice::sectorSize(int index)
{
    Q_D(DDiskDevice);
    if (index < d->m_listDeviceInfo.count())  {
        return  d->m_listDeviceInfo[index].deviceInfoLstMap.value("SectorSize");
    } else
        return QString();
}

QString DDiskDevice::temperature(int index)
{
    Q_D(DDiskDevice);
    if (index < d->m_listDeviceInfo.count())  {
        return  d->m_listDeviceInfo[index].deviceInfoLstMap.value("Temperature");
    } else
        return QString();
}

DDiskDevice::DDiskIoStat DDiskDevice::diskIoStat(int index)
{
    return DDiskIoStat();
}


DDEVICE_END_NAMESPACE
