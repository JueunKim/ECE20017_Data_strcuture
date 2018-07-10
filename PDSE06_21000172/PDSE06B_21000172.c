/***********************************************
	���� :	PDSE06B
	�̸� :	������
	�й� :  21000172
	�к� :  �������� ���к�

	���� : iterative �������� AVL Tree delete �˰����� �����Ͽ��� 

	�������� : �����Լ����� inputdata�� ���� ������ �о�� ��, avl Ʈ�������� ���α׷��� �����.
			 ������ ������ ����(4��)�� ������, ��������� data value�� balance ���� Ȯ���� ���ִ�.	
	���糯¥ : 2012. 10.29
***********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_SIZE 100
#define MAX_NUM_SIZE 100

//����������
typedef struct element{
	char p_num[MAX_NUM_SIZE];
}element;

//����� ����
typedef struct avl_node{
	element key;
	struct avl_node *left_child,*right_child;
}avl_node;
avl_node *root=NULL;

int compare(element e1,element e2);
void display(avl_node *p);
void insert_node(avl_node **root, element key);
void delete_node(avl_node **root,element key);
void f1_open();
void f2_open();
void menu();
void f_write(avl_node *p);				//��ȭ��ȣ�� ���� ����Լ�
int max2(int x, int y);

FILE *f1;
FILE *f2;

// ������ ȸ�� �Լ� -- LL  rotation 
avl_node *
rotate_LL(struct avl_node *parent)
{
	struct avl_node *child = parent->left_child;
	parent->left_child = child->right_child;
	child->right_child = parent;
	return child;
}
// ���� ȸ�� �Լ� -- RR rotation 
avl_node *rotate_RR(struct avl_node *parent)
{
	struct avl_node *child = parent->right_child;
	parent->right_child = child->left_child;
	child->left_child = parent;
	return child;
}
// ������-���� ȸ�� �Լ� -- RL rotaion  
avl_node * rotate_right_left(struct avl_node *parent)
{
	struct avl_node *child = parent->right_child;
	parent->right_child = rotate_LL(child);
	return rotate_RR(parent);
}
// ����-������ ȸ�� �Լ�--LR rotation 
avl_node *rotate_left_right(struct avl_node *parent)
{
	struct avl_node *child = parent->left_child;
	parent->left_child = rotate_RR(child);
	return rotate_LL(parent);
}

int max2(int x, int y)
{

    return( (x >= y) ? x:y);
}

// Ʈ���� ���̸� ��ȯ
int get_height(struct avl_node *node)
{
	int height=0;
	if( node != NULL )
		height = 1 + max2(get_height(node->left_child), 
						get_height(node->right_child));
	return height;
}

// ����� �����μ��� ��ȯ
int get_height_diff(struct avl_node *node) 
{
	if( node == NULL ) return 0;
	return get_height(node->left_child) - get_height(node->right_child);
} 

struct avl_node *rebalance(struct avl_node **node)
{
	int height_diff = get_height_diff(*node);
	if( height_diff > 1 ){
		if( get_height_diff((*node)->left_child) > 0 )
			*node = rotate_LL(*node);
		else
			*node = rotate_left_right(*node);
	}
	else if ( height_diff < -1 ){
		if( get_height_diff((*node)->right_child) < 0 )
			*node = rotate_RR(*node);
		else
			*node = rotate_right_left(*node);
	}
	return *node;
}

int compare(element e1,element e2){
	return strcmp(e1.p_num, e2.p_num);
}
//�����Լ�
void insert_node(avl_node **root, element key2){
	avl_node *p,*q;				//p=�θ��� , q=�ڽĳ��
	avl_node *n;				//���ο� ���

	p=*root;
	q=NULL;

	while(p!=NULL){
		if(compare(key2,p->key)==0) return;
		q=p;
		if(compare(key2,p->key)<0) 
			p=p->left_child;
		else p=p->right_child;
	}
	//���ο� ��� ����, ����
	n=(avl_node*)malloc(sizeof(avl_node));
	if(n==NULL)return ;
	//������ ����
	n->key = key2;
	n->left_child=n->right_child=NULL;

	//�θ���� ��ũ����
	if(q!=NULL)
		if(compare(key2,q->key)<0)
			q->left_child=n;
		else q->right_child=n;
	else *root =n;

	rebalance(root);
}
//�����Լ�
void delete_node(avl_node **root,element key){
	avl_node*p, *child, *succ,*succ_p,*t;
	p=NULL;
	t=*root;

	//Ž������
	while(t!=NULL && compare(t->key,key)!=0){
	p=t;
	t=(compare(key,t->key)<0) ? t->left_child : t->right_child;
	}
	if(t==NULL){
		printf("key is not the tree");
		return ;
	}
	//�ܸ������ ���
	if((t->left_child ==NULL) &&(t->right_child ==NULL)){
		if(p!=NULL){
			if(p->left_child ==t)
					p->left_child =NULL;
			else p->right_child=NULL;
		}
		else *root =NULL;
	}
	//�ϳ��� �ڽĸ� ������ ���
	else if((t->left_child ==NULL)||(t->right_child ==NULL)){
		child=(t->left_child!=NULL) ? t->left_child : t->right_child;
		if(p!=NULL){
			if(p->left_child ==t)
				p->left_child =child;
			else p->right_child =child;
		}
		else *root = child;
	}
	//�ΰ��� �ڽ��� ������ ���
	else{
		succ_p =t;
		succ=t->right_child;

		while(succ->left_child !=NULL){
			succ_p=succ;
			succ=succ->left_child;
		}
		if(succ_p->left_child ==succ)
			succ_p->left_child = succ->right_child;
		else succ_p->right_child = succ->right_child;
		t->key = succ->key;
		t=succ;
	}
	rebalance(root);
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
			fscanf(f1,"%s", temp.p_num);
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
	printf("1. �Է�\n");
	printf("2. ���� \n");
	printf("3. ���\n");
	printf("4. ���� \n");
}

//Result���Ͽ� ����ϴ� �Լ�
void f_write(avl_node *p){
		
	if(p!=NULL){			//Ʈ����� Ž�� ����
		f_write(p->left_child);
		fprintf(f2,"[data value]:%s [valance value]:(%d) \n", p->key.p_num,get_height(p->left_child) - get_height(p->right_child));
		f_write(p->right_child);
	}
}
//��ü ��ȭ��ȣ�� ����Լ�
void display(avl_node *p){

	if(p!=NULL){
		display(p->left_child);
		printf("[data value]:%s [valance value]:(%d) \n",p->key.p_num,get_height(p->left_child) - get_height(p->right_child));
		display(p->right_child);
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
	case 1 :printf("�����ҹ�ȣ \n");
			gets(e.p_num);
			insert_node(&root,e);
			break;
	case 2 : printf("�����ҹ�ȣ \n");
			gets(e.p_num);
			delete_node(&root,e);
			printf("�����Ǿ����ϴ� .\n");
			break;
	case 3 :display(root);
			printf("\n");
			break;
	case 4 : printf("���α׷��� �����մϴ�. \n");
			f_write(root);
			fclose(f1);
			fclose(f2);
			return ;
		}
	}
	
}