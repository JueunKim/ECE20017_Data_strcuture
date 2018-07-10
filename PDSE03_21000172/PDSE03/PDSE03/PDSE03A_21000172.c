/*  �̸� : ������
	�к� : �������ڰ��к�
	�й� : 21000172
	���� : PDSE03A ��ũ�� ����Ʈ�� ����Ͽ�
		   �ΰ��� ����Ʈ�� ��ġ�� �˰����� �����϶�.
	���� �˰��� : inputdata�� ���� ������ �о�� ������ ����Ǿ��ִ� ��ũ�� ����Ʈ�� �����δ�.
					������� Result.txt�� ����Ѵ�.
		   */

#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode { 
	element data;
	struct ListNode *link;   	
} ListNode; 

ListNode *head;				//�Ӹ��κ�
ListNode *tail;				//�����κ�
FILE *fp1;					//�Է� ����������
FILE *fp2;					//��� ����������

void insert_node(int item){			//�����Լ�

	//�޸� �����Ҵ�
	ListNode *ptr;			
	ptr=(ListNode*)malloc(sizeof(ListNode));

	ptr->data= item;
	ptr->link= head;
	head=ptr;

	printf("���ԵǾ����ϴ� \n");
}
void printAll(){

	ListNode *ptr;
	ptr = head->link;
	if(head->link ==tail)
		printf("������ �����ϴ� \n");

	while(ptr!=NULL){
			printf("%d",ptr->data);
			ptr=ptr->link;
		}
}	
void load_file(){				//���� �ҷ����� �Լ�

	FILE *fp1;
	ListNode *ptr = NULL;
	int res, tmp;

	fp1=fopen("inputdata.txt","r");
	
	if (fp1==NULL){
		printf("Error \n"); 
		return;
	}

	while(1){
		res=fscanf(fp1,"%d ",&tmp);
		
		//inputdata�κ��� �о���� ���� ��ũ�帮��Ʈ�� �����Ѵ�.
		insert_node(tmp);

		if(res < 0) break;

	}

	fclose(fp1);
}
void save_file(){
	
	FILE *fp2;
	ListNode *ptr = head;

	//�޸� ����Ʈ�� Result ���Ͽ� ����
	fp2=fopen("Result.txt","w");
	
	if(fp2==NULL){
		printf("Error\n");
			return ;}
	
	while(1) {
		if(ptr==NULL) break;
		fprintf(fp2,"%d ",ptr->data);
		ptr=ptr->link;
	}
	
	fclose(fp2);
}

int main(){

	//20 30 40�� ��ũ�帮��Ʈ�� ����
	insert_node(20);
	insert_node(30);
	insert_node(40);

	//inputdata������ �о���δ�.
	load_file();


	//������� Result���Ͽ� ����Ѵ�.
	save_file();

	//����� ���
	printAll();

	return 0;
}