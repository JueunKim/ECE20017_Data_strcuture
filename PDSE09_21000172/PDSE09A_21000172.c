/*
 과제: PDSE09A 
	write an algorithm that determines whether a node is disjoint.
	->인접한 노드가 있는지 확인하는 문제

이름 : 김주은
학번 : 210000172
알고리즘 : inputdata파일로 부터 값을 읽어와 insert_edge 함수를 호출하여 간선을 추가시켜준다.
			dfs알고리즘을 사용하여 지나온 노드들을 방문하고 인접한 노드를 출력시켜준다.
		 

작성일 : 2012. 11.26
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
	int n;	// 정점의 개수
	GraphNode *adj_list[MAX_VERTICES];
} GraphType;
int visited[MAX_VERTICES];

// 그래프 초기화 
void graph_init(GraphType *g)
{	int v;
	g->n=0;
	for(v=0;v<MAX_VERTICES;v++)
		g->adj_list[v]=NULL;
}
// 인접리스트로 표현된 그래프의 깊이우선탐색
void graph_dfs_list(GraphType *g, int v)   
{	
	int x;
    GraphNode *w; 
    visited[v] = 1;								// 노드 v를 방문했음을 체크 
    fprintf(f2,"인접노드 :[%d] \n ", v);			// 방문한 노드 출력 
    
	for(w=g->adj_list[v]; w; w=w->link){
		if(g->adj_list[v] != NULL){
		//	if(!(g->adj_list[v]->link == w))
		//		printf("[%d]\n", v);
	}
		  if(!visited[w->vertex])
			  graph_dfs_list(g,w->vertex);
	  	 }
}	
// 정점 삽입 연산
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
	//	printf("[%d] [%d] \n",u, v);

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

		fclose(f1);
		fclose(f2);

	system("PAUSE");
	return(0);

}