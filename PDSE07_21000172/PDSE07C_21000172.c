/***********************************************
	과제 :	PDSE07C
	이름 :	김주은
	학번 :  21000172
	학부 :  전산전자 공학부

	문제 : 두 heap을 합쳐 세번째 heap을 만들어라.

	구현내용 : 우선, 메인 함수에서 heap1을 생성한다. 그 다음 
			   inputdata로 부터 파일을 읽어온 후,insert함수를 사용하여
			  heap2를 만든다. 두 heap을 합쳐 최종 third heap을 생성하고
			  그 결과값을 result 파일에 저장한다.

	만든날짜 : 2012. 11.16
***********************************************/

#include <stdio.h>
#include <stdlib.h>

typedef struct{							//구조체 정의

	int array[512];
	int size;
}PRIOR_QUEUE, PRIOR_QUEUE2;


//우선순위 큐 인터페이스에 포함된 함수 선언
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
void reheapDown(int *array, int size, int parent);	//reheapDown 함수
void reheapUp(int *array, int child);				//reheapUp 함수
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
	pq-> size--;							//	dequeue할때마다 크기가 1씩 감소한다.
	swap(pq->array, pq->array+pq->size);		//배열의 마지막 원소와 루트노드를 교환한다.
	reheapDown(pq->array, pq->size,0);			//reheapDown함수를 호출한다.

	return pq->array[pq->size];

}
int isEmpty(PRIOR_QUEUE *pq){
	return pq->size <=0;
}

//reheapDown 함수
void reheapDown(int *array, int size, int parent){
	int left, right, min;
	while(1){

		left = parent *2 + 1;
		right= parent *2 + 2;

		//자식이 없다면
		if(left>=size)		
			break;

		if(left == size -1)	min = left;						//자식이 하나밖에 없는 경우
		else if(array[left] < array[right]) min = left;		//자식이 둘일 경우에, 왼쪽 자식이 클경우
		else min = right;

		if(array[parent] <= array[min])
			break;

		swap(array + parent, array+min);
		parent = min;

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
	
	//초기화
	init(&priorQueue);
	init(&priorQueue2);

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

	
	//inputdat.txt 파일로 부터 값을 읽어들여 heap1를 생성한다.
	while (!feof(f1)){
		fscanf(f1,"%d",&temp);
		printf("[%d] ",temp);
		fprintf(f2,"[%d]",temp);
		enQueue(&priorQueue,temp);
	}

	fprintf(f2,"\n");
	fprintf(f2,"\n");


	//heap2을 생성한다.
	enQueue2(&priorQueue2,11);
	enQueue2(&priorQueue2,22);
	enQueue2(&priorQueue2,33);
	enQueue2(&priorQueue2,44);
	enQueue2(&priorQueue2,55);
	enQueue2(&priorQueue2,63);
	enQueue2(&priorQueue2,77);


	//heap1의 값 출력
	fprintf(f2,"heap1 값 : \n");
	printShape(&priorQueue,0,1);
	fprintf(f2,"\n");
	fprintf(f2,"\n");
	fprintf(f2,"\n");
	fprintf(f2,"\n");
	
	//heap2의 값 출력
	fprintf(f2,"heap2 값 \n");
	printShape(&priorQueue2,0,1);
	fprintf(f2,"\n");
	fprintf(f2,"\n");

		while(!isEmpty(&priorQueue)){
		enQueue2(&priorQueue2,deQueue(&priorQueue));
	}

	fprintf(f2,"\n");
	fprintf(f2,"\n");
	fprintf(f2,"\n");
	fprintf(f2,"heap3 출력값 : \n");
	printShape(&priorQueue2,0,1);
	

	fclose(f1);
	fclose(f2);
	system("pause");

}