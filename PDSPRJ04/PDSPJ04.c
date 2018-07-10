/***************************************************
����� :	���α׷��� �ǽ� (��,�� 3����) 
				
				����-PKs
				�к�_�������ڰ��к�
				�й�_ 21000172, 21100571
				�̸�_ ������, ������
				
���α׷���    : Huffman Translator
���α׷� ���� : Huffman Tree�� ���� Huffman Code�� ����� �̸� encode, decode�ϴ� ���α׷�
�ۼ��� : 2012.10.12
�����ڷ� : Fundamentals of Data structure in C
****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STACK_SIZE 20


typedef struct treeNode * treePointer;
typedef struct treeNode { //tree�� doubly linked list 2���� ����� ������
	int weight;
	char letter;

	char code[MAX_STACK_SIZE];

	treePointer left;
	treePointer right;

	treePointer rlink;
	treePointer llink;
}treeNode;

void sort(); // linked list�� sort �����ش�
treePointer swap(treePointer a); // a�� �״��� node�� swap�����ش�.

void init(); // file�κ��� weight �� �ҷ��鿩 node�� �ʱ�ȭ�����ش�.

void push(treePointer ); //list�� �� ��带 �߰��Ѵ�.
treePointer pop(); // list���� node�� �����´�.

void printcode(); // ��ȯ�� huffman code�� ��½����ش�.
void fprintcode(); // ���Ϸ� ��½����ش�.

void encode(char []); // �Է¹��� ������ code�� ��ȯ���ش�.

void decode(char []); // �Է¹��� code�� �������� ��ȯ���ش�.


treePointer alphabet[26]; // A-Z ���� ��带 ����Ű�� pointer
treePointer head; // list�� head 
treePointer merged[25]; // merge�� ���� ���Ǵ� pointer


//---------stack ADT
void pushstack(char item);
char stackpop();
int IsEmpty();
int IsFull();

char stack[MAX_STACK_SIZE];
int top = -1;

// ---------------


void inorder(treePointer ptr); // tree�� inorder�� traverse�ϰ� , code�� �������ش�.

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
			printf("inputdata.txt�� �ҷ��� �� �����ϴ�. ���α׷��� �����մϴ�.\n");
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


	
	// huffman tree ����
	for(i=0;i<25;i++){
		sort();

		merged[i]=(treePointer) malloc(sizeof(treeNode));
		merged[i]->left = pop();
		merged[i]->right = pop();
		merged[i]->weight = merged[i]->left->weight + merged[i]->right->weight;
		push(merged[i]);
	} 

	inorder(merged[24]);
	
	//code �������
	printcode();
	fprintcode();

	while(1)  //menu driven program 
  {
	printf("\n");
   printf("����������������������������������������������\n");   
   printf("��1. ���ڿ� -> Huffman Code (Encoding)      ��\n");
   printf("��2. Huffman Code -> ���ڿ� (Decoding)      ��\n");
   printf("��3. Huffman Code ����                      ��\n");
   printf("��4. ���α׷� ����                          ��\n");
   printf("����������������������������������������������\n");
   printf(" - ������ ����� �Է����ּ��� : "); 
   scanf("%d",&menu);
   getchar();
   
   if(menu==1)
   {
		printf(" - Encoding �� ���ڿ��� �Է��� �ּ��� : ");
		gets(sentence);
		encode(sentence);
   }
   
   else if(menu==2)
   {
		printf(" - Decoding �� Huffman  Code�� �Է��� �ּ��� : ");
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
   
   else printf("�߸� �Է��ϼ̽��ϴ�. �ٽ� �Է��� �ּ��� \n"); 
   }

	fclose(output);

}

void init(){

	int i;
	//���� ����ġ�� �ʱ�ȭ file�κ��� �ҷ����δ�.
	for(i=0;i<26;i++)
	{
		fscanf(input,"%d",&(alphabet[i]->weight));
	}

	//letter �ʱ�ȭ
	for(i=0;i<26;i++)
	{
		alphabet[i]->letter = i+65;
	}
	

	// double linked list ����
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
			if( (temp->weight) > (temp -> rlink->weight)) // ���ʰ��� ���ʺ��� ũ�� �ٲ���
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



void push(treePointer p) //list�� head������ node�� �־���
{
	p->rlink = head->rlink;
	p->llink = head;
	head -> rlink = p;
	p->rlink->llink = p;
}

treePointer pop() // list�� head ������ ��带 ���ش�
{

	treePointer temp;

	if(head->llink == head)
		return;

	temp = head->rlink;
	head->rlink = temp->rlink;
	head->rlink->llink = head;
	return temp;
}

void inorder(treePointer ptr) // tree�κ��� code�� ������Ű�� �Լ�
{
	int i;
	
	if(ptr){
	
			if(ptr->right==NULL && ptr->left == NULL) // �� node�̸� code����
			{
				i = (int)(ptr->letter) - 65;
				strcpy(alphabet[i]->code, stack);

			}

		if(ptr->left) //�����̸� 1
		{	
			pushstack('1');
			stack[top+1]='\0';
		}

		inorder(ptr->left);
	

		if(ptr->right) // �������̸� 0
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
	printf(" * Alphabet �� huffman code�� ��ȯ�� ��� * \n");
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
	fprintf(output," * Alphabet �� huffman code�� ��ȯ�� ��� * \n");
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
				if(temp->left == NULL) /// ���ʳ��� ���ߵǴµ� ������
				{
					printf("\n�ùٸ��� ���� code�Դϴ�...\n");
					fprintf(output,"\n�ùٸ��� ���� code�Դϴ�...\n");
						return ;
				}
				temp = temp->left;
			}
			else if(code[i]=='0')
			{
				if(temp->right == NULL) // �����ʳ��� ������ߴµ� ������
				{
					printf("\n�ùٸ��� ���� code�Դϴ�...\n");
					fprintf(output,"\n�ùٸ��� ���� code�Դϴ�...\n");
						return ;
				}
				temp = temp->right;
			}
			i++;
			if(!(temp->left == NULL && temp->right ==NULL) && code[i]=='\0') // ���ڿ��� ã�� �ʾҴµ� ������ 
			{
					printf("\n�ùٸ��� ���� code�Դϴ�...\n");
					fprintf(output,"\n�ùٸ��� ���� code�Դϴ�...\n");
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
