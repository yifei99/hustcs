#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include "DPLL.h"
int *f;
int tmin;
int sudo[81];
int main(){
	int op=1;
	int a;
	root head;
	clock_t start, end;
	double duration;
	char filename1[1000];
	char filename2[1000];
	//LoadinFile(filename1, &head);
	while(op){
	system("cls");	printf("\n\n");
	printf("-------------------------------------------------\n");
	printf("    	  1. LoadinFile       \n");
	printf("    	  2. DPLL1\n");
	printf("    	  3. DPLL2\n");
	printf("          4. LoadtoFile\n");
	printf("          5. Trans_sudoku\n");
	printf("          0. Exit\n");
	printf("-------------------------------------------------\n");
	printf("    请选择你的操作:");
	scanf("%d",&op);
	switch(op){
	case 1:
	  printf("请输入文件名:");
	  scanf("%s",filename1);
	  LoadinFile(filename1, &head); 
	  printf("导入成功!\n");
	  getchar();getchar();
	  break;
	case 2:
	  start = clock();
	  if (a=DPLL1(&head))
		 printf("TRUE\n");
	  else
		 printf("FALSA\n");
	  end = clock();
	  duration = (double)(end - start) ;
	  printf("the DPLL uses %f ms\n", duration);
	  getchar();getchar();
	  break;
	case 3:
			  start = clock();
	  if (a=DPLL2(&head))
		 printf("TRUE\n");
	  else
		 printf("FALSA\n");
	  end = clock();
	  duration = (double)(end - start) ;
	  printf("the DPLL uses %f ms\n", duration);
	  getchar();getchar();
	  break;
	case 4:
       if (a == TRUE) {
		   int h;
		   printf("是否是操作数独？y-1/n-0\n");
		   scanf("%d",&h);
		   if(h==0){
	   for (int t = 0; t < head.NumOfVari; t++) {
	 				printf("%2d %d\n", *(f + t),t+1);
				}
		   }
		   else if(h==1){
			   int d,o,l,k;
		        k=0;
			    d=0;
			for (int t = 0; t < head.NumOfVari; t++){
				if(*(f+t)==1){
					if((t+1)%9==0)
						sudo[d]=9;
					else
					sudo[d]=(t+1)%9;
					d++;
				}
			}
				for(o=0;o<19;o++){
			if(o%2==0){
			for(l=0;l<37;l++){
				if(l%4==0)
					printf("\033[;31m+\033[0m");
				else
					printf("\033[;33m-\033[0m");
			}
			printf("\n");
			}
			else{
				for(l=0;l<37;l++){
					if(l%4==0&&l!=36){
						printf("\033[;31m+\033[0m");	
						printf("\033[;;1m %d \033[0m",sudo[k]);
						k++;
					}	
					if(l==36)
						printf("\033[;31m+\033[0m");
		}
				printf("\n");
		}
		}
		   }
				printf("TRUE!\n");
				int length = strlen(filename1);
				filename1[length - 1] = 's';
				filename1[length - 2] = 'e';
				filename1[length - 3] = 'r';
				FILE *fp;
				if ((fp = fopen(filename1, "w")) == NULL) {
					printf("File open error!\n");
					break;
				}
				fprintf(fp, "s 1\n");
				fprintf(fp, "v");
				for (int t = 0; t < head.NumOfVari; t++) {
					if(*(f+t)==1)fprintf(fp," %d",t+1);
					else fprintf(fp, " %d", -t - 1);
				}
				fprintf(fp, "\n");
				fprintf(fp, "t %f ms\n", duration);
				fclose(fp);
			}
			else {
				printf("FALSE!\n");
				int length = strlen(filename1);
				filename1[length - 1] = 's';
				filename1[length - 2] = 'e';
				filename1[length - 3] = 'r';
				FILE *fp;
				if ((fp = fopen(filename1, "w")) == NULL) {
					printf("File open eror!\n");
					break;
				}
				fprintf(fp, "s 0\n");
				fprintf(fp, "v\n");
				fprintf(fp, "t %f ms\n", duration);
				fclose(fp);
			}
			printf("导出成功！\n");
			memset(f,0,sizeof(f));
			getchar();getchar();
		break;
	case 5:
		printf("请输入文件名:");
		scanf("%s",filename2);
		FILE *f2;
		f2=fopen(filename2,"r");
		if(f2==NULL){
			printf("wrong!\n");
			break;
		}
		int i,o,l,k;
		k=0;
		for(i=0;i<81;i++){
				sudo[i]=fgetc(f2)-48;
		}
		for(o=0;o<19;o++){
			if(o%2==0){
			for(l=0;l<37;l++){
				if(l%4==0)
					printf("\033[;31m+\033[0m");
				else
					printf("\033[;33m-\033[0m");
			}
			printf("\n");
			}
			else{
				for(l=0;l<37;l++){
					if(l%4==0&&l!=36){
						printf("\033[;31m+\033[0m");
						if(sudo[k]==0)
							printf("   ");
						else
						printf("\033[;;1m %d \033[0m",sudo[k]);
						k++;
					}	
					if(l==36)
						printf("\033[;31m+\033[0m");
		}
				printf("\n");
		}
		}
		transudo(filename2);
	getchar();getchar();
       break;
	case 0:
		break;
	return 0;
	}
	}
} 
int Destroy(Node2 *p, root *head){
	Node1 *temp1, *temp2;
	for (; p->pL != NULL;){
		for (temp1 = p->pL, temp2 = p->pL; temp1->next1 != NULL; temp1 = temp1->next1)
			temp2 = temp1;
		if (temp1 ==p->pL){
			p->pL = NULL;
			free(temp1);
		}
		else
		{
			free(temp1);
			temp2->next1 = NULL;
		}
	}
	free(p);
	head->NumOfClause--;
	return 0;
}//传入一个子句指针，回收该子句及其所有文字
int IsUnitClause(root head, int *Elem){
	int i;
	Node2 *temp2;
	for (temp2 = head.p, i = 1; temp2 != NULL; temp2 = temp2->next2, i++){
		if (temp2->pL->next1 == NULL)
		{
			*Elem = temp2->pL->Elem;
			return i;
		}
	}
	return i = 0;
}//传入一个cnf公式，和一个整数指针，若有单子句则返回第一个单子句的位置和该单子句文字的值，否则返回0
int RemoveClause(root *head, int Elem){
	int i, j, k;//i标识子句是否是首子句，j标识当前子句是否含L，i为0标识首子句含L，i为1标识首子句不含L
	Node1 *temp11, *temp12;
	Node2 *temp21 = head->p, *temp22 = head->p;
	for (i = 1; temp21 != NULL; i++){//控制子句循环
		j = 1;
		for (temp11 = temp21->pL, temp12 = temp21->pL, k = 1; temp11 != NULL; k++){//循环子句中的每一个文字
			if (temp11->Elem == Elem){//若存在单子句规则要简化的文字L，则简化
				if (i == 1){//若第一个子句含有L
					head->p = temp21->next2;
					Destroy(temp21, head);
					i--;//使i为0，更新第一个子句
				}
				else{//其他子句含有L
					temp22->next2 = temp21->next2;
					Destroy(temp21, head);
					i++;
				}
				j = 0;
				break;//跳出第二重循环
			}
			if (temp11->Elem == -Elem){
				if (k == 1){
					temp21->pL = temp11->next1;
					free(temp11);
					temp11 = temp21->pL;
					temp12 = temp21->pL;
					k--;
				}
				else{
					temp12->next1 = temp11->next1;
					free(temp11);
					temp11 = temp12->next1;
				}
				continue;
			}
			temp12 = temp11;
			temp11 = temp11->next1;
		}
			if (i == 0)
			{
				temp21 = head->p; temp22 = head->p;
			}
			else if (i == 1 || (i>1 && j == 0))
				temp21 = temp22->next2;
			else{
				temp22 = temp21;
				temp21 = temp22->next2;
			}

		}
	return 0;
}//传入一个root型和一个elem，删除root中所有包含elem文字的子句
root* AddClause(root *head, int VariElem){
	Node2 *tempCp, *tempCp2, *tempCp3;
	Node1 *tempLp, *tempLp2, *tempLp3;
	root * NewHead;
	int i;
	NewHead = (root*)malloc(sizeof(root));
	NewHead->NumOfClause = head->NumOfClause + 1;
	NewHead->NumOfVari = head->NumOfVari;
	tempLp = (Node1*)malloc(sizeof(Node1));
	tempCp = (Node2*)malloc(sizeof(Node2));
	tempCp->pL = tempLp;
	tempLp->next1 = NULL;
	tempLp->Elem = VariElem;
	NewHead->p = tempCp;
	for (tempCp2 = head->p, tempCp3 = tempCp; tempCp2 != NULL; tempCp2 = tempCp2->next2){
		tempCp = (Node2*)malloc(sizeof(Node2));
		tempCp3->next2 = tempCp;
		for (tempLp2 = tempCp2->pL, i = 1; tempLp2 != NULL; tempLp2 = tempLp2->next1){
			if (i == 1){
				tempLp = (Node1*)malloc(sizeof(Node1));
				tempCp->pL = tempLp;
				tempLp3 = tempLp;
				tempLp->Elem = tempLp2->Elem;
				i++;
			}
			else{
				tempLp3 = tempLp;
				tempLp = (Node1*)malloc(sizeof(Node1));
				tempLp3->next1 = tempLp;
				tempLp->Elem = tempLp2->Elem;
			}
		}
		tempLp->next1 = NULL;
		tempCp3 = tempCp;
	}
	tempCp->next2 = NULL;
	return NewHead;
}//添加子句
int IsEmptyClause(root *head){//若含空子句，则返回0；否则返回1
	Node2 *tempCp;
	for (tempCp = head->p; tempCp != NULL; tempCp = tempCp->next2)
		if (tempCp->pL == NULL)
			return 0;
	return 1;
}
int IsOver(root *head){
	if (head->p == NULL)
		return 1;
	return 0;
}//是否删除结束
int DestroyHead(root *head){
	Node2 *tempCp, *tempCp2;
	for (tempCp = head->p; tempCp != NULL; tempCp = tempCp2){
		tempCp2 = tempCp->next2;
		Destroy(tempCp, head);
	}
	free(head);
	return 0;
}
int LoadinFile(char filename[], root *head){
	FILE * file;
	char str[LENGTH], stemp[LENGTH], ch = '0';
	int i, j, k, l, m;//临时变量
	Node1 *temp1;
	Node2 *temp2;
	
	file = fopen(filename, "r");
	if (file == NULL)
	{
		printf("wrong!\n");
		return FALSE;
	}
	for (; fgets(str, LENGTH, file);)//跳过注释，读到"p cnf "
		if (strstr(str, DESCRIPTION) != NULL)
			break;
	for (i = 6; str[i] != ' '; i++)
		stemp[i - 6] = str[i];
	stemp[i - 6] = '\0';//stemp记录变元数
	for (m = i; str[i] != '\0'; i++)
		str[i - m] = str[i];
	str[i - m] = '\0';//str记录子句数
	head->NumOfVari = atoi(stemp);//读取变元数，atoi(字符串转整形）
	f=(int*)malloc(sizeof(int)*atoi(stemp));
	memset(f,0,atoi(stemp));
	head->NumOfClause = atoi(str);//读取子句数
	head->p = (Node2*)malloc(sizeof(Node2));//分配第一个子句
	temp2 = head->p;
	fgets(str, LENGTH, file);
	ch = '0';
	for (i = 0, j = 0, l = 0; str[i] != '0' || ch != ' '; i++){//i控制当前子句字符位置,j控制当前行位置，l判断是否为第一行,此for循环创建第一个子句
		if (str[i] != ' ')
			stemp[j++] = str[i];
		else{
			stemp[j] = '\0';
			if (l == 0){
				temp1 = (Node1*)malloc(sizeof(Node1));
				temp2->pL = temp1;
				temp1->Elem = atoi(stemp);
				l++, j = 0;
			}
			else{
				temp1->next1 = (Node1*)malloc(sizeof(Node1));
				temp1 = temp1->next1;
				temp1->Elem = atoi(stemp);
				j = 0;
			}
		}
		ch = str[i];
	}
	temp1->next1 = NULL;//将最后一行的指针链向空
	for (k = 1; k < head->NumOfClause; k++){//k控制子句数目
		temp2->next2 = (Node2*)malloc(sizeof(Node2));
		temp2 = temp2->next2;
		fgets(str, LENGTH, file);//读当前子句字符串
		ch = '0';//置前一个字符为‘0’
		for (i = 0, j = 0, l = 0; str[i] != '0' || ch != ' '; i++){//i控制当前子句字符位置,j控制当前行位置，l判断是否为第一行,此for循环创建第一个子句
			if (str[i] != ' ')
				stemp[j++] = str[i];
			else{
				stemp[j] = '\0';
				if (l == 0){
					temp1 = (Node1*)malloc(sizeof(Node1));
					temp2->pL = temp1;
					temp1->Elem = atoi(stemp);
					l++, j = 0;
				}
				else{
					temp1->next1 = (Node1*)malloc(sizeof(Node1));
					temp1 = temp1->next1;
					temp1->Elem = atoi(stemp);
					j = 0;
				}
			}
			ch = str[i];
		}
		temp1->next1 = NULL;//将最后一行的指针链向空
	}
	temp2->next2 = NULL;//将最后一个子句的指针链向空
	fclose(file);
	return 0;
}
int DPLL1(root *head){
	int e;
	root *p;
	while (IsUnitClause(*head, &e) != 0){
		RemoveClause(head, e);
	if(e>0)
		*(f+e-1)=TRUE;
	else
		*(f-e-1)=FALSE;//文件输出所用
		if (IsEmptyClause(head) == 0)
			return FALSE;
		if (IsOver(head) == 1)
			return TRUE;
	}
	if (e = DPLL1(p = AddClause(head, head->p->pL->Elem))){
		DestroyHead(p);
		return TRUE;
	}
	if (e == 0)
		DestroyHead(p);
	e = DPLL1(p = AddClause(head, -head->p->pL->Elem));
	DestroyHead(p);
	return e;
}
int DPLL2(root *head){
	int e;
	int ifmin=99;
	int min;
	Node1 *m;
	Node2 *n;
		root *p;
	while (IsUnitClause(*head, &e) != 0){
		RemoveClause(head, e);
	if(e>0)
		*(f+e-1)=TRUE;
	else
		*(f-e-1)=FALSE;//文件输出所用
		if (IsEmptyClause(head) == 0)
			return FALSE;
		if (IsOver(head) == 1)
			return TRUE;
	}
	for (n=head->p; n != NULL;n=n->next2){//控制子句循环
		min=0;
			for (m = n->pL; m != NULL;m=m->next1){//循环子句中的每一个文字
				min=m->Elem;
				}
			if (min<ifmin){
				ifmin=min;
				tmin=n->pL->Elem;
			}
			}
	if (e = DPLL2(p = AddClause(head,tmin))){
		DestroyHead(p);
		return TRUE;
	}
	if (e == 0)
		DestroyHead(p);
	e = DPLL2(p = AddClause(head, -tmin));
	DestroyHead(p);
	return e;
}
int sudos(int x,int y,int d){
    return ((x-1)*9 +y-1)*9 +d;
}
int transudo(char filename[]){
    int clause = 0;
    clause += 81+324*27;
    FILE *fp_out;
    fp_out = fopen("sudoku.cnf","w");
    fprintf(fp_out,"p cnf 729 %d\n",clause);
    
    for(int i =1;i <=9; i++){
        for(int j = 1; j<=9;j++)
            if(sudo[(i-1)*9 +j-1] == 0){
                for(int d = 1;d <= 9;d++)
                    fprintf(fp_out,"%d ",sudos(i,j,d));
                fprintf(fp_out,"0\n");
                for(int d =1;d <=9;d++)
                    for(int l = d+1;l <=9;l++)
                        fprintf(fp_out,"%d %d 0\n",-1*sudos(i,j,d),-1*sudos(i,j,l));
            }
            else{
                for(int d = 1;d <= 9;d++)
                    if(sudo[(i-1)*9 +j-1] != d)
                        fprintf(fp_out, "%d 0\n",-1*sudos(i,j,d));
                    else
                        fprintf(fp_out, "%d 0\n",sudos(i,j,d));      
            }
            
    }//行列不同

    for(int i = 1;i <=9; i++){
        for(int j = 1;j <= 9; j++)
            for(int k = j+1; k<=9; k++)
                for(int d =1; d<=9; d++)
                    fprintf(fp_out,"%d %d 0\n",-1*sudos(i,j,d), -1*sudos(i,k,d));
    }//每点至少一个

    for(int i = 1;i <=9; i++){
        for(int j = 1;j <= 9; j++)
            for(int k = j+1; k<=9; k++)
                for(int d =1; d<=9; d++)
                    fprintf(fp_out,"%d %d 0\n",-1*sudos(j,i,d), -1*sudos(k,i,d));
    }//每点至多一个
	//以下为九宫格不同
    for(int i = 1;i <= 3;i++){
        for(int j = 1;j <=3;j++)
            for(int k =1;k <= 3;k++)
                for(int l = 1;l <=3;l++){
                    if((i-1)*3 +j >= (k-1)*3 +l )
                        continue;
                    for(int d= 1; d<= 9;d++)
                        fprintf(fp_out,"%d %d 0\n",-1*sudos(i,j,d), -1*sudos(k,l,d));
                
                }
    }

    for(int i = 1;i <= 3;i++){
        for(int j = 4;j <=6;j++)
            for(int k =1;k <= 3;k++)
                for(int l = 4;l <=6;l++){
                    if((i-1)*3 +j >= (k-1)*3 +l )
                        continue;
                    for(int d= 1; d<= 9;d++)
                        fprintf(fp_out,"%d %d 0\n",-1*sudos(i,j,d), -1*sudos(k,l,d));
                
                }
    }

    for(int i = 1;i <= 3;i++){
        for(int j = 7;j <=9;j++)
            for(int k =1;k <= 3;k++)
                for(int l = 7;l <=9;l++){
                    if((i-1)*3 +j >= (k-1)*3 +l )
                        continue;
                    for(int d= 1; d<= 9;d++)
                        fprintf(fp_out,"%d %d 0\n",-1*sudos(i,j,d), -1*sudos(k,l,d));
                
                }
    }



    for(int i = 4;i <= 6;i++){
        for(int j = 1;j <=3;j++)
            for(int k =4;k <= 6;k++)
                for(int l = 1;l <=3;l++){
                    if((i-1)*3 +j >= (k-1)*3 +l )
                        continue;
                    for(int d= 1; d<= 9;d++)
                        fprintf(fp_out,"%d %d 0\n",-1*sudos(i,j,d), -1*sudos(k,l,d));
                
                }
    }

    for(int i = 4;i <= 6;i++){
        for(int j = 4;j <=6;j++)
            for(int k =4;k <= 6;k++)
                for(int l = 4;l <=6;l++){
                    if((i-1)*3 +j >= (k-1)*3 +l )
                        continue;
                    for(int d= 1; d<= 9;d++)
                        fprintf(fp_out,"%d %d 0\n",-1*sudos(i,j,d), -1*sudos(k,l,d));
                
                }
    }

    for(int i = 4;i <= 6;i++){
        for(int j = 7;j <=9;j++)
            for(int k =4;k <= 6;k++)
                for(int l = 7;l <=9;l++){
                    if((i-1)*3 +j >= (k-1)*3 +l )
                        continue;
                    for(int d= 1; d<= 9;d++)
                        fprintf(fp_out,"%d %d 0\n",-1*sudos(i,j,d), -1*sudos(k,l,d));
                
                }
    }

    
    for(int i = 7;i <= 9;i++){
        for(int j = 1;j <=3;j++)
            for(int k =7;k <= 9;k++)
                for(int l = 1;l <=3;l++){
                    if((i-1)*3 +j >= (k-1)*3 +l )
                        continue;
                    for(int d= 1; d<= 9;d++)
                        fprintf(fp_out,"%d %d 0\n",-1*sudos(i,j,d), -1*sudos(k,l,d));
                
                }
    }

    for(int i = 7;i <= 9;i++){
        for(int j = 4;j <=6;j++)
            for(int k =7;k <= 9;k++)
                for(int l = 4;l <=6;l++){
                    if((i-1)*3 +j >= (k-1)*3 +l )
                        continue;
                    for(int d= 1; d<= 9;d++)
                        fprintf(fp_out,"%d %d 0\n",-1*sudos(i,j,d), -1*sudos(k,l,d));
                
                }
    }

    for(int i = 7;i <= 9;i++){
        for(int j = 7;j <=9;j++)
            for(int k =7;k <= 9;k++)
                for(int l = 7;l <=9;l++){
                    if((i-1)*3 +j >= (k-1)*3 +l )
                        continue;
                    for(int d= 1; d<= 9;d++)
                        fprintf(fp_out,"%d %d 0\n",-1*sudos(i,j,d), -1*sudos(k,l,d));
                
                }
    }
    fclose(fp_out);
	return 0;
}