/*
 ����: PDSE09C 
 
 -->Depth-first Traversal, use a stack to traverse the graph.
	Rewrite the algorithm to use recursion,( ��Ʈ. you need two algorithms, 
	one to interface with the using algorithm and one for the recursion. )

	�̸� : ������
	�й� : 210000172	

	�˰��� : Depth_first Traversal�� stack�� ����Ͽ� �׷����� Ž���Ѵ�.
		  �湮�� ���� push�Ͽ� ���� �����ϰ�, ���� ȭ�鿡�� pop�Ͽ� ���� Ȯ���Ѵ�.

�ۼ��� : 2012.11.26
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 10
#define MAX_STACK_SIZE 100

typedef struct GraphNode
{  
   int vertex;
   struct GraphNode *link;
} GraphNode;

int visited[MAX_VERTICES];

typedef struct GraphType {
	int n;	// ������ ����
	GraphNode *adj_list[MAX_VERTICES];
} GraphType;
//==========stack ADT======================
void push(int x);
int pop();
int isEmpty();
int isFull();

int top = -1;
int stack[MAX_STACK_SIZE];
//===========================================
FILE *f1,*f2;

void push(int x){

	if(top>=MAX_STACK_SIZE-1){
		printf("stack is full \n");
		return;
	}

	stack[++top] = x;
}
int pop(){
	
	if(top == -1)
		printf("stack is empty \n");


	return stack[(top)--];

}
int IsEmpty(){

	if(top==-1)
		return (1);
	else 
		return (0);

}
int IsFull(){

	if(top>=MAX_STACK_SIZE -1)
		return (1);
	else
		return (0);

}
// �׷��� �ʱ�ȭ 
void graph_init(GraphType *g)
{
	int v;
	g->n=0;
	for(v=0;v<MAX_VERTICES;v++)
		g->adj_list[v]=NULL;
}
// ��������Ʈ�� ǥ���� �׷����� ���̿켱Ž��
void graph_dfs_list(GraphType *g, int v)   
{
   		int x;
    GraphNode *w; 
    visited[v] = 1;							// ��� v�� �湮������ üũ 
    fprintf(f2,"�湮��� :[%d] \n ", v);		// �湮�� ��� ��� 
	push(v);								// �湮�� ��尪�� push�Ѵ�
  
	for(w=g->adj_list[v]; w; w=w->link){
      if(!visited[w->vertex])     
		graph_dfs_list(g,w->vertex);
  
   }
}

void insert_vertex(GraphType *g, int v)
{
	if( ((g->n)+1) > MAX_VERTICES ){ 
		fprintf(stderr, "�׷���: ������ ���� �ʰ�");
		return;
	}
	g->n++;
}
// ���� ���� ����, v�� u�� ���� ����Ʈ�� �����Ѵ�.
void insert_edge(GraphType *g, int u, int v)
{
	GraphNode *node;
	if( u >= g->n || v >= g->n ){
		fprintf(stderr, "�׷���: ���� ��ȣ ����");		
		return;
	}
	node = (GraphNode *)malloc(sizeof(GraphNode));
	node->vertex = v;
	node->link = g->adj_list[u];
	g->adj_list[u] = node;
}

int main()
{
	    int i;
		int a,b;
		GraphType g;
		graph_init(&g);
		
		
		//inputdata ���� ����
		f1=fopen("inputdata.txt","r");
		if(f1 == NULL){
			printf("������ ���������ϴ�.");
			return;
		}
		//result ���� ����
		f2=fopen("Result.txt","w");
		if(f2==NULL){
			printf("������ �� �������ϴ�.");
				return;}

			for(i=0;i<MAX_VERTICES;i++)
					insert_vertex(&g, i);

		fprintf(f2,"inputdata ��  : \n");

		while(!feof(f1)){
			fscanf(f1,"%d %d \n",&a,&b);		//inputdata�� ���� ���� �о�� ���� a,b�� �����Ѵ�.
			fprintf(f2,"%d %d\n",a,b); 
			insert_edge(&g,a,b);				//�� ���� ���� ������ �߰������ش�.
			}
	
		
		fprintf(f2,"\n");
		fprintf(f2,"\n");
	
		graph_dfs_list(&g,0);

		fprintf(f2,"\n");
		fprintf(f2,"pop�� ����� : ");

		while (!IsEmpty()){						//isEmpty�϶����� push�� ���� pop�Ͽ� �ش�.
			fprintf(f2,"%d  ",pop());
		}
	
		fclose(f1);
		fclose(f2);

	system("PAUSE");
	return(0);
}
