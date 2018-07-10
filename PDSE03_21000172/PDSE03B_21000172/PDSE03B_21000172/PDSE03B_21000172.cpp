/******************************************************************  
	�̸� : ������
	�й� : 21000172
	
	���� : PDSE03B
	Write a new ADT algorithm to merge two lists.Use linked list implementation.
	 		
			-�Է� �����͸� ���Ϸ� �Է�(inputdata.txt)
			-Doubly Linked List�� ����
			-����� ���ȭ�Ϸ� ���(Result.txt)
			-�ΰ��� ��ũ�� ����Ʈ�� (�̹� sorting�Ǿ��� ����) Merge�Ͽ�
			��ü sort�� �� �ٸ� ����Ʈ�� ����� ����

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

// ���� ���� ����Ʈ�� �ʱ�ȭ
void init(DlistNode *phead) 
{
	phead->llink = phead;
	phead->rlink = phead;
}

//inputdata���� �б�
void load_file(){
	
	DlistNode *ptr;
	FILE * fp1;
	int res, tmp;
	fp1=fopen("inputdata.txt","r");

	//������ ���ٸ�
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

// ���� ���� ����Ʈ�� ��带 ���
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

// �����Լ� ����
void main()
{
	// 32 57 88
	list_add(32);
	list_add(57);
	list_add(88);

	//inputdata�� ���� ������ �о�´�.
	load_file();

	//������ Result ���Ͽ� �����Ѵ�.
	save_file(list.first);

} 