#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX_CHAR 3
#define MAX_VERTEX_NUM 20

typedef int status;
typedef int InfoType;//弧相关的信息
typedef struct VertexType{
	char key[MAX_CHAR];
	int value;
	int isInit;
};
typedef enum{DG,DN}GraphKind;//{有向图，有向网}
typedef struct ArcNode{
	int adjvex;//该弧指向的顶点的位置
	struct ArcNode *nextarc;//指向下一条弧的指针
	InfoType *info;//该弧相关信息的指针
};
typedef struct VNode{
	VertexType data;//顶点信息
	ArcNode *firstarc;//指向第一条依附该顶点的弧的指针
}List[MAX_VERTEX_NUM];
typedef struct Graph{
	List vertices;
	int vexnum,arcnum;//图的当前顶点数和弧数
	int type;//图的种类标志
};
typedef int QElemType;
typedef struct QNode{
	QElemType data;
	struct QNode *next;
}*QueuePtr;
typedef struct{
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;
int visited[MAX_VERTEX_NUM];
int count=1;
status LocateVex(Graph G,VertexType elem);
status CreatGraph(Graph&G){//创建图
	int i,j;
	int weigh;//边的权
	VertexType vtail,vhead;
	int headloc,tailloc;
	ArcNode *cur,*last;
	printf("请输入要创建图的类型：0（有向图）/1（有向网）：");
	scanf("%d",&G.type);
	printf("请输入图的顶点数：");
	scanf("%d",&G.vexnum);
	printf("请输入图的边数:");
	scanf("%d",&G.arcnum);
	for(i=0;i<G.vexnum;i++){
		printf("请输入第%d个顶点的值:",i+1);
		scanf("%s",G.vertices[i].data.key);
		G.vertices[i].firstarc=NULL;
		G.vertices[i].data.isInit=0;
	}
	if(G.type==0){
		printf("请依次输入每条弧的弧尾和弧头，中间用回车隔开\n");
	}
	else{
		printf("请依次输入每条弧的权值、弧尾和弧头，中间用回车隔开\n");
	}
		for(i=0;i<G.arcnum;i++){
			printf("下面输入第%d组弧的参数\n",i+1);
			if(G.type==0){
				printf("请输入弧尾（字符串）：");
				scanf("%s",vtail.key);
				printf("请输入弧头（字符串）：");
				scanf("%s",vhead.key);
			}
			else{
				printf("请输入弧尾（字符串）：");
				scanf("%s",vtail.key);
				printf("请输入弧头（字符串）：");
				scanf("%s",vhead.key);
				printf("请输入权值（整数）：");
				scanf("%d",&weigh);
			}
			if((tailloc=LocateVex(G,vtail))==-1)
				return ERROR;
			if((headloc=LocateVex(G,vhead))==-1)
				return ERROR;
			cur=(ArcNode *)malloc(sizeof(ArcNode));
			cur->adjvex=headloc;
			if(G.type==0){
				cur->info=NULL;
			}
			else{
				cur->info=(int*)malloc(sizeof(int));
				*(cur->info)=weigh;
			}
			cur->nextarc=G.vertices[tailloc].firstarc;
			G.vertices[tailloc].firstarc=cur;
		}
		return OK;
}
status DestroyGraph(Graph&G){//销毁图
	G.vexnum=0;
	G.arcnum=0;
	ArcNode *cur,*temp;
	int i;
	for(i=0;i<G.vexnum;++i){
		cur=G.vertices[i].firstarc;
		G.vertices[i].firstarc=NULL;
		while(cur!=NULL){
			temp=cur->nextarc;
			if(G.type==1){
				free(cur->info);
			}
			free(cur);
			cur=temp;
		}
	}
	return OK;
}
status LocateVex(Graph G,VertexType elem){//查找顶点
	int i;
	for(i=0;i<G.vexnum;i++){
		if(strcmp(elem.key,G.vertices[i].data.key)==0){
			return i;
		}
	}
	return -1;
}
status GetVex(Graph G,VertexType elem,int &value){//获得结点值
	int i;
	for(i=0;i<G.vexnum;i++){
		if(strcmp(elem.key,G.vertices[i].data.key)==0){
			if(G.vertices[i].data.isInit==0){
				return INFEASIBLE;
			}
			else{
				value=G.vertices[i].data.value;
				return OK;
			}
		}
	}
	return FALSE;
}
status PutVex(Graph&G,VertexType elem,int value){//给结点赋值
	int i;
	for(i=0;i<=G.vexnum;i++){
		if(strcmp(elem.key,G.vertices[i].data.key)==0){
			G.vertices[i].data.isInit=1;
			G.vertices[i].data.value=value;
			return OK;
		}
	}
	return FALSE;
}
int FirstAdjVex(Graph G,VertexType elem){//获得第一个邻接结点
	int n;
	n=LocateVex(G,elem);
	if(n==-1)
		return -2;
	ArcNode *p=G.vertices[n].firstarc;
	if(p!=NULL){
		return p->adjvex;
	}
	else{
		return -1;
	}
}
int NextAdjVex(Graph G,VertexType elem,VertexType elem2){//获得下一个邻接结点
	int n,n2;
	n=LocateVex(G,elem);
	n2=LocateVex(G,elem2);
	if(n==-1||n2==-1)
		return -1;
	ArcNode *p=G.vertices[n].firstarc;
	if(p!=NULL){
		while(p){
			if(p->adjvex==n2){
				if(p->nextarc!=NULL){
					return p->nextarc->adjvex;
				}
				else{
					return -4;//该结点不存在下一个结点
				}
			}
			p=p->nextarc;
		}
		return -3;//顶点elem不与elem2相连
	}
	else{
		return -2;//顶点elem不存在邻接结点
	}
}
status InsertVex(Graph&G,VertexType elem){//添加一个新顶点
	strcpy(G.vertices[G.vexnum].data.key,elem.key);
	G.vertices[G.vexnum].data.isInit=0;
	G.vertices[G.vexnum].firstarc=NULL;
	G.vexnum++;
	return OK;
}
status DeleteVex(Graph &G,VertexType elem){//删除一个结点以及和它相关
	int n,i;
	ArcNode *temp,*q,*pretemp;
	n=LocateVex(G,elem);
	if(n==-1)
		return FALSE;
	temp=G.vertices[n].firstarc;
	while(temp!=NULL){
		q=temp;
		if(G.type==-1){
			free(temp->info);
		}
		temp=temp->nextarc;
		free(q);
		G.arcnum--;
	}
	for(i=n;i<G.vexnum-1;i++){
		G.vertices[i]=G.vertices[i+1];
	}
	G.vexnum--;
	for(i=0;i<G.vexnum;i++){
		temp=G.vertices[i].firstarc;
		if(temp!=NULL&&temp->adjvex==n){
			G.vertices[i].firstarc->nextarc=G.vertices[i].firstarc->nextarc->nextarc;
			if(G.type==1){
				free(temp->info);
			}
			free(temp);
			G.arcnum--;
		}
		else if(temp==NULL){
			G.arcnum=G.arcnum;
		}
		else{
			if(temp->adjvex>n){
				temp->adjvex--;
			}
			pretemp=temp;
			temp=temp->nextarc;
			while(temp!=NULL){
				q=temp;
				if(temp->adjvex>n){
					temp->adjvex--;
				}
				if(temp->adjvex==n){
					pretemp->nextarc=pretemp->nextarc->nextarc;
					temp=temp->nextarc;
					if(G.type==1){
						free(q->info);
					}
					free(q);
					G.arcnum--;
				}
				pretemp=pretemp->nextarc;
				temp=temp->nextarc;
			}
		}
	}
	return OK;
}
status InsertArc(Graph&G,VertexType elem,VertexType elem2){//c插入一条邻边
	int n,n2;
	n=LocateVex(G,elem);
	n2=LocateVex(G,elem2);
	if(n==-1||n2==-1)
		return ERROR;
	ArcNode *p;
	p=G.vertices[n].firstarc;
	while(p!=NULL){
		if(p->adjvex==n2){
			return -2;
		}
		p=p->nextarc;
	}
	ArcNode *temp;
	temp=(ArcNode *)malloc(sizeof(ArcNode));
	temp->adjvex=n2;
	if(G.type==1){
		temp->info=(int*)malloc(sizeof(int));
		int weigh;
		printf("\n请输入插入边的权值:");
		scanf("%d",&weigh);
		*(temp->info)=weigh;
	}
	else if(G.type==0){
		temp->info=NULL;
	}
	temp->nextarc=G.vertices[n].firstarc;
	G.vertices[n].firstarc=temp;
	G.arcnum++;
	return OK;
}
status DeleteArc(Graph&G,VertexType elem,VertexType elem2){//删除一条邻边
	int n,n2;
	n=LocateVex(G,elem);
	n2=LocateVex(G,elem2);
	if(n==-1||n2==-1)
		return ERROR;
	ArcNode *p,*q,*temp;
	p=G.vertices[n].firstarc;
	int found=0;
	if(p==NULL)
		return ERROR;
	if(p->adjvex==n2){
		q=p;
		G.vertices[n].firstarc=p->nextarc;
		if(G.type==1){
			free(q->info);
		}
		found=1;
		free(q);
		G.arcnum--;
	}
	else{
		while(p!=NULL){
			q=p;
			p=p->nextarc;
			if(p->adjvex==n2){
				found=1;
				q->nextarc=p->nextarc;
				if(G.type==1){
					free(p->info);
				}
				free(p);
				break;
			}
		}
	}
	if(!found){
		return INFEASIBLE;
	}
	return OK;
}
void DFS(Graph G,int num){//进行深度遍历
	ArcNode *temp;
	int t;
	printf("第%d个结点为：%s\n",count,G.vertices[num].data.key);
	count++;
	visited[num]=TRUE;
	for(temp=G.vertices[num].firstarc;temp!=NULL;temp=temp->nextarc){
		t=temp->adjvex;
		if(visited[t]!=1)
			DFS(G,t);
	}
}
status DFSTraverse(Graph G){
	int i;
	for(i=0;i<G.vexnum;i++){
		visited[i]=FALSE;
	}
	for(i=0;i<G.vexnum;i++){
		if(visited[i]!=1)
			DFS(G,i);
	}
	return OK;
}
status InitQueue(LinkQueue &Q){
	Q.front=Q.rear=(QueuePtr)malloc(sizeof(QNode));
	if(!Q.front)
		exit(OVERFLOW);
	Q.front->next=NULL;
	return OK;
}
status QueueEmpty(LinkQueue Q){
	if(Q.front==Q.rear)
		return TRUE;
	else
		return FALSE;
}
status EnQueue(LinkQueue &Q,QElemType e){
	QueuePtr p=(QueuePtr)malloc(sizeof(QNode));
	if(!p)
		exit(OVERFLOW);
	p->data=e;
	p->next=NULL;
	Q.rear->next=p;
	Q.rear=p;
	return OK;
}
status DeQueue(LinkQueue &Q,QElemType &e){
	QueuePtr p;
	if(Q.front==Q.rear)
		return ERROR;
	p=Q.front->next;
	e=p->data;
	Q.front->next=p->next;
	if(Q.rear==p)
		Q.rear=Q.front;
	free(p);
	return OK;
}
status BFSTraverse(Graph G,LinkQueue Q){
	int v,u;
	ArcNode *temp;
	for(v=0;v<G.vexnum;v++){
		visited[v]=FALSE;
	}
	for(v=0;v<G.vexnum;v++){
		if(!visited[v]){
			visited[v]=TRUE;
			printf("第%d个结点为: %s\n",v+1,G.vertices[v].data.key);
			EnQueue(Q,v);
			while(!QueueEmpty(Q)){
				DeQueue(Q,u);
				for(temp=G.vertices[u].firstarc;temp!=NULL;temp=temp->nextarc){
					if(visited[temp->adjvex]!=1){
						visited[temp->adjvex]=TRUE;
						printf("第%d个结点为：%s\n",++count,G.vertices[temp->adjvex].data.key);
						EnQueue(Q,temp->adjvex);
					}
				}
			}
		}
	}
	return OK;
}
status LoadToFile(Graph *G, char * filename)
{
	int i;
	int number = -1;
	ArcNode * node;
	FILE * fp = fopen(filename, "w");
	if (fp == NULL)
		return ERROR;		//file open error

	fwrite(&(G->vexnum), sizeof(int), 1, fp);
	fwrite(&(G->arcnum), sizeof(int), 1, fp);

	for (i = 0; i < G->arcnum; i++)
		fwrite(&(G->vertices[i].data), sizeof(VertexType), 1, fp);

	for (i = 0; i < G->vexnum; i++)
	{
		node = G->vertices[i].firstarc;
		while (node != NULL)
		{
			fwrite(&(node->adjvex), sizeof(int), 1, fp);
			fwrite(&(node->info), sizeof(int), 1, fp);
			node = node->nextarc;
		}
		fwrite(&number, sizeof(int), 1, fp);
		fwrite(&number, sizeof(int), 1, fp);
	}
	fclose(fp);
	return OK;
}

status LoadFromFile(Graph *G, char * filename)
{
	int i;
	ArcNode * node;
	ArcNode * tempnode;
	FILE * fp = fopen(filename, "r");
	if (fp == NULL)
		return ERROR;		//file open error

	fread(&(G->vexnum), sizeof(int), 1, fp);
	fread(&(G->arcnum), sizeof(int), 1, fp);
	for (i = 0; i < G->vexnum; i++)
		fread(&(G->vertices[i].data), sizeof(VertexType), 1, fp);

	for (i = 0; i < G->vexnum; i++)
	{
		tempnode = (ArcNode *)malloc(sizeof(ArcNode));
		fread(&(tempnode->adjvex), sizeof(int), 1, fp);
		fread(&(tempnode->info), sizeof(int), 1, fp);
		if (tempnode->adjvex == -1)
			G->vertices[i].firstarc = NULL;
		else
		{
			G->vertices[i].firstarc = tempnode;
			node = tempnode;
			while (1)
			{
				tempnode = (ArcNode *)malloc(sizeof(ArcNode));
				fread(&(tempnode->adjvex), sizeof(int), 1, fp);
				fread(&(tempnode->info), sizeof(int), 1, fp);
				if (tempnode->adjvex == -1)
				{
					node->nextarc = NULL;
					break;
				}
				node->nextarc = tempnode;
				node = node->nextarc;
			}
		}
	}
	fclose(fp);
	return OK;
}
int main(void){
  int reCreate=2;
  Graph *G;
  Graph G1,G2,G3;
  G1.vexnum=0;
  G2.vexnum=0;
  G3.vexnum=0;
  G=&G1;
  VertexType elem,elem2;
  VertexType insertElem;
  int value=0;
  int Initial=0;
  int i,j;
  QElemType e;
  LinkQueue Q;
  char filename[30];
  int op=1;
  while(op){
	system("cls");	printf("\n\n");
	printf("      基  于  邻  接  表  的  图  演  示  系  统 \n");
	printf("-------------------------------------------------\n");
	printf("    	  1. CreateGraph       7. NextAdjVex\n");
	printf("    	  2. DestroyGraph      8. InsertVex\n");
	printf("    	  3. LocateVex         9. DeleteVex \n");
	printf("    	  4. GetVex            10. InsertArc\n");
	printf("    	  5. PutVex            11. DeleteArc\n");
	printf("    	  6. FirstAdjVex       12. DFSTrabverse\n");
	printf("    	  13.BFSTraverse       14. LoadToFile\n");
	printf("    	  15.LoadFromFile      16. ChangeGraph\n");
	printf("    	  0.exit\n");
	printf("-------------------------------------------------\n");
	printf("    请选择你的操作[0~13]:");
	scanf("%d",&op);
    switch(op){
	   case 1:
		 if(Initial){
			 printf("图已创建，是否覆盖？（1/0--YES/NO）\n");
			 scanf("%d",&reCreate);
		 }
			 if(reCreate==0)
				 break;
			 if(CreatGraph(*G)==OK){
				 printf("创建成功！\n");
				 getchar();getchar();
				 Initial=1;
			 }
			 else{
				 printf("创建失败!\n");
				 getchar();getchar();
			 }
		 break;
	   case 2:
		   if(!Initial){
			   printf("请先创建图！\n");
			   getchar();getchar();
			   break;
		   }
		   if(DestroyGraph(*G)==OK){
			   printf("销毁成功！\n");
			   Initial=0;
			   getchar();getchar();
		   }
		   else{
			   printf("销毁失败！\n");
			   getchar();getchar();
		   }
		 break;
	   case 3:
		  if(!Initial){
			   printf("请先创建图！\n");
			   getchar();getchar();
			   break;
		   }
		  printf("请输入你要查找的顶点：");
		  scanf("%s",elem.key);
		  if((i=LocateVex(*G,elem))>-1){
			  printf("该结点位于邻接表的第%d个，其标记为%d\n",i+1,i);
		      getchar();getchar();
		  }
		  else{
			  printf("未找到该顶点！\n");
			  getchar();getchar();
		  }
		 break;
	   case 4:
		 if(!Initial){
			   printf("请先创建图！\n");
			   getchar();getchar();
			   break;
		   }
		  printf("请输入你要查找的顶点：");
		  scanf("%s",elem.key);
		  if((i=GetVex(*G,elem,value))==OK){
			  printf("顶点%s的值为%d\n",elem.key,value);
			  getchar();getchar();
		  }
		  else if(i=INFEASIBLE){  
		    printf("该顶点还未赋值！\n");
			getchar();getchar();
		  }
		  else if(i==FALSE){
			  printf("未找到该顶点！\n");
			  getchar();getchar();
		  }
		 break;
	   case 5:
		if(!Initial){
			   printf("请先创建图！\n");
			   getchar();getchar();
			   break;
		   }
		printf("请输入你想赋值的顶点：");
		scanf("%s",elem.key);
		printf("请输入你要赋的值：");
		scanf("%d",&value);
		if((i=PutVex(*G,elem,value))==OK){
			printf("赋值成功！顶点%s的值为%d\n",elem.key,value);
		getchar();getchar();
		}
		else if(i==FALSE){
			printf("未找到该顶点！\n");
			getchar();getchar();
		}
		 break;
	   case 6:
		 if(!Initial){
			   printf("请先创建图！\n");
			   getchar();getchar();
			   break;
		   }
		 printf("请输入你想查找的顶点：");
		 scanf("%s",elem.key);
		 if((i=FirstAdjVex(*G,elem))>=0){
			 printf("顶点%s的邻接结点为%s\n",elem.key,G->vertices[i].data.key);
			 getchar();getchar();
		 }
		 else if(i==-2){
			 printf("未找到该结点！\n");
		 getchar();getchar();
		 }
		 else if(i==-1){
			 printf("该结点无邻接结点\n");
			 getchar();getchar();
		 }
		 else{
			 printf("查找失败！\n");
			 getchar();getchar();
		 }

		 break;
	   case 7:
		  if(!Initial){
			   printf("请先创建图！\n");
			   getchar();getchar();
			   break;
		   }
		 printf("请输入你想查找的顶点：");
		 scanf("%s",elem.key);
		 printf("请输入与该顶点相连的一个顶点：");
		 scanf("%s",elem2.key);
		 if((i=NextAdjVex(*G,elem,elem2))>=0){
			 printf("所查询的结点为%s\n",G->vertices[i].data.key);
		 getchar();getchar();
		 }
		 else if(i==-1){
			 printf("未找到该结点！\n");
		 getchar();getchar();
		 }
		 else if(i==-2){
			 printf("该结点不存在邻接结点！\n");
			 getchar();getchar();
		 }
		 else if(i==-3){
			 printf("所输入的顶点%s不与%s相连\n",elem2.key,elem.key);
			 getchar();getchar();
		 }
		 else if(i==-4){
			 printf("顶点%s不存在下一个结点\n",elem2.key);
			 getchar();getchar();
		 }			
		break;
	   case 8:
		 if(!Initial){
			   printf("请先创建图！\n");
			   getchar();getchar();
			   break;
		   }
		 printf("请输入你想插入的顶点：");
		 scanf("%s",insertElem.key);
		 if(InsertVex(*G,insertElem)==OK){
			 printf("插入成功！\n");
			 getchar();getchar();
		 }
		 else{
			 printf("插入失败！\n");
			 getchar();getchar();
		 }
		 break;
	   case 9:
		 if(!Initial){
			   printf("请先创建图！\n");
			   getchar();getchar();
			   break;
		   }
		 printf("请输入你想删除的顶点：");
		 scanf("%s",elem.key);
		 if(DeleteVex(*G,elem)==OK){
			 printf("删除成功！\n");
		     getchar();getchar();
		 }
		 else{
			 printf("删除失败！\n");
			 getchar();getchar();
		 }
		 break;
	   case 10:
		 if(!Initial){
			   printf("请先创建图！\n");
			   getchar();getchar();
			   break;
		   }
		 printf("请输入你想插入边的尾顶点：");
		 scanf("%s",elem.key);
		 printf("请输入你想插入边的头顶点：");
		 scanf("%s",elem2.key);
		 if(InsertArc(*G,elem,elem2)==OK){
			 printf("插入成功！\n");
			 getchar();getchar();
		 }
		 else{
			 printf("插入失败！\n");
			 getchar();getchar();
		 }
		 break;
	   case 11:
			 if(!Initial){
			   printf("请先创建图！\n");
			   getchar();getchar();
			   break;
		   }
		 printf("请输入你想删除弧的弧尾顶点：");
		 scanf("%s",elem.key);
		 printf("请输入你想删除弧的弧头顶点：");
		 scanf("%s",elem2.key);
		 if(DeleteArc(*G,elem,elem2)==OK){
			 printf("删除成功！\n");
			 getchar();getchar();
		 }
		 else{
			 printf("删除失败！\n");
			 getchar();getchar();
		 }
		 break;
	   case 12:
		 if(!Initial){
			   printf("请先创建图！\n");
			   getchar();getchar();
			   break;
		   }
		 count=1;
		 DFSTraverse(*G);
		 getchar();getchar();
		 break;
	   case 13:
		   if(!Initial){
			   printf("请先创建图！\n");
			   getchar();getchar();
			   break;
		   }
		   InitQueue(Q);
		   count=1;
		   BFSTraverse(*G,Q);
		   getchar();getchar();
		   break;
		  case 14:
			 if(!Initial){
			   printf("请先创建图！\n");
			   getchar();getchar();
			   break;
		   }
			else
			{
				printf("请输入存储的文件名: ");
				scanf("%s", filename);
				if (LoadToFile(G,filename) == ERROR){
					printf("文件打开失败!\n");
					getchar();getchar();
				}
				else{
					printf("成功输出到文件!\n");
					getchar();getchar();
			}
			 }
			break;
		case 15:
			 if(!Initial){
			   printf("请先创建图！\n");
			   getchar();getchar();
			   break;
		   }
			 else{
				printf("请输入读取的文件名: ");
				scanf("%s", filename);
				if (LoadFromFile(G,filename) == ERROR){
					printf("文件打开失败!\n");
					getchar();getchar();
				}
				else{
					printf("成功载入有向网!\n");
	            	getchar(); getchar();
				}
			 }
			break;
		case 16:
			int m;
			printf("请输入你想操作的图[1~3]:");
			scanf("%d",&m);
			if(m==1){
				G=&G1;
				if(G->vexnum==0){
					Initial=0;
				}
				else{
					Initial=1;
				}
				printf("切换成功！\n");
				getchar();getchar();
			}
			else if(m==2){
				G=&G2;
				if(G->vexnum==0){
					Initial=0;
				}
				else{
					Initial=1;
				}
				printf("切换成功！\n");
				getchar();getchar();
			}
			else if(m==3){
				G=&G3;
				if(G->vexnum==0){
					Initial=0;
				}
				else{
					Initial=1;
				}
				printf("切换成功！\n");
				getchar();getchar();
			}
			else{
				printf("切换失败！\n");
				getchar();getchar();
			}
	   case 0:
         break;
	}//end of switch
  }//end of while
  printf("欢迎下次再使用本系统！\n");
}//end of main()
