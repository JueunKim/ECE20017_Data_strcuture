/***************************************************
과목명 :	프로그래밍 실습 (월,목 3교시) 
				
				팀명-PKs
				학부_전산전자공학부
				학번_ 21000172, 21100571
				이름_ 김주은, 이혜민
				
프로그램명    : Huffman Translator
프로그램 내용 : Huffman Tree를 만들어서 Huffman Code를 만들고 이를 encode, decode하는 프로그램
작성일 : 2012.10.12
참고자료 : Fundamentals of Data structure in C
****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STACK_SIZE 20


typedef struct treeNode * treePointer;
typedef struct treeNode { //tree와 doubly linked list 2가지 기능을 가진다
	int weight;
	char letter;

	char code[MAX_STACK_SIZE];

	treePointer left;
	treePointer right;

	treePointer rlink;
	treePointer llink;
}treeNode;

void sort(); // linked list를 sort 시켜준다
treePointer swap(treePointer a); // a와 그다음 node를 swap시켜준다.

void init(); // file로부터 weight 를 불러들여 node를 초기화시켜준다.

void push(treePointer ); //list에 새 노드를 추가한다.
treePointer pop(); // list에서 node를 꺼내온다.

void printcode(); // 변환된 huffman code를 출력시켜준다.
void fprintcode(); // 파일로 출력시켜준다.

void encode(char []); // 입력받은 문장을 code로 변환해준다.

void decode(char []); // 입력받은 code를 문장으로 변환해준다.


treePointer alphabet[26]; // A-Z 까지 노드를 가르키는 pointer
treePointer head; // list의 head 
treePointer merged[25]; // merge를 위해 사용되는 pointer


//---------stack ADT
void pushstack(char item);
char stackpop();
int IsEmpty();
int IsFull();

char stack[MAX_STACK_SIZE];
int top = -1;

// ---------------


void inorder(treePointer ptr); // tree를 inorder로 traverse하고 , code를 생성해준다.

FILE *input, *output;

void main()
{
	treePointer temp;
	int i;
	int menu;
	char sentence[100];
	char code[1000];

    input = fopen("inputdata.txt","r");

    
    if(input==NULL)
    {
			printf("inputdata.txt를 불러올 수 없습니다. 프로그램을 종료합니다.\n");
			system("PAUSE");
			return;
    }
    
    output = fopen("Result.txt","w");


	head = (treePointer) malloc(sizeof(treeNode));
	for(i=0;i<26;i++)
		alphabet[i]=(treePointer) malloc(sizeof(treeNode));
	
	init();

	for(i=0;i<MAX_STACK_SIZE;i++)
		stack[i]='\0';


	
	// huffman tree 생성
	for(i=0;i<25;i++){
		sort();

		merged[i]=(treePointer) malloc(sizeof(treeNode));
		merged[i]->left = pop();
		merged[i]->right = pop();
		merged[i]->weight = merged[i]->left->weight + merged[i]->right->weight;
		push(merged[i]);
	} 

	inorder(merged[24]);
	
	//code 출력해줌
	printcode();
	fprintcode();

	while(1)  //menu driven program 
  {
	printf("\n");
   printf("┌─────────────────────┐\n");   
   printf("│1. 문자열 -> Huffman Code (Encoding)      │\n");
   printf("│2. Huffman Code -> 문자열 (Decoding)      │\n");
   printf("│3. Huffman Code 보기                      │\n");
   printf("│4. 프로그램 종료                          │\n");
   printf("└─────────────────────┘\n");
   printf(" - 수행할 명령을 입력해주세요 : "); 
   scanf("%d",&menu);
   getchar();
   
   if(menu==1)
   {
		printf(" - Encoding 할 문자열을 입력해 주세요 : ");
		gets(sentence);
		encode(sentence);
   }
   
   else if(menu==2)
   {
		printf(" - Decoding 할 Huffman  Code를 입력해 주세요 : ");
		gets(code);
		decode(code);
   }
   
   else if(menu==3)
   {
        printcode();      

   }

   else if(menu==4)
   {
        break;      

   }
   
   else printf("잘못 입력하셨습니다. 다시 입력해 주세요 \n"); 
   }

	fclose(output);

}

void init(){

	int i;
	//문자 가중치값 초기화 file로부터 불러들인다.
	for(i=0;i<26;i++)
	{
		fscanf(input,"%d",&(alphabet[i]->weight));
	}

	//letter 초기화
	for(i=0;i<26;i++)
	{
		alphabet[i]->letter = i+65;
	}
	

	// double linked list 생성
	head->rlink = alphabet[0];
	for(i=0;i<26;i++){ 
		alphabet[i]->left = NULL;
		alphabet[i]->right = NULL; 
		alphabet[i]->rlink=alphabet[i+1];
	}
	alphabet[25]->rlink = head;

	for(i=25;i>0;i--)
		alphabet[i]->llink = alphabet[i-1];

	alphabet[0]->llink = head;
	head->llink = alphabet[25];


}


void sort(){
	treePointer temp;
	int i;
	for(i=0;i<25;i++)
		for(temp=head->rlink;temp->rlink!=head;temp=temp->rlink)
		{	
			if( (temp->weight) > (temp -> rlink->weight)) // 앞쪽값이 뒷쪽보다 크면 바꿔줌
				temp = swap(temp);
		}

}

treePointer swap(treePointer temp)
{
	treePointer temp2;
	temp2 = temp->rlink;

	temp->llink->rlink = temp2;
	temp2->rlink->llink = temp;

	temp->rlink = temp2->rlink;
	temp2->llink = temp->llink;

	temp->llink = temp2;
	temp2->rlink =temp;

	return temp2;
}



void push(treePointer p) //list의 head다음에 node를 넣어줌
{
	p->rlink = head->rlink;
	p->llink = head;
	head -> rlink = p;
	p->rlink->llink = p;
}

treePointer pop() // list의 head 다음의 노드를 빼준다
{

	treePointer temp;

	if(head->llink == head)
		return;

	temp = head->rlink;
	head->rlink = temp->rlink;
	head->rlink->llink = head;
	return temp;
}

void inorder(treePointer ptr) // tree로부터 code를 생성시키는 함수
{
	int i;
	
	if(ptr){
	
			if(ptr->right==NULL && ptr->left == NULL) // 끝 node이면 code생성
			{
				i = (int)(ptr->letter) - 65;
				strcpy(alphabet[i]->code, stack);

			}

		if(ptr->left) //왼쪽이면 1
		{	
			pushstack('1');
			stack[top+1]='\0';
		}

		inorder(ptr->left);
	

		if(ptr->right) // 오른쪽이면 0
		{
			pushstack('0');
		
			stack[top+1]='\0';
		}
		inorder(ptr->right);
	
	
		stackpop();
		stack[top+1]='\0';
	
	
	
	}

}

void printcode()
{
	int i;
	int j=1;
	printf(" * Alphabet 을 huffman code로 변환한 결과 * \n");
	printf("---------------------------------------------------------------\n");
	
	for(i=0;i<26;i++,j++)
	{
		printf(" - %c : %s		",alphabet[i]->letter,alphabet[i]->code);
		if(j%3==0)
			printf("\n");
	}
	printf("\n");
	printf("---------------------------------------------------------------\n");
}

void fprintcode()
{
	int i;
	int j=1;
	fprintf(output," * Alphabet 을 huffman code로 변환한 결과 * \n");
	fprintf(output,"---------------------------------------------------------------\n");
	
	for(i=0;i<26;i++,j++)
	{
		fprintf(output," - %c : %s		",alphabet[i]->letter,alphabet[i]->code);
		if(j%3==0)
			fprintf(output,"\n");
	}
	fprintf(output,"\n");
	fprintf(output,"---------------------------------------------------------------\n");
}


void encode(char sentence[])
{
	int i=0;
	fprintf(output,"* input sentence : %s \n", sentence);
	printf("* encoded code : ");
	fprintf(output,"* encoded code : ");
	while(sentence[i]!='\0')
	{
		if(isalpha(sentence[i]))
		{
			printf("%s", alphabet[ (int)toupper(sentence[i]) - 65]->code);
			fprintf(output,"%s", alphabet[ (int)toupper(sentence[i]) - 65]->code);
		}
			i++;
		
	}
	printf("\n");
	fprintf(output,"\n\n");
}

void decode(char code[])
{
	int i=0;
	treePointer temp; 
	fprintf(output,"* input code : %s \n", code);
	printf("* decoded sentence : ");
	fprintf(output,"* decoded sentence : ");
	
	while(code[i]!='\0')
	{
		temp = merged[24];
		while(!(temp->left == NULL && temp->right ==NULL))
		{
			if(code[i]=='1'){
				if(temp->left == NULL) /// 왼쪽노드로 가야되는데 없으면
				{
					printf("\n올바르지 않은 code입니다...\n");
					fprintf(output,"\n올바르지 않은 code입니다...\n");
						return ;
				}
				temp = temp->left;
			}
			else if(code[i]=='0')
			{
				if(temp->right == NULL) // 오른쪽노드로 가라고했는데 없으면
				{
					printf("\n올바르지 않은 code입니다...\n");
					fprintf(output,"\n올바르지 않은 code입니다...\n");
						return ;
				}
				temp = temp->right;
			}
			i++;
			if(!(temp->left == NULL && temp->right ==NULL) && code[i]=='\0') // 문자열을 찾지 않았는데 끝나면 
			{
					printf("\n올바르지 않은 code입니다...\n");
					fprintf(output,"\n올바르지 않은 code입니다...\n");
						return ;
			}
		}
		printf("%c", temp->letter);
		fprintf(output,"%c", temp->letter);
	}
	printf("\n");
	fprintf(output,"\n\n");
}



//stackADT ---------------------
void pushstack(char item){

	if(top>=MAX_STACK_SIZE-1){
		printf("stack is full \n");
		return;
	}

	stack[++top] = item;
}

char stackpop(){
	
	//if(top == -1)
		//printf("stack is empty \n");


	return stack[(top)--];

}

int IsEmpty(){

	if(top==-1)
		return (1);
	else 
		return (0);

}

int IsFull(){

	if(top>=MAX_STACK_SIZE -1)
		return (1);
	else
		return (0);

}
//---------------------------------------
