/*************************************************************************
����� :	���α׷��� �ǽ� (��,�� 3����) 
				
				�к�_�������ڰ��к�
				�й�_ 21000172
				�̸�_ ������


�ǽ� ����(02A) : �־��� �Ϸ��� ���� ������ �Է¼����� ����ϴ� 
				 ���α׷��� ť�� ���Ͽ� �����϶�.

����				1)Queue�� array�� ����
				2)�Էµ����͸� ���Ϸ� �Է��϶�(inputdata.txt)
				3)����� ������Ϸ� ����Ѵ�(Result.txt)

�ۼ��� : 2012.09.10(������)

�˰��� : queue�迭�� 1 3 5 7 ���� �ִ´�.���� inputdata.txt�� ���� �о�鿩�� ����
 while���� ����Ͽ� queue2�� �ְ� , �� queue2�� ���� queue�� add�Ѵ�.
 ������� dequeue�Ͽ� result.txt�� ����Ѵ�.

***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 100
int queue[MAX_QUEUE_SIZE];
int queue2[MAX_QUEUE_SIZE];
int front, rear;

void creat();		//ť�� ����
int is_empty();		//ť�� ����ִ��� �˻�
int is_full();		//ť�� ������ �ִ��� �˻�
void enqueue(int );		//ť�� �ڿ� ��Ҹ� �߰�
int dequeue();		//ť�� �տ� �ִ� ��Ҹ� ��ȯ�� ���� ����
void f1_open();		//inputdata.txt ���� ���� �Լ�
void f2_open();		//Result.txt ���� �����Լ�

FILE *f1=NULL;
FILE *f2=NULL;

void main(){
	
	int i=0;
	int x,y=0;
	int temp;

	f1_open();		
	f2_open();

	//���� ���� addq�Ѵ�.
	enqueue(1);
	enqueue(3);
	enqueue(5);
	enqueue(7);

	//f1�� ������ ������ ����
	while(!feof(f1)){

		//���������� f1�� ����Ű�� inputdata�� ���� ���� �о���δ�.
		fscanf(f1,"%d ,",&temp);
		
		enqueue(temp);			//queue�� queue2�� ���� ���Ѵ�.
		
	}

		while(!is_empty()){

			y=dequeue();
			fprintf(f2,"%d ",y);		//queue2�� ������ queue�� ����Ѵ�.
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
int dequeue(){

	if(is_empty()){
		printf("queue is empty !\n");
	
	}
	front = (front +1)%MAX_QUEUE_SIZE;
		return queue[front];
}
// ��ȭ ���� ���� �Լ�
int is_full(){
	return ((rear+1)%MAX_QUEUE_SIZE == front);
}
// ���� �Լ�
void enqueue(int x){
	if(is_full()){
		printf("queue is full!\n");
	}
	rear = (rear+1)%MAX_QUEUE_SIZE;
	queue[rear]=x;
}

//������� �����Լ�
int is_empty(){
	return (front == rear);

}