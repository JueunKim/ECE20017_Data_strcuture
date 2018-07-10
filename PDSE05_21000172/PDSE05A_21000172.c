/***********************************************
	���� :	PDSE05A
	�̸� :	������
	�й� :  21000172
	�к� :  �������� ���к�

	���� : �����͸� Ȱ���� ����Ʈ���� ��ȭ��ȣ�� �����ϱ�(�Է�,����,���,����)

	�������� : �����Լ����� inputdata�� ���� ������ �о�� ��, insert�Լ��� ���� �����Ѵ�.
				switch�� �޴��� �����Ͽ� ���ϴ� ����� �ҷ��´�.
				���Ḧ �ϸ�, �̸� ������� ���� ����Լ��� ����ȴ�.

	���糯¥ : 2012. 10. 23
***********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_SIZE 100
#define MAX_NUM_SIZE 100

//����������
typedef struct element{
	char name[MAX_NAME_SIZE];
	char p_num[MAX_NUM_SIZE];
}element;

//����� ����
typedef struct TreeNode{
	element key;
	struct TreeNode *left,*right;
}TreeNode;
TreeNode *root=NULL;

int compare(element e1,element e2);
void display(TreeNode *p);
void insert_node(TreeNode **root, element key);
void delete_node(TreeNode **root,element key);
void f1_open();
void f2_open();
void menu();
void f_write(TreeNode *p);				//��ȭ��ȣ�� ���� ����Լ�

FILE *f1;
FILE *f2;

int compare(element e1,element e2){
	return strcmp(e1.name, e2.name);
}
//��ü ��ȭ��ȣ�� ����Լ�
void display(TreeNode *p){

	if(p!=NULL){
		printf(" ");
		display(p->left);
		printf("%s   %s \n",p->key.name,p->key.p_num);
		printf("\n");
		display(p->right);
		printf(" ");
	}
}
//Ž���Լ�
TreeNode *search(TreeNode *root, element key){
	
	TreeNode *p=root;
	while(p!=NULL){
		switch(compare(key,p->key)){
		case -1: p=p->left;
				break;
		case 0 : printf("ã�Ҿ��!!\n");
					printf("%s \n",p->key.p_num);
			return p;
		case 1: p=p->right;
				break;
		}
	}	return p;
}
//�����Լ�
void insert_node(TreeNode **root, element key2){
	TreeNode *p,*q;				//p=�θ��� , t=�ڽĳ��
	TreeNode *n;				//���ο� ���

	p=*root;
	q=NULL;

	while(p!=NULL){
		if(compare(key2,p->key)==0) return;
		q=p;
		if(compare(key2,p->key)<0) 
			p=p->left;
		else p=p->right;
	}
	//���ο� ��� ����, ����
	n=(TreeNode*)malloc(sizeof(TreeNode));
	if(n==NULL)return ;
	//������ ����
	n->key = key2;
	n->left=n->right=NULL;

	//�θ���� ��ũ����
	if(q!=NULL)
		if(compare(key2,q->key)<0)
			q->left=n;
		else q->right=n;
	else *root =n;
}
//�����Լ�
void delete_node(TreeNode **root,element key){
	TreeNode*p, *child, *succ,*succ_p,*t;
	p=NULL;
	t=*root;

	//Ž������
	while(t!=NULL && compare(t->key,key)!=0){
	p=t;
	t=(compare(key,t->key)<0) ? t->left : t->right;
	}
	if(t==NULL){
		printf("key is not the tree");
		return ;
	}
	//�ܸ������ ���
	if((t->left ==NULL) &&(t->right ==NULL)){
		if(p!=NULL){
			if(p->left ==t)
					p->left =NULL;
			else p->right=NULL;
		}
		else *root =NULL;
	}
	//�ϳ��� �ڽĸ� ������ ���
	else if((t->left ==NULL)||(t->right ==NULL)){
		child=(t->left!=NULL) ? t->left : t->right;
		if(p!=NULL){
			if(p->left ==t)
				p->left =child;
			else p->right =child;
		}
		else *root = child;
	}
	//�ΰ��� �ڽ��� ������ ���
	else{
		succ_p =t;
		succ=t->right;

		while(succ->left !=NULL){
			succ_p=succ;
			succ=succ->left;
		}
		if(succ_p->left ==succ)
			succ_p->left = succ->right;
		else succ_p->right = succ->right;
		t->key = succ->key;
		t=succ;
	}
	free(t);
}
//inputdata���� �о���� �Լ�
void f1_open(){
	
	element temp;
	f1=fopen("inputdata.txt","r");
	if(f1==NULL){
		printf("������ ���������ϴ� \n");
		return;	
	}
		while(!feof(f1)){
			fscanf(f1,"%s %s",temp.name, temp.p_num);
			insert_node(&root,temp);
		}

}
//������� ����Լ�
void f2_open(){
	f2=fopen("Result.txt","w");
	if(f2==NULL){
		printf("������ �� �� �����ϴ�.");
		return;
	}

}
void menu(){
	
	printf("===========menu=============\n");
	printf("1. �˻� \n");
	printf("2. �Է�\n");
	printf("3. ���� \n");
	printf("4. ���\n");
	printf("5. ���� \n");
}

//Result���Ͽ� ����ϴ� �Լ�
void f_write(TreeNode *p){
	
	
	if(p!=NULL){			//Ʈ����� Ž�� ����
		fprintf(f2," ");
		f_write(p->left);
		fprintf(f2,"%s , %s \n",p->key.name, p->key.p_num);
		f_write(p->right);
		fprintf(f2," ");
	}
}
void main(){
	
	element e;

	int num;
	f1_open();
	f2_open();

	while(1){
		menu();
		fflush(stdin);
		scanf("%d",&num);
		fflush(stdin);
	switch(num){
	case 1 : printf("ã�»��\n");
			gets(e.name);
			search(root,e);
			break;
	case 2 : printf("�߰��һ��\n");
			gets(e.name);
			printf("��ȣ \n");
			gets(e.p_num);
			insert_node(&root,e);
			break;
	case 3 : printf("�����һ�� \n");
			gets(e.name);
			delete_node(&root,e);
			printf("�����Ǿ����ϴ� .\n");
			break;
	case 4 : display(root);
			printf("\n");
			break;
	case 5 : printf("���α׷��� �����մϴ�. \n");
			f_write(root);
			fclose(f1);
			fclose(f2);
			return ;
		}
	}
	
}