#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
 //数据元素类型定义
typedef int status;                                                    

typedef  struct {
	int key ;
	int value ;
} Elemtype;

typedef struct node{                                                    
    Elemtype data;
    struct node *lchild ,* rchild;
}Tnode,*Bitree;

typedef struct { 
	int  * elem;
	int length;;
}SqList;
 
 Tnode **T;
 Tnode *q,*c,*L1,*L2,*L3;
 int j=0,i=0,x=0,xx=0,res=0;
 int a[6];
//case 1 初始化二叉树
status InitBiTree(Bitree   &T)
{ 
	T=(Bitree)malloc(sizeof(Tnode)) ;
	T->lchild=T->rchild=NULL;                                                                                 
	return OK;
}  
//case2 销毁二叉树
status DestroyBiTree(Bitree  &T)
{
	if(T)
    {
        if((T)->lchild) 
            DestroyBiTree(T->lchild); 
        if((T)->rchild) 
            DestroyBiTree(T->rchild); 
        free(T); 
        T=NULL;
    }
	return OK;
}
//case3 创建二叉树
status CreateBiTree(Bitree & T,int * p){                               
	
	if(*(p+xx)==-1) 
		 {xx++;
	  return OK;
	  }
		 T=(Bitree)malloc(sizeof(Tnode)) ;
	     T->lchild=T->rchild=NULL;      
	     T->data.key=*(p+xx);
		 xx++;
	     T->data.value=*(p+xx);
	     xx++;
		   CreateBiTree(T->lchild,(p));
	       CreateBiTree(T->rchild,(p));
		 return OK;
			
}
//case4 清空二叉树
status ClearBiTree(Bitree  T)
{                                                  
	 if(T)
    {
        if((T)->lchild) 
            DestroyBiTree(T->lchild); 
        if((T)->rchild) 
            DestroyBiTree(T->rchild); 
        free(T); 
        T=NULL;
    }
	T=(Bitree)malloc(sizeof(Tnode)) ; 
	T->lchild=T->rchild=NULL;     
	return OK;
}
//case 5 判断二叉树是否为空
status BiTreeEmpty(Bitree  T)
{                                             
	if((T)->lchild||T->rchild)
	return ERROR;
	else return OK;
}
//case 6 求二叉树深度
status BiTreeDepth(Bitree T,int j,int &x){                                 
	if(T)
	     {    j=j+1;                                    
              if(j>x)x=j;                                    
              BiTreeDepth(T->lchild,j,x);                
              BiTreeDepth(T->rchild,j,x);
          }
       return x;
}
//case7  求根节点
status Root(Bitree  T)
{      printf("该二叉树的根结点值为:%d\n\n",T->data.value);
       return OK;                                                    
}
//case8  求节点
Tnode * Value(Bitree T,int e)
{   Tnode * t1;
    if(T==NULL)
		return NULL;
	if(T->data.key==e)
		return T;
	t1=Value(T->lchild,e);
	if(t1!=NULL)
		return t1;
	return Value (T->rchild,e);
}   
//case9  改变节点的值
 status Assign(Bitree T,int e,int d)
{     if( Value(T,e)) 
           Value(T,e)->data.value=d;  return OK;
		   return ERROR;
} 
//case10 求双亲节点
Tnode * Parent(Bitree T,int e)
{   Tnode * t1;
    if(T)
	{
		if(T->data.key==e)return NULL;
	    else 
	    {
	 	    if(T->lchild!=NULL&&T->lchild->data.key==e||T->rchild!=NULL&&T->rchild->data.key==e)
	         return T;
		     else if (t1=Parent( T->lchild, e))return t1;
		     else if (t1=Parent( T->rchild, e))return t1;
	     }
	}
	return NULL;
}
//case11 求左孩子节点
Tnode * LeftChild(Bitree T,int e)
{   
	if(Value(T,e)==NULL) return NULL;
	else return Value(T,e)->lchild;
}
//case12 求右孩子节点
Tnode * RightChild(Bitree T,int e)
{   
	if(Value(T,e)==NULL) return NULL;
	else return Value(T,e)->rchild;
}
//case13 求左兄弟
Tnode * LeftSibling(Bitree T,int e)
{   
	 if(Parent( T, e)&&Parent( T, e)->lchild)
	 {
		 if(Parent(T, e)->lchild->data.key == e)
			 return NULL;
		 return Parent( T, e)->lchild;
	 }

	else return NULL;
}
//case14 求右兄弟
Tnode * RightSibling(Bitree T,int e)
{   if(Parent( T, e)&&Parent( T, e)->rchild)
	 {
		 if(Parent(T, e)->rchild->data.key == e)
			 return NULL;
		 return Parent( T, e)->rchild;
	 }

	else return NULL;
}
//case15  插入子树
status InsertChild(Bitree T,int e,int LR,Bitree c)
{  if(Value(T,e))
         {
		  if(LR==0)
		  {
		         c->rchild=Value(T,e)->lchild;
		          Value(T,e)->lchild=c;
		  }
          if(LR==1)
		  {
		          c->rchild=Value(T,e)->rchild;
		           Value(T,e)->rchild=c;
		  }
          return OK;
          }
 else return ERROR;
}
//case16 删除子树
status DeleteChild(Bitree T,int e ,int LR)
{  if(Value(T,e))
         {
		  if(LR==0&&Value(T,e)->lchild)DestroyBiTree(T->lchild);
          if(LR==1&&Value(T,e)->rchild)DestroyBiTree(T->rchild);
		return OK;
          }
           else return ERROR;
}
//case17 前序遍历
status PreOrderTraverse(Bitree T)
{  if(T)
     {       printf("%d.%d ",T->data.key,T->data.value);
             PreOrderTraverse(T->lchild);
			 PreOrderTraverse(T->rchild);
			 return OK;
}
return ERROR;
}
//case18 中序遍历
status InOrderTraverse(Bitree T)
{  if(T)
     {       InOrderTraverse(T->lchild);
		     printf("%d.%d ",T->data.key,T->data.value);
			 InOrderTraverse(T->rchild);
			 return OK;
}
return ERROR;
}
//case19 后序遍历
status PostOrderTraverse(Bitree T)
{  if(T)
     {       PostOrderTraverse(T->lchild);
			 PostOrderTraverse(T->rchild);
			 printf("%d.%d ",T->data.key,T->data.value);
			 return OK;
}
return ERROR;
}
//case20 层序遍历
status LevelOrderTraverse(Bitree T)
{     int i=0,n=0;
      Bitree temp[100],p;
	  temp[n]=T;
	  while(i<=n)
	  {p=temp[i];
	 printf("%d.%d ",p->data.key,p->data.value);
	 if(p->lchild)temp[++n]=p->lchild;
	 if(p->rchild)temp[++n]=p->rchild;
	 i++;
	  }
	  return OK;
}
//case 21 文件输入
status LoadToFile(Bitree T, char * filename,FILE *fp)
{   
	int a=-1;
	if(!T)
	{
		fwrite(&a, sizeof(int),1, fp);
		return 0;
	}
		fwrite(&(T->data.key), sizeof(int),1, fp);
		fwrite(&(T->data.value), sizeof(int), 1, fp);
		 LoadToFile( T->lchild, filename,fp);
	     LoadToFile( T->rchild, filename,fp);

	return 0;
}
//case 22 文件输出
int LoadFromFile(Bitree & T, char * filename)                           
{   
	FILE * fp;
	SqList *L;
	L=NULL;
	L=(SqList *)malloc(  sizeof (int));
    L->elem = (int *)malloc( 100 * sizeof (int));
	L->length=0;
	if ((fp = fopen(filename, "r")) == NULL)
	{
		
		printf("File open error!\n");
		return 1;
	}
	if(T->lchild||T->rchild)
		return 1;
	while (fread(&L->elem[L->length], sizeof(int), 1, fp))
	{
		L->length++;
	}
	fclose(fp);
	CreateBiTree(T,L->elem);
	return 0;
}
          
void main(void){ 
    int op=1,d=0;
    char filename[30];
	SqList *L;
	L=(SqList *)malloc(  sizeof (int));
          L->elem = (int *)malloc( 100 * sizeof (int));
          L->length=0;
	while(op){
	system("cls");	printf("\n\n");
	printf("      二叉树菜单 \n");
	printf("-------------------------------------------------\n");
	printf("    	  1.InitBiTree              12. LeftChild\n");
	printf("    	  2. DestroyBitree        13. LeftSibling \n");
	printf("    	  3. CreateBitree        14. RightSibling\n");
	printf("    	  4. ClearBitree         15. InsertBitree\n");
	printf("    	  5. BiTreeEmpty         16. DeleteBitree\n");
	printf("    	  6. Depth           17. PreOrderTraverse\n");
	printf("    	  7. Root             18. InOrderTraverse\n");
	printf("    	  8. Value          19. PostOrderTraverse\n");
	printf("    	  9. Assign        20. LevelOrderTraverse\n");
	printf("    	  10. Parent               21. LoadToFile\n");
	printf("    	  11.LeftChild           22. LoadFromFile\n");
	printf("    	  23. ChangeBiTree                0. Exit\n");
	printf("-------------------------------------------------\n");	
	T=&L1;
	printf("    请选择你的操作[0~23]:");
		while (scanf("%d", &op) != 1 || (op < 0 || op > 23))
		{
			printf("输入错误，请重新选择你的操作[0~23]: ");	                         
			while (getchar() != '\n');
		}
 
    switch(op){
 //初始化二叉树
	   case 1:
		 if(InitBiTree(*T)==OK)
		 {
		 printf("二叉树初始化成功！\n"); a[d]=1;
		 }                                                                      
		     else printf("二叉树初始化失败！\n");   
			
		 getchar();getchar();
		 break;
 //二叉树销毁
	   case 2:
		 if(a[d]==0)
		     printf("二叉树不存在！\n"); 
		 else {
			 if(DestroyBiTree(*T)==OK)
			 { 
				 printf("二叉树销毁成功！\n");  a[d]=0;
			 }                                                                   
		 else printf("二叉树销毁失败！\n"); 
		 }
		 getchar();getchar();
		 break;
//创建二叉树
	   case 3:
		 if(a[d]==0)
		     printf("二叉树不存在！\n"); 
		 else {xx=0;
          int *p,fl=0,n=0;
          p=L->elem+1;
		  printf("输入要创建的二叉树总标记数\n");
		  scanf("%d",&j);
          printf("输入要创建的二叉树\n");
		  while (n<j )
          { printf("输入第%d个数\n",n+1);
            scanf("%d",&fl);
	       *p=fl;
            p++;
			n++;
          }	
         if (CreateBiTree(*T,(L->elem+1))==OK)
		 {
		 printf("二叉树创建成功！\n");
		 a[d]=1;
		 }                                                                          
		 else printf("二叉树创建失败！\n");  }
		 getchar();getchar();
		 break;
//二叉树清空
	   case 4:
		  if(a[d]==0)
		     printf("二叉树不存在！\n");                                             
		   else 
			 {
			 if(ClearBiTree(*T)==OK)
			 { 
				 printf("二叉树清空成功！\n"); a[d]=2;
			 }                                                                    
		    else printf("二叉树清空失败！\n"); 
		     }
		 getchar();getchar();
		 break;
//判定二叉树是否为空
	   case 5:
		 if(a[d]==0)
		     printf("二叉树不存在！\n");                                       
		   else 
		   {
			if(   BiTreeEmpty(*T)==OK)  printf("二叉树为空！\n");
			else printf("二叉树不为空！\n");
		   }
		 getchar();getchar();
		 break;
 //求二叉树的深度
	   case 6:      
		 if(a[d]==0){
		     printf("二叉树不存在！\n"); 
			 getchar();getchar();
		 }
		 else  if(a[d]==2){
		     printf("二叉树为空！\n");  
			 getchar();getchar();
		 }
		 else{
         printf("%d\n",BiTreeDepth(*T,0,x));                                         
		getchar();getchar();
		 }
		 break;
//求二叉树的根节点
	   case 7:
		 if(a[d]==0){
		     printf("二叉树不存在！\n");  
			 getchar();getchar();
		 }
		 else if(a[d]==2){
		     printf("二叉树为空！\n");  
			 getchar();getchar();
		  }
			 else   {
				 Root( *T)      ;                                         
		         getchar();getchar();
			 }
		 break;
//获得节点
	   case 8:
		   int e;
		  if(a[d]==0){
		     printf("二叉树不存在！\n");  
			 getchar();getchar();
		  }
		  else if(a[d]==2){
		     printf("二叉树为空！\n");  
			 getchar();getchar();
		   }
		 else  {
			 printf("输入一个值\n"); 
		        scanf("%d",&e);
		 if(Value(*T,e)) {
			 printf("该节点的值为%d ",Value(*T,e)->data.value); 
			 getchar();getchar();
		 }
		 else{
			 printf("无该节点");  
		 getchar();getchar();
		 } 
		 }
		 break;
//节点赋值
	   case 9:
		  if(a[d]==0) {                                                           
		     printf("二叉树不存在！\n"); 
			 getchar();getchar();
		  }
		  else if(a[d]==2){
		     printf("二叉树为空！\n"); 
			  getchar();getchar();
		  }
		   else {
		     int e,d;
		     printf("要改变值的节点\n"); 
		     scanf("%d",&e);
			 printf("要改变的值\n"); 
		     scanf("%d",&d);			 
		     if (Assign(*T,e,d)==OK) {
				 printf("赋值完成");    
				  getchar();getchar();
		  }
		     else{
				 printf("没有对应的节点！\n"); 
			 getchar();getchar();
		    }
		   }
	
		 break;
//求双亲节点
	   case 10:
		 if(a[d]==0){                                                              
		     printf("二叉树不存在！\n"); 
			  getchar();getchar();
		  }
		 else if(a[d]==2){
		     printf("二叉树为空！\n");
			  getchar();getchar();
		  }
		   else
		   {
		 printf("要查询的值\n"); 
		 scanf("%d",&e);
		 if(e==1||Parent(*T,e)==NULL){
			 printf ("该值没有双亲节点");
			  getchar();getchar();
		  }
		 else {  	
		 printf("要求节点的值为:%d",Parent(*T,e)->data.value);
		  getchar();getchar();
		  }
		}
		 break;
//求左孩子节点
	   case 11:
		 if(a[d]==0){                                                           
		     printf("二叉树不存在！\n"); 
			  getchar();getchar();
		  }
		 else  if(a[d]==2){
		     printf("二叉树为空！\n");
			  getchar();getchar();
		  }
		   else{
			   printf("要查询的值\n"); 
		 scanf("%d",&e);
		 if(LeftChild(*T,e)==NULL){
			 printf ("该值没有左孩子节点");
			  getchar();getchar();
		  }
		 else {  	
		 printf("要求节点的值为:%d",LeftChild(*T,e)->data.value);
		  getchar();getchar();
		 }
		   }
		 break; 
//求右孩子节点
	   case 12:  
	 if(a[d]==0) {                                                               
		     printf("二叉树不存在！\n");
			  getchar();getchar();
		  }
	 else  if(a[d]==2){
		     printf("二叉树为空！\n"); 
			  getchar();getchar();
		  }
		   else{
			   printf("要查询的值\n"); 
		 scanf("%d",&e);
		if(RightChild(*T,e)==NULL){
			printf ("该值没有右孩子节点");
			 getchar();getchar();
		  }
		 else {  	
		 printf("要求节点的值为:%d",RightChild(*T,e)->data.value);
		  getchar();getchar();
		 }
		   }
		 break; 
//求左兄弟节点
		 case 13:
		 if(a[d]==0) {                                                            
		     printf("二叉树不存在！\n"); 
			  getchar();getchar();
		  }
		 else  if(a[d]==2){
		     printf("二叉树为空！\n");  
			  getchar();getchar();
		  }
		   else
		   {
			   printf("要查询的值\n"); 
		 scanf("%d",&e);
		if(LeftSibling(*T,e)==NULL){
			printf ("该值没有左兄弟节点");
			 getchar();getchar();
		  }
		 else {  	
		 printf("要求节点的值为:%d",LeftSibling(*T,e)->data.value);
		 getchar();getchar();
		 }
		  }
		 break; 
//求右兄弟节点
		case 14:
		 if(a[d]==0) {                                                          
		     printf("二叉树不存在！\n"); 
			  getchar();getchar();
		  }
		 else if(a[d]==2){
		     printf("二叉树为空！\n"); 
			  getchar();getchar();
		  }
		   else{
			   printf("要查询的值\n"); 
		 scanf("%d",&e);
		if(RightSibling(*T,e)==NULL){
			printf ("该值没有右兄弟节点");
			 getchar();getchar();
		  }
		 else {  	
		 printf("要求节点的值为:%d",RightSibling(*T,e)->data.value);
		getchar();getchar();
		 }
		   }
		 break; 
//  插入子树
          case 15:
		 if(a[d]==0) {                                                              
		     printf("二叉树不存在！\n");
			  getchar();getchar();
		  }
		 else if(a[d]==2){
		     printf("二叉树为空！\n"); 
			  getchar();getchar();
		  }
		 else
		    {     int *p1,fl1=0,n1=0,LR;
		          Bitree T1;
				  T1=NULL;
          p1=L->elem+1;
		  printf("输入要创建的新二叉树数\n");
		  scanf("%d",&j);
          printf("输入要创建的新二叉树\n");
		  while (n1<j )
          { printf("输入第%d个数\n",n1+1);
            scanf("%d",&fl1);
	       *p1=fl1;
            p1++;
			n1++;
          }	
		  xx=0;
         if (CreateBiTree(T1,(L->elem+1))==OK)	{ 
			 printf("新二叉树创建成功！\n"); 
		  getchar();getchar();
		  }
		 else {printf("新二叉树创建失败！\n");
		  getchar();getchar();
		  }
		  printf("输入二叉树插入的节点e\n");
		  scanf("%d",&e);
		 printf("输入插入二叉树为左子树还是右子树LR(0 or 1 ）\n");
			scanf("%d",&LR);
			if(InsertChild(*T,e,LR,T1)==OK){
				printf("插入成功");
				 getchar();getchar();
		  }
			else{ printf("插入失败");
			 getchar();getchar();
		  }
		 }
		 break; 
// 删除子树
		case 16:
			 if(a[d]==0){                                                              
		     printf("二叉树不存在！\n"); 
			  getchar();getchar();
		  }
			 else  if(a[d]==2){
		     printf("二叉树为空！\n"); 
			  getchar();getchar();
		  }
		 else {
			int LR;
			printf("输入二叉树删除的节点e\n");
			scanf("%d",&e);
			printf("输入删除二叉树为左子树还是右子树LR(0 or 1 ）\n");
			scanf("%d",&LR);
			DeleteChild(*T,e,LR);
			if(DeleteChild(*T,e,LR)==OK){
				printf("删除成功");
				 getchar();getchar();
		  }
			else{
			 printf("删除失败");
			 getchar();getchar();
		  }
		 }
		 break; 
//前序遍历
case 17:
			if(a[d]==0)   {                                                             
		     printf("二叉树不存在！\n"); 
			  getchar();getchar();
			 }
	    else if(a[d]==2){
		     printf("二叉树为空！\n");  
			  getchar();getchar();
			 }
		 else{
		     PreOrderTraverse(*T);
			  getchar();getchar();
		 }
		 break; 
//中序遍历
case 18:
		if(a[d]==0)   {                                                             
		     printf("二叉树不存在！\n"); 
			  getchar();getchar();
			 }
	    else if(a[d]==2){
		     printf("二叉树为空！\n");  
			  getchar();getchar();
			 }
		 else{
		     InOrderTraverse(*T);
			  getchar();getchar();
		 }
		 break; 
//后序遍历
case 19:
		 if(a[d]==0) {                                                           
		     printf("二叉树不存在！\n"); 
			 getchar();getchar();
			 }
		 else if(a[d]==2){
		     printf("二叉树为空！\n");  
			 getchar();getchar();
			  }
		 else{
		     PostOrderTraverse(*T);
			  getchar();getchar();
		 }
		 break; 
//层序遍历
case 20:
			if(a[d]==0)   {                                                             
		     printf("二叉树不存在！\n"); 
			  getchar();getchar();
			 }
	    else if(a[d]==2){
		     printf("二叉树为空！\n");  
			  getchar();getchar();
			 }
		 else{
		     LevelOrderTraverse(*T);
			  getchar();getchar();
		 }
		 break;
//文件输入
case 21:
	 if(a[d]==0)                                                             
	printf("二叉树不存在！\n");
	  else if(a[d]==2)
	printf("二叉树为空！\n");  

			else{   FILE * fp;  
				printf("input file name: ");
				scanf("%s", filename);
				if ((fp = fopen(filename, "w")) == NULL)
	{
		printf("File open error!\n");
	}
				res = LoadToFile(*T, filename,fp);
				if (res == 0)
					printf("成功输出到文件!\n");
		
				else
					printf("文件打开失败!\n");
				 fclose(fp);
		
			}
	  getchar();getchar();
	 
			break;
//读入文件	
case 22:
			 if(a[d]==0)                                                           
		     printf("二叉树不存在！\n"); 
			 else if(a[d]==2)
		     printf("二叉树为空！\n"); 
			 else { 
				printf("input file name: ");
				scanf("%s", filename);
				xx=0;
				res = LoadFromFile(*T, filename);
				if (res == 1)
					printf("二叉树中已存在元素，请清空后再从文件载入!\n");
		
				else
					printf("载入成功!\n");
		
			}
			 getchar();getchar();
			break;
case 23:
	printf("请输入你要操作的二叉树[1~3]:");
	int m;
	scanf("%d",&m);
	if(m==1){
		T=&L1;
		d=1;
		printf("切换成功！");
		getchar();getchar();
	}
	else if(m==2){
		T=&L2;
		d=2;
		printf("切换成功！");
		getchar();getchar();

	}
	else if(m==3){
		T=&L3;
		d=3;
		printf("切换成功！");
		getchar();getchar();
	}
	else{
		printf("切换失败!\n");
		getchar();getchar();
	}
	break;
	}//end of switch
  }//end of while
  printf("欢迎下次再使用本系统！\n");
}//end of main()