/***********************************************
	���� :	PDSE07A
	�̸� :	������
	�й� :  21000172
	�к� :  �������� ���к�

	���� : 'ReheapUp'���� min heap ���� �˰����� �����Ͽ��� 

	�������� : �����Լ����� inputdata�� ���� ������ �о�� ��,insert�Լ��� ����Ͽ�
			  min heapƮ�� ������ �����. ���ĵ� ���� result���Ͽ� ����Ѵ�.

	���糯¥ : 2012. 11.16
***********************************************/

#include <stdio.h>
#include <stdlib.h>

typedef struct{							//����ü ����

	int array[512];
	int size;
}PRIOR_QUEUE;
//�켱 ���� �� �������̽��� ���Ե� �Լ��� ����
//================================================
void init(PRIOR_QUEUE *pq);
void enQueue(PRIOR_QUEUE *pq, int data);
int deQueu(PRIOR_QUEUE *pq);
int isEmpty(PRIOR_QUEUE *pq);

void printArray(PRIOR_QUEUE *pq);
void printShape(PRIOR_QUEUE *pq, int cur, int level);
//=====================================================
//Heap interface
void reheapDown(int *array, int size, int parent);	//reheapDown �Լ�
void reheapUp(int *array, int child);				//reheapUp �Լ�
void swap(int *p1, int *p2);						
FILE *f1;
FILE *f2;


void init(PRIOR_QUEUE *pq){		
	
	pq->size = 0;
}
void enQueue(PRIOR_QUEUE *pq,int data){
	pq->array[pq->size] = data;
	reheapUp(pq->array,pq->size++);
}
int deQueue(PRIOR_QUEUE *pq){
	pq-> size--;								//������ ��Ҹ� ����Ų��.
	swap(pq->array, pq->array+pq->size);		//�迭�� ������ ���ҿ� ��Ʈ��带 ��ȯ�Ѵ�.
	reheapDown(pq->array, pq->size,0);			//reheapDown�Լ��� ȣ���Ѵ�.

	return pq->array[pq->size];

}
int isEmpty(PRIOR_QUEUE *pq){
	return pq->size <=0;
}

//reheapDown �Լ�
void reheapDown(int *array, int size, int parent){
	int left, right, max;
	while(1){

		left = parent *2 + 1;
		right= parent *2 + 2;

		if(left>=size)
			break;

		if(left == size -1)	max = left;
		else if(array[left] > array[right]) max = left;
		else max = right;

		if(array[parent] >= array[max])
			break;

		swap(array + parent, array+max);
		parent = max;

	}
}
//reheapup �Լ�
void reheapUp(int *array, int child){
	int parent;
	while(child>0){
		parent = (child-1) /2;
		if(array[parent] < array[child])
			break;

		swap(array+parent, array+child);
		child = parent;
	}
}
void swap(int *p1, int *p2){
	int tmp;
	tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

void printArray(PRIOR_QUEUE *pq){
	int i;
	for(i = 0; i < pq->size; i++){
		printf("[%d] ",pq->array[i]);
	}
		printf("\n");
	
		fprintf(f2,"heap value : ");
		for (i =0; i <pq->size; i++){
		fprintf(f2,"[%d] ",pq->array[i]);

		}
		printf("\n");

}
void printShape(PRIOR_QUEUE *pq, int cur, int level){
	if(cur < pq->size){
		int i;
		printShape(pq, cur*2+2, level+1);
		for(i = 1; i < level; i++)
			printf("     ");
		printf("[%2d]\n",pq->array[cur]);
		
		printShape(pq, cur*2+1,level+1);
	}

}
void main(){
	PRIOR_QUEUE priorQueue;
	int i, n;
	int temp;
	
	//�ʱ�ȭ
	init(&priorQueue);

	//inputdata ���� ����
	f1=fopen("inputdata.txt","r");
	if(f1 == NULL){
		printf("������ ���������ϴ�.");
		return;
	}
	//result ���� ����
	f2=fopen("Result.txt","w");
	if(f2==NULL){
		printf("������ �� �������ϴ�.");
			return;}



	fprintf(f2,"inputdata �� : ");
	printf("inputdata �� : ");
	//inputdat.txt ���Ϸ� ���� ���� �о�鿩 enQueue�� �����Ѵ�.
	while (!feof(f1)){
		fscanf(f1,"%d",&temp);
		printf("[%d] ",temp);
		fprintf(f2,"[%d]",temp);
		enQueue(&priorQueue,temp);
	}
	printf("\n");
	fprintf(f2,"\n");
	printf("heap value :");
	printArray(&priorQueue,0,1);

	
	printf("\n");
	printf("\n");
	//���Ե� ���� ���� Ʈ���� �� �� �ִ� �Լ�
	printShape(&priorQueue,0,1);

	fclose(f1);
	fclose(f2);
	system("pause");

}