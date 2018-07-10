/*************************************************************************
과목명 :	프로그래밍 실습 (월,목 3교시) 
				
				학부_전산전자공학부
				학번_ 21000172
				이름_ 김주은


실습 내용(02A) : 주어진 일련의 양의 정수를 입력순서를 출력하는 
				 프로그램을 큐를 통하여 구현하라.

조건				1)Queue을 array로 구현
				2)입력데이터를 파일로 입력하라(inputdata.txt)
				3)결과를 출력파일로 출력한다(Result.txt)

작성일 : 2012.09.10(월요일)

알고리즘 : queue배열에 1 3 5 7 값을 넣는다.다음 inputdata.txt로 부터 읽어들여온 값을
 while문을 사용하여 queue2에 넣고 , 그 queue2의 값을 queue에 add한다.
 결과값을 dequeue하여 result.txt에 출력한다.

***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 100
int queue[MAX_QUEUE_SIZE];
int queue2[MAX_QUEUE_SIZE];
int front, rear;

void creat();		//큐를 생성
int is_empty();		//큐가 비어있는지 검사
int is_full();		//큐가 가득차 있는지 검사
void enqueue(int );		//큐의 뒤에 요소를 추가
int dequeue();		//큐의 앞에 있는 요소를 반환한 다음 삭제
void f1_open();		//inputdata.txt 파일 열기 함수
void f2_open();		//Result.txt 파일 열기함수

FILE *f1=NULL;
FILE *f2=NULL;

void main(){
	
	int i=0;
	int x,y=0;
	int temp;

	f1_open();		
	f2_open();

	//비교할 값을 addq한다.
	enqueue(1);
	enqueue(3);
	enqueue(5);
	enqueue(7);

	//f1의 파일이 끝날때 까지
	while(!feof(f1)){

		//파일포인터 f1이 가리키는 inputdata로 부터 값을 읽어들인다.
		fscanf(f1,"%d ,",&temp);
		
		enqueue(temp);			//queue에 queue2의 값을 더한다.
		
	}

		while(!is_empty()){

			y=dequeue();
			fprintf(f2,"%d ",y);		//queue2가 더해진 queue를 출력한다.
		}

		fclose(f1);
		fclose(f2);
}
void f1_open(){
	
	f1=fopen("inputdata.txt","r");
	if(f1==NULL)
		printf("파일을 열 수 없습니다.");

}
void f2_open(){
	
	f2=fopen("Result.txt","w");

	if(f2==NULL)
		printf("파일을 열 수 없습니다.");

}
int dequeue(){

	if(is_empty()){
		printf("queue is empty !\n");
	
	}
	front = (front +1)%MAX_QUEUE_SIZE;
		return queue[front];
}
// 포화 상태 검출 함수
int is_full(){
	return ((rear+1)%MAX_QUEUE_SIZE == front);
}
// 삽입 함수
void enqueue(int x){
	if(is_full()){
		printf("queue is full!\n");
	}
	rear = (rear+1)%MAX_QUEUE_SIZE;
	queue[rear]=x;
}

//공백상태 검출함수
int is_empty(){
	return (front == rear);

}