#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/types.h>
#include<unistd.h>

#define KEY 9090

int semId;

union semun 
{
 int val;
 struct semid_ds *buf;
 unsigned short int *array;
 };

void init()
{
  int i=0, status;
  union semun semInit;
  semId = semget((key_t)KEY,1,0666|IPC_CREAT);
  semInit.val = 1;
  status = semctl(semId, 0, SETVAL, semInit);
  if(status < 0)
  {
    printf("Unable to initialize semaphore\n");
    exit(1);
  }
}

int signal()
{
  int status;
  struct sembuf op[1];
  op[0].sem_num = 0;
  op[0].sem_op = 1;
  op[0].sem_flg = SEM_UNDO;
  
  status = semop(semId, op, 1);
  if(status < 0)
    return 0;
  return 1;
  
}

int wait()
{
  int status;
  struct sembuf op[1];
  op[0].sem_num = 0;
  op[0].sem_op = -1;
  op[0].sem_flg = SEM_UNDO;
  
  status = semop(semId, op, 1);
  if(status < 0)
    return 0;
  return 1;
}

int main(int argc, char* argv[])
{
  int i=0;
  char* sharedMem;
  init();
  //semId = semget((key_t)KEY,1,0666);
  if(semId < 0)
  {
    printf("Unable to get id of semaphore\n");
    exit(1);
  }
  fork();
  while(i++ < 20)
  {
    if(!wait())
    {
      printf("Error in waiting\n");
      exit(1);
    }
    printf("In critical section of %d\n", getpid());
    printf("Executing critical section of %d \n", getpid());
    printf("Finished Executing critical section  of%d \n", getpid());
    if(!signal())
    {
      printf("Error while signaling\n");    
      exit(1);
    }
  }
  
}