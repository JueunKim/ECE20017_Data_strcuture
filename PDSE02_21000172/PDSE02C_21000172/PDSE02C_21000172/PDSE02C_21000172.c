/*************************************************************************
과목명 :	프로그래밍 실습 (월,목 3교시) 
				
				학부_전산전자공학부
				학번_ 21000172
				이름_ 김주은


실습 내용(02B) : 양방향 큐 원소 front, rear 삽입,삭제함수를 구현한다.

조건				1)덱을 array로 구현
				2)입력데이터를 파일로 입력하라(inputdata.txt)
				3)결과를 출력파일로 출력한다(Result.txt)

작성일 : 2012.09.10(월요일)

알고리즘 : inputdata파일로 부터 값을 읽어들어여와 지정해 놓은 큐에 add_rear함수를 사용하여 
			값을 입력한다. delete_rear함수를 사용하여 값을 result파일에 출력한다.
			add_rear과 delete_rear함수를 사용하여 스택과 같은 기능을 하도록 구현하였다.
메인 독창적 구현
***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>　 
#define MAX_QUEUE_SIZE 100
typedef int QueueObject;
QueueObject  queue[MAX_QUEUE_SIZE]; 
int  front=0; 
int rear =0; 
FILE *f1 =NULL;
FILE *f2 =NULL;
void f1_open();
void f2_open();
int isEmpty();
int isFull();
void add_rear(QueueObject item);
QueueObject delete_rear();
void add_front(QueueObject item);
QueueObject delete_front();

void main()
{
	int i=0;
	int x,y=0;
	int temp;

	f1_open();			//inputdata.txt 파일을 연다.
	f2_open();			//Resutlt.txt 파일을 연다.

	while(!feof(f1)){
		//파일포인터 f1이 가리키는 inputdata로 부터 값을 읽어들인다.
		fscanf(f1,"%d ,",&temp);
		add_rear(temp);				
	}


	while(!isEmpty()){
			y=delete_rear();		뒤
			fprintf(f2,"%d ",y);		
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
int isEmpty(){

	return (front == rear);
}

int isFull()
{

	return (((rear+1)%MAX_QUEUE_SIZE == front) || ((front-1+MAX_QUEUE_SIZE)%MAX_QUEUE_SIZE==rear));
}

void add_rear(QueueObject item)		//add_rear
{ 
  	if( isFull() ) { 
		printf("queue is full\n");
	} 
	rear = (rear+1)%MAX_QUEUE_SIZE;
	queue[rear] = item;
}
void add_front(QueueObject item)		//add_front
{ 
  	if( isFull() ) { 
		printf("queue is full\n");
	} 
	queue[front] = item; 
	front = (front-1+MAX_QUEUE_SIZE)%MAX_QUEUE_SIZE;
	
}

QueueObject delete_front()			//delete_front
{ 
   	if( isEmpty() ) {
		printf("queue is empty\n");
	}
	front = (front+1)%MAX_QUEUE_SIZE;
	return queue[front];
} 
QueueObject delete_rear()			//delete_rear
{ 
	int temp;
   	if( isEmpty() ) {
		printf("queue is empty\n");
	}
	temp= rear;
	rear = (rear-1+MAX_QUEUE_SIZE)%MAX_QUEUE_SIZE;
	return queue[temp];
} 

