#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>

#define MAX 100
#define SKEY 9090
#define RKEY 9091

int msgIdR, msgIdS;

struct message
{
  long  mType;
  char buf[MAX];
};

void init()
{
    msgIdR = msgget((key_t)RKEY, 0666|IPC_CREAT);
    msgIdS = msgget((key_t)SKEY, 0666|IPC_CREAT);
  if(msgIdR < 0)
  {
    printf("Unable to create message queue for receive\n");
    exit(1);
  }
  if(msgIdS < 0)
  {
    printf("Unable to create message queue for send\n");
    exit(1);
  }
}

void recvMessage(struct message* msg)
{
  int status;
  status = msgrcv(msgIdR, (void *)msg, MAX, 0, 0);
  if(status < 0)
  {
    printf("Unable to receive message\n");
    exit(1);
  }
}

void sendMessage(struct message* msg)
{
  int status;
  status = msgsnd(msgIdS, (void *)msg, MAX, 0);
}

int main(int argc, char* argv[])
{
  sleep(atoi(argv[1]));
  int  status, i=0, j=0;
  struct message sMsg, rMsg;
  init();
  while( j++ < 1000)
  {
    bzero((char*)&sMsg, sizeof(struct message));
    bzero((char*)&rMsg, sizeof(struct message));
    sMsg.mType = 1;
    sprintf(sMsg.buf,"Message %d", i++);
    sendMessage(&sMsg);
    recvMessage(&rMsg);
    while(strcmp(rMsg.buf, "okay"));
  }
  bzero((char*)&sMsg, sizeof(struct message));
  sMsg.mType = 1;
  sprintf(sMsg.buf,"finished");
  sendMessage(&sMsg);
}
