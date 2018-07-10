/***********************************************
	과제 :	PDSE05A
	이름 :	김주은
	학번 :  21000172
	학부 :  전산전자 공학부

	문제 : 포인터를 활용한 이진트리로 전화번호부 구현하기(입력,삽입,출력,삭제)

	구현내용 : 메인함수에서 inputdata로 부터 파일을 읽어온 후, insert함수에 값을 저장한다.
				switch로 메뉴를 선택하여 원하는 기능을 불러온다.
				종료를 하면, 이름 순서대로 값이 출력함수에 저장된다.

	만든날짜 : 2012. 10. 23
***********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_SIZE 100
#define MAX_NUM_SIZE 100

//데이터형식
typedef struct element{
	char name[MAX_NAME_SIZE];
	char p_num[MAX_NUM_SIZE];
}element;

//노드의 구조
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
void f_write(TreeNode *p);				//전화번호부 파일 출력함수

FILE *f1;
FILE *f2;

int compare(element e1,element e2){
	return strcmp(e1.name, e2.name);
}
//전체 전화번호부 출력함수
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
//탐색함수
TreeNode *search(TreeNode *root, element key){
	
	TreeNode *p=root;
	while(p!=NULL){
		switch(compare(key,p->key)){
		case -1: p=p->left;
				break;
		case 0 : printf("찾았어요!!\n");
					printf("%s \n",p->key.p_num);
			return p;
		case 1: p=p->right;
				break;
		}
	}	return p;
}
//삽입함수
void insert_node(TreeNode **root, element key2){
	TreeNode *p,*q;				//p=부모노드 , t=자식노드
	TreeNode *n;				//새로운 노드

	p=*root;
	q=NULL;

	while(p!=NULL){
		if(compare(key2,p->key)==0) return;
		q=p;
		if(compare(key2,p->key)<0) 
			p=p->left;
		else p=p->right;
	}
	//새로운 노드 생성, 삽입
	n=(TreeNode*)malloc(sizeof(TreeNode));
	if(n==NULL)return ;
	//데이터 복사
	n->key = key2;
	n->left=n->right=NULL;

	//부모노드와 링크연결
	if(q!=NULL)
		if(compare(key2,q->key)<0)
			q->left=n;
		else q->right=n;
	else *root =n;
}
//삭제함수
void delete_node(TreeNode **root,element key){
	TreeNode*p, *child, *succ,*succ_p,*t;
	p=NULL;
	t=*root;

	//탐색시작
	while(t!=NULL && compare(t->key,key)!=0){
	p=t;
	t=(compare(key,t->key)<0) ? t->left : t->right;
	}
	if(t==NULL){
		printf("key is not the tree");
		return ;
	}
	//단말노드일 경우
	if((t->left ==NULL) &&(t->right ==NULL)){
		if(p!=NULL){
			if(p->left ==t)
					p->left =NULL;
			else p->right=NULL;
		}
		else *root =NULL;
	}
	//하나의 자식만 가지는 경우
	else if((t->left ==NULL)||(t->right ==NULL)){
		child=(t->left!=NULL) ? t->left : t->right;
		if(p!=NULL){
			if(p->left ==t)
				p->left =child;
			else p->right =child;
		}
		else *root = child;
	}
	//두개의 자식을 가지는 경우
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
//inputdata파일 읽어오는 함수
void f1_open(){
	
	element temp;
	f1=fopen("inputdata.txt","r");
	if(f1==NULL){
		printf("파일을 열수없습니다 \n");
		return;	
	}
		while(!feof(f1)){
			fscanf(f1,"%s %s",temp.name, temp.p_num);
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
	printf("1. 검색 \n");
	printf("2. 입력\n");
	printf("3. 삭제 \n");
	printf("4. 출력\n");
	printf("5. 종료 \n");
}

//Result파일에 출력하는 함수
void f_write(TreeNode *p){
	
	
	if(p!=NULL){			//트리노드 탐색 시작
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
	case 1 : printf("찾는사람\n");
			gets(e.name);
			search(root,e);
			break;
	case 2 : printf("추가할사람\n");
			gets(e.name);
			printf("번호 \n");
			gets(e.p_num);
			insert_node(&root,e);
			break;
	case 3 : printf("삭제할사람 \n");
			gets(e.name);
			delete_node(&root,e);
			printf("삭제되었습니다 .\n");
			break;
	case 4 : display(root);
			printf("\n");
			break;
	case 5 : printf("프로그램을 종료합니다. \n");
			f_write(root);
			fclose(f1);
			fclose(f2);
			return ;
		}
	}
	
}