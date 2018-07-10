/*************************************************************************
과목명 :	프로그래밍 실습 (월,목 3교시) 
				
				학부_전산전자공학부
				학번_ 21000172
				이름_ 김주은


실습 내용(01A) : 주어진 일련의 양의 정수를 입력순서의 거꾸로 출력하는 
				 프로그램을 스택을 통하여 구현하라.

조건				1)stack을 array로 구현
				2)입력데이터를 파일로 입력하라(inputdata.txt)
				3)결과를 출력파일로 출력한다(Result.txt)

작성일 : 2012.09.01(토요일)
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

	//변수 선언 및 값을 초기화한다.
	int i = 0;
	int x,y = 0;
	FILE *f1 = NULL;	
	FILE *f2 = NULL;

	//데이터를 불러올 inputdata파일 읽기 모드로 연다.
	f1=fopen ("inputdata.txt","r");

	//결과값을 저장할 Result파일을 쓰기모드로 연다.
	f2=fopen("Result.txt","w");

	
	if(f1==NULL)
		printf("파일을 열 수 없습니다.");

	//f1의 파일이 끝날때 까지
	while(!feof(f1)){

		//파일포인터 f1이 가리키는 inputdata로 부터 값을 읽어들인다.
		fscanf(f1,"%d",&stack[i]);

		// stack[i]의 값을 변수x에 넣은 후 push 한다.
		x=stack[i]; 
		push(x);
		i++;
	
	}
	//empty될때까지 while문을돌려 값을 f2의 파일에 값을 출력한다.
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