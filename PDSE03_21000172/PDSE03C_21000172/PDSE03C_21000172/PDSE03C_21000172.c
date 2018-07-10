/*************************************************
	�̸� : ������
	�й� : 21000172
	�к� : �������ڰ��к�
	�ۼ��� : 2012.9.26

	�ǽ� 03C. 
	Create a function that searches for an integer, num, in a circularly linked list. 
	The function should return a pointer to the node that contains num 
	if num is in the list and NULL otherwise. 

�����ڷ� : datastructureå, ����
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

//����Ʈ �����Լ�
void list_add(int v){		

	//��������
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

	else if(list.count == 0)		//����Ʈ�� ó���̸�
	{
		list.first = temp;
		list.last = temp;

		temp->llink = temp;
		temp->rlink = temp;
	}
	
	list.count++;
}

// ���� ���� ����Ʈ�� �ʱ�ȭ
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

DlistNode* searchInt(int num)			//����Ʈ search�Լ�
{
	DlistNode* tmp;

	//�Է¹��� ���� ����Ʈ�� ���� ������, �� ���� ��ȯ�Ѵ�.
	for(tmp = list.first->rlink;tmp!=list.first;tmp=tmp->rlink) {
		if(tmp->data == num)
			return tmp;
	}
}

// �����Լ� ����
void main()
{
	int num;
	DlistNode* result;
	
	// 32 57 88 24������� ���� �Է��Ѵ�.
	list_add(32);
	list_add(57);
	list_add(88);
	list_add(24);


	printf("���� �Է��Ͻÿ�:");
	scanf("%d",&num);

	result = searchInt(num);

	printf("����� : %d\n",result->data);


} 