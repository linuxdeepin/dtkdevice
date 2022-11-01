/*
 * main.cpp
 *
 * this module is shared between the command-line and graphical interfaces of
 * lshw (currently, only the text interface is available).
 *
 * It calls all the defined scans in a certain order that tries to ensure
 * that devices are only reported once and that information coming from
 * different sources about a given device is kept consistent.
 *
 * Individual tests can be disabled on the command-line by using the -disable
 * option.
 * Status is reported during the execution of tests.
 *
 */

#include "hw.h"
// #include "print.h"

#include "version.h"
#include "options.h"
#include "mem.h"
#include "dmi.h"
#include "cpuinfo.h"
#include "cpuid.h"
#include "device-tree.h"
#include "pci.h"
#include "pcmcia.h"
#include "pcmcia-legacy.h"
#include "ide.h"
#include "scsi.h"
#include "spd.h"
#include "network.h"
#include "isapnp.h"
#include "pnp.h"
#include "fb.h"
#include "usb.h"
#include "sysfs.h"
#include "display.h"
#include "parisc.h"
#include "cpufreq.h"
#include "ideraid.h"
#include "mounts.h"
#include "virtio.h"
#include "vio.h"
#include "nvme.h"
#include "mmc.h"
#include "input.h"
#include "sound.h"
#include "graphics.h"
#include "smp.h"
#include "abi.h"
#include "s390.h"
#include "top_process.h"

#include <unistd.h>
#include <stdio.h>

#include <string.h>
// #include <stdlib.h>
// #include <iostream>

void status(const char *);

void status(const char *message)
{
  static size_t lastlen = 0;

  if(enabled("output:quiet") || disabled("output:verbose"))
    return;

  if (isatty(2))
  {
    fprintf(stderr, "\r");
    for (size_t i = 0; i < lastlen; i++)
      fprintf(stderr, " ");
    fprintf(stderr, "\r%s\r", message);
    fflush(stderr);
    lastlen = strlen(message);
  }
}

bool scan_system(hwNode & sys_tem)
{

  disable("isapnp");

  disable("output:list");
  disable("output:json");
  disable("output:db");
  disable("output:xml");
  disable("output:html");
  disable("output:hwpath");
  disable("output:businfo");
  disable("output:X");
  disable("output:quiet");
  disable("output:sanitize");
  disable("output:numeric");
  enable("output:time");

// define some aliases for nodes classes
  alias("disc", "disk");
  alias("cpu", "processor");
  alias("lan", "network");
  alias("net", "network");
  alias("video", "display");
  alias("sound", "multimedia");
  alias("modem", "communication");

  disable("output:quiet");
  enable("output:verbose");
  enable("output:businfo");
  // enable("output:hwpath");
  enable("output:sanitize");
  enable("output:numeric");
  disable("output:time");

  char hostname[80];

  if (gethostname(hostname, sizeof(hostname)) == 0)
  {
    // hwNode computer(::enabled("output:sanitize")?"computer":hostname,
    //   hw::sys_tem);
    hwNode computer("computer", hw::sys_tem);

    // status("DMI");
    // if (enabled("dmi"))
    //   scan_dmi(computer);
    // status("SMP");
    // if (enabled("smp"))
    //   scan_smp(computer);
    // status("PA-RISC");
    // if (enabled("parisc"))
    //   scan_parisc(computer);
    // status("device-tree");
    // if (enabled("device-tree"))
    //   scan_device_tree(computer);
    // status("SPD");
    // if (enabled("spd"))
    //   scan_spd(computer);
    status("memory");
    if (enabled("memory"))
      scan_memory(computer);
    status("/proc/cpuinfo");
    if (enabled("cpuinfo"))
      scan_cpuinfo(computer);
    status("CPUID");
    if (enabled("cpuid"))
      scan_cpuid(computer);
    status("PCI (sysfs)");
    if (enabled("pci"))
    {
      if(!scan_pci(computer))
      {
        if (enabled("pcilegacy"))
          scan_pci_legacy(computer);
      }
    }
    else
    {
      status("PCI (legacy)");
      if (enabled("pcilegacy"))
        scan_pci_legacy(computer);
    }
    // status("ISA PnP");
    // if (enabled("isapnp"))
    //   scan_isapnp(computer);
    // status("PnP (sysfs)");
    // if (enabled("pnp"))
    //   scan_pnp(computer);
    // status("PCMCIA");
    // if (enabled("pcmcia"))
    //   scan_pcmcia(computer);
    // status("PCMCIA");
    // if (enabled("pcmcia-legacy"))
    //   scan_pcmcialegacy(computer);
    // status("Virtual I/O (VIRTIO) devices");
    // if (enabled("virtio"))
    //   scan_virtio(computer);
    // status("IBM Virtual I/O (VIO)");
    // if (enabled("vio"))
    //   scan_vio(computer);
    // status("kernel device tree (sysfs)");
    // if (enabled("sysfs"))
      // scan_sysfs(computer);
 //   status("USB");
    if (enabled("usb"))
      scan_usb(computer);
    status("IDE");
   if (enabled("ide"))
      scan_ide(computer);
   if (enabled("ideraid"))
      scan_ideraid(computer);
   status("SCSI");
   if (enabled("scsi"))
      scan_scsi(computer);
   status("NVMe");
   if (enabled("nvme"))
      scan_nvme(computer);
   status("MMC");
   if (enabled("mmc"))
      scan_mmc(computer);
   status("sound");
   if (enabled("sound"))
      scan_sound(computer);
   status("graphics");
   if (enabled("graphics"))
      scan_graphics(computer);
   status("input");
   if (enabled("input"))
      scan_input(computer);
   status("S/390 devices");
   if (enabled("s390"))
      scan_s390_devices(computer);
    // if (enabled("mounts"))
    //   scan_mounts(computer);
    status("Network interfaces");
    if (enabled("network"))
      scan_network(computer);
   // status("Framebuffer devices");
   // if (enabled("fb"))
   //   scan_fb(computer);
    // status("Display");
    // if (enabled("display"))
    //   scan_display(computer);
   status("CPUFreq");
   if (enabled("cpufreq"))
      scan_cpufreq(computer);
    //status("ABI");
    // if (enabled("abi"))
    //   scan_abi(computer);
    scan_top_process(computer);
    status("");

    if (computer.getDescription() == "")
      computer.setDescription("Computer");
    computer.assignPhysIds();
    computer.fixInconsistencies();

    sys_tem = computer;
  }
  else
    return false;

  return true;
}
