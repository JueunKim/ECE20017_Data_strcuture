/******************************************
	PDSE04B �ǽ�
	�̸� : ������
	�й� : 21000172

	���� :write a program that determines whether a binary tree is full 
	
	�������� : �����Լ����� inputdata�� ���� ������ �о�� binary tree�� �����.
	inorder �Լ���  level�� ���ϴ� �Լ��� ����Ͽ� ,full binary �̸�, Result.txt�� full binary�� ����Ѵ�.

	�ۼ��� : 2012.10.9

********************************************/

#include <stdio.h>
#include <math.h>

#define MAX_SIZE 1000
char tree_array[MAX_SIZE];
int cnt=0;
int i=0;
int count=0;
int height=0;
int node=0;
FILE *f1;
FILE *f2;
void make_tree();
void inorder();
void postorder();

void main(){

	make_tree();		//���� Ʈ�� ���� �Լ��� ȣ���Ѵ�.
	
	inorder(1);			//inorder �Լ��� ȣ���Ͽ� ��ȸ�ϸ鼭, node�� ����Ʈ�Ѵ�.
	postorder(1);		//������ ���Ѵ�.  
	
	fprintf(f2,"node�� : %d \n",node);
	fprintf(f2,"height �� : %d \n",height);


	if(node==pow(2.0,height)-1.0)					//���� == 2^height�̸� full binary�̴�.
		fprintf(f2,"full binary�Դϴ�. \n");
	else fprintf(f2,"full binary�� �ƴմϴ�. \n");	//�׷��� ���� ��� ������ ���� ����Ѵ�.
	
	fclose(f1);
	fclose(f2);


}
void make_tree()
{	
	f1=fopen("inputdata.txt","r");		//inputdata.txt�� ����..
	f2=fopen("Result.txt","w");			//������� ����� ������ ����.

	//������ ���������Ҷ����� �迭 tree_array�� �����Ѵ�.
	while(!feof(f1)){
		fscanf(f1,"%c ",&tree_array[i]);
		i++;
	}
	
	
}
//Ž�� �Լ�,  node�� ī��Ʈ �Ѵ�.
void inorder( int index )
{	
	printf("inorder(%d)\n",index);
	if( tree_array[index] == 0 ){
		node++ ;return;						//��带 ī��Ʈ�Ѵ�.
	}
	inorder( 2*index ); 					// ���� ���� Ʈ�� �˻�
	
	printf("<%c>", tree_array[index]);    	// ��� �湮
	inorder( 2*index+1 );					// ���� ���� Ʈ�� �˻�

}

//level ���ϱ� 
void postorder (int index){	

	height ++;
	if(tree_array[2*index]==0){					//���� ����Ʈ���� �˻��ϴµ�
	  return ;}									//��尡 ���� ���, ī��Ʈ �� ��, �����Ѵ�.
	
	postorder(2*index);

}