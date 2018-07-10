/******************************************************************  
	이름 : 김주은
	학번 : 21000172
	
	과제 : PDSE03B
	Write a new ADT algorithm to merge two lists.Use linked list implementation.
	 		
			-입력 데이터를 파일로 입력(inputdata.txt)
			-Doubly Linked List로 구현
			-결과를 출력화일로 출력(Result.txt)
			-두개의 링크드 리스트를 (이미 sorting되어진 상태) Merge하여
			전체 sort된 또 다른 리스트를 만드는 문제

*******************************************************************/

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
};

List list;

void list_add(int v){		

	DlistNode *temp;
	DlistNode *cur;
	temp=(DlistNode*)malloc(sizeof(DlistNode));
	temp->data = v;
	temp->llink =NULL;
	temp->rlink =NULL;
	
	if(list.count != 0)
	{
		if(list.last->data <= v)
		{
			list.last->rlink = temp;
			temp->llink = list.last;
			list.last = temp;
		}
		else if(list.first->data >= v)
		{
			list.first->llink = temp;
			temp->rlink = list.first;
			list.first = temp;
		}
		else
		{
			cur = list.last;

			while(cur->data > v)
				cur = cur->llink;

			temp->llink = cur;
			temp->rlink = cur->rlink;
			cur->rlink->llink = temp;
			cur->rlink = temp;
		}
	}
	else
	{
		list.first	= temp;
		list.last	= temp;
	}

	list.count++;
}

// 이중 연결 리스트를 초기화
void init(DlistNode *phead) 
{
	phead->llink = phead;
	phead->rlink = phead;
}

//inputdata파일 읽기
void load_file(){
	
	DlistNode *ptr;
	FILE * fp1;
	int res, tmp;
	fp1=fopen("inputdata.txt","r");

	//파일이 없다면
	if(fp1==NULL){
		printf("Error \n");
		return ;
	}

	while(1){
		
		res=fscanf(fp1,"%d ",&tmp);
		list_add(tmp);
		if(res<0)
			break;
	}
}

// 이중 연결 리스트의 노드를 출력
void save_file(DlistNode *phead) 
{
	FILE *fp2;
	fp2=fopen("Result.txt","w+");
	DlistNode *p=phead;
	do {
		fprintf(fp2,"%d ",p->data);
		p = p->rlink;
	} while(p != NULL);
}

void printLink(void)
{
	DlistNode* tmp = list.first;

	for( ;tmp != NULL ;tmp=tmp->rlink)
		printf("%d ",tmp->data);

	printf("\n");
}

// 메인함수 구현
void main()
{
	// 32 57 88
	list_add(32);
	list_add(57);
	list_add(88);

	//inputdata로 부터 파일을 읽어온다.
	load_file();

	//파일을 Result 파일에 저장한다.
	save_file(list.first);

} 