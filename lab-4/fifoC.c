#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

#define MAX 100

int main()
{
  char* path = "/home/me/Desktop/oslab/lab4/fifo1";
  char buf[MAX];
  int i,fd;
  i = 0;
  fd = open(path, O_RDONLY);
  while(1)
  {
    sleep(5);
    bzero(buf,MAX);
    read(fd, buf, MAX);
    printf("Received: %s\n", buf);
  }
}  
 