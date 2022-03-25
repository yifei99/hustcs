#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
    int test;
    char buf[1024];
    //测试打开
    test = open("/dev/mydev",O_RDWR);
    if(test==-1){
        printf("Fail to open！\n");
        exit(0);
    }
    else{
        printf("Open success!\n");
}
//测试读
    printf("当前设备缓冲区内容为:");
    read(test,buf,1024);
    printf("%s\n",buf);
//测试写
    printf("请输入内容：");
    scanf("%s",buf);
    write(test,buf,sizeof(buf));
    printf("\n写入的内容为：");
    read(test,buf,1024);
    printf("%s\n",buf);
//测试关闭
   printf("设备成功关闭！\n");
   return 0;
}