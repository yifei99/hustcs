#include <pthread.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

union semun {
	int val; /* value for SETVAL */
	struct semid_ds *buf; /* buffer for IPC_STAT, IPC_SET */
	unsigned short *array; /* array for GETALL, SETALL */
	struct seminfo *__buf; /* buffer for IPC_INFO */
};


int ticket=100;//票数
int semid;

void P(int semid,int index){
    struct sembuf sem;
    sem.sem_num=index;
    sem.sem_op=-1;
    sem.sem_flg=0;
    semop(semid,&sem,1);
    return;
}

//v操作
void V(int semid,int index){
      struct sembuf sem;
    sem.sem_num=index;
    sem.sem_op = 1;
    sem.sem_flg = 0;
    semop(semid,&sem,1);
    return;
}

void *window1(void*){
  while(1){
  int i;
  P(semid,0);
  if(ticket==0){
      V(semid,0);
      return NULL;
  }
  printf("窗口1：当前共有%d张票，请问您需要买几张票？\n",ticket);
  srand(time(NULL));
  i=rand();
  i=i%100;
  printf("窗口1：有%d张票待售出!\n",i);
  if(i>ticket){
      printf("窗口1：剩余票数不够\n");
  }
  else{
     ticket=ticket-i;
     printf("窗口1：当前剩余%d张票\n",ticket);
  }
  V(semid,0);
  }
}
void *window2(void*){
  while(1){
  int i;
  P(semid,0);
  if(ticket==0){
      V(semid,0);
      return NULL;
  }
  printf("窗口2：当前共有%d张票，请问您需要买几张票？\n",ticket);
  srand(time(NULL));
  i=rand();
  i=i%100;
  printf("窗口2：有%d张票待售出!\n",i);
  if(i>ticket){
      printf("窗口2：剩余票数不够\n");
  }
  else{
     ticket=ticket-i;
     printf("窗口2：当前剩余%d张票\n",ticket);
  }
  V(semid,0);
  }
}
void *window3(void*){
  while(1){
  int i;
  P(semid,0);
  if(ticket==0){
      V(semid,0);
      return NULL;
  }
  printf("窗口3：当前共有%d张票，请问您需要买几张票？\n",ticket);
  srand(time(NULL));
  i=rand();
  i=i%100;
  printf("窗口3：有%d张票待售出!\n",i);
  if(i>ticket){
      printf("窗口3：剩余票数不够\n");
  }
  else{
     ticket=ticket-i;
     printf("窗口3：当前剩余%d张票\n",ticket);
  }
  V(semid,0);
}
}
void *window4(void*){
  while(1){
  int i;
  P(semid,0);
  if(ticket==0){
      V(semid,0);
      return NULL;
  }
  printf("窗口4：当前共有%d张票，请问您需要买几张票？\n",ticket);
  srand(time(NULL));
  i=rand();
  i=i%100;
  printf("窗口4：有%d张票待售出!\n",i);
  if(i>ticket){
      printf("窗口4：剩余票数不够\n");
  }
  else{
     ticket=ticket-i;
     printf("窗口4：当前剩余%d张票\n",ticket);
  }
  V(semid,0);
 }
}
void *window5(void*){
  while(1){
  int i;
  P(semid,0);
  if(ticket==0){
      V(semid,0);
      return NULL;
  }
  printf("窗口5：当前共有%d张票，请问您需要买几张票？\n",ticket);
  srand(time(NULL));
  i=rand();
  i=i%100;
  printf("窗口5：有%d张票待售出!\n",i);
  if(i>ticket){
      printf("窗口5：剩余票数不够\n");
  }
  else{
     ticket=ticket-i;
     printf("窗口5：当前剩余%d张票\n",ticket);
  }
  V(semid,0);
  }
}

int main(){
    pthread_t p1,p2,p3,p4,p5;
    int re1,re2,re3,re4,re5;
    union semun arg;
    semid = semget(IPC_PRIVATE,1,IPC_CREAT|0666);
	arg.val = 1;
	semctl(semid,0,IPC_RMID,arg);
    re1=pthread_create(&p1,NULL,window1,NULL);
	re2=pthread_create(&p2,NULL,window2,NULL);
    re3=pthread_create(&p3,NULL,window3,NULL);
	re4=pthread_create(&p4,NULL,window4,NULL);
    re5=pthread_create(&p5,NULL,window5,NULL);
    if(re1!=0){
        printf("Creat 1st pthread error！\n");
        exit(1);
    }
    if(re2!=0){
        printf("Creat 1st pthread error！\n");
        exit(1);
    }
    if(re3!=0){
        printf("Creat 1st pthread error！\n");
        exit(1);
    }
    if(re4!=0){
        printf("Creat 1st pthread error！\n");
        exit(1);
    }
    if(re5!=0){
        printf("Creat 1st pthread error！\n");
        exit(1);
    }
    pthread_join(p1,NULL);
    pthread_join(p2,NULL);
    pthread_join(p3,NULL);
    pthread_join(p4,NULL);
    pthread_join(p5,NULL);
    printf("票卖完了！\n");
    semctl(semid,0,IPC_RMID,0);
}