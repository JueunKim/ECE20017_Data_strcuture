/***********************************************
	과제 :	PDSE10A
	이름 :	김주은
	학번 :  21000172
	학부 :  전산전자 공학부

	문제 : 랜덤함수로 데이터를 추출하여 Shell sort로 값을 정렬하여 출력하여라. 

	구현내용 : 메인함수에서 랜덤함수로 값을 읽어와 Shell sort로 sorting한다.
				결과값을 result파일로 저장한다.
	만든날짜 : 2012. 12.03
	참고  :인터넷 구글링 
***********************************************/
#include <stdio.h>
#include <stdlib.h>
#define SIZE 10

void shellsort(int list[], int total, int index);
FILE *f1;
int cnt =0;		//data이동횟수 카운트 변수선언
int main(void) {

	int list[SIZE] = {0};
	 int i = 0;

	f1=fopen("Result.txt","w");
	if(f1==NULL){
		printf("파일을 열수없습니다 \n");
		return;	
	}

	//정렬 전 data 값 추출
	fprintf(f1,"정렬하기전 값: ");
	for(i = 0; i < SIZE; i++) {
		list[i] = (rand()*rand()) % 100;
		fprintf(f1,"[%d] ", list[i]); 
 }
 
 shellsort(list, SIZE, 1);

 fprintf(f1,"\n");
 //정렬 후 data값
 fprintf(f1,"정렬 후 값: ");
	 for(i = 0; i < SIZE; i++) {
		fprintf(f1,"[%d] ", list[i]); 
	 }

 fprintf(f1,"\n");
 fprintf(f1,"data 이동횟수 %d",cnt);

 
 system("PAUSE");
 return 0;
}

void shellsort(int list[], int total, int index) {

	int i,j,k,l = 0; 
	
	
		for(i = 0; i < total; i++) {
			cnt ++;			//카운트 /
			l = list[i];
		
			for(j = (i - index); j >= 0; j--) {
				cnt ++;	//카운트
			if(list[j] > l){
				cnt ++;	//카운트
				list[j + index] = list[j];
			}
				else break;
		
				}
				list[j + index] = l;
				cnt ++;			//카운트
		}

		return;
}
