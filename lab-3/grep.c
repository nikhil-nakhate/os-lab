#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int main(int argc, char* argv[])
   {
      int a;
      char command[50];
      bzero(command,50);
      sprintf(command, "grep %s %s", argv[1], argv[2]);
      a=system(command);
      return 0;
   }