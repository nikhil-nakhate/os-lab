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
  mode_t mode = S_IRUSR|S_IRGRP|S_IROTH|S_IWUSR|S_IWGRP|S_IWOTH;
  int i, flag, fd;
  flag = mkfifo(path,mode);
  if(flag < 0)
  {
    printf("Unable to create Fifo\n");
    exit(1);
  }
  i = 0;
  fd = open(path, O_WRONLY);
  while(1)
  {
    bzero(buf,MAX);
    sprintf(buf,"Message %d",i++);
    write(fd, buf, MAX);
  }
}  
  
