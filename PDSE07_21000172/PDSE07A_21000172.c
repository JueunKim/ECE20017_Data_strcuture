/***********************************************
	과제 :	PDSE07A
	이름 :	김주은
	학번 :  21000172
	학부 :  전산전자 공학부

	문제 : 'ReheapUp'으로 min heap 삽입 알고리즘을 구현하여라 

	구현내용 : 메인함수에서 inputdata로 부터 파일을 읽어온 후,insert함수를 사용하여
			  min heap트리 구조를 만든다. 정렬된 값을 result파일에 출력한다.

	만든날짜 : 2012. 11.16
***********************************************/

#include <stdio.h>
#include <stdlib.h>

typedef struct{							//구조체 정의

	int array[512];
	int size;
}PRIOR_QUEUE;
//우선 순위 쿠 인터페이스에 포함된 함수들 선언
//================================================
void init(PRIOR_QUEUE *pq);
void enQueue(PRIOR_QUEUE *pq, int data);
int deQueu(PRIOR_QUEUE *pq);
int isEmpty(PRIOR_QUEUE *pq);

void printArray(PRIOR_QUEUE *pq);
void printShape(PRIOR_QUEUE *pq, int cur, int level);
//=====================================================
//Heap interface
void reheapDown(int *array, int size, int parent);	//reheapDown 함수
void reheapUp(int *array, int child);				//reheapUp 함수
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
	pq-> size--;								//마지막 요소를 가리킨다.
	swap(pq->array, pq->array+pq->size);		//배열의 마지막 원소와 루트노드를 교환한다.
	reheapDown(pq->array, pq->size,0);			//reheapDown함수를 호출한다.

	return pq->array[pq->size];

}
int isEmpty(PRIOR_QUEUE *pq){
	return pq->size <=0;
}

//reheapDown 함수
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
//reheapup 함수
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



	fprintf(f2,"inputdata 값 : ");
	printf("inputdata 값 : ");
	//inputdat.txt 파일로 부터 값을 읽어들여 enQueue에 삽입한다.
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
	//삽입된 값을 히프 트리로 볼 수 있는 함수
	printShape(&priorQueue,0,1);

	fclose(f1);
	fclose(f2);
	system("pause");

}