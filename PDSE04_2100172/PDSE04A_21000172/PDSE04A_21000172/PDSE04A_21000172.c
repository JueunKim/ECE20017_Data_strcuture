/*******************************************************
	PESE04A _ 실습프로젝트
	이름 : 김주은
	학번 : 21000172

	문제 :  write a program that counts the number of nodes and leaves in a binary tree 
	구현내용 : main 함수에서 inputdata로 부터 파일을 읽어와 
	이진 트리를 구성한다. 노드 수 구하는 함수와 단말 함수를 이용하여 conut값을
	 구한다. 결과값을 Result.txt에 출력한다. 

참고 : 교수님 ppt
********************************************************/
#include <stdio.h>

#define MAX_SIZE 1000
char tree_array[MAX_SIZE];
int cnt=0;
int i=0;
int count=0;
FILE *f1;
FILE *f2;
void make_tree();
void inorder();
void postorder();

void main(){

	make_tree();		//이진 트리 형성 함수를 호출한다.
	
	inorder(1);
	postorder(1);

	fprintf(f2,"노드 갯수  %d \n",cnt);
	fprintf(f2,"Leaves의 수 : %d \n",count);

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
void inorder( int index )
{	
	printf("inorder(%d)\n",index);
	if( tree_array[index] == 0 ){
		cnt++ ;return; 
	}
	inorder( 2*index ); 					// 좌측 서브 트리 검사
	
	printf("<%c>", tree_array[index]);    	// 노드 방문
	inorder( 2*index+1 );					// 우측 서브 트리 검사

}

//단말노드 구하기
void postorder (int index){	

	
	if(tree_array[2*index]==0){ 
//		if(tree_array[2*index]+1==0){	//양쪽 트리의 자식노드가 없는지 확인, 
			count ++; return ;}
	//}
	
	postorder(2*index);
	postorder(2*index+1);
	
	
}