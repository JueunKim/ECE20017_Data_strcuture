/*
 과제: PDSE09C 
 
 -->Depth-first Traversal, use a stack to traverse the graph.
	Rewrite the algorithm to use recursion,( 힌트. you need two algorithms, 
	one to interface with the using algorithm and one for the recursion. )

	이름 : 김주은
	학번 : 210000172	

	알고리즘 : Depth_first Traversal을 stack을 사용하여 그래프를 탐색한다.
		  방문한 노드는 push하여 값을 저장하고, 메인 화면에서 pop하여 값을 확인한다.

작성일 : 2012.11.26
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
	int n;	// 정점의 개수
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
// 그래프 초기화 
void graph_init(GraphType *g)
{
	int v;
	g->n=0;
	for(v=0;v<MAX_VERTICES;v++)
		g->adj_list[v]=NULL;
}
// 인접리스트로 표현된 그래프의 깊이우선탐색
void graph_dfs_list(GraphType *g, int v)   
{
   		int x;
    GraphNode *w; 
    visited[v] = 1;							// 노드 v를 방문했음을 체크 
    fprintf(f2,"방문노드 :[%d] \n ", v);		// 방문한 노드 출력 
	push(v);								// 방문한 노드값을 push한다
  
	for(w=g->adj_list[v]; w; w=w->link){
      if(!visited[w->vertex])     
		graph_dfs_list(g,w->vertex);
  
   }
}

void insert_vertex(GraphType *g, int v)
{
	if( ((g->n)+1) > MAX_VERTICES ){ 
		fprintf(stderr, "그래프: 정점의 개수 초과");
		return;
	}
	g->n++;
}
// 간선 삽입 연산, v를 u의 인접 리스트에 삽입한다.
void insert_edge(GraphType *g, int u, int v)
{
	GraphNode *node;
	if( u >= g->n || v >= g->n ){
		fprintf(stderr, "그래프: 정점 번호 오류");		
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
		
		
		//inputdata 파일 오픈
		f1=fopen("inputdata.txt","r");
		if(f1 == NULL){
			printf("파일을 열수없습니다.");
			return;
		}
		//result 파일 오픈
		f2=fopen("Result.txt","w");
		if(f2==NULL){
			printf("파일을 열 수없습니다.");
				return;}

			for(i=0;i<MAX_VERTICES;i++)
					insert_vertex(&g, i);

		fprintf(f2,"inputdata 값  : \n");

		while(!feof(f1)){
			fscanf(f1,"%d %d \n",&a,&b);		//inputdata로 부터 값을 읽어와 변수 a,b에 저장한다.
			fprintf(f2,"%d %d\n",a,b); 
			insert_edge(&g,a,b);				//두 개의 값을 간선에 추가시켜준다.
			}
	
		
		fprintf(f2,"\n");
		fprintf(f2,"\n");
	
		graph_dfs_list(&g,0);

		fprintf(f2,"\n");
		fprintf(f2,"pop한 결과값 : ");

		while (!IsEmpty()){						//isEmpty일때까지 push한 값을 pop하여 준다.
			fprintf(f2,"%d  ",pop());
		}
	
		fclose(f1);
		fclose(f2);

	system("PAUSE");
	return(0);
}
