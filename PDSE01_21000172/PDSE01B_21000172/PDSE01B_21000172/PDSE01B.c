/*************************************************************************
과목명 :	프로그래밍 실습 (월,목 3교시) 
				
				학부_전산전자공학부
				학번_ 21000172
				이름_ 김주은


실습 내용(01B) : palindrome(회문)
				
조건				1)stack을 linked list로 구현한다.
				2)입력데이터를 파일로 입력하라(inputdata.txt)
				3)결과를 출력파일로 출력한다(Result.txt)

작성일:2012.09.01
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

	//값을 읽어들일 inputdata파일을 연다.
	f1=fopen("inputdata.txt","r");

	//결과값을 저장할 Result파일을 연다.
	f2=fopen("Result.txt","w");

	if(f1==NULL){
		printf("파일을 찾을 수 없습니다.");
	}
	if(f2==NULL){
		printf("파일을 찾을 수 없습니다.");
	}	

	//파일포인터 f1이 가리키는 inputdata로 부터 문자열 값을 읽어들여 stack에 저장한다.
	fgets(stack,100,f1);

	//문자열의 끝('\0')에 도달할 때까지 값을 읽어들여 int형으로 변환 후 push한다.
	while(stack[i]!='\0'){
		x=(int)stack[i];
		push(x);
		i++;
	}

	while(!isEmpty()){
		
		//값을 pop하여 파일포인터 f2가 가리키는 Result파일에 출력한다.
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
