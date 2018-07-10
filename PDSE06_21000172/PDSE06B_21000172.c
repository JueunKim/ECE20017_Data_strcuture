/***********************************************
	과제 :	PDSE06B
	이름 :	김주은
	학번 :  21000172
	학부 :  전산전자 공학부

	문제 : iterative 버전으로 AVL Tree delete 알고리즘을 구현하여라 

	구현내용 : 메인함수에서 inputdata로 부터 파일을 읽어온 후, avl 트리구조로 프로그램을 만든다.
			 삭제가 끝나면 종료(4번)을 누르고, 결과값으로 data value와 balance 값을 확인할 수있다.	
	만든날짜 : 2012. 10.29
***********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_SIZE 100
#define MAX_NUM_SIZE 100

//데이터형식
typedef struct element{
	char p_num[MAX_NUM_SIZE];
}element;

//노드의 구조
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
void f_write(avl_node *p);				//전화번호부 파일 출력함수
int max2(int x, int y);

FILE *f1;
FILE *f2;

// 오른쪽 회전 함수 -- LL  rotation 
avl_node *
rotate_LL(struct avl_node *parent)
{
	struct avl_node *child = parent->left_child;
	parent->left_child = child->right_child;
	child->right_child = parent;
	return child;
}
// 왼쪽 회전 함수 -- RR rotation 
avl_node *rotate_RR(struct avl_node *parent)
{
	struct avl_node *child = parent->right_child;
	parent->right_child = child->left_child;
	child->left_child = parent;
	return child;
}
// 오른쪽-왼쪽 회전 함수 -- RL rotaion  
avl_node * rotate_right_left(struct avl_node *parent)
{
	struct avl_node *child = parent->right_child;
	parent->right_child = rotate_LL(child);
	return rotate_RR(parent);
}
// 왼쪽-오른쪽 회전 함수--LR rotation 
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

// 트리의 높이를 반환
int get_height(struct avl_node *node)
{
	int height=0;
	if( node != NULL )
		height = 1 + max2(get_height(node->left_child), 
						get_height(node->right_child));
	return height;
}

// 노드의 균형인수를 반환
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
//삽입함수
void insert_node(avl_node **root, element key2){
	avl_node *p,*q;				//p=부모노드 , q=자식노드
	avl_node *n;				//새로운 노드

	p=*root;
	q=NULL;

	while(p!=NULL){
		if(compare(key2,p->key)==0) return;
		q=p;
		if(compare(key2,p->key)<0) 
			p=p->left_child;
		else p=p->right_child;
	}
	//새로운 노드 생성, 삽입
	n=(avl_node*)malloc(sizeof(avl_node));
	if(n==NULL)return ;
	//데이터 복사
	n->key = key2;
	n->left_child=n->right_child=NULL;

	//부모노드와 링크연결
	if(q!=NULL)
		if(compare(key2,q->key)<0)
			q->left_child=n;
		else q->right_child=n;
	else *root =n;

	rebalance(root);
}
//삭제함수
void delete_node(avl_node **root,element key){
	avl_node*p, *child, *succ,*succ_p,*t;
	p=NULL;
	t=*root;

	//탐색시작
	while(t!=NULL && compare(t->key,key)!=0){
	p=t;
	t=(compare(key,t->key)<0) ? t->left_child : t->right_child;
	}
	if(t==NULL){
		printf("key is not the tree");
		return ;
	}
	//단말노드일 경우
	if((t->left_child ==NULL) &&(t->right_child ==NULL)){
		if(p!=NULL){
			if(p->left_child ==t)
					p->left_child =NULL;
			else p->right_child=NULL;
		}
		else *root =NULL;
	}
	//하나의 자식만 가지는 경우
	else if((t->left_child ==NULL)||(t->right_child ==NULL)){
		child=(t->left_child!=NULL) ? t->left_child : t->right_child;
		if(p!=NULL){
			if(p->left_child ==t)
				p->left_child =child;
			else p->right_child =child;
		}
		else *root = child;
	}
	//두개의 자식을 가지는 경우
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
//inputdata파일 읽어오는 함수
void f1_open(){
	
	element temp;
	f1=fopen("inputdata.txt","r");
	if(f1==NULL){
		printf("파일을 열수없습니다 \n");
		return;	
	}
		while(!feof(f1)){
			fscanf(f1,"%s", temp.p_num);
			insert_node(&root,temp);
		}
}
//결과파일 출력함수
void f2_open(){
	f2=fopen("Result.txt","w");
	if(f2==NULL){
		printf("파일을 열 수 없습니다.");
		return;
	}
}
void menu(){
	
	printf("===========menu=============\n");
	printf("1. 입력\n");
	printf("2. 삭제 \n");
	printf("3. 출력\n");
	printf("4. 종료 \n");
}

//Result파일에 출력하는 함수
void f_write(avl_node *p){
		
	if(p!=NULL){			//트리노드 탐색 시작
		f_write(p->left_child);
		fprintf(f2,"[data value]:%s [valance value]:(%d) \n", p->key.p_num,get_height(p->left_child) - get_height(p->right_child));
		f_write(p->right_child);
	}
}
//전체 전화번호부 출력함수
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
	case 1 :printf("삽입할번호 \n");
			gets(e.p_num);
			insert_node(&root,e);
			break;
	case 2 : printf("삭제할번호 \n");
			gets(e.p_num);
			delete_node(&root,e);
			printf("삭제되었습니다 .\n");
			break;
	case 3 :display(root);
			printf("\n");
			break;
	case 4 : printf("프로그램을 종료합니다. \n");
			f_write(root);
			fclose(f1);
			fclose(f2);
			return ;
		}
	}
	
}