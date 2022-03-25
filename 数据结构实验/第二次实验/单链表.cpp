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
typedef struct Node{  //单链表的定义
	ElemType  elem;
	struct Node *next;
}Node,*pNode;
            

/*-----page 19 on textbook ---------*/
status IntiaList(pNode  &L);
status DestroyList(pNode & L);
status ClearList(pNode &L);
status ListEmpty(pNode L);
int ListLength(pNode L);
status GetElem(pNode  L,int seq,ElemType & e);
status LocateElem(pNode  L,ElemType e); //简化过
status PriorElem(pNode L,ElemType cue,ElemType &pre);
status NextElem(pNode  L,ElemType cue,ElemType & next);
status ListInsert(pNode  & L,int seq,ElemType e);
status ListDelete(pNode & L,int seq,ElemType &e);
status ListTrabverse(pNode L);  //简化过
status StoreInFile(pNode  L,char * filename);
status ReadFromFile(pNode & L,char * filename);
/*--------------------------------------------*/
int main(void){
  int op=1;
  pNode* L;
  pNode L1,L2,L3;
  L1=NULL;L2=NULL;L3=NULL;
  L=&L1;
  int seq,result;//seq表示序号数,result返回结果；e用来代入函数获取结果
  ElemType e,cue,pre,next;
  int Initial=0;//判断链表是否存在 
  while(op){
	system("cls");	printf("\n\n");
	printf("      Menu for Linear Table On Linked Structure \n");
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
		 if(IntiaList(*L) == OK) {
			 printf("单链表创建成功！\n");
			 Initial=1;
		     getchar();getchar();
		 }
		     else{
				 printf("单链表创建失败！\n");
		         getchar();getchar();
			 }
		 break;
	   case 2:
		   // printf("\n----DestroyList功能待实现！\n");  
		   if(!Initial){
			   printf("请先初始化！\n");
			   getchar();getchar();
		   }

		   else{
		  if(DestroyList(*L) == OK){
			   printf("单链表销毁成功！\n");
			   Initial=0;
			   getchar();getchar();
		  }
		  else {
			  printf("单链表销毁失败！\n");
		      getchar();getchar();
		  }
		   }
		 break;
	   case 3: 
		   //printf("\n----ClearList功能待实现！\n");
		     if(!Initial){
			   printf("请先初始化！\n");
			   getchar();getchar();
		   }

		   else{
		  if(ClearList(*L) == OK){
			   printf("单链表清空成功!\n");
			   getchar();getchar();
		  }
		   else {
			  printf("单链表清空失败！\n");
			  getchar();getchar();
		   }
		   }
		 break;
	   case 4:
		   //printf("\n----ListEmpty功能待实现！\n"); 
		     if(!Initial){
			   printf("请先初始化！\n");
			   getchar();getchar();
		   }

		   else{
		   if(ListEmpty(*L) == TRUE){
			   printf("单链表已清空！\n");
			   getchar();getchar();
		   }
		  else { 
			  printf("单链表未清空！\n");
		      getchar();getchar();
		  }
		   }
			  break;
	   case 5:
		   //printf("\n----ListLength功能待实现！\n");
		     if(!Initial){
			   printf("请先初始化！\n");
			   getchar();getchar();
		   }
		 else{
         printf("单链表长度为%d\n",ListLength(*L));
		 getchar();getchar();
		}
		 break;
	   case 6:
		 //printf("\n----GetElem功能待实现！\n");
		     if(!Initial){
			   printf("请先初始化！\n");
			   getchar();getchar();
		   }

		   else{
		   printf("请输入要查询的序数：");
		   scanf("%d",&seq);	
		      if( GetElem(*L,seq,e)==OK) {
			   printf("表中的第%d个数据为%d\n",seq,e);
			   getchar();getchar();}
			  else{
				  printf("查询失败！\n");
				  getchar();getchar();
			  }
		   }
		       break;
	   case 7:
		   //printf("\n----LocateElem功能待实现！\n");
		     if(!Initial){
			   printf("请先初始化！\n");
			   getchar();getchar();
		   }

		   else{
		   printf("请输入要查询的数据：");
		   scanf("%d",&e);
		   result=LocateElem(*L,e);
	    if(result!=ERROR){
		      printf("第一个与%d相等的元素序号是%d\n",e,result);
			  getchar();getchar();}
		else {
			printf("这样的数据元素不存在！\n");
			getchar();getchar();
		}
		   }
				   
		  
	
		 break;
	   case 8:
		//printf("\n----PriorElem功能待实现！\n");
		    if(!Initial){
			   printf("请先初始化！\n");
			   getchar();getchar();
		   }

		   else{
			   	 printf("请输入要查询的元素：");
		         scanf("%d",&cue);
		   if(PriorElem(*L,cue,pre) == OK){
			   printf("前驱为%d\n",pre);
			   getchar();getchar();
		   }
		   else {
			   printf("无此前驱\n");
			   getchar();getchar();
		   }
		   }
		 break;
	   case 9:
		// printf("\n----NextElem功能待实现！\n"); 
		    if(!Initial){
			   printf("请先初始化！\n");
			   getchar();getchar();
		   }

		   else{
		   printf("请输入要查询的元素：");
		   scanf("%d",&cue);
		   if(NextElem(*L,cue,next) == OK){
			   printf("后继为%d\n",next);
			   getchar();getchar();
		   }
		   else if(NextElem(*L,cue,next) == FALSE){
			   printf("无此后继\n");
		       getchar();getchar();
		   }
		   else{
		    printf("查找失败！\n");
		    getchar();getchar();
		   }
		   }
		   break;
	     case 10:
		// printf("\n----ListInsert功能待实现！\n");
			  if(!Initial){
			   printf("请先初始化！\n");
			   getchar();getchar();
		   }

		   else{
		   printf("请输入要插入的位置：");
		   scanf("%d",&seq);
		   printf("请输入要插入的元素：");
		   scanf("%d",&e);
		   if(ListInsert(*L,seq,e) == OK){
			   printf("单链表插入成功\n");
			   getchar();getchar();
		   }
		   else{
			   printf("单链表插入失败\n");
		       getchar();getchar();
		   }
		   }
		 break;
	   case 11:
		// printf("\n----ListDelete功能待实现！\n");
		    if(!Initial){
			   printf("请先初始化！\n");
			   getchar();getchar();
		   }

		   else{
		   printf("请输入要删除的元素的序列：");
		   scanf("%d",&seq);
		   if(ListDelete(*L,seq,e) == OK){
			   printf("元素删除成功\n");
			   getchar();getchar();
		   }
		   else{
			   printf("元素删除失败\n");
		       getchar();getchar();
		   }
		   }
		 break;
	   case 12:
		 //printf("\n----ListTrabverse功能待实现！\n");     
		 if(!Initial){
			   printf("请先初始化！\n");
			   getchar();getchar();
		   }

		   else{
			   if(ListTrabverse(*L)==ERROR){
				   printf("链表为空！\n");
			   }
			   getchar();getchar();
		   }
		 break;
		  case 13:
		    if(!Initial){
			   printf("请先初始化！\n");
			   getchar();getchar();
		   }

		   else{
              printf("input file name: ");
			  char filename[30];
				  scanf("%s",filename);//写文件的方法 
             if(StoreInFile(*L,filename)==ERROR){
				 printf("写入出错！\n");
				 getchar();getchar();
			 }
			 else{
				 printf("写入成功！\n");
				 getchar();getchar();
			 }
		   }
		  	 break;
		   
	   case 14:
		    if(!Initial){
			   printf("请先初始化！\n");
			   getchar();getchar();
		   }

		   else{
		   printf("input file name: ");
		   char filename[30];
           scanf("%s",filename);//写文件的方法 
           if(ReadFromFile(*L,filename)==ERROR){
			   printf("读入失败！\n");
		       getchar();getchar();
		   }
		   else{
			   printf("读入成功！\n");
			   getchar();getchar();
		   }
		   }
		   break;
         case 15:
			 int m;
			 printf("请输入要操作的链表[1~3]：");
			 scanf("%d",&m);
			 if(m==1){
				 L=&L1;
				 printf("切换成功！\n");
				 if(!L1)
				     Initial=0;
				 else
					 Initial=1;
				 getchar();getchar();
			 }
			 if(m==2){
				 L=&L2;
				 printf("切换成功！\n");
				 if(!L2)
				     Initial=0;
				  else
					 Initial=1;
				 getchar();getchar();
			 }
			 if(m==3){
				 L=&L3;
				 printf("切换成功！\n");
				 if(!L3)
				     Initial=0;
				  else
					 Initial=1;
				 getchar();getchar();
			 }
			 if(m<1||m>3){
				 printf("切换失败！\n");
				 getchar();getchar();
			 }
			 break;
	     case 0:
         break;
		 
		


   }//end of switch
  } //end of while
   printf("欢迎下次再使用本系统！\n");
}//end of main()

/*--------page 23 on textbook --------------------*/
status IntiaList(pNode& L){
	L=(pNode)malloc(2*sizeof(pNode));
	L->elem=0;
	L->next=NULL;
	return OK;
}//初始化表
status DestroyList(pNode &L){
    pNode Lp;
	if(L->elem==0){
		free(L);
		return OK;
	}
	while(L->next!=NULL){
		Lp=L;
		L=L->next;
		free(Lp);
	}
	free(L);
	return OK;
}//销毁表
status ClearList(pNode & L){
	pNode Lp,Lq;
	if(L->elem==0)
		return ERROR;
	Lp=L->next;
	while(Lp->next!=NULL){
		Lq=Lp;
		Lp=Lp->next;
		free(Lq);
	}
	free(Lp);
	L->elem=0;
	return OK;
}//清空表
status ListEmpty(pNode L){
	
    if(L->elem == 0)
	return TRUE;
	else 
	return FALSE;
}//判定空表
int ListLength(pNode L){
	return L->elem;
} //求表长
status GetElem(pNode  L,int i,ElemType &e){
	if(i<1||i>L->elem)
		return ERROR;
	pNode Lp=L;
	int k;
	for(k=0;k<i;k++){
		Lp=Lp->next;
	}
	e=Lp->elem;
	return OK;
}//获得元素
int LocateElem(pNode L,ElemType e){
	int k=0;
	pNode Lp=L->next;
	while(Lp!=NULL){
		k++;
		if(Lp->elem==e){
			return k;
		}
		Lp=Lp->next;
	}
	return ERROR;
}//查找元素
status PriorElem(pNode L,ElemType cue,ElemType &pre){
	if(!L->elem){
		return FALSE;
	}
	int k=0;
	pNode Lp,Lq;
	Lp=L;
	while(Lp!=NULL){
		k++;
		Lq=Lp;
		Lp=Lp->next;
		if(Lp==NULL)
			return FALSE;
		if(cue==Lp->elem&&k!=1){
			pre=Lq->elem;
			return OK;
		}
	}
	return FALSE;
}//获得前驱
status NextElem(pNode L,ElemType cue,ElemType &next){
	if(!L->elem)
		return FALSE;
	pNode Lp=L;
	while(Lp->next!=NULL){
		Lp=Lp->next;
		if(cue==Lp->elem){
			if(Lp->next==NULL)
				return ERROR;
			next=Lp->next->elem;
			return OK;}
	}
	return FALSE;
}//获得后继
status ListInsert(pNode &L,int i,ElemType e){
	if(i<1||i>L->elem+1)
		return ERROR;
	pNode p=L,q,newNode;
	newNode=(pNode)malloc(2*sizeof(pNode));
	newNode->elem=e;
	int k=0;
	while(p!=NULL&&k<i){
		q=p;
		p=p->next;
		k++;}
	q->next=newNode;
	newNode->next=p;
	L->elem=L->elem+1;
	return OK;
}//插入元素
status ListDelete(pNode & L,int i,ElemType &e){
		if(i<1||i>L->elem)
			return ERROR;
		pNode p=L,q;
		int k=0;
		while(p!=NULL&&k<i-1){
			p=p->next;
			k++;
		}
		q=p->next;
		p->next=q->next;
		e=q->elem;
		free(q);
		L->elem=L->elem-1;
		return OK;
}//删除元素
status ListTrabverse(pNode L){
	if(L->elem==0)
		return ERROR;
	pNode p=L->next;
	printf("\n-----------all elements -----------------------\n");
	while(p!=NULL){
		printf("%d ",p->elem);
		p=p->next;
	}
   printf("\n------------------ end ------------------------\n");
   return OK;
}//遍历表
status StoreInFile(pNode L,char * filename){
	if(L->elem==0)
		return ERROR;
	pNode p=L->next;
	FILE *fp;
        if ((fp=fopen(filename,"wb"))==NULL){
	            printf("File open error\n ");
				return ERROR;
		}
		while(p!=NULL){
              fwrite(p,2*sizeof(pNode),1,fp);//这里是1次性写入，对于其它物理结构，可通过遍历，逐个访问数据元素并写入到文件中
			  p=p->next;
		}
              fclose(fp);
			  return OK;

}
status ReadFromFile(pNode &L,char * filename){
	ClearList(L);
	L->elem=0;
	pNode p=L;
	FILE *fp;
	  if ((fp=fopen(filename,"rb"))==NULL){
	       printf("File open error\n ");
		   return ERROR;
	    }
    Node temp;
	   while(fread(&temp,2*sizeof(pNode),1,fp)){
		   p->next=(pNode)malloc(2*sizeof(pNode));
		   p=p->next;
		   *p=temp;
		   L->elem++;
	   }
	   p->next=NULL;
	   fclose(fp);
		   return OK;
	
}