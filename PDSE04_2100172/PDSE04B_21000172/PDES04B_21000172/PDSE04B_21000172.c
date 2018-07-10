/******************************************
	PDSE04B 실습
	이름 : 김주은
	학번 : 21000172

	문제 :write a program that determines whether a binary tree is full 
	
	구현내용 : 메인함수에서 inputdata로 부터 파일을 읽어와 binary tree로 만든다.
	inorder 함수와  level수 구하는 함수를 사용하여 ,full binary 이면, Result.txt에 full binary를 출력한다.

	작성일 : 2012.10.9

********************************************/

#include <stdio.h>
#include <math.h>

#define MAX_SIZE 1000
char tree_array[MAX_SIZE];
int cnt=0;
int i=0;
int count=0;
int height=0;
int node=0;
FILE *f1;
FILE *f2;
void make_tree();
void inorder();
void postorder();

void main(){

	make_tree();		//이진 트리 형성 함수를 호출한다.
	
	inorder(1);			//inorder 함수를 호출하여 순회하면서, node를 가운트한다.
	postorder(1);		//레벨을 구한다.  
	
	fprintf(f2,"node수 : %d \n",node);
	fprintf(f2,"height 수 : %d \n",height);


	if(node==pow(2.0,height)-1.0)					//노드수 == 2^height이면 full binary이다.
		fprintf(f2,"full binary입니다. \n");
	else fprintf(f2,"full binary가 아닙니다. \n");	//그렇지 않을 경우 다음과 같이 출력한다.
	
	fclose(f1);
	fclose(f2);


}
void make_tree()
{	
	f1=fopen("inputdata.txt","r");		//inputdata.txt를 연다..
	f2=fopen("Result.txt","w");			//결과값을 출력할 파일을 연다.

	//파일이 끝에도달할때까지 배열 tree_array에 저장한다.
	while(!feof(f1)){
		fscanf(f1,"%c ",&tree_array[i]);
		i++;
	}
	
	
}
//탐색 함수,  node를 카운트 한다.
void inorder( int index )
{	
	printf("inorder(%d)\n",index);
	if( tree_array[index] == 0 ){
		node++ ;return;						//노드를 카운트한다.
	}
	inorder( 2*index ); 					// 좌측 서브 트리 검사
	
	printf("<%c>", tree_array[index]);    	// 노드 방문
	inorder( 2*index+1 );					// 우측 서브 트리 검사

}

//level 구하기 
void postorder (int index){	

	height ++;
	if(tree_array[2*index]==0){					//좌측 서브트리를 검사하는데
	  return ;}									//노드가 없을 경우, 카운트 한 후, 리턴한다.
	
	postorder(2*index);

}