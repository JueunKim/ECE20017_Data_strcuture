/***********************************************
	과제 :	PDSE10B
	이름 :	김주은
	학번 :  21000172
	학부 :  전산전자 공학부

	문제 : 랜덤함수로 데이터를 추출하여 Quicksort로 값을 정렬하여 출력하여라. 

	구현내용 : 메인함수에서 랜덤함수로 값을 읽어와 quicksort로 sorting한다.
				결과값을 result파일로 저장한다.
	만든날짜 : 2012. 12.03
	참고  :인터넷 구글링 
***********************************************/

#include <stdio.h>
#include <stdlib.h>
#define SIZE 10			//랜덤 숫자 조정


void quicksort(int list[], int left, int right);
int partition(int list[], int left, int right);
FILE *f1;
int cnt=0;

void main(){

	
	int i =0;
	int list[SIZE];

	f1=fopen("Result.txt","w");
	if(f1==NULL){
		printf("파일을 열수없습니다 \n");
		return;	
	}

	//정렬 전 data 값 추출
	fprintf(f1,"정렬전 \n");
	for(i =0; i< SIZE; i++){
		list[i] = rand()%100;
		fprintf(f1,"[%d] ", list[i]);
	}
	printf("\n");
	

	//quick sort 함수 호출
	quicksort(list, 0, SIZE -1);
	
	//정렬 후 data 값
	fprintf(f1,"정렬후 \n");
	for(i =0; i< SIZE; i++){
		fprintf(f1,"[%d] ", list[i]);
	}
	
	fprintf(f1,"\n");
	
	fprintf(f1,"data 이동횟수 = %d",cnt);
	
	system("PAUSE");
}
void quicksort(int list[],int left, int right){

	int q;			//피벗 q 변수 선언
	if(left < right){

		q = partition(list, left, right);

		quicksort(list,left, q-1);		//피벗 왼쪽 리스트 quicksort
		cnt++;

		quicksort(list, q+1, right);	//피벗 오른쪽 리스트 quicksort	
		cnt++;
	}
}
int partition(int list[],int left, int right){

	int pivot, temp;
	int low, high;
	//int cnt =0;			//카운트 변수 선언
	low = left;
	high = right+1;
	pivot = list[left];		//정렬할 리스트의 가장 왼쪽 data를 피벗으로 선택

	//low와 high가 교차할 때 까지 반복
	do{
		
		do{ 
			cnt++;
			low++;		//list[low]가 pivot보다 작으면 계속 low 증가
			
		}while(list[low] < pivot);

		do{
			cnt++;
			high--;		//list[high]가 pivot 보다 크면 계속 high 감소
		}while(list[high] > pivot);

		//list[low]와 list[high]가 교차하지 않으면
		//두개의 값을 교환
		if(low<high){ 
			temp = list[low];
			list[low] = list[high];
			list[high]=temp;
		}


	}while(low < high);
	

	//피벗을 가운데 위치시킨다.
	temp = list[left];
	list[left] = list[high];
	list[high]=temp;

	//피벗 위치반환
	return high;
	}