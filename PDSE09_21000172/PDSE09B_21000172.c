/*
 ����: PDSE09B 
 Write an algorithm that finds the sum of the degrees for a node,
using the adjacency list representation.

�̸� : ������
�й� : 210000172
�˰��� : inputdata���Ϸ� ���� ���� �о�鿩 adjacency list �Լ��� �����Ѵ�.
		travesal�ϸ鼭 �� ����� ���� ī��Ʈ�Ͽ� sum���� Result.txt�� ����Ѵ�.
		(�湮�� ����� ������ ���� �� ������ ������ �̿��Ͽ���.)
�ۼ��� : 2012. 11.26
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 15
FILE *f1,*f2;	
typedef struct GraphNode{ 
   int vertex;
   struct GraphNode *link;
} GraphNode;

typedef struct GraphType {
	int n;	// ������ ����
	GraphNode *adj_list[MAX_VERTICES];
} GraphType;
int visited[MAX_VERTICES];

// �׷��� �ʱ�ȭ 
void graph_init(GraphType *g)
{	int v;
	g->n=0;
	for(v=0;v<MAX_VERTICES;v++)
		g->adj_list[v]=NULL;
}
// ��������Ʈ�� ǥ���� �׷����� ���̿켱Ž��
int graph_dfs_list(GraphType *g, int v)   
{	
	static int cnt;
	int x;
    GraphNode *w; 
    visited[v] = 1;							// ��� v�� �湮������ üũ 
    fprintf(f2,"�湮��� :[%d] \n ", v);			// �湮�� ��� ��� 
    for(w=g->adj_list[v]; w; w=w->link){
      if(!visited[w->vertex])     
		graph_dfs_list(g,w->vertex);
  
   }
  
	cnt++;			//�湮�� ����� ī��Ʈ ���� �� �� ����� �հ� ����. 
  
	return cnt;		//�� ���� ���� return������ �Ѱ��ش�.
}
// ���� ���� ����
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
		int u;
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
	
	 u=graph_dfs_list(&g,0);						//�� ���� ���� ��ȯ�Ͽ� ���� u�� �־��ش�.
		
	 fprintf(f2,"�� ���� ���� : %d ��",u);			//���� u�� ����Ǿ��ִ� �� ���� ���� ����Ѵ�.

		fclose(f1);
		fclose(f2);

	system("PAUSE");
	return(0);

}