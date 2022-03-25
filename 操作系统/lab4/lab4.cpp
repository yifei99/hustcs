#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <time.h>
#include <pwd.h>


void rwx(const unsigned short n)
{  
    if(S_ISDIR(n) )
      printf("d");
    else
     printf("-");
    if (n& S_IRUSR)
       printf("r");
   else
       printf("-");

    if (n & S_IWUSR)
         printf("w");
    else
        printf("-");

    if (n & S_IXUSR)
         printf("x");
    else
        printf("-");

    if (n & S_IRGRP)
        printf("r");
    else
        printf("-");

    if (n & S_IWGRP)
         printf("w");
    else
        printf("-");

    if (n& S_IXGRP)
        printf("x");
    else
        printf("-");

    if (n & S_IROTH)
        printf("r");
    else
        printf("-");

    if (n & S_IWOTH)
        printf("w");
    else
        printf("-");

    if (n & S_IXOTH)
        printf("x   ");
    else
        printf("-   ");
        return;
}

void printdir(char *dir, int depth){
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
    if  ((dp = opendir(dir))==NULL){     
        printf("打开 dir出错\n");
        return;
    }
    chdir(dir);//将dir设置为当前目录;       
    while((entry=readdir(dp))!=NULL){   
       lstat(entry->d_name,&statbuf);//以该目录项的名字为参数,调用lstat得到该目录项的相关信息;
        if(S_ISDIR(statbuf.st_mode)){
            if(strcmp(entry->d_name,"..")==0||strcmp(entry->d_name,".")==0)
               	continue;//跳过该目录项
            //打印目录项的深度、目录名等信息
            //递归调用printdir,打印子目录的信息,其中的depth+4;
            rwx(statbuf.st_mode);
              printf("%d   ",depth);   //深度
               struct passwd *pwd1;
               pwd1 = getpwuid(statbuf.st_uid);
               printf("%s   ",pwd1->pw_name);  //文件所有者ID

               struct passwd *pwd2;
               if((pwd2 = getpwuid(statbuf.st_gid))!=NULL)
              {
              printf("%s\t",pwd2->pw_name);  //文件所有者组ID
              }
              printf("%ld\t",statbuf.st_size); //文件大小

              printf("%s\t",strtok(ctime(&statbuf.st_mtime)+4,"\n")); //最后修改内容时间
	          printf("%s\n",entry->d_name);
              printdir(entry->d_name,depth+4);
              }
              else{
              rwx(statbuf.st_mode);
              printf("%d   ",depth);   //深度
               struct passwd *pwd1;
               pwd1 = getpwuid(statbuf.st_uid);
               printf("%s   ",pwd1->pw_name);  //文件所有者ID
              struct passwd *pwd2;
              if((pwd2 = getpwuid(statbuf.st_gid))!=NULL)
              {
              printf("%s\t",pwd2->pw_name);  //文件所有者组ID
              }
              printf("%ld\t",statbuf.st_size); //文件大小
              printf("%s\t",strtok(ctime(&statbuf.st_ctime)+4, "\n")); //最后修改内容时间
              printf("%s\n",entry->d_name);
              }
              }
    chdir("..");
    closedir(dp);
}
int main(){
    char dirname[50];
    printf("please input the dir name\n");
    scanf("%s",dirname);
    printdir(dirname,1);
    return 0;
}