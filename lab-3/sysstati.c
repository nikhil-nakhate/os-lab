#include<linux/kernel.h>
#include<stdio.h>
#include<sys/sysinfo.h>

int main ()
   {
      const long minute = 60;
      const long hour = minute * 60;
      const long day = hour * 24;
      const double megabyte = 1024 * 1024;

      struct sysinfo si;
      sysinfo (&si);

      printf ("System uptime : %ld days, %ld:%02ld:%02ld\n",si.uptime / day, (si.uptime % day) / hour,(si.uptime % hour) / minute, si.uptime % minute);
      printf ("Total RAM: %5.1f MB\n", si.totalram / megabyte);
      printf ("Free RAM: %5.1f MB\n", si.freeram / megabyte);
      printf ("Process count : %d\n", si.procs);
      //printf ("Page size : %d\n", si.procs);
      //printf ("Size of user memory : %d\n", si.procs);

      return 0;
   }
