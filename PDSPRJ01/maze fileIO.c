/***************************************************
����� :	���α׷��� �ǽ� (��,�� 3����) 
				
				����-Pks
				�к�_�������ڰ��к�
				�й�_ 21000172, 21100571
				�̸�_ ������, ������
				
���α׷���    : MAZE ����
���α׷� ���� : 2���� ����(visited stack, alternative)�� �̿��Ͽ� MAZE���� �����ϱ�
�ۼ��� : 2012.09.03

->��â�� ����
****************************************************/




#include <stdio.h>
#include<stdlib.h>

#define STACK_SIZE 1000
#define ROW_SIZE 7
#define COL_SIZE 14


//spot�� ��Ÿ���� structure ���� 
typedef struct spot{  
int row;
int col;
}spot;

spot currentSpot; //���� ��ġ ��Ÿ�� 
spot exitSpot; // �ⱸ�� ǥ���� 




void printMaze(); //console�� mazeǥ�� 
void eMove(); 
void wMove(); 
void sMove(); 
void nMove(); 
void move();
void interCheck();//������ üŷ�ϴ� �Լ�
void backTrack(); //Dead -end�� �����ϸ� �ǵ��ư��� �Լ�
void is_exit();	//�ⱸ Ȯ���Լ�
void backMove(); //backtracking�� sub �Լ�
void tracePush(spot);//trace stack�� push
void altPush(spot);//alternative stack�� push
spot tracePop(); // trace stack�� pop
spot altPop(); //alternative stack�� pop
void printSpot(); //������ġ print 


spot trace[STACK_SIZE]; //������ ���� �����ϴ� stack 
int traceTop = -1;

spot alternative[STACK_SIZE]; //�������� �����ϴ� stack 
int altTop = -1;

int maze[ROW_SIZE][COL_SIZE];
// maze ���� 


void main(){

	int x,y; //�ʱ������� �ޱ����� ��ǥ
	int i=0, j=0;// index
	char temp; // file���� �ҷ����̱� ���� �ӽ�char
    int exitcheck=0; 
	FILE *input;
	
	input = fopen("inputdata.txt", "r");
	
	if(input==NULL)
    {
                   printf("mazefile�� �� �� �����ϴ�.\n");
                   exit(0);
    } 
	
	while(!feof(input))// input data�κ��� maze �޾Ƶ��� 
	{
         temp = fgetc(input);
         
         if(temp=='0')
         {
                               maze[i][j]=0;
                               j++;
                                        
         }
         
         if(temp=='1')
         {
                              maze[i][j]=1;
                              j++;
                              
         }
         
         if(temp=='3')
         {
                              maze[i][j]=0;
        	                  exitSpot.row = i;
                              exitSpot.col = j; //exit spot���� 
                              exitcheck++;
                              j++;
         }
                              
         
         if(temp=='\n')
         {
                               i++;
                               j=0;
                              
         }
         
 
                               
 
    }  
    
    
	
	
		
	printf("* It's amazing maze program !*\n");
	printMaze();


   
   if(exitcheck!=0)
    printf("�ⱸ�� ��ǥ�� %d, %d �Դϴ� \n", exitSpot.row, exitSpot.col); 

	do{
		printf("���������Է��ϼ��� ex(3 5) : ");
		scanf("%d %d",&x,&y);
			if(x>=0 && y>=0 && x<ROW_SIZE && y<COL_SIZE) //����ڰ� ������ ������ ������ ����ų� 
				if(maze[x][y]==0)                        // black field�̸� ��� �ݺ� 
					break;
			printf("�߸��� ��ǥ�Դϴ�. �ٽ� �Է����ּ��� ^^ \n"); 
			
				
	}while(1);
	currentSpot.row = x;
	currentSpot.col = y;

    //start ���� 
	tracePush(currentSpot); 
	maze[currentSpot.row][currentSpot.col]=2;
	interCheck();
    printf("START ");
	printSpot();
	is_exit();
	
    //move�Լ��ν� ���� 
    while(1)
	{
		move();
	}
	
	
}



void printMaze(){
	int i,j; //index
	printf("  ");
	for(j=0;j<COL_SIZE;j++)
                           printf("%2d",j);
 printf("  ");
    printf("\n");
	for(i=0;i<ROW_SIZE;i++){
        printf("%2d",i);
		for(j=0;j<COL_SIZE;j++)
		{
                               if(maze[i][j]==1)
                               printf("%s","��");
  
                               if(maze[i][j]==0)
                               printf("%s","��");                                
			//printf("%2d",maze[i][j]);
		}
		printf("\n");
	}

}


//4�������� move�ø��� exit check, intersection check, print spot�� ������
// 4������ move�Լ��� move�Լ��� sub�Լ��� ������. 
void eMove(){
	currentSpot.col++;
	tracePush(currentSpot);
	maze[currentSpot.row][currentSpot.col]=2;
	interCheck();
	printf("EAST  "); 
	printSpot();
	is_exit();
	

}

void wMove(){

	currentSpot.col--;
	tracePush(currentSpot);
	maze[currentSpot.row][currentSpot.col]=2;
	interCheck();
	printf("WEST  ");
	printSpot();
	is_exit();

}
void sMove(){

	currentSpot.row++;
	tracePush(currentSpot);
	maze[currentSpot.row][currentSpot.col]=2;
	interCheck();
	printf("SOUTH ");
	printSpot();
	is_exit();

}
void nMove(){

	currentSpot.row--;
	tracePush(currentSpot);
	maze[currentSpot.row][currentSpot.col]=2;
	interCheck();
	printf("NORTH ");
	printSpot();
	is_exit();

}

void backTrack(){  //intersection�������� back tracking �ϴ� �Լ� 

	if(alternative[altTop].row == currentSpot.row && alternative[altTop].col == currentSpot.col) //���� ������ intersection�̶��!
		altPop();                 //���� intersection���� ���� 
	
	while(!(alternative[altTop].row == currentSpot.row && alternative[altTop].col == currentSpot.col)) //intersection ������ ������ ������ 
	{
		backMove();
	}
	tracePush(currentSpot);

}

void backMove(){
	currentSpot = tracePop();  // trace���� �Ųٷ� ã�Ƶ� 
	printf("BACK  ");
	printSpot();

}

void printSpot(){
	printf(" %d, %d \n", currentSpot.row, currentSpot.col);
}

void is_exit(){ //exit�� �����ߴ��� �ƴ��� Ȯ�� 
	if(currentSpot.col == exitSpot.col && currentSpot.row == exitSpot.row)
	{
		printf("YOU GET CHEESE!~~!~!~!~!~! ^^ Congratulation!!! \n");
		system("pause");
		exit(1);

	}
}

void interCheck(){  //counter�� ����Ͽ� �� ���� �̻� ���� ���������� alternative stack�� push�Ѵ�.! 
	int count=0;

	if(maze[currentSpot.row][currentSpot.col+1]==0 && currentSpot.col+1 < COL_SIZE) 
		count++;
	if(maze[currentSpot.row][currentSpot.col-1]==0 && currentSpot.col-1 >= 0)
		count++;
	if(maze[currentSpot.row+1][currentSpot.col]==0 && currentSpot.row+1 < ROW_SIZE)
		count++;
	if(maze[currentSpot.row-1][currentSpot.col]==0 && currentSpot.row-1 >= 0)
		count++;
			
	if(count>1)
		altPush(currentSpot);


}

void move(){                 // east, west, south, north �� �켱������ move�� �����Ѵ�. 
	if(maze[currentSpot.row][currentSpot.col+1]==0 && currentSpot.col+1 < COL_SIZE){
		eMove();
		return;
	}
	else if(maze[currentSpot.row][currentSpot.col-1]==0 && currentSpot.col-1 >= 0){
		wMove();
		return;
	}
	else if(maze[currentSpot.row+1][currentSpot.col]==0 && currentSpot.row+1 < ROW_SIZE){
		sMove();
		return;
	}
	else if(maze[currentSpot.row-1][currentSpot.col]==0 && currentSpot.row-1 >= 0){
		nMove();
		return;
	}
	else  // dead end ������ ��!
	{
		tracePop();
		backTrack();
		return;
	}
}


void tracePush(spot current){
	trace[++traceTop]=current;
}//trace stack�� push


void altPush(spot current){
	alternative[++altTop]=current;

}//alternative stack�� push
spot tracePop(){
	if(traceTop == -1){
			printf("exit�� �������� �ʽ��ϴ�!!!!\n");  //��� ���� ���ƺð� �� �̻� �� ���� �����Ƿ� exit�� ���� 
			system("pause");
			exit(1);
	}
	else return trace[traceTop--];
	
} // trace stack�� pop

spot altPop(){

	if(altTop==-1){
			printf("exit�� �������� �ʽ��ϴ�!!!!\n");  //��� ���� ���ƺð� �� �̻� �� ���� �����Ƿ� exit�� ���� 
			system("pause");
			exit(1);
	}
	else return alternative[altTop--];


} //alternative stack�� pop

