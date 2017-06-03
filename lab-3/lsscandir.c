#include<dirent.h>
#include<stdio.h>

int main()
   {
      struct dirent **namelist;
      int n;
      n = scandir("..", &namelist,0,0);
      if (n < 0)
         printf("scandir error");
      else
      {
         while (n--)
         {
            printf("%s\n", namelist[n]->d_name);
         }
      }
   }
