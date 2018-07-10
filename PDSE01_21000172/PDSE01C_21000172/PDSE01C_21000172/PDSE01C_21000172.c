/*************************************************************************
과목명 :	프로그래밍 실습 (월,목 3교시) 
				
				학부_전산전자공학부
				학번_ 21000172
				이름_ 김주은

실습 내용(01C) : 배열 memory[MEMORY_SIZE]에 2개의 스택을 나타내고자 한다.
				스택 i(0<=i<=n)에서 원소를 삽입하고 삭제하는 함수

조건				1)배열의 왼쪽 끝과 오른쪽 끝을 각각의 스택의 bottom으로 정의한다.
				2)적절히 push와 pop을 통한 테스트를 수행한다.

작성일:2012.09.01
***********************************************************************/
#include<stdio.h>
#include<stdlib.h>
#define MEMORY_SIZE 10
static int stack[MEMORY_SIZE];
int leftTop=0, rightTop=MEMORY_SIZE-1;

//push함수, 즉 삽입 함수에 해당한다. 
//첫번째 인자는 왼쪽,오른쪽 스택의 구별값으로 하며, 두번째 인자는 push할 실값을 의미한다.
void push(int i,int item){

 if(leftTop==rightTop){
	printf("Stack is Full\n");
	exit(1);
	}
 //push함수의 첫번째 인자값이 1일경우, 왼쪽 스택을 기준으로 값을 증가시킨다.
 if(i==1)
  stack[leftTop++]=item;

 //push 함수의 첫번째 인자값이 1이 아닐경우,
 else
  stack[rightTop--]=item;
}

//pop함수, 즉 삭제함수에 해당한다.
int pop(int item){
	
	//pop함수의 첫번째 인자가 1일경우,배열의 왼쪽을 스택 기준으로 한다.
	if(item==1){
		if(leftTop<=0){
			printf("stack is empty\n");
			exit(1);
			}
	return stack[--leftTop];
		}
	//pop함수의 첫번째 인자가 1이 아닐경우, 배열의 오른쪽을 스택기준으로 한다.
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

	printf("pop한 결과값을 출력합니다 \n");
	printf("%d %d %d %d\n",a,b,c,d);
}