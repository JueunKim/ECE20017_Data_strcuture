/***********************************************
	과제 :	PDSE05B
	이름 :	김주은
	학번 :  21000172
	학부 :  전산전자 공학부

	문제 : 배열을 활용한 이진트리로 전화번호부구현(입력,출력,삭제,검색)
	구현내용 : inputdata로 부터 파일을 읽어온 후, 배열에 값을 저장하여
		이진 트리를 구현한다. 메인함수에서 구현된 메뉴를 통해 각 기능을 
		수행한다. 이름이 이진트리로 정렬되어 종료 후 값이 출력파일에 저장된다.
		
	만든날짜 : 2012. 10. 23
***********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 30

typedef struct element{
	char name[20];
	char phone[20];
}element;

element node[MAX_SIZE];

void search(int i, char *);
void insert_node();		//노드 삽입
void delete_node();		//노드 삭제
void display(int i);			//전화번호부 출력 
void f_write(int i);			//Result 파일에 결과값 출력
void f1_open();			//입력 파일 open 
void f2_open();			//출력 파일 open
void menu();			//메뉴출력

FILE *f1;
FILE *f2;

//inputdata 파일 오픈
void f1_open(){
	
	int i=0;
	f1=fopen("inputdata.txt","r");
		if(f1==NULL){
			printf("파일을 열수없습니다\n.");
			return ;
		}
		while(!feof(f1)){
		fscanf(f1,"%s %s ",&node[i].name,&node[i].phone);
		i++;
			}
}
//Result.txt 파일 오픈
void f2_open(){
	
	f2=fopen("Result.txt","w");
	
	if(f2==NULL){
		printf("파일을 열 수 없습니다.");
		return ;
	}	
}
//전화번호부 출력
void display(int i){

	if( node[i].name == 0 ){
		return;}
	
		display(2*i);				//왼쪽노드 방문
		printf("%s , %s \n",node[i].name,node[i].phone);
		display((2*i)+1);			//오른쪽 노드 방문
		
}
void search(int i,char *s){
	
	
	if( node[i].name == 0 ){
		return;}

		display(2*i);				//왼쪽노드 방문
		printf("%s , %s \n",node[i].name,node[i].phone);
		display((2*i)+1);			//오른쪽 노드 방문

}
void delete_node(){

}
void insert_node(){

}
void f_write(int index){
	
	if( node[index].name == 0 ){
		return;
		}
		f_write(2*index);				// 좌측 서브 트리 검사
		fprintf(f2,"%s %s", node[index].name, node[index].phone); // 노드 방문
		f_write((2*index)+1);			// 우측 서브 트리 검사
}
void menu(){
	printf("===========menu=============\n");
	printf("1. 검색 \n");
	printf("2. 입력 \n");
	printf("3. 삭제 \n");
	printf("4. 출력\n");
	printf("5. 종료 \n");
}
void main(){


	int num=0;
	char searched[30];

    f1_open();
    f2_open();
	while(1){
		menu();
		fflush(stdin);
		scanf("%d",&num);
	switch(num){
	case 1 : printf("찾는사람\n");
			gets(searched);
			search(1,searched);
			break;
	case 2 : printf("추가할사람\n");
			gets(searched);
			printf("번호 \n");
			gets(searched);
			insert_node();
			break;
	case 3 : printf("삭제할사람 \n");
			gets(searched);
			delete_node();
			break;
	case 4 : display(1);
			printf("\n");
			break;
	case 5 : printf("프로그램을 종료합니다. \n");
		//	f_write(1);
			return ;
		}
	}
	fclose(f1);
	fclose(f2);
}
