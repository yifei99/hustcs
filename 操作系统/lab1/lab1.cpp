#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

pid_t p1;
pid_t p2;
int pipefd[2];
char a[30];
char b1[40]="\nChild Process 1 is Killed by Parent!\n";
char b2[40]="Child Process 2 is Killed by Parent!\n";
int i=1;
int* status;
//父进程收到SIGINT信号处理函数
void dosigint(int sig_no){
  kill(p1,SIGUSR1);
  usleep(1000);//让子进程1先结束
  kill(p2,SIGUSR2);
}

//子进程1收到SIGUSR1信号的处理函数
void dosig1(int sig_no){
   printf("%s",b1);//输出结束信息
   exit(0);
}

//子进程2收到SIGUSR1信号的处理函数
void dosig2(int sig_no){
    printf("%s",b2);
    exit(0);
}

//子进程1
int child1(){
  signal(SIGINT,SIG_IGN);//设置忽略信号SIGINT
  signal(SIGUSR1,dosig1);//设置信号SIGUSR1
  while (1)
  {
    sprintf(a,"I send you %d times.\n",i);//将数据写入数组a
    write(pipefd[1],a,30);//发送数据至管道数据
    i++;//计数器++
    sleep(1);//睡眠一秒
  }
}

//子进程2
int child2(){
    signal(SIGINT,SIG_IGN);//设置忽略信号SIGINT
    signal(SIGUSR2,dosig2);//设置信号SIGUSR2
    while(1)
    {
      usleep(200000);//休眠0.3s后接收管道数据
      read(pipefd[0],a,30);//接收管道数据
      printf("%s",a);//显示数据
      usleep(800000);//休眠0.7s使一周期为1s
    }
}

int main(void){
    if(pipe(pipefd)==-1){
		perror("make pipe");
		exit(-1);
	}//创建管道
    signal(SIGINT,dosigint);//设置软中断信号SIGINT
    if((p1=fork())==0){
        child1();//执行子进程1函数
    }
    else{
        p2=fork();//创建子进程2
        if(p2==0){
        child2();//执行子进程2函数
        }
        else{
        waitpid(p1,status,0);//等待子进程1退出
        waitpid(p2,status,0);//等待子进程2退出
       }
    }
    //关闭管道
    close(pipefd[0]);
    close(pipefd[1]);
    return 0;
}