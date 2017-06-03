#include <stdio.h>
#include <sys/utsname.h>

int main ()
   {
      struct utsname u;
      uname (&u);
      printf("System Name: %s\nRelease: %s\nVersion: %s\nProcessor: %s\n", u.nodename, u.release, u.version, u.machine);
      return 0;
   }
