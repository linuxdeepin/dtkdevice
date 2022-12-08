// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DLSDEVICETYPES_H
#define DLSDEVICETYPES_H

#include <QObject>
#include <QMap>

#include "dtklsdevice_global.h"

DLSDEVICE_BEGIN_NAMESPACE
enum DevClass {
    DtkUnkown = 0,
    DtkBridge,   DtkController, DtkHub,
    DtkBios,     DtkBus,        DtkAddress, DtkVolume,
    DtkVirtual,
    DtkGeneric,
    DtkProductSystem,
    DtkMainboard,
    DtkCpu,
    DtkMemory,
    DtkStorage,  DtkDisk,
    DtkDvd,      DtkTape,
    DtkNetwork,  Dtkwlan,   DtkCommunication,
    DtkDisplayGPU,         DtkMonitor,
    DtkInput,
    DtkMouse,
    DtkKeyboard,
    DtkFingerprint,
    DtkCamera,
    DtkSoundAudio,
    DtkTouchscreen,
    DtkTouchpad,
    DtkBluetooth,
    DtkPrinter,
    DtkPower,    DtkBattery,
    DtkSensor,
    DtkLed,
    DtkSwitchbuttion,
    DtkScanner,
    DtkChipcard,

    DtkOther,
    DtkRevers1,
    DtkRevers2,

    DtkMax = 100
};


struct DDeviceInfo {
    QMap<QString, QString>  deviceInfoLstMap;

    QString vendorName;
    QString productName;
    QString modalias;
    QString vendorID;
    QString productID;
    QString sysFsPath;
    QString baseClassName;
    QString subClassName;
    QString description;
    QStringList deviceBaseAttrisLst;
    QStringList deviceOtherAttrisLst;
    DevClass devClass;
};

struct DCpuStat {
    quint64 user {0}; // user time
    quint64 nice {0}; // user time with low priority
    quint64 sys {0}; // system time
    quint64 idle {0}; // idle time
    quint64 iowait {0}; // io wait time
    quint64 hardirq {0}; // interrupt time
    quint64 softirq {0}; // soft interrupt time
    quint64 steal {0}; // stolen time
    quint64 guest {0}; // guest time
    quint64 guestNice {0}; // guest time (niced)
};

struct DCpuUsage {
    quint64 total {0};
    quint64 idle {0};
};

struct DDiskIoStat {
    quint64 readsCompletedSuccessfully {0};     // # of reads completed successfully
    quint64 readsMerged {0};                    // # of reads merged
    quint64 readSectors {0};                    // # of sectors read
    quint64 spentReadingTime {0};               // # of time spent reading (ms)
    quint64 writesCompleted {0};                // # of writes completed
    quint64 writesMerged {0};                   // # of writes merged
    quint64 writtenSectors {0};                 // # of sectors written
    quint64 spentWritingTime {0};               // # of time spent writing (ms)
    quint64 currentProgressIOs {0};             // # of I/Os currently in progress
    quint64 spentDoingIOsTime {0};              // # of time spent doing I/Os (ms)
    quint64 spentDoingIOsWeightedTime {0};      // # of weighted time spent doing I/Os (ms)
    quint64 discardsCompletedSuccessfully {0};  // # of discards completed successfully
    quint64 discardsMerged {0};                 // # of discards merged
    quint64 discardedSectors {0};               // # of sectors discarded
    quint64 spentDiscardingTime {0};            // # of time spent discarding
};

struct DInetAddr4 {
    int        family {0};
    QByteArray addr;
    QByteArray mask;
    QByteArray bcast;
};

struct DInetAddr6 {
    int        family {0};
    QByteArray addr;
    int        prefixlen {0};
    int        scope {0};
};

struct DNetifInfo {
    quint64 rxPackets {0};   // total packets received
    quint64 rxBytes {0};     // total bytes received
    quint64 rxErrors {0};    // bad packets received
    quint64 rxDropped {0};   // no space in linux buffers
    quint64 rxFifo {0};      // FIFO overruns
    quint64 rxFrame {0};     // frame alignment error
    quint64 txPackets {0};   // total packets transmitted
    quint64 txBytes {0};     // total bytes transmitted
    quint64 txErrors {0};    // packet transmit problems
    quint64 txDropped {0};   // no space available in linux
    quint64 txFifo {0};      // FIFO overruns
    quint64 txCarrier {0};   // loss of link pulse
};

struct DProcessBaseInfo {
    QString          name;
    int              type;
    QString          cmdline;
    QString          usrerName;
    quint32          mask;                 // mask
    pid_t            pid;                  // pid
    QByteArray       icon;
};

struct DProcessMemoryInfo {
    quint64          vmsize;               // vm size in kB
    quint64          rss;                  // resident set size in kB
    quint64          shm;                  // resident shared size in kB
};

struct DProcessIOInfo {
    quint64          readBytes;            // disk read bytes
    quint64          writeBytes;           // disk write bytes
    quint64          cancelledWriteBytes;  // cancelled write bytes
};

struct DProcessNetworkInfo {
    quint64 recvBytes;
    quint64 sentBytes;
};

struct DProcessStatus {
    char             state;                // process state
    pid_t            ppid;                 // parent process
    pid_t            pgid;                 // process group id
    uid_t            uid;                  // real uid
    gid_t            gid;                  // real gid
    uid_t            euid;                 // effective uid
    gid_t            egid;                 // effective gid
    uid_t            suid;                 // saved uid
    gid_t            sgid;                 // saved gid
    uid_t            fuid;                 // filesystem uid
    gid_t            fgid;                 // filesystem gid

    quint32          processor;            // cpu number
    quint32          rtPrio;               // real time priority
    quint32          policy;               // scheduling policy
    quint32          nthreads;             // number of threads
    int              nice;                 // process nice

    quint64          utime;                // user time
    quint64          stime;                // kernel time
    qint64           cutime;               // user time on waiting children
    qint64           cstime;               // kernel time on waiting children
    quint64          startTime;           // start time since system boot in clock ticks
    quint64          guestTime;            // guest time (virtual cpu time for guest os)
    qint64           cguestTime;           // children guest time in clock ticks
    quint64          wtime;                // time spent waiting on a runqueue
};

DLSDEVICE_END_NAMESPACE

#endif
