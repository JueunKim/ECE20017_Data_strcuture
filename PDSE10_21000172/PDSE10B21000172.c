/***********************************************
	���� :	PDSE10B
	�̸� :	������
	�й� :  21000172
	�к� :  �������� ���к�

	���� : �����Լ��� �����͸� �����Ͽ� Quicksort�� ���� �����Ͽ� ����Ͽ���. 

	�������� : �����Լ����� �����Լ��� ���� �о�� quicksort�� sorting�Ѵ�.
				������� result���Ϸ� �����Ѵ�.
	���糯¥ : 2012. 12.03
	����  :���ͳ� ���۸� 
***********************************************/

#include <stdio.h>
#include <stdlib.h>
#define SIZE 10			//���� ���� ����


void quicksort(int list[], int left, int right);
int partition(int list[], int left, int right);
FILE *f1;
int cnt=0;

void main(){

	
	int i =0;
	int list[SIZE];

	f1=fopen("Result.txt","w");
	if(f1==NULL){
		printf("������ ���������ϴ� \n");
		return;	
	}

	//���� �� data �� ����
	fprintf(f1,"������ \n");
	for(i =0; i< SIZE; i++){
		list[i] = rand()%100;
		fprintf(f1,"[%d] ", list[i]);
	}
	printf("\n");
	

	//quick sort �Լ� ȣ��
	quicksort(list, 0, SIZE -1);
	
	//���� �� data ��
	fprintf(f1,"������ \n");
	for(i =0; i< SIZE; i++){
		fprintf(f1,"[%d] ", list[i]);
	}
	
	fprintf(f1,"\n");
	
	fprintf(f1,"data �̵�Ƚ�� = %d",cnt);
	
	system("PAUSE");
}
void quicksort(int list[],int left, int right){

	int q;			//�ǹ� q ���� ����
	if(left < right){

		q = partition(list, left, right);

		quicksort(list,left, q-1);		//�ǹ� ���� ����Ʈ quicksort
		cnt++;

		quicksort(list, q+1, right);	//�ǹ� ������ ����Ʈ quicksort	
		cnt++;
	}
}
int partition(int list[],int left, int right){

	int pivot, temp;
	int low, high;
	//int cnt =0;			//ī��Ʈ ���� ����
	low = left;
	high = right+1;
	pivot = list[left];		//������ ����Ʈ�� ���� ���� data�� �ǹ����� ����

	//low�� high�� ������ �� ���� �ݺ�
	do{
		
		do{ 
			cnt++;
			low++;		//list[low]�� pivot���� ������ ��� low ����
			
		}while(list[low] < pivot);

		do{
			cnt++;
			high--;		//list[high]�� pivot ���� ũ�� ��� high ����
		}while(list[high] > pivot);

		//list[low]�� list[high]�� �������� ������
		//�ΰ��� ���� ��ȯ
		if(low<high){ 
			temp = list[low];
			list[low] = list[high];
			list[high]=temp;
		}


	}while(low < high);
	

	//�ǹ��� ��� ��ġ��Ų��.
	temp = list[left];
	list[left] = list[high];
	list[high]=temp;

	//�ǹ� ��ġ��ȯ
	return high;
	}