/*************************************************
	이름 : 김주은
	학번 : 21000172
	학부 : 전산전자공학부
	작성일 : 2012.9.26

	실습 03C. 
	Create a function that searches for an integer, num, in a circularly linked list. 
	The function should return a pointer to the node that contains num 
	if num is in the list and NULL otherwise. 

참고자료 : datastructure책, 지인
*************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

typedef int element;
typedef struct DlistNode {
	element data;
	struct DlistNode *llink;
	struct DlistNode *rlink;
} DlistNode;

typedef struct List {
	struct DlistNode * first;
	struct DlistNode * last;
	int count;
}List; 

List list;

//리스트 삽입함수
void list_add(int v){		

	//변수선언
	DlistNode *temp;
	temp=(DlistNode*)malloc(sizeof(DlistNode));
	temp->data = v;
	temp->llink =NULL;
	temp->rlink =NULL;
	
	if(list.count > 0)				
	{
		temp->rlink = list.first;
		temp->llink = list.first->llink;
		list.first->llink->rlink = temp;
		list.first->llink = temp;
	}

	else if(list.count == 0)		//리스트가 처음이면
	{
		list.first = temp;
		list.last = temp;

		temp->llink = temp;
		temp->rlink = temp;
	}
	
	list.count++;
}

// 이중 연결 리스트를 초기화
void init(DlistNode *phead) 
{
	phead->llink = phead;
	phead->rlink = phead;
}

void printLink(void)
{
	DlistNode* tmp = list.first;

	for( ;tmp != NULL ;tmp=tmp->rlink)
		printf("%d ",tmp->data);

	printf("\n");
}

DlistNode* searchInt(int num)			//리스트 search함수
{
	DlistNode* tmp;

	//입력받은 값과 리스트의 값이 같으면, 그 값을 반환한다.
	for(tmp = list.first->rlink;tmp!=list.first;tmp=tmp->rlink) {
		if(tmp->data == num)
			return tmp;
	}
}

// 메인함수 구현
void main()
{
	int num;
	DlistNode* result;
	
	// 32 57 88 24순서대로 값을 입력한다.
	list_add(32);
	list_add(57);
	list_add(88);
	list_add(24);


	printf("값을 입력하시요:");
	scanf("%d",&num);

	result = searchInt(num);

	printf("결과는 : %d\n",result->data);


} 