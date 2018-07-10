/***********************************************
	���� :	PDSPRJ07
	�̸� :	������ , ������
	�й� :  21000172
	�к� :  �������� ���к�

	���� : HeapƮ�� �˰����� ����Ͽ� inputdata�� ���� �о���� ����
			����Ͽ� �켱������� �����Ͽ� ���� ����ϴ� ���α׷�

	�������� : inputdata�� ���� ���� �о�� reheapup�Լ��� �̿��Ͽ�
				heap ������ �����, ������� ���ĵ� ���� dequeue�Ͽ�
				result������Ͽ� �����Ѵ�. 
	���糯¥ : 2012. 11.20
***********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct element{
	char name[40];
	int mileage;
	int years;
	int sequence;
	int key;
}element;

typedef struct{							//����ü ����

	element array[512];
	int size;
}PRIOR_QUEUE;


//�켱���� ť �������̽��� ���Ե� �Լ� ����
//================================================
void init(PRIOR_QUEUE *pq);
void enQueue(PRIOR_QUEUE *pq, element data);
element deQueu(PRIOR_QUEUE *pq);
int isEmpty(PRIOR_QUEUE *pq);

void printArray(PRIOR_QUEUE *pq);
void printShape(PRIOR_QUEUE *pq, int cur, int level);
//=====================================================
//Heap interface
void reheapDown(element *array, int size, int parent);	//reheapDown �Լ�
void reheapUp(element *array, int child);				//reheapUp �Լ�
void swap(element *p1, element *p2);						
FILE *f1;
FILE *f2;


void init(PRIOR_QUEUE *pq){		
	
	pq->size = 0;
}
void enQueue(PRIOR_QUEUE *pq,element data){
	pq->array[pq->size] = data;
	reheapUp(pq->array,pq->size++);
}
element deQueue(PRIOR_QUEUE *pq){
	pq-> size--;							//	dequeue�Ҷ����� ũ�Ⱑ 1�� �����Ѵ�.
	swap(pq->array, pq->array+pq->size);		//�迭�� ������ ���ҿ� ��Ʈ��带 ��ȯ�Ѵ�.
	reheapDown(pq->array, pq->size,0);			//reheapDown�Լ��� ȣ���Ѵ�.

	return pq->array[pq->size];

}
int isEmpty(PRIOR_QUEUE *pq){
	return pq->size <=0;
}

//reheapDown �Լ�
void reheapDown(element *array, int size, int parent){
	int left, right, max;
	while(1){

		left = parent *2 + 1;
		right= parent *2 + 2;

		//�ڽ��� ���ٸ�
		if(left>=size)		
			break;

		if(left == size -1)	max = left;						//�ڽ��� �ϳ��ۿ� ���� ���
		else if(array[left].key > array[right].key) max = left;		//�ڽ��� ���� ��쿡, ���� �ڽ��� Ŭ���
		else max = right;

		if(array[parent].key >= array[max].key)
			break;

		swap(array + parent, array+max);
		parent = max;

	}
}
//reheapup �Լ�
void reheapUp(element *array, int child){
	int parent;
	while(child>0){
		parent = (child-1) /2;
		if(array[parent].key >= array[child].key)
			break;

		swap(array +parent, array+child);
		child = parent;
	}
}
void swap(element *p1, element *p2){
	element tmp;
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
	element temp;
	int i, n;

	
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



	
	//inputdat.txt ���Ϸ� ���� ���� �о�鿩 key���� ����ϰ� heap�� �����Ѵ�.
	while (!feof(f1)){
		fgets(temp.name,50,f1);
		fscanf(f1,"%d %d %d\n",&temp.mileage,&temp.years,&temp.sequence);
		temp.key = temp.mileage/1000 + temp.years - temp.sequence;
		temp.name[strlen(temp.name)-1] = '\0';
		enQueue(&priorQueue,temp);
	}


	//������� ����Ѵ�.
	fprintf(f2,"               Name     Mil Year Seq Key\n");
	while(!isEmpty(&priorQueue)){
		temp = deQueue(&priorQueue);
		fprintf(f2,"%20s  %5d %3d %3d %3d \n",temp.name,temp.mileage,temp.years,temp.sequence,temp.key);
	}
	

	fclose(f1);
	fclose(f2);
	system("pause");

}