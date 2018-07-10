/***********************************************
	���� :	PDSE04C
	�̸� :	������
	�й� :  21000172
	�к� :  �������� ���к�

	���� : write a program that creates a mirror image of a binary tree. 
			all left children become right children and vice versa. 

	�������� : inputdata�� ���� ������ �о�� ��, tree_array�� ���� �����Ͽ�
				���� Ʈ���� �����Ѵ�. travesal �Լ��� ����Ͽ� ���� child�� 
				������ child�� ���� �ٲ� ��, �� ���� Result���Ϸ� ��½�Ų��.

	�˰��� : ����Ʈ���� ���ʰ� ������ child�� ���� �ٲٱ� ����, temp��� ���Ǻ�����
				���� �ڽĳ�尪�� �ְ�, ������ �ڽ� ��尪�� ���ʿ� �־� ü�����Ѵ�.
				�׷��� ����Ʈ���� �ڽĳ�尡 reverse�Ǵ� �Լ��� ���� �� �� �ִ�. 
	���糯¥ : 2012. 10. 10
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


	fprintf(f2,"reverse �� ����� : \n");

	for(i=1;tree_array[i]!='\0';i++){
			fprintf(f2,"%d ",tree_array[i]);
	}

	fclose(f1);
	fclose(f2);

}

void make_tree()
{	int i=1;
	int j=1;

	f1=fopen("inputdata.txt","r");		//inputdata.txt�� ����..
	f2=fopen("Result.txt","w");			//������� ����� ������ ����.

	//������ ���������Ҷ����� �迭 tree_array�� �����Ѵ�.
	while(!feof(f1)){
		fscanf(f1,"%d",&tree_array[i]);
		i++;
	}
	fprintf(f2,"inputdata�� �� : ");
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


		if(index%2==0){									//���ʳ���
			temp=tree_array[index];						//temp ������ ������ ��� ���� �ְ�
			tree_array[index]=tree_array[index+1];		//������ ��带 ���ʿ� �ְ�
			tree_array[index+1]=temp;					//���� ��尪�� ������ ��忡 �ִ´�.
			}

	inorder(2*index +1);
}