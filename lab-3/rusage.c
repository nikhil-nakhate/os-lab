#include<sys/time.h>
#include<sys/resource.h>
#include<time.h>
#include<stdio.h>

int main()
   {
      struct rusage ru;
      
      getrusage(RUSAGE_SELF, &ru);

      printf("User Time: %ld\n",ru.ru_utime.tv_usec);
      printf("System time: %ld\n",ru.ru_stime.tv_usec);

      return 0;
   }
