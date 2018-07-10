/*************************************************************************
����� :	���α׷��� �ǽ� (��,�� 3����) 
				
				�к�_�������ڰ��к�
				�й�_ 21000172
				�̸�_ ������


�ǽ� ����(02B) : �־��� �Ϸ��� ���� ������ �Է¼����� ����ϴ� 
				 ���α׷��� ť�� ���Ͽ� �����϶�.

����				1)Queue�� Linked List�� ����
				2)�Էµ����͸� ���Ϸ� �Է��϶�(inputdata.txt)
				3)����� ������Ϸ� ����Ѵ�(Result.txt)

�ۼ��� : 2012.09.10(������)

�˰��� : inputdata���Ϸ� ���� ���� �о���� ������ ���� ť2�� ���� �ִ´�.
		   ������ ť1�� ���� ť2�� ���� ���ϱ� ���� peek�� �Լ��� ����Ͽ� 
		   ��ġ�� ��ȯ�ϰ�, ������ delete�Ǿ� while���� ������ �����Ҷ����� next peek�� �̵��Ѵ�.
		   ������ true�� ����ϰ�, ���� ������ false�� ����Ѵ�. 
		   ť 2���� ����ϱ� ����, ������ ť�� �ʿ��� add�� deleteť�� �����Ͽ���.
��â�� ������.
***********************************************************************/

#include <stdio.h>
#include <malloc.h>�� 

typedef int QueueObject;
typedef struct QueueRec { 
	QueueObject item; 
	struct QueueRec *link; 
} QueueNode;
QueueNode *front, *rear;
QueueNode *front2, *rear2;


void f1_open();
void f2_open(); 
FILE *f1=NULL;
FILE *f2=NULL;
int isEmpty();
int isFull();
void addq(QueueObject item);
void addq2(QueueObject item);
QueueObject deleteq();
QueueObject deleteq2(); 
int rear;
int front;

void main()
{
	int i=0;
	int x,y=0;
	int var;

	f1_open();			//inputdata.txt ������ ����.
	f2_open();			//Resutlt.txt ������ ����.

	addq(3);
	addq(3);
	addq(5);
	addq(7);

	while(!feof(f1)){

		//���������� f1�� ����Ű�� inputdata�� ���� ���� �о�鿩 ������ �����Ѵ�.
		fscanf(f1,"%d",&var);
		addq2(var);
	
	}


	while(1){
	if(peek()==peek2()){					// �� ���� ��ġ�ϸ� peek�� ������ġ�� ��ȯ�ϰ�		 
		deleteq();							//deleteť�Ͽ�  ���� ��ġ�� ���� ���Ѵ�.	
		deleteq2();
	}
	else {									//�� ���� ��ġ���� ������ false�� ���
		fprintf(f2,"%s","false");
		break;
	}

	if(isEmpty()&&isEmpty2()){				
		fprintf(f2,"%s","true\n");
		break;
	}
	
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
int isEmpty()
{
	return (front==NULL);
}

int isEmpty2()
{
	return (front2==NULL);
}
int isFull()
{
 	QueueNode *temp = (QueueNode *)malloc(sizeof(QueueNode)); 
	if(temp == NULL ){
		free(temp);
		return 1;
	}
	else return 0;
}

void addq(QueueObject item)
{ 
 	QueueNode *temp = (QueueNode *)malloc(sizeof(QueueNode)); 
	if(temp == NULL ){
		printf("�޸𸮸� �Ҵ��� �� �����ϴ�.\n");
	}
	else {
		temp->item = item; 
		temp->link = NULL; 
		if( front ) rear->link = temp;	// ť�� ������ 
		else front = temp;				// ť�� �����϶� 
		rear = temp; 
	}
}
void addq2(QueueObject item)
{ 
 	QueueNode *temp = (QueueNode *)malloc(sizeof(QueueNode)); 
	if(temp == NULL ){
		printf("�޸𸮸� �Ҵ��� �� �����ϴ�.\n");
	}
	else {
		temp->item = item; 
		temp->link = NULL; 
		if( front2 ) rear2->link = temp;	// ť�� ������ 
		else front2 = temp;				// ť�� �����϶� 
		rear2 = temp; 
	}
}

QueueObject deleteq() 
{ 
 	QueueNode *temp = front;
 	QueueObject item; 
	if( isEmpty() ){
		printf("ť�� ��� �����ϴ�.\n");
	}
	else {
		item = temp->item; 
		front = front->link; 
		free(temp); 
		return item; 
	}
} 
QueueObject deleteq2() 
{ 
 	QueueNode *temp = front2;
 	QueueObject item; 
	if( isEmpty2() ){
		printf("ť�� ��� �����ϴ�.\n");
	}
	else {
		item = temp->item; 
		front2 = front2->link; 
		free(temp); 
		return item; 
	}
} 

int peek(){

	return front->item;

}
int peek2(){

	return front2->item;
}
