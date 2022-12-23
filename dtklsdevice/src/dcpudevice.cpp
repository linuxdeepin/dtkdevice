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

/*
     [ cache.1----cpu_cache ]
          description = L2 cache
          physical id = 16
          slot = L2 Cache
          size = 2097152
          capacity = 2MiB
          capabilities = synchronous internal write-back unified
          configuration: level=2
     [ cache.2----cpu_cache ]
          description = L3 cache
          physical id = 17
          slot = L3 Cache
          size = 16777216
          capacity = 16MiB
          capabilities = synchronous internal write-back unified
          configuration: level=3
     [ cpu----processor ]
          description = CPU
          vendor = Intel Corp.
          product = Intel(R) Core(TM) i7-10700 CPU @ 2.90GHz
          physical id = 18
          bus_info = cpu@0
          version = 6.165.5
          serial = To Be Filled By O.E.M.
          slot = 1200
          size = 2012MHz
          capacity = 4800MHz
          width = 64 bits
          clock = 100MHz
          capabilities = lm fpu fpu_exception wp vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush dts acpi mmx fxsr sse sse2 ss ht tm pbe syscall nx pdpe1gb rdtscp x86-64 constant_tsc art arch_perfmon pebs bts rep_good nopl xtopology nonstop_tsc cpuid aperfmperf pni pclmulqdq dtes64 monitor ds_cpl vmx smx est tm2 ssse3 sdbg fma cx16 xtpr pdcm pcid sse4_1 sse4_2 x2apic movbe popcnt tsc_deadline_timer aes xsave avx f16c rdrand lahf_lm abm 3dnowprefetch cpuid_fault epb invpcid_single ssbd ibrs ibpb stibp ibrs_enhanced tpr_shadow vnmi flexpriority ept vpid ept_ad fsgsbase tsc_adjust bmi1 avx2 smep bmi2 erms invpcid mpx rdseed adx smap clflushopt intel_pt xsaveopt xsavec xgetbv1 xsaves dtherm ida arat pln pts pku ospke md_clear flush_l1d arch_capabilities cpufreq
          configuration: cores=8 cpufreq=2012662000 enabledcores=8 microcode=240 threads=16

*/
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
