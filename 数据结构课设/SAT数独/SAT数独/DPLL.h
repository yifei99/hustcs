#define TRUE 1
#define FALSE 0
#define DESCRIPTION "p cnf "
#define LENGTH 1000
typedef struct Node1{
	int Elem;
	struct Node1 *next1;
}Node1;//句链表
typedef struct Node2{
	Node1 *pL;
	struct Node2 *next2;
}Node2;//行链表
typedef struct root{
	Node2 *p;
	int NumOfClause;
	int NumOfVari;
}root;//用于操作的根节点
int LoadinFile(char filename[], root *head);
int Destroy(Node2 *p, root *head);
int IsUnitClause(root head, int *Elem);
int RemoveClause(root *head, int Elem);
root* AddClause(root *head, int VariElem);
int IsEmptyClause(root *head);
int IsOver(root *head);
int DestroyHead(root *head);
int DPLL1(root *head);
int DPLL2(root *head);
int transudo(char filename[]);
int sudos(int x,int y,int d);