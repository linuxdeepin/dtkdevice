// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
#include "dinputdevice.h"
#include "dlsdevice.h"

#include "scan.h"
#include "hw.h"

#include <QDebug>

DDEVICE_BEGIN_NAMESPACE

class DInputDevicePrivate
{
public:
    explicit DInputDevicePrivate(DInputDevice *parent)
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
    Q_DECLARE_PUBLIC(DInputDevice)

private:
    DInputDevice *q_ptr = nullptr;
};

void DInputDevicePrivate::addDeviceInfo(hwNode &node, QList<DlsDevice::DDeviceInfo> &infoLst)
{
    struct DlsDevice::DDeviceInfo entry;

    entry.deviceInfoLstMap.clear();
    entry.deviceInfoLstMap.clear();
    entry.devClass = DlsDevice::DtkInput;

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

//--------------------------------ADD Children---------------------
    if (hw::input == node.getClass())
        infoLst.append(entry);
    for (int i = 0; i < node.countChildren(); i++) {
        addDeviceInfo(*node.getChild(i), infoLst);
    }
}

DInputDevice::DInputDevice(QObject *parent)
    : QObject(parent)
    , d_ptr(new DInputDevicePrivate(this))
{
}

DInputDevice::~DInputDevice()
{
}

int DInputDevice::count()
{
    Q_D(DInputDevice);
    return  d->m_listDeviceInfo.count();
}

QString DInputDevice::vendor(int index)
{
    Q_D(DInputDevice);
    if (index < d->m_listDeviceInfo.count()) {
        return  d->m_listDeviceInfo[index].vendorName;
    } else
        return QString();
}

QString DInputDevice::model(int index)
{
    Q_D(DInputDevice);
    if (index < d->m_listDeviceInfo.count()) {
        return  d->m_listDeviceInfo[index].productName;
    } else
        return QString();
}

QString DInputDevice::interface(int index)
{
    return QString();
}

QString DInputDevice::driver(int index)
{
    return QString();
}

DDEVICE_END_NAMESPACE
