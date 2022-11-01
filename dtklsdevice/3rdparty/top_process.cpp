#include "version.h"
#include "config.h"
#include "abi.h"
#include "osutils.h"
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <limits.h>


#define PROC_PATH "/proc"

bool scan_top_process(hwNode & pid)
{

  pushd(PROC_PATH);
  {
    int i,n,j;
    struct dirent **namelist;
    string pidpath ;
    string value;

    j = 0;
    n = scandir(".", &namelist, selectdir, alphasort);   

    for(i=0; i<n; i++)
    {
    //   pid.addCapability(namelist[i]->d_name);
      if(matches(namelist[i]->d_name, "^[0-9]+$")) 
      {
        pidpath = string(namelist[i]->d_name);
        value = get_string(pidpath+"/stat");
        if(!value.empty())
         pid.setConfig("proc"+pidpath,value+", \n");
       // pushd(namelist[i]->d_name);
       // popd();
       j++;
      }

      free(namelist[i]);
    }
    if(namelist)
      free(namelist);
    if(j > 0)
      pid.setDescription("PID Show");
  }
  popd();
  //pid.describeCapability("vsyscall64", _("64-bit processes"));
  return true;
}
