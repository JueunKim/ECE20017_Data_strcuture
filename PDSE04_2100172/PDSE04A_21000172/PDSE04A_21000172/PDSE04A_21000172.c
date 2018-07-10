/*******************************************************
	PESE04A _ �ǽ�������Ʈ
	�̸� : ������
	�й� : 21000172

	���� :  write a program that counts the number of nodes and leaves in a binary tree 
	�������� : main �Լ����� inputdata�� ���� ������ �о�� 
	���� Ʈ���� �����Ѵ�. ��� �� ���ϴ� �Լ��� �ܸ� �Լ��� �̿��Ͽ� conut����
	 ���Ѵ�. ������� Result.txt�� ����Ѵ�. 

���� : ������ ppt
********************************************************/
#include <stdio.h>

#define MAX_SIZE 1000
char tree_array[MAX_SIZE];
int cnt=0;
int i=0;
int count=0;
FILE *f1;
FILE *f2;
void make_tree();
void inorder();
void postorder();

void main(){

	make_tree();		//���� Ʈ�� ���� �Լ��� ȣ���Ѵ�.
	
	inorder(1);
	postorder(1);

	fprintf(f2,"��� ����  %d \n",cnt);
	fprintf(f2,"Leaves�� �� : %d \n",count);

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
void inorder( int index )
{	
	printf("inorder(%d)\n",index);
	if( tree_array[index] == 0 ){
		cnt++ ;return; 
	}
	inorder( 2*index ); 					// ���� ���� Ʈ�� �˻�
	
	printf("<%c>", tree_array[index]);    	// ��� �湮
	inorder( 2*index+1 );					// ���� ���� Ʈ�� �˻�

}

//�ܸ���� ���ϱ�
void postorder (int index){	

	
	if(tree_array[2*index]==0){ 
//		if(tree_array[2*index]+1==0){	//���� Ʈ���� �ڽĳ�尡 ������ Ȯ��, 
			count ++; return ;}
	//}
	
	postorder(2*index);
	postorder(2*index+1);
	
	
}