/*************************************************************************
����� :	���α׷��� �ǽ� (��,�� 3����) 
				
				�к�_�������ڰ��к�
				�й�_ 21000172
				�̸�_ ������


�ǽ� ����(01B) : palindrome(ȸ��)
				
����				1)stack�� linked list�� �����Ѵ�.
				2)�Էµ����͸� ���Ϸ� �Է��϶�(inputdata.txt)
				3)����� ������Ϸ� ����Ѵ�(Result.txt)

�ۼ���:2012.09.01
***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#define MAX_STACK_SIZE 100

char stack[MAX_STACK_SIZE];
int stack_empty();
void push(int item);
int pop();

struct StackRec{
	int item;
	struct StackRec *link;
};
struct StackRec *top;

void main(void){

	int i=0;
	int x=0;
	FILE *f1 ;
	FILE *f2 ;

	//���� �о���� inputdata������ ����.
	f1=fopen("inputdata.txt","r");

	//������� ������ Result������ ����.
	f2=fopen("Result.txt","w");

	if(f1==NULL){
		printf("������ ã�� �� �����ϴ�.");
	}
	if(f2==NULL){
		printf("������ ã�� �� �����ϴ�.");
	}	

	//���������� f1�� ����Ű�� inputdata�� ���� ���ڿ� ���� �о�鿩 stack�� �����Ѵ�.
	fgets(stack,100,f1);

	//���ڿ��� ��('\0')�� ������ ������ ���� �о�鿩 int������ ��ȯ �� push�Ѵ�.
	while(stack[i]!='\0'){
		x=(int)stack[i];
		push(x);
		i++;
	}

	while(!isEmpty()){
		
		//���� pop�Ͽ� ���������� f2�� ����Ű�� Result���Ͽ� ����Ѵ�.
		fprintf(f2,"%c",pop());
	}
	
	fclose(f1);
	fclose(f2);
}

void initialize(){
	
	top=NULL;
}

int isEmpty(){
	
	return( top==NULL);
}

int isFull(){

	return 0;
}

void push(int item){

		struct StackRec *temp = (struct StackRec *)malloc(sizeof (struct StackRec));
	
		if(temp == NULL){
		printf("stack is full \n");
	}
	else {
		temp ->item = item;
		temp->link=top;
		top = temp;
	}
}

int pop(){
	if(isEmpty()){
		printf("stack is empty \n");}
	else {
		struct StackRec *temp =top;
		int item = temp ->item;
		top = top->link;
		free(temp);

		return item;
	}
}
