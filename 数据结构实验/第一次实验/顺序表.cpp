/* Linear Table On Sequence Structure */
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

/*---------page 10 on textbook ---------*/
#define TRUE 1
#define FALSE -1
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2

typedef int status; 
typedef int ElemType; //数据元素类型定义

/*-------page 22 on textbook -------*/
#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef struct{  //顺序表（顺序结构）的定义
	ElemType * elem;
	int length;
	int listsize;
}SqList;
            

/*-----page 19 on textbook ---------*/
status IntiaList(SqList  *L);
status DestroyList(SqList * L);
status ClearList(SqList *L);
status ListEmpty(SqList* L);
int ListLength(SqList *L);
status GetElem(SqList *L,int i,ElemType & e);
status LocateElem(SqList *L,ElemType e); //简化过
status PriorElem(SqList *L,ElemType cue,ElemType *pre);
status NextElem(SqList *L,ElemType cue,ElemType * next);
status ListInsert(SqList * L,int i,ElemType e);
status ListDelete(SqList * L,int i,ElemType * e);
status ListTrabverse(SqList *L);  //简化过
int ReadFromFile(SqList * L,char * filename);
int StoreInFile(SqList * L,char * filename);


/*--------------------------------------------*/
int main(int argc, char *argv[]){

  SqList L1,L2,L3,*L=&L1;  int op=1;
  L1.elem=NULL;
  L2.elem=NULL;
  L3.elem=NULL;
  ElemType e;
  ElemType temp,*pre=&temp;
  ElemType temp1,*next=&temp1;
  ElemType cue;
  char filename[30];
  int i; 
  while(op){
	system("cls");	printf("\n\n");
	printf("      Menu for Linear Table On Sequence Structure \n");
	printf("-------------------------------------------------\n");
	printf("    	  1. IntiaList       7. LocateElem\n");
	printf("    	  2. DestroyList     8. PriorElem\n");
	printf("    	  3. ClearList       9. NextElem \n");
	printf("    	  4. ListEmpty     10. ListInsert\n");
	printf("    	  5. ListLength     11. ListDelete\n");
	printf("    	  6. GetElem       12. ListTrabverse\n");
	printf("          13.StoreInFile     14.ReadFromFile\n");
	printf("    	  15.ChangeList      0. Exit\n");
	printf("-------------------------------------------------\n");
	printf("    请选择你的操作[0~15]:");
	scanf("%d",&op);
    switch(op){
	   case 1:
		 //printf("\n----IntiaList功能待实现！\n");
		 if(IntiaList(L) == OK) {
			 printf("线性表创建成功！\n");
		     getchar();getchar();
		 }
		     else{
				 printf("线性表创建失败！\n");
		         getchar();getchar();
			 }
		 break;
	   case 2:
		   // printf("\n----DestroyList功能待实现！\n");     
		  if(DestroyList(L) == OK){
			   printf("线性表销毁成功！\n");
			   getchar();getchar();
		  }
		  else {
			  printf("线性表销毁失败！\n");
		      getchar();getchar();
		  }
		 break;
	   case 3: 
		   //printf("\n----ClearList功能待实现！\n");
		  if(ClearList(L) == OK){
			   printf("线性表清空成功!\n");
			   getchar();getchar();
		  }
		   else {
			  printf("线性表清空失败！\n");
			  getchar();getchar();
		   }
		 break;
	   case 4:
		   //printf("\n----ListEmpty功能待实现！\n"); 
		   if(ListEmpty(L) == OK){
			   printf("线性表已清空！\n");
			   getchar();getchar();
		   }
		  else if(ListEmpty(L) ==FALSE){ 
			  printf("线性表未清空！\n");
		      getchar();getchar();
		  }
		  else if(ListEmpty(L)==ERROR){
			  printf("线性表未初始化！\n");
		      getchar();getchar();
		  }
			  break;
	   case 5:
		   //printf("\n----ListLength功能待实现！\n");
		if( ListLength(L)!=ERROR){
         printf("线性表长度为%d\n",ListLength(L));
		 getchar();getchar();
		}
		else{
			printf("获取长度失败！\n");
			getchar();getchar();
		}
		 break;
	   case 6:
		 //printf("\n----GetElem功能待实现！\n");
		   printf("请输入要查询的序数：");
		   scanf("%d",&i);
		   if (( L->elem!=NULL)&&( L->listsize>=LIST_INIT_SIZE)&&i<=L->length){
		       GetElem(L,i,e) ;
			   printf("表中的第%d个数据为%d\n",i,e);
			   getchar();getchar();
		   }
		   else{
			   printf("查询失败！\n");
		       getchar();getchar();
		   }
		 break;
	   case 7:
		   //printf("\n----LocateElem功能待实现！\n");
		   printf("请输入要查询的数据：");
		   scanf("%d",&e);
		   i=LocateElem(L,e);
		    if(i==FALSE) {
			   printf("这样的数据元素不存在！\n");
		       getchar();getchar();
		   }
			else if(i==ERROR){
			   printf("查询失败！\n");
			   getchar();getchar();
		   }
		   else {
			   printf("L中第一个与查询数据相等的数据的位序是%d\n",i);
			   getchar();getchar();
		   }
		 break;
	   case 8:
		//printf("\n----PriorElem功能待实现！\n");
	
		   if (( L->elem!=NULL)&&( L->listsize>=LIST_INIT_SIZE)){
			   	 printf("请输入要查询的元素：");
		         scanf("%d",&cue);
		   if(PriorElem(L,cue,pre) == OK){
			   printf("前驱为%d\n",*pre);
			   getchar();getchar();
		   }
		   else {
			   printf("无此前驱\n");
			   getchar();getchar();
		   }
		   }
		   else{
			   printf("查询失败！\n");
			   getchar();getchar();
		   }
		 break;
	   case 9:
		// printf("\n----NextElem功能待实现！\n"); 
		   printf("请输入要查询的元素：");
		   scanf("%d",&cue);
		   if(NextElem(L,cue,next) == OK){
			   printf("后继为%d\n",*next);
			   getchar();getchar();
		   }
		   else if(NextElem(L,cue,next) == FALSE){
			   printf("无此后继\n");
		       getchar();getchar();
		   }
		   else{
		    printf("查找失败！\n");
		    getchar();getchar();
		   }
		   break;
	     case 10:
		// printf("\n----ListInsert功能待实现！\n");
		   printf("请输入要插入的位置：");
		   scanf("%d",&i);
		   printf("请输入要插入的元素：");
		   scanf("%d",&e);
		   if(ListInsert(L,i,e) == OK){
			   printf("线性表插入成功\n");
			   getchar();getchar();
		   }
		   else{
			   printf("线性表插入失败\n");
		       getchar();getchar();
		   }
		 break;
	   case 11:
		// printf("\n----ListDelete功能待实现！\n");
		   printf("请输入要删除的元素的序列：");
		   scanf("%d",&i);
		   if(ListDelete(L,i,&e) == OK){
			   printf("元素删除成功\n");
			   getchar();getchar();
		   }
		   else{
			   printf("元素删除失败\n");
		       getchar();getchar();
		   }
		 break;
	   case 12:
		 //printf("\n----ListTrabverse功能待实现！\n");     
		 if(!ListTrabverse(L))
			 printf("线性表是空表！\n");
		 getchar();getchar();
		 break;
	   case 13:
		   if (( L->elem!=NULL)&&( L->listsize>=LIST_INIT_SIZE)){
              printf("input file name: ");
              scanf("%s",filename);//写文件的方法 
             if(StoreInFile(L,filename)==OK){
				 printf("写入成功！\n");
				 getchar();getchar();
			 }
			 else{
				 printf("写入失败！\n");
				 getchar();getchar();
			 }
		   }
		   else{
			   printf("未初始化！\n");
			   getchar();getchar();
		   }
			 break;
		   
	   case 14:
		   if (( L->elem!=NULL)&&( L->listsize>=LIST_INIT_SIZE)){
		   printf("input file name: ");
           scanf("%s",filename);//写文件的方法 
           if(ReadFromFile(L,filename)==OK){
			   printf("读入成功！\n");
		       getchar();getchar();
		   }
		   else{
			   printf("读入失败！\n");
			   getchar();getchar();
		   }
		   }
		   else{
			   printf("未初始化！\n");
			   getchar();getchar();
		   }
		   break;
	   case 15:
		   int m;
		   printf("请输入你要操作的表[1-3]:");
		   scanf("%d",&m);
		   if(m==1){
			   L=&L1;
		      printf("切换成功\n");
		   getchar();getchar();
		   }
		   else if(m==2){
			   L=&L2;
		      printf("切换成功\n");
		   getchar();getchar();
		   }
		   else if(m==3){
			   L=&L3;
		   printf("切换成功\n");
		   getchar();getchar();
		   }
		   else {
			   printf("切换失败！\n");
				   getchar();getchar();
		   }
		   break;
	     case 0:
         break;
	}//end of switch
  }//end of while
  printf("欢迎下次再使用本系统！\n");

}//end of main()
/*--------page 23 on textbook --------------------*/
status IntiaList(SqList * L){
	L->elem = (ElemType *)malloc( LIST_INIT_SIZE * sizeof (ElemType));
    if(!L->elem) 
		exit(OVERFLOW);
	L->length=0;
    L->listsize=LIST_INIT_SIZE;
	return OK;
}//初始化表
status DestroyList(SqList *L){
	if (( L->elem!=NULL)&&( L->listsize>=LIST_INIT_SIZE)){
	free(L->elem);
	L->elem = NULL;
	return OK;
	}
	else
		return ERROR;
}//销毁表
status ClearList(SqList* L){
	if (( L->elem!=NULL)&&( L->listsize>=LIST_INIT_SIZE)){
	L->length = 0;
	return OK;
	}
	else
		return ERROR;
}//清空表
status ListEmpty(SqList *L){
	if (( L->elem!=NULL)&&( L->listsize>=LIST_INIT_SIZE)){
    if(L->length == 0)
	return TRUE;
	else 
	return FALSE;
	}
	else
		return ERROR;
}//判定空表
int ListLength(SqList *L){
	if (( L->elem!=NULL)&&( L->listsize>=LIST_INIT_SIZE))
	  return L->length;
	else
		return ERROR;
}//求表长
status GetElem(SqList* L,int i,ElemType &e){
	  e=*(L->elem+i-1);
	  return e;
}//获得元素
int LocateElem(SqList *L,ElemType e){
	if (( L->elem!=NULL)&&( L->listsize>=LIST_INIT_SIZE)){
	int k=1;
	while(*L->elem != e){
		L->elem++;
		k++;
		if(k >L->length){
			return FALSE;
		}
	}
	return k;
	}
	else
		return ERROR;
}//查找元素
status PriorElem(SqList *L,ElemType cue,ElemType *pre){
	    int i;
        for(i=0;i<L->length;i++){
		if(L->elem[i] == cue){
			if(i==0)
				return FALSE;
			*pre=L->elem[i-1];
			return OK;
		}
		}
		return FALSE;
}//获得前驱
status NextElem(SqList* L,ElemType cue,ElemType *next){
	int i;
	if (( L->elem!=NULL)&&( L->listsize>=LIST_INIT_SIZE)){
	for(i=0;i<L->length-1;i++){
		if(L->elem[i] == cue){
			if(i==L->length-1)
				return FALSE;
			*next = (int)L->elem[i+1];
			return OK;
		}
	}
	  return FALSE;
	}
	else
		return ERROR;
}//获得后继
status ListInsert(SqList *L,int i,ElemType e){
	ElemType *f,*t,*p;
	if (( L->elem!=NULL)&&( L->listsize>=LIST_INIT_SIZE)){
	if(!L->elem)
		return ERROR;
	if(i<1||i>L->length+1)
		return ERROR;
	if(L->length >= L->length+1)
		return ERROR;
	if(L->length >= L->listsize){
		f = (ElemType *)realloc(L->elem,(L->listsize +LISTINCREMENT)*sizeof(ElemType));
		if(!f)
			return ERROR;
		L->elem = f;
		L->listsize += LISTINCREMENT;
	}
	t =&(L->elem[i-1]);
	for(p=&(L->elem[L->length-1]);p>=t;p--){
		*(p+1)=*p;
	}
	*t=e;
	++L->length;
	return OK;
	}
	else
		return ERROR;
}//插入元素
status ListDelete(SqList *L,int i,ElemType*e){
	ElemType *t,*p;
	if(i<1||i>L->length||!L->elem)
		return ERROR;
	p=&(L->elem[i-1]);
	e=p;
	t=&(L->elem[L->length-1]);
	for(p++;p<=t;++p)
		*(p-1)=*p;
	--L->length;
	return OK;
}//删除元素
status ListTrabverse(SqList *L){
	if (( L->elem!=NULL)&&( L->listsize>=LIST_INIT_SIZE)){
   int i;
   printf("\n-----------all elements -----------------------\n");
   for(i=0;i<L->length;i++) printf("%d ",L->elem[i]);
   printf("\n------------------ end ------------------------\n");
   return L->length;
	}
	else
		return ERROR;
}//遍历表
int StoreInFile(SqList *L,char * filename){
	FILE *fp;
	if (( L->elem!=NULL)&&( L->listsize>=LIST_INIT_SIZE)){
        if ((fp=fopen(filename,"w"))==NULL){
	            printf("File open error\n ");
		}
              fwrite(L->elem,sizeof(ElemType),L->length,fp);//这里是1次性写入，对于其它物理结构，可通过遍历，逐个访问数据元素并写入到文件中
              fclose(fp);
			  return OK;
	}
	else 
		return ERROR;

}
int ReadFromFile(SqList  *L,char * filename){
	L->length=0;
	FILE *fp;
	if (L->length<=LIST_INIT_SIZE){
  
	  if ((fp=fopen(filename,"r"))==NULL){
	       printf("File open error\n ");
		   return 1;
	    }
           while(fread(&(L->elem[L->length]),sizeof(ElemType),1,fp)){
           L->length++;//这里从文件中逐个读取数据元素恢复顺序表，对于不同的物理结构，可通过读取的数据元素恢复内存中的物理结构。
		   }
           fclose(fp);
		   return OK;
	}
	
}
