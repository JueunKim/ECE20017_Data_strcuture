/*************************************************************************
����� :	���α׷��� �ǽ� (��,�� 3����) 
				
				�к�_�������ڰ��к�
				�й�_ 21000172
				�̸�_ ������

�ǽ� ����(01C) : �迭 memory[MEMORY_SIZE]�� 2���� ������ ��Ÿ������ �Ѵ�.
				���� i(0<=i<=n)���� ���Ҹ� �����ϰ� �����ϴ� �Լ�

����				1)�迭�� ���� ���� ������ ���� ������ ������ bottom���� �����Ѵ�.
				2)������ push�� pop�� ���� �׽�Ʈ�� �����Ѵ�.

�ۼ���:2012.09.01
***********************************************************************/
#include<stdio.h>
#include<stdlib.h>
#define MEMORY_SIZE 10
static int stack[MEMORY_SIZE];
int leftTop=0, rightTop=MEMORY_SIZE-1;

//push�Լ�, �� ���� �Լ��� �ش��Ѵ�. 
//ù��° ���ڴ� ����,������ ������ ���������� �ϸ�, �ι�° ���ڴ� push�� �ǰ��� �ǹ��Ѵ�.
void push(int i,int item){

 if(leftTop==rightTop){
	printf("Stack is Full\n");
	exit(1);
	}
 //push�Լ��� ù��° ���ڰ��� 1�ϰ��, ���� ������ �������� ���� ������Ų��.
 if(i==1)
  stack[leftTop++]=item;

 //push �Լ��� ù��° ���ڰ��� 1�� �ƴҰ��,
 else
  stack[rightTop--]=item;
}

//pop�Լ�, �� �����Լ��� �ش��Ѵ�.
int pop(int item){
	
	//pop�Լ��� ù��° ���ڰ� 1�ϰ��,�迭�� ������ ���� �������� �Ѵ�.
	if(item==1){
		if(leftTop<=0){
			printf("stack is empty\n");
			exit(1);
			}
	return stack[--leftTop];
		}
	//pop�Լ��� ù��° ���ڰ� 1�� �ƴҰ��, �迭�� �������� ���ñ������� �Ѵ�.
	else{
		if(rightTop>=MEMORY_SIZE-1){
		printf("stack is empty\n");
		exit(1);
		}
	return stack[++rightTop];
	 }
}
void main(void){ 
	
	int a,b,c,d,e=0;

	push(1,5);
	push(1,7);
	push(2,3);
	push(2,5);
	
	a=pop(1),b=pop(1),c=pop(2),d=pop(2);

	printf("pop�� ������� ����մϴ� \n");
	printf("%d %d %d %d\n",a,b,c,d);
}