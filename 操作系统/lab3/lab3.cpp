#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <errno.h>
#define blocknum 10//环形缓冲区个数
#define size 1024
union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short * arry;
};

int semid;//创建两个信号量 s0表示空闲缓冲区个数，s1表示被占用的缓冲区个数
char (*buf) [size];
int* flag;
//flag[0]存环形缓冲的in指针，指向空闲缓冲区的头
//flag[1]存out指针，指向已被占用的缓冲区的头
//flag[2]存最后一次读入的字节数
//flag[3]存文件是否读完的标志信息
pid_t readbuf,writebuf;

//P操作
void P(int semid,int index)
{
	struct sembuf sem;
	sem.sem_num = index;
	sem.sem_op = -1;
	sem.sem_flg = 0;
	semop(semid,&sem,1);
    return;
}

//V操作
void V(int semid,int index)
{
	struct sembuf sem;
	sem.sem_num = index;
	sem.sem_op = 1;
	sem.sem_flg = 0;
	semop(semid,&sem,1);
    return;
}

//读
void* readtxt(void)
{
	FILE* f1 = fopen("/home/lyf/下载/操作系统实验/lab3/input.txt","r");
	long readbytenum = 0;
	while(1)
	{
		P(semid,0);
		flag[2] = fread(buf[flag[0]],sizeof(char),size,f1);
		readbytenum += flag[2];
		V(semid,1);
		flag[0] = (flag[0]+1)%blocknum;//当in达到数组最大下标时，重新从0开始
		if(flag[2]!= size) {
            flag[3] = 1;
            break;
        } //每读一次文件就将最后一次读的字节数设置成此次读取到的字节数
        //当读取到的字节数和缓冲区大小1024不相等时，说明读完
	}
	return NULL;
}

//写
void* writetxt(void)
{
	FILE* f2 = fopen("/home/lyf/下载/操作系统实验/lab3/output.txt","w");
	long writebytenum = 0;
	while(1)
	{
		P(semid,1);
		if((flag[1]+1)%blocknum == flag[0])//当out指针的下一个与in相等并且读完标志为1，程序结束
		{
			writebytenum += fwrite(buf[flag[1]],sizeof(char),flag[2],f2);
			if(flag[3] == 1)
			{
				break;
			}
		}
        //当out下一个不是in时，直接写文件。
		else
		{
			writebytenum += fwrite(buf[flag[1]],sizeof(char),size,f2);
			flag[1] = (flag[1]+1) % blocknum;//当out达到数组最大下标，重新从0开始
		}
		V(semid,0);
	}
	return NULL;
}



int main(void)
{   //创建共享内存
	int shm;
	shm = shmget(1,sizeof(char[size])*blocknum,IPC_CREAT|0666);//选择1是为了进程能够共享，为不会再复制一份
	int shmid;
	shmid = shmget(2,sizeof(int)*4,IPC_CREAT|0666);//in out 指针和已经读入的个数 是否读完标志
	buf = (char(*)[size])shmat(shm,NULL,SHM_R|SHM_W);
	flag = (int *)shmat(shmid,NULL,SHM_R|SHM_W);
	//in，out,标志位赋初值
    flag[0] = 0;
	flag[1] = 0;
	flag[2] = 0;
	flag[3] = 0;
	//创建信号灯，赋初值
	semid = semget(3,2,IPC_CREAT|0666);
	union semun arg;
    //创建信号量s0 = blocknum s1 = 0
	arg.val = blocknum;
	semctl(semid,0,SETVAL,arg);
	arg.val = 0;
	semctl(semid,1,SETVAL,arg);
	
	//创建两个进程readbuf,writebuf
    readbuf = fork();
    if(readbuf == 0)
	{
		readtxt();
	}
	else
	{
		writebuf = fork();
		if(writebuf == 0)
		{
			writetxt();
		}
	}
	//等待两个进程运行结束
    wait(&readbuf);
	wait(&writebuf);
	//删除信号灯
    semctl(semid,0,IPC_RMID);
    //删除共享内存组
	shmctl(shm,IPC_RMID,0);
	shmctl(shmid,IPC_RMID,0);
	return 0;
}





