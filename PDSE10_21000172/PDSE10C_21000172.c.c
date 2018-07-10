/***********************************************
	과제 :	PDSE10C
	이름 :	김주은
	학번 :  21000172
	학부 :  전산전자 공학부

	문제 :  hashed list search를 구현하라. 약 20개의 데이터를 저장하고 테스트하라 

	구현내용 : 메인함수에서 저장해 놓은 데이터값을 해시테이블에 저장한다.
			   이에 적절한 값을 추출하여 HASH SEARCH가 이뤄졌는지 확인해본다.
			   result파일로 값을 저장한다.

	만든날짜 : 2012. 12.03
	참고  :인터넷 구글링 
***********************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void init();
void insertkey(const char*s);
int deletekey(const char*s);
const char*findekey(const char*s);
unsigned gethashcode(const char*s);

void printhash(void);
void printBucket(unsigned index);

enum {word_size = 32};
enum {bucket_size = 512, BUCKET_COUNT = 7};

typedef struct bucket{
	int count;
	char bucket[bucket_size][word_size];
}BUCKET;

static BUCKET g_hash[BUCKET_COUNT];
FILE *f1;
//해시자료 구조 초기화
void init(void){		
	int i;
	for(i=0;i<BUCKET_COUNT;i++)
		g_hash[i].count = 0;

}
unsigned gethashcode(const char*s){
	unsigned sum =0;
		while(*s)
			sum+= *s++;
		return sum%BUCKET_COUNT ;
}
void insertkey(const char*s){
		BUCKET* pb = g_hash + gethashcode(s);
		strcpy(pb->bucket[pb->count], s);
		pb->count++;
}
//삭제하고자 하는 키를 반환한다.
int deletekey(const char*s){
	BUCKET *pb= g_hash + gethashcode(s);
	int i;

	for(i = 0; i <pb->count ; i++){
		if(strcmp (pb-> bucket[i],s) == 0){
			strcpy(pb->bucket[i], pb->bucket[--pb ->count]);
			return 1;
		}
	}
	return 0;
}
//find key함수
const char*findkey(const char * s){
	int i , code = gethashcode(s);
	
	for(i = 0;i<g_hash[code].count; i++){
		//키가 일치하는지 슬롯을 찾아 키의 위치를 반환
		if(strcmp(g_hash[code].bucket[i],s) == 0)
			return g_hash[code].bucket[i];
	}
	//키를 찾지 못하면 null 반환
	return NULL;
}
//버켓에 들어있는 모든 사용중인 슬롯의 내용을 출력
void printbucket(unsigned index){
	BUCKET *pb = g_hash + index ;
	int i ;
	printf("%d[%2d] : ", index, pb->count);
	fprintf(f1,"%d[%2d] : ", index, pb->count);

	for(i = 0; i<pb->count; i++){
		printf("[%s]", pb->bucket[i]);
		fprintf(f1,"[%s]", pb->bucket[i]);
		
	}
		printf("\n");
		fprintf(f1,"\n");

}
//해시 자료구조에 포함되어있는 모든 키를 출력
void printhash(){
	int i;
	for(i =0 ; i<BUCKET_COUNT; i++)
		printbucket(i);

	printf("\n");
	fprintf(f1,"\n");
}
void main(){

	
	char* words[] = {"love", "black", "angel","pink","e",
						"bob", "money", "h","chicken","cake",
						"kimchi", "house", "m","music","power",
						"hope", "pill", "r","book","tent",};
	int i, code;
	char key[60];
 
	init();

	f1=fopen("Result.txt","w");
		if(f1==NULL){
		printf("파일을 열수없습니다 \n");
		return;	
	}
	//현재 저장되어있는 data값출력
	for(i=0;i<20;i++){
	printf("[%s] ", words[i]);
	fprintf(f1,"[%s] ", words[i]);
	insertkey(words[i]);

	if(i%10 ==9)
		printf("\n");
	//	fprintf(f1,"\n");
}
	fprintf(f1,"\n");
	printf("\n");
	printhash();

	while(1){
		printf("삭제할 단어를 입력해주세요 : (종료는 q)");
		scanf("%s", key);

		if(strcmp(key,"q") ==0)
			return ;

		printf("속해있는 code :");
		fprintf(f1,"속해있는 code :");
		printf(" %d \n", code = gethashcode(key));
		fprintf(f1," %d \n", code = gethashcode(key));

		printf("삭제하기 전 ");
		fprintf(f1,"삭제하기 전");
		printbucket(code);

		if(deletekey(key) ==0)
			break ;
		printf("삭제하한 후 ");
		fprintf(f1,"삭제하한 후 ");

		printbucket(code);
		printf("\n");
		fprintf(f1,"\n");
	}

	fclose(f1);
	system("PAUSE");
}