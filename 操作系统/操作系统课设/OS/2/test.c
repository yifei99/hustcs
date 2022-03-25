#include<sys/syscall.h>
#include<unistd.h>
#include<stdio.h>

int main(int argc,char *argv[]){
     if(argc != 3)
    {
        printf("输入参数不正确！\n");
        printf("格式：copy <源文件名> <目标文件名>\n");
        return 0;
    }
    syscall(326,argv[1],argv[2]);
    return 0;
}
