#include "version.h"
#include "disk.h"
#include "osutils.h"
#include "heuristics.h"
#include "partitions.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>

#include <iostream>
#include <fstream>
#include <regex>
#include <tuple>
#include <chrono>
#include <thread>
#include <cstdint>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


#define MAX_NAME_LEN 128
#define PROC_PATH_DISK      "/proc/diskstats"
#define SYSFS_PATH_BLOCK    "/sys/block"  //fetch the disk label name :sda sdb  nvme0n1   loop0~loopxx
#define SYSFS_PATH_MODEL    "/sys/block/%1/device/model" // $ cat model      WDC WD10EZEX-08W
#define SYSFS_PATH_SIZE     "/sys/block/%1/size"
#define SYSFS_PATH_STATE    "/sys/block/%1/stat"
// /sys/block/<dev>/stat

/*
/sys/block/sda$ cat size
1953525168
*/

// unsigned long long read_speed;  // 读取速度
// unsigned long long wirte_speed; // 写入速度
/*
https://www.kernel.org/doc/html/latest/block/stat.html
Block layer statistics in /sys/block/<dev>/stat

$ cd /sys/devices/pci0000:00/0000:00:1b.0/0000:02:00.0/nvme/nvme0/nvme0n1
$ cat  stat
  966139   212542 70100870   518841  2499079  2282714 163794184 18050349        0  1671852 19064545        0        0        0        0   172406   495355
---------------------------------------------------
*/
const int HDD_READ_POS     = 2;  //ReadSectors
const int HDD_WRITE_POS    = 6;  //WriteSectors
const int UNIX_SECTOR_SIZE = 1;  //512

std::tuple<uint64_t, uint64_t>   hddStatus(const std::string &name="sda")
{
  
  auto readVal_ = static_cast<uint64_t>(0);
  auto writeVal_= static_cast<uint64_t>(0);

  std::ifstream in("/sys/block/"+name+"/stat");
  if ( ! in.is_open() ) {
      return std::tuple<uint64_t, uint64_t> (readVal_, writeVal_);
  }

  std::string line;
  std::regex rgx ( "\\d+" );
  std::regex_token_iterator<std::string::iterator> end;

  while (std::getline(in, line) )
  {
      std::regex_token_iterator<std::string::iterator> iter( line.begin(), line.end(), rgx, 0 );
      int pos_ = 0 ;

      while ( iter != end ) {

          if ( pos_ == HDD_READ_POS){
              readVal_ = std::stoul( *iter ) ;
          }

          if ( pos_ == HDD_WRITE_POS){
              writeVal_ = std::stoul( *iter ) ;
          }
          ++iter;
          ++pos_;
      }
  }
  return std::tuple<uint64_t, uint64_t> (readVal_, writeVal_);
}



bool scan_seed(hwNode & n)
{
    uint64_t curRead  = static_cast<uint64_t>(0);
    uint64_t curWrite = static_cast<uint64_t>(0);
    string diskname = shortname(n.getLogicalName().c_str());
    if(diskname.empty())
    return  false;
    auto values = hddStatus(diskname);
    curRead  = std::get<0>( values ) ;
    curWrite = std::get<1>( values ) ;
    n.setConfig("ReadSectors",curRead);
    n.setConfig("WriteSectors",curWrite);

   return true;
}


#ifndef BLKROGET
#define BLKROGET   _IO(0x12,94)                   /* get read-only status (0 = read_write) */
#endif
#ifndef BLKGETSIZE
#define BLKGETSIZE _IO(0x12,96)                   /* return device size */
#endif
#ifndef BLKGETSIZE64
#define BLKGETSIZE64 _IOR(0x12,114,size_t)        /* size in bytes */
#endif
#ifndef BLKSSZGET
#define BLKSSZGET  _IO(0x12,104)                  /* get block device sector size */
#endif
#ifndef BLKPBSZGET
#define BLKPBSZGET _IO(0x12,123)
#endif


bool scan_disk(hwNode & n)
{
  long size = 0;
  unsigned long long bytes = 0;
  int sectsize = 0;
  int physsectsize = 0;

  if (n.getLogicalName() == "")
    return false;

  int fd = open(n.getLogicalName().c_str(), O_RDONLY | O_NONBLOCK);

  if (fd < 0)
    return false;

  if (ioctl(fd, BLKPBSZGET, &physsectsize) != 0)
    physsectsize = 0;
  if(physsectsize)
    n.setConfig("sectorsize", physsectsize);

  if (ioctl(fd, BLKSSZGET, &sectsize) < 0)
    sectsize = 0;
  if (sectsize)
    n.setConfig("logicalsectorsize", sectsize);

  if (n.getSize() == 0)
  {
    if(ioctl(fd, BLKGETSIZE64, &bytes) == 0)
    {
      n.setSize(bytes);
    }
    else
    {
      if (ioctl(fd, BLKGETSIZE, &size) != 0)
        size = 0;
      
      if ((size > 0) && (sectsize > 0)){
        n.setSize((unsigned long long) size * (unsigned long long) sectsize);
      }
    }
  }

  close(fd);

  if(n.getSize()>=0)
  {
    n.addHint("icon", string("disc"));
    scan_partitions(n);
    scan_seed(n);
  }

  return true;
}



