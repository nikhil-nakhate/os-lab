#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>

int main(int argc, char* argv[])
   {
      struct stat buf;
      int fd,n;
      fd=open(argv[1],O_RDONLY);
      n=fstat(fd, &buf);
      printf("Size: %d\n",buf.st_blocks);
      return 0;
   }
