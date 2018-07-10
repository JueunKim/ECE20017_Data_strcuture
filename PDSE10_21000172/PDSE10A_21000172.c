/***********************************************
	���� :	PDSE10A
	�̸� :	������
	�й� :  21000172
	�к� :  �������� ���к�

	���� : �����Լ��� �����͸� �����Ͽ� Shell sort�� ���� �����Ͽ� ����Ͽ���. 

	�������� : �����Լ����� �����Լ��� ���� �о�� Shell sort�� sorting�Ѵ�.
				������� result���Ϸ� �����Ѵ�.
	���糯¥ : 2012. 12.03
	����  :���ͳ� ���۸� 
***********************************************/
#include <stdio.h>
#include <stdlib.h>
#define SIZE 10

void shellsort(int list[], int total, int index);
FILE *f1;
int cnt =0;		//data�̵�Ƚ�� ī��Ʈ ��������
int main(void) {

	int list[SIZE] = {0};
	 int i = 0;

	f1=fopen("Result.txt","w");
	if(f1==NULL){
		printf("������ ���������ϴ� \n");
		return;	
	}

	//���� �� data �� ����
	fprintf(f1,"�����ϱ��� ��: ");
	for(i = 0; i < SIZE; i++) {
		list[i] = (rand()*rand()) % 100;
		fprintf(f1,"[%d] ", list[i]); 
 }
 
 shellsort(list, SIZE, 1);

 fprintf(f1,"\n");
 //���� �� data��
 fprintf(f1,"���� �� ��: ");
	 for(i = 0; i < SIZE; i++) {
		fprintf(f1,"[%d] ", list[i]); 
	 }

 fprintf(f1,"\n");
 fprintf(f1,"data �̵�Ƚ�� %d",cnt);

 
 system("PAUSE");
 return 0;
}

void shellsort(int list[], int total, int index) {

	int i,j,k,l = 0; 
	
	
		for(i = 0; i < total; i++) {
			cnt ++;			//ī��Ʈ /
			l = list[i];
		
			for(j = (i - index); j >= 0; j--) {
				cnt ++;	//ī��Ʈ
			if(list[j] > l){
				cnt ++;	//ī��Ʈ
				list[j + index] = list[j];
			}
				else break;
		
				}
				list[j + index] = l;
				cnt ++;			//ī��Ʈ
		}

		return;
}
