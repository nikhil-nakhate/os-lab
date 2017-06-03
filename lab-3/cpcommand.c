#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<stdio.h>
#include<string.h>

int main(int argc, char* argv[])
   {
      char* source = argv[1];
      char* desti = argv[2];
      char buff[100];
      int fd,rd;
      fd=open(source,O_RDONLY);
      bzero(buff,sizeof(buff));
      rd=read(fd,buff,100);
      fd=creat(desti,S_IRWXU);
      rd=write(fd,buff,100);
      return 0;
   }
