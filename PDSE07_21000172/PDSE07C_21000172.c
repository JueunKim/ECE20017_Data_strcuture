/***********************************************
	���� :	PDSE07C
	�̸� :	������
	�й� :  21000172
	�к� :  �������� ���к�

	���� : �� heap�� ���� ����° heap�� ������.

	�������� : �켱, ���� �Լ����� heap1�� �����Ѵ�. �� ���� 
			   inputdata�� ���� ������ �о�� ��,insert�Լ��� ����Ͽ�
			  heap2�� �����. �� heap�� ���� ���� third heap�� �����ϰ�
			  �� ������� result ���Ͽ� �����Ѵ�.

	���糯¥ : 2012. 11.16
***********************************************/

#include <stdio.h>
#include <stdlib.h>

typedef struct{							//����ü ����

	int array[512];
	int size;
}PRIOR_QUEUE, PRIOR_QUEUE2;


//�켱���� ť �������̽��� ���Ե� �Լ� ����
//================================================
void init(PRIOR_QUEUE *pq);
void init2(PRIOR_QUEUE2 *pq2);
void enQueue(PRIOR_QUEUE *pq, int data);
void enQueue2(PRIOR_QUEUE2 *pq2, int data);
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
void init2(PRIOR_QUEUE2 *pq2){		
	
	pq2->size = 0;
}
void enQueue(PRIOR_QUEUE *pq,int data){
	pq->array[pq->size] = data;
	reheapUp(pq->array,pq->size++);
}

void enQueue2(PRIOR_QUEUE2 *pq2,int data){
	pq2->array[pq2->size] = data;
	reheapUp(pq2->array,pq2->size++);
}
int deQueue(PRIOR_QUEUE *pq){
	pq-> size--;							//	dequeue�Ҷ����� ũ�Ⱑ 1�� �����Ѵ�.
	swap(pq->array, pq->array+pq->size);		//�迭�� ������ ���ҿ� ��Ʈ��带 ��ȯ�Ѵ�.
	reheapDown(pq->array, pq->size,0);			//reheapDown�Լ��� ȣ���Ѵ�.

	return pq->array[pq->size];

}
int isEmpty(PRIOR_QUEUE *pq){
	return pq->size <=0;
}

//reheapDown �Լ�
void reheapDown(int *array, int size, int parent){
	int left, right, min;
	while(1){

		left = parent *2 + 1;
		right= parent *2 + 2;

		//�ڽ��� ���ٸ�
		if(left>=size)		
			break;

		if(left == size -1)	min = left;						//�ڽ��� �ϳ��ۿ� ���� ���
		else if(array[left] < array[right]) min = left;		//�ڽ��� ���� ��쿡, ���� �ڽ��� Ŭ���
		else min = right;

		if(array[parent] <= array[min])
			break;

		swap(array + parent, array+min);
		parent = min;

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
		fprintf(f2,"[%d] ",pq->array[i]);
	}
		fprintf(f2,"\n");
	
		fprintf(f2,"heap1 value : ");
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
			fprintf(f2,"     ");
		fprintf(f2,"[%2d]\n",pq->array[cur]);
		
		printShape(pq, cur*2+1,level+1);
	}

}
void main(){

	PRIOR_QUEUE priorQueue;
	PRIOR_QUEUE priorQueue2;

	int i, n;
	int temp;
	
	//�ʱ�ȭ
	init(&priorQueue);
	init(&priorQueue2);

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

	
	//inputdat.txt ���Ϸ� ���� ���� �о�鿩 heap1�� �����Ѵ�.
	while (!feof(f1)){
		fscanf(f1,"%d",&temp);
		printf("[%d] ",temp);
		fprintf(f2,"[%d]",temp);
		enQueue(&priorQueue,temp);
	}

	fprintf(f2,"\n");
	fprintf(f2,"\n");


	//heap2�� �����Ѵ�.
	enQueue2(&priorQueue2,11);
	enQueue2(&priorQueue2,22);
	enQueue2(&priorQueue2,33);
	enQueue2(&priorQueue2,44);
	enQueue2(&priorQueue2,55);
	enQueue2(&priorQueue2,63);
	enQueue2(&priorQueue2,77);


	//heap1�� �� ���
	fprintf(f2,"heap1 �� : \n");
	printShape(&priorQueue,0,1);
	fprintf(f2,"\n");
	fprintf(f2,"\n");
	fprintf(f2,"\n");
	fprintf(f2,"\n");
	
	//heap2�� �� ���
	fprintf(f2,"heap2 �� \n");
	printShape(&priorQueue2,0,1);
	fprintf(f2,"\n");
	fprintf(f2,"\n");

		while(!isEmpty(&priorQueue)){
		enQueue2(&priorQueue2,deQueue(&priorQueue));
	}

	fprintf(f2,"\n");
	fprintf(f2,"\n");
	fprintf(f2,"\n");
	fprintf(f2,"heap3 ��°� : \n");
	printShape(&priorQueue2,0,1);
	

	fclose(f1);
	fclose(f2);
	system("pause");

}