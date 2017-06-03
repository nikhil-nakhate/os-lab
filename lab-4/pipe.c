#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#define MAX 100

int main()
{
  pid_t pid;
  int dPipe[2];
  char buf[MAX];
  pipe(dPipe);
  int i = 0;
  pid=fork();
  if(pid < 0)
  {
    printf("Unable to fork\n");
  }
  else if(pid)
  {
    close(dPipe[0]);
    while(1)
    {
      bzero(buf,MAX);
      sprintf(buf,"From parent message %d", i++);
      write(dPipe[1],buf, MAX);
      //printf("parent : %d\n",i);
    }
  }
  else
  {
    close(dPipe[1]);
    while(1)
    {
     //sleep(10);
      bzero(buf,MAX);
      read(dPipe[0],buf, MAX);
      printf("Received: %s\n",buf);
    }
  }
}