#include <pthread.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>


union semun {
	int val; /* value for SETVAL */
	struct semid_ds *buf; /* buffer for IPC_STAT, IPC_SET */
	unsigned short *array; /* array for GETALL, SETALL */
	struct seminfo *__buf; /* buffer for IPC_INFO */
};

int semid;
pthread_t p1,p2;
int i;//用于计数

//p操作
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

//两个线程的行为定义
void *subop1(){
  	for(int j = 1;j != 101;j++){	
		P(semid,0);
		printf("subp1:a=%d\n",i);	//打印结果
		V(semid,1);
	}
	return 0;
}


void *subop2(){
	i = 0;
	for(int j = 1;j != 101;j++){		//循环累加计算
		P(semid,1);
		i = i+j;
		V(semid,0);
	}
	return 0;
}

int main(void){
    union semun arg;
	//创建信号灯
	semid = semget(0,2,IPC_CREAT|0666);
    //信号灯赋初值
	arg.val = 0;
	semctl(semid,0,SETVAL,arg);
	arg.val = 1;
	semctl(semid,1,SETVAL,arg);
	//创建两个线程
	pthread_create(&p1,NULL,subop1,NULL);
	pthread_create(&p2,NULL,subop2,NULL);
    //等待两个线程运行结束
	pthread_join(p1,NULL);
	pthread_join(p2,NULL);
    //删除信号灯
	semctl(semid,0,IPC_RMID,0);
	return 0;
}
