/*  이름 : 김주은
	학부 : 전산전자공학부
	학번 : 21000172
	과제 : PDSE03A 링크드 리스트를 사용하여
		   두개의 리스트를 합치는 알고리즘을 구현하라.
	메인 알고리즘 : inputdata로 부터 파일을 읽어와 기존에 연결되어있던 링크드 리스트에 덧붙인다.
					결과값을 Result.txt로 출력한다.
		   */

#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode { 
	element data;
	struct ListNode *link;   	
} ListNode; 

ListNode *head;				//머리부분
ListNode *tail;				//꼬리부분
FILE *fp1;					//입력 파일포인터
FILE *fp2;					//출력 파일포인터

void insert_node(int item){			//삽입함수

	//메모리 동적할당
	ListNode *ptr;			
	ptr=(ListNode*)malloc(sizeof(ListNode));

	ptr->data= item;
	ptr->link= head;
	head=ptr;

	printf("삽입되었습니다 \n");
}
void printAll(){

	ListNode *ptr;
	ptr = head->link;
	if(head->link ==tail)
		printf("파일이 없습니다 \n");

	while(ptr!=NULL){
			printf("%d",ptr->data);
			ptr=ptr->link;
		}
}	
void load_file(){				//파일 불러오기 함수

	FILE *fp1;
	ListNode *ptr = NULL;
	int res, tmp;

	fp1=fopen("inputdata.txt","r");
	
	if (fp1==NULL){
		printf("Error \n"); 
		return;
	}

	while(1){
		res=fscanf(fp1,"%d ",&tmp);
		
		//inputdata로부터 읽어들인 값을 링크드리스트로 삽입한다.
		insert_node(tmp);

		if(res < 0) break;

	}

	fclose(fp1);
}
void save_file(){
	
	FILE *fp2;
	ListNode *ptr = head;

	//메모리 리스트를 Result 파일에 저장
	fp2=fopen("Result.txt","w");
	
	if(fp2==NULL){
		printf("Error\n");
			return ;}
	
	while(1) {
		if(ptr==NULL) break;
		fprintf(fp2,"%d ",ptr->data);
		ptr=ptr->link;
	}
	
	fclose(fp2);
}

int main(){

	//20 30 40을 링크드리스트로 연결
	insert_node(20);
	insert_node(30);
	insert_node(40);

	//inputdata파일을 읽어들인다.
	load_file();


	//결과값을 Result파일에 출력한다.
	save_file();

	//결과값 출력
	printAll();

	return 0;
}