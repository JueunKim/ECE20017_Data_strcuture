/***********************************************
	과제 :	PDSE04C
	이름 :	김주은
	학번 :  21000172
	학부 :  전산전자 공학부

	문제 : write a program that creates a mirror image of a binary tree. 
			all left children become right children and vice versa. 

	구현내용 : inputdata로 부터 파일을 읽어온 후, tree_array에 값을 저장하여
				이진 트리를 구현한다. travesal 함수를 사용하여 왼쪽 child와 
				오른쪽 child의 값을 바꾼 후, 그 값을 Result파일로 출력시킨다.

	알고리즘 : 이진트리의 왼쪽과 오른쪽 child의 값을 바꾸기 위해, temp라는 임의변수에
				왼쪽 자식노드값을 넣고, 오른쪽 자식 노드값을 왼쪽에 넣어 체인지한다.
				그러면 이진트리의 자식노드가 reverse되는 함수를 구현 할 수 있다. 
	만든날짜 : 2012. 10. 10
***********************************************/
#include <stdio.h>
#include <stdlib.h>
void make_tree();
#define MAX_SIZE 100
int tree_array[MAX_SIZE]={0};
int  a[MAX_SIZE];
void inorder(int );
void make_tree();
FILE *f1;
FILE *f2;

void main(){
	int i=1;

	make_tree();

	inorder(1);


	fprintf(f2,"reverse 한 결과값 : \n");

	for(i=1;tree_array[i]!='\0';i++){
			fprintf(f2,"%d ",tree_array[i]);
	}

	fclose(f1);
	fclose(f2);

}

void make_tree()
{	int i=1;
	int j=1;

	f1=fopen("inputdata.txt","r");		//inputdata.txt를 연다..
	f2=fopen("Result.txt","w");			//결과값을 출력할 파일을 연다.

	//파일이 끝에도달할때까지 배열 tree_array에 저장한다.
	while(!feof(f1)){
		fscanf(f1,"%d",&tree_array[i]);
		i++;
	}
	fprintf(f2,"inputdata한 값 : ");
	for(j=1;tree_array[j]!='\0';j++){
		fprintf(f2,"%d",tree_array[j]);
	}
	fprintf(f2, "\n");
	
	
}
void inorder( int index )
{	
	int temp;
	if( tree_array[index] == 0 ){
		return; 
	}

	inorder(2*index);
	

	printf("inorder(%d)\n",index);


		if(index%2==0){									//왼쪽노드면
			temp=tree_array[index];						//temp 임의의 변수에 노드 값을 넣고
			tree_array[index]=tree_array[index+1];		//오른쪽 노드를 왼쪽에 넣고
			tree_array[index+1]=temp;					//왼쪽 노드값을 오른쪽 노드에 넣는다.
			}

	inorder(2*index +1);
}