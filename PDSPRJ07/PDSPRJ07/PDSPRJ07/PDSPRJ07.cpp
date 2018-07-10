/***********************************************
	과제 :	PDSPRJ07
	이름 :	김주은 , 이혜민
	학번 :  21000172
	학부 :  전산전자 공학부

	문제 : Heap트리 알고리즘을 사용하여 inputdata로 부터 읽어들인 값을
			계산하여 우선순위대로 정렬하여 값을 출력하는 프로그램

	구현내용 : inputdata로 부터 값을 읽어와 reheapup함수를 이용하여
				heap 구조를 만들고, 순서대로 정렬된 값을 dequeue하여
				result출력파일에 저장한다. 
	만든날짜 : 2012. 11.20
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

typedef struct{							//구조체 정의

	element array[512];
	int size;
}PRIOR_QUEUE;


//우선순위 큐 인터페이스에 포함된 함수 선언
//================================================
void init(PRIOR_QUEUE *pq);
void enQueue(PRIOR_QUEUE *pq, element data);
element deQueu(PRIOR_QUEUE *pq);
int isEmpty(PRIOR_QUEUE *pq);

void printArray(PRIOR_QUEUE *pq);
void printShape(PRIOR_QUEUE *pq, int cur, int level);
//=====================================================
//Heap interface
void reheapDown(element *array, int size, int parent);	//reheapDown 함수
void reheapUp(element *array, int child);				//reheapUp 함수
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
	pq-> size--;							//	dequeue할때마다 크기가 1씩 감소한다.
	swap(pq->array, pq->array+pq->size);		//배열의 마지막 원소와 루트노드를 교환한다.
	reheapDown(pq->array, pq->size,0);			//reheapDown함수를 호출한다.

	return pq->array[pq->size];

}
int isEmpty(PRIOR_QUEUE *pq){
	return pq->size <=0;
}

//reheapDown 함수
void reheapDown(element *array, int size, int parent){
	int left, right, max;
	while(1){

		left = parent *2 + 1;
		right= parent *2 + 2;

		//자식이 없다면
		if(left>=size)		
			break;

		if(left == size -1)	max = left;						//자식이 하나밖에 없는 경우
		else if(array[left].key > array[right].key) max = left;		//자식이 둘일 경우에, 왼쪽 자식이 클경우
		else max = right;

		if(array[parent].key >= array[max].key)
			break;

		swap(array + parent, array+max);
		parent = max;

	}
}
//reheapup 함수
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

	
	//초기화
	init(&priorQueue);


	//inputdata 파일 오픈
	f1=fopen("inputdata.txt","r");
	if(f1 == NULL){
		printf("파일을 열수없습니다.");
		return;
	}
	//result 파일 오픈
	f2=fopen("Result.txt","w");
	if(f2==NULL){
		printf("파일을 열 수없습니다.");
			return;}



	
	//inputdat.txt 파일로 부터 값을 읽어들여 key값을 계산하고 heap을 생성한다.
	while (!feof(f1)){
		fgets(temp.name,50,f1);
		fscanf(f1,"%d %d %d\n",&temp.mileage,&temp.years,&temp.sequence);
		temp.key = temp.mileage/1000 + temp.years - temp.sequence;
		temp.name[strlen(temp.name)-1] = '\0';
		enQueue(&priorQueue,temp);
	}


	//결과값을 출력한다.
	fprintf(f2,"               Name     Mil Year Seq Key\n");
	while(!isEmpty(&priorQueue)){
		temp = deQueue(&priorQueue);
		fprintf(f2,"%20s  %5d %3d %3d %3d \n",temp.name,temp.mileage,temp.years,temp.sequence,temp.key);
	}
	

	fclose(f1);
	fclose(f2);
	system("pause");

}