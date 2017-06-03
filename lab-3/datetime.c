#include<stdio.h>
#include<sys/time.h>
#include<time.h>

int main()
   {
      time_t tm=time(NULL);
      struct timeval tv;
      struct tm* ptm;
      char time_string[40],*tmptr;
      
      gettimeofday (&tv, NULL);
      ptm = localtime (&tv.tv_sec);
      
      strftime (time_string, sizeof (time_string), "Date: %d-%m-%Y\nTime: %H:%M:%S", ptm);
      printf("%s\n",time_string);

      tmptr=ctime(&tm);
      printf("Time(using ctime() fnctn) : %s",tmptr);
      return 0;
   }
