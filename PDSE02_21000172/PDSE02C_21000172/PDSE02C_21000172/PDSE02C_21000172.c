/*************************************************************************
����� :	���α׷��� �ǽ� (��,�� 3����) 
				
				�к�_�������ڰ��к�
				�й�_ 21000172
				�̸�_ ������


�ǽ� ����(02B) : ����� ť ���� front, rear ����,�����Լ��� �����Ѵ�.

����				1)���� array�� ����
				2)�Էµ����͸� ���Ϸ� �Է��϶�(inputdata.txt)
				3)����� ������Ϸ� ����Ѵ�(Result.txt)

�ۼ��� : 2012.09.10(������)

�˰��� : inputdata���Ϸ� ���� ���� �о���� ������ ���� ť�� add_rear�Լ��� ����Ͽ� 
			���� �Է��Ѵ�. delete_rear�Լ��� ����Ͽ� ���� result���Ͽ� ����Ѵ�.
			add_rear�� delete_rear�Լ��� ����Ͽ� ���ð� ���� ����� �ϵ��� �����Ͽ���.
���� ��â�� ����
***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>�� 
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

	f1_open();			//inputdata.txt ������ ����.
	f2_open();			//Resutlt.txt ������ ����.

	while(!feof(f1)){
		//���������� f1�� ����Ű�� inputdata�� ���� ���� �о���δ�.
		fscanf(f1,"%d ,",&temp);
		add_rear(temp);				
	}


	while(!isEmpty()){
			y=delete_rear();		��
			fprintf(f2,"%d ",y);		
		}

		fclose(f1);
		fclose(f2);

	
}
void f1_open(){
	
	f1=fopen("inputdata.txt","r");
	if(f1==NULL)
		printf("������ �� �� �����ϴ�.");

}
void f2_open(){
	
	f2=fopen("Result.txt","w");

	if(f2==NULL)
		printf("������ �� �� �����ϴ�.");

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

