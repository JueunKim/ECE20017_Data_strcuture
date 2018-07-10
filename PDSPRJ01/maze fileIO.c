/***************************************************
과목명 :	프로그래밍 실습 (월,목 3교시) 
				
				팀명-Pks
				학부_전산전자공학부
				학번_ 21000172, 21100571
				이름_ 김주은, 이혜민
				
프로그램명    : MAZE 게임
프로그램 내용 : 2개의 스택(visited stack, alternative)을 이용하여 MAZE게임 구현하기
작성일 : 2012.09.03

->독창적 구현
****************************************************/




#include <stdio.h>
#include<stdlib.h>

#define STACK_SIZE 1000
#define ROW_SIZE 7
#define COL_SIZE 14


//spot을 나타내는 structure 선언 
typedef struct spot{  
int row;
int col;
}spot;

spot currentSpot; //현재 위치 나타냄 
spot exitSpot; // 출구를 표시함 




void printMaze(); //console에 maze표시 
void eMove(); 
void wMove(); 
void sMove(); 
void nMove(); 
void move();
void interCheck();//교차점 체킹하는 함수
void backTrack(); //Dead -end에 도착하면 되돌아가는 함수
void is_exit();	//출구 확인함수
void backMove(); //backtracking의 sub 함수
void tracePush(spot);//trace stack에 push
void altPush(spot);//alternative stack에 push
spot tracePop(); // trace stack의 pop
spot altPop(); //alternative stack의 pop
void printSpot(); //현재위치 print 


spot trace[STACK_SIZE]; //지나간 점을 저장하는 stack 
int traceTop = -1;

spot alternative[STACK_SIZE]; //교차점을 저장하는 stack 
int altTop = -1;

int maze[ROW_SIZE][COL_SIZE];
// maze 설정 


void main(){

	int x,y; //초기지점을 받기위한 좌표
	int i=0, j=0;// index
	char temp; // file에서 불러들이기 위한 임시char
    int exitcheck=0; 
	FILE *input;
	
	input = fopen("inputdata.txt", "r");
	
	if(input==NULL)
    {
                   printf("mazefile을 열 수 없습니다.\n");
                   exit(0);
    } 
	
	while(!feof(input))// input data로부터 maze 받아들임 
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
                              exitSpot.col = j; //exit spot지정 
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
    printf("출구의 좌표는 %d, %d 입니다 \n", exitSpot.row, exitSpot.col); 

	do{
		printf("시작지점입력하세요 ex(3 5) : ");
		scanf("%d %d",&x,&y);
			if(x>=0 && y>=0 && x<ROW_SIZE && y<COL_SIZE) //사용자가 설정한 지점이 범위를 벗어나거나 
				if(maze[x][y]==0)                        // black field이면 계속 반복 
					break;
			printf("잘못된 좌표입니다. 다시 입력해주세요 ^^ \n"); 
			
				
	}while(1);
	currentSpot.row = x;
	currentSpot.col = y;

    //start 지점 
	tracePush(currentSpot); 
	maze[currentSpot.row][currentSpot.col]=2;
	interCheck();
    printf("START ");
	printSpot();
	is_exit();
	
    //move함수로써 구현 
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
                               printf("%s","■");
  
                               if(maze[i][j]==0)
                               printf("%s","□");                                
			//printf("%2d",maze[i][j]);
		}
		printf("\n");
	}

}


//4방향으로 move시마다 exit check, intersection check, print spot을 수행함
// 4방향의 move함수는 move함수의 sub함수로 구현함. 
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

void backTrack(){  //intersection지점까지 back tracking 하는 함수 

	if(alternative[altTop].row == currentSpot.row && alternative[altTop].col == currentSpot.col) //현재 지점이 intersection이라면!
		altPop();                 //이전 intersection으로 지정 
	
	while(!(alternative[altTop].row == currentSpot.row && alternative[altTop].col == currentSpot.col)) //intersection 지점에 도달할 때까지 
	{
		backMove();
	}
	tracePush(currentSpot);

}

void backMove(){
	currentSpot = tracePop();  // trace에서 거꾸로 찾아들어감 
	printf("BACK  ");
	printSpot();

}

void printSpot(){
	printf(" %d, %d \n", currentSpot.row, currentSpot.col);
}

void is_exit(){ //exit에 도달했는지 아닌지 확인 
	if(currentSpot.col == exitSpot.col && currentSpot.row == exitSpot.row)
	{
		printf("YOU GET CHEESE!~~!~!~!~!~! ^^ Congratulation!!! \n");
		system("pause");
		exit(1);

	}
}

void interCheck(){  //counter를 사용하여 두 갈래 이상 길이 열려있으면 alternative stack에 push한다.! 
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

void move(){                 // east, west, south, north 의 우선순위로 move를 수행한다. 
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
	else  // dead end 상태일 때!
	{
		tracePop();
		backTrack();
		return;
	}
}


void tracePush(spot current){
	trace[++traceTop]=current;
}//trace stack에 push


void altPush(spot current){
	alternative[++altTop]=current;

}//alternative stack에 push
spot tracePop(){
	if(traceTop == -1){
			printf("exit가 존재하지 않습니다!!!!\n");  //모든 길을 돌아봤고 더 이상 갈 곳이 없으므로 exit가 없음 
			system("pause");
			exit(1);
	}
	else return trace[traceTop--];
	
} // trace stack의 pop

spot altPop(){

	if(altTop==-1){
			printf("exit가 존재하지 않습니다!!!!\n");  //모든 길을 돌아봤고 더 이상 갈 곳이 없으므로 exit가 없음 
			system("pause");
			exit(1);
	}
	else return alternative[altTop--];


} //alternative stack의 pop

