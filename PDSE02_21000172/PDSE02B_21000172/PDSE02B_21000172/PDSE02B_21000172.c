/*************************************************************************
과목명 :	프로그래밍 실습 (월,목 3교시) 
				
				학부_전산전자공학부
				학번_ 21000172
				이름_ 김주은


실습 내용(02B) : 주어진 일련의 양의 정수를 입력순서를 출력하는 
				 프로그램을 큐를 통하여 구현하라.

조건				1)Queue을 Linked List로 구현
				2)입력데이터를 파일로 입력하라(inputdata.txt)
				3)결과를 출력파일로 출력한다(Result.txt)

작성일 : 2012.09.10(월요일)

알고리즘 : inputdata파일로 부터 값을 읽어들어여와 지정해 놓은 큐2에 값을 넣는다.
		   기존의 큐1의 값과 큐2의 값을 비교하기 위해 peek의 함수를 사용하여 
		   위치를 반환하고, 같으면 delete되어 while문의 조건이 만족할때까지 next peek로 이동한다.
		   같으면 true를 출력하고, 같지 않으면 false를 출력한다. 
		   큐 2개를 사용하기 위해, 각각의 큐에 필요한 add와 delete큐를 생성하였다.
독창적 구현함.
***********************************************************************/

#include <stdio.h>
#include <malloc.h>　 

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

	f1_open();			//inputdata.txt 파일을 연다.
	f2_open();			//Resutlt.txt 파일을 연다.

	addq(3);
	addq(3);
	addq(5);
	addq(7);

	while(!feof(f1)){

		//파일포인터 f1이 가리키는 inputdata로 부터 값을 읽어들여 변수에 저장한다.
		fscanf(f1,"%d",&var);
		addq2(var);
	
	}


	while(1){
	if(peek()==peek2()){					// 두 값이 일치하면 peek이 현재위치를 반환하고		 
		deleteq();							//delete큐하여  다음 위치의 값을 비교한다.	
		deleteq2();
	}
	else {									//두 값이 일치하지 않으면 false를 출력
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
		printf("파일을 열 수 없습니다.");
	
}

void f2_open(){
	
	f2=fopen("Result.txt","w");
	
	if(f2==NULL)
		printf("파일을 열 수 없습니다.");

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
		printf("메모리를 할당할 수 없습니다.\n");
	}
	else {
		temp->item = item; 
		temp->link = NULL; 
		if( front ) rear->link = temp;	// 큐가 있을때 
		else front = temp;				// 큐가 공백일때 
		rear = temp; 
	}
}
void addq2(QueueObject item)
{ 
 	QueueNode *temp = (QueueNode *)malloc(sizeof(QueueNode)); 
	if(temp == NULL ){
		printf("메모리를 할당할 수 없습니다.\n");
	}
	else {
		temp->item = item; 
		temp->link = NULL; 
		if( front2 ) rear2->link = temp;	// 큐가 있을때 
		else front2 = temp;				// 큐가 공백일때 
		rear2 = temp; 
	}
}

QueueObject deleteq() 
{ 
 	QueueNode *temp = front;
 	QueueObject item; 
	if( isEmpty() ){
		printf("큐가 비어 있읍니다.\n");
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
		printf("큐가 비어 있읍니다.\n");
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
