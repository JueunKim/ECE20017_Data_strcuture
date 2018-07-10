/***********************************************
	���� :	PDSE05B
	�̸� :	������
	�й� :  21000172
	�к� :  �������� ���к�

	���� : �迭�� Ȱ���� ����Ʈ���� ��ȭ��ȣ�α���(�Է�,���,����,�˻�)
	�������� : inputdata�� ���� ������ �о�� ��, �迭�� ���� �����Ͽ�
		���� Ʈ���� �����Ѵ�. �����Լ����� ������ �޴��� ���� �� ����� 
		�����Ѵ�. �̸��� ����Ʈ���� ���ĵǾ� ���� �� ���� ������Ͽ� ����ȴ�.
		
	���糯¥ : 2012. 10. 23
***********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 30

typedef struct element{
	char name[20];
	char phone[20];
}element;

element node[MAX_SIZE];

void search(int i, char *);
void insert_node();		//��� ����
void delete_node();		//��� ����
void display(int i);			//��ȭ��ȣ�� ��� 
void f_write(int i);			//Result ���Ͽ� ����� ���
void f1_open();			//�Է� ���� open 
void f2_open();			//��� ���� open
void menu();			//�޴����

FILE *f1;
FILE *f2;

//inputdata ���� ����
void f1_open(){
	
	int i=0;
	f1=fopen("inputdata.txt","r");
		if(f1==NULL){
			printf("������ ���������ϴ�\n.");
			return ;
		}
		while(!feof(f1)){
		fscanf(f1,"%s %s ",&node[i].name,&node[i].phone);
		i++;
			}
}
//Result.txt ���� ����
void f2_open(){
	
	f2=fopen("Result.txt","w");
	
	if(f2==NULL){
		printf("������ �� �� �����ϴ�.");
		return ;
	}	
}
//��ȭ��ȣ�� ���
void display(int i){

	if( node[i].name == 0 ){
		return;}
	
		display(2*i);				//���ʳ�� �湮
		printf("%s , %s \n",node[i].name,node[i].phone);
		display((2*i)+1);			//������ ��� �湮
		
}
void search(int i,char *s){
	
	
	if( node[i].name == 0 ){
		return;}

		display(2*i);				//���ʳ�� �湮
		printf("%s , %s \n",node[i].name,node[i].phone);
		display((2*i)+1);			//������ ��� �湮

}
void delete_node(){

}
void insert_node(){

}
void f_write(int index){
	
	if( node[index].name == 0 ){
		return;
		}
		f_write(2*index);				// ���� ���� Ʈ�� �˻�
		fprintf(f2,"%s %s", node[index].name, node[index].phone); // ��� �湮
		f_write((2*index)+1);			// ���� ���� Ʈ�� �˻�
}
void menu(){
	printf("===========menu=============\n");
	printf("1. �˻� \n");
	printf("2. �Է� \n");
	printf("3. ���� \n");
	printf("4. ���\n");
	printf("5. ���� \n");
}
void main(){


	int num=0;
	char searched[30];

    f1_open();
    f2_open();
	while(1){
		menu();
		fflush(stdin);
		scanf("%d",&num);
	switch(num){
	case 1 : printf("ã�»��\n");
			gets(searched);
			search(1,searched);
			break;
	case 2 : printf("�߰��һ��\n");
			gets(searched);
			printf("��ȣ \n");
			gets(searched);
			insert_node();
			break;
	case 3 : printf("�����һ�� \n");
			gets(searched);
			delete_node();
			break;
	case 4 : display(1);
			printf("\n");
			break;
	case 5 : printf("���α׷��� �����մϴ�. \n");
		//	f_write(1);
			return ;
		}
	}
	fclose(f1);
	fclose(f2);
}
