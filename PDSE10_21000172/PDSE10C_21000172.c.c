/***********************************************
	���� :	PDSE10C
	�̸� :	������
	�й� :  21000172
	�к� :  �������� ���к�

	���� :  hashed list search�� �����϶�. �� 20���� �����͸� �����ϰ� �׽�Ʈ�϶� 

	�������� : �����Լ����� ������ ���� �����Ͱ��� �ؽ����̺� �����Ѵ�.
			   �̿� ������ ���� �����Ͽ� HASH SEARCH�� �̷������� Ȯ���غ���.
			   result���Ϸ� ���� �����Ѵ�.

	���糯¥ : 2012. 12.03
	����  :���ͳ� ���۸� 
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
//�ؽ��ڷ� ���� �ʱ�ȭ
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
//�����ϰ��� �ϴ� Ű�� ��ȯ�Ѵ�.
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
//find key�Լ�
const char*findkey(const char * s){
	int i , code = gethashcode(s);
	
	for(i = 0;i<g_hash[code].count; i++){
		//Ű�� ��ġ�ϴ��� ������ ã�� Ű�� ��ġ�� ��ȯ
		if(strcmp(g_hash[code].bucket[i],s) == 0)
			return g_hash[code].bucket[i];
	}
	//Ű�� ã�� ���ϸ� null ��ȯ
	return NULL;
}
//���Ͽ� ����ִ� ��� ������� ������ ������ ���
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
//�ؽ� �ڷᱸ���� ���ԵǾ��ִ� ��� Ű�� ���
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
		printf("������ ���������ϴ� \n");
		return;	
	}
	//���� ����Ǿ��ִ� data�����
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
		printf("������ �ܾ �Է����ּ��� : (����� q)");
		scanf("%s", key);

		if(strcmp(key,"q") ==0)
			return ;

		printf("�����ִ� code :");
		fprintf(f1,"�����ִ� code :");
		printf(" %d \n", code = gethashcode(key));
		fprintf(f1," %d \n", code = gethashcode(key));

		printf("�����ϱ� �� ");
		fprintf(f1,"�����ϱ� ��");
		printbucket(code);

		if(deletekey(key) ==0)
			break ;
		printf("�������� �� ");
		fprintf(f1,"�������� �� ");

		printbucket(code);
		printf("\n");
		fprintf(f1,"\n");
	}

	fclose(f1);
	system("PAUSE");
}