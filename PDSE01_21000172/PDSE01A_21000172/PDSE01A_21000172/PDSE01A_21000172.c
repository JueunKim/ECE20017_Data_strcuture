/*************************************************************************
����� :	���α׷��� �ǽ� (��,�� 3����) 
				
				�к�_�������ڰ��к�
				�й�_ 21000172
				�̸�_ ������


�ǽ� ����(01A) : �־��� �Ϸ��� ���� ������ �Է¼����� �Ųٷ� ����ϴ� 
				 ���α׷��� ������ ���Ͽ� �����϶�.

����				1)stack�� array�� ����
				2)�Էµ����͸� ���Ϸ� �Է��϶�(inputdata.txt)
				3)����� ������Ϸ� ����Ѵ�(Result.txt)

�ۼ��� : 2012.09.01(�����)
***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100

void push(int item);
int pop();
int IsEmpty();
int IsFull();
FILE *f;

int top = -1;
int stack[MAX_STACK_SIZE] ;

int main(void){

	//���� ���� �� ���� �ʱ�ȭ�Ѵ�.
	int i = 0;
	int x,y = 0;
	FILE *f1 = NULL;	
	FILE *f2 = NULL;

	//�����͸� �ҷ��� inputdata���� �б� ���� ����.
	f1=fopen ("inputdata.txt","r");

	//������� ������ Result������ ������� ����.
	f2=fopen("Result.txt","w");

	
	if(f1==NULL)
		printf("������ �� �� �����ϴ�.");

	//f1�� ������ ������ ����
	while(!feof(f1)){

		//���������� f1�� ����Ű�� inputdata�� ���� ���� �о���δ�.
		fscanf(f1,"%d",&stack[i]);

		// stack[i]�� ���� ����x�� ���� �� push �Ѵ�.
		x=stack[i]; 
		push(x);
		i++;
	
	}
	//empty�ɶ����� while�������� ���� f2�� ���Ͽ� ���� ����Ѵ�.
	while (!IsEmpty()){
		
		y=pop();
		fprintf(f2,"%d ",y);
	}

	fclose(f1);
	fclose(f2);
	return 0;

}


void push(int item){

	if(top>=MAX_STACK_SIZE-1){
		printf("stack is full \n");
		return;
	}

	stack[++top] = item;
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