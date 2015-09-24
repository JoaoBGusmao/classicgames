#include<windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include <time.h>

typedef struct Pieces {
	int x;
	int y;
} Pieces;

Pieces pi[250];

void gotoxy(int x, int y){
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x,y});
}

int writeScore(int score) {
	gotoxy(10,1);
	printf("%.2d",score);
}

int getNumOfElements() {
	int count = 0;
	int i=0;
	for(i=0;i<250;i++) {
		if(pi[i].x > 0) count++;
	}
	return count;
}

void removePiece(int *size) {
	gotoxy(pi[(*size)-1].x,pi[(*size)-1].y);
	printf("%c",0);
}

void registerPiece(int x, int y,int *size) {
	int i;
	for(i=*size;i!=0;i--) {
		pi[i].x = pi[i-1].x;
		pi[i].y = pi[i-1].y;
	}
	pi[0].x = x;
	pi[0].y = y;
}

int colideEvent(int nextX,int nextY,int *size) {
	if(nextX < 4 || nextX > 74 || nextY < 4 || nextY > 22) return 1;
	int i;
	for(i=0;i<*size;i++) {
		if(nextX == pi[i].x && nextY == pi[i].y) return 1;
	}
	return 0;
}

int drawnNext(int *curx,int *cury,char *direction,int *size,int *colide,int food[2]) {
	int nextX = *curx;
	int nextY = *cury;
	
	switch(*direction) {
		case 72: //Key UP
			nextY--;
			break;
		case 75: //Key LEFT
			nextX--;
			break;
		case 77: //Key RIGTH
			nextX++;
			break;
		case 80: //Key DOWN
			nextY++;
			break;
		default:
			break;
	}
	
	*colide = colideEvent(nextX,nextY,size);
	removePiece(size);
	registerPiece(nextX,nextY,size);
	
	*curx = nextX;
	*cury = nextY;
	
	writeScore(*size-1);
	
	if(food[0] == nextX && food[1] == nextY) {
		*size=*size+1;
		food[0] = 0;
		food[1] = 0;
	}
	
	gotoxy(nextX,nextY);
	putch(42);
}

int buildScenery() {
	gotoxy(3,1);
	printf("SCORE: 0");
	
	gotoxy(3,3);
	//Constrói as paredes de cima e baixo
	int i;
	for(i=0;i<148;i++) {
		if(i == 74) gotoxy(3,23);
		printf("%c",219);
	}
	//Constrói as paredes laterais
	gotoxy(3,3);
	
	for(i=0;i<20;i++) {
		gotoxy(3,3+i);
		printf("%c",219);
	}
	for(i=0;i<20;i++) {
		gotoxy(76,3+i);
		printf("%c",219);
	}
}

int RandRange(int Min, int Max) {
    int diff = Max-Min;
    return (int) (((double)(diff+1)/RAND_MAX) * rand() + Min);
}

int registerFood(int food[2],int *size,int *speed) {
	if(food[0] != 0) return 0;
	int x = RandRange(4, 74); 
	int y = RandRange(4,20);
	if( colideEvent(x,y,size) == 1) return registerFood(food,size,speed);
	food[0] = x;
	food[1] = y;
	if(*speed > 50) *speed = *speed-3;
	gotoxy(x,y);
	putch(42);
}

void listenKeyboard(char *direction, char *newDirection) {
	if(kbhit()){
        *newDirection = getch();
		if( (*newDirection == 72 && *direction != 80) || (*newDirection == 80 && *direction != 72) || (*newDirection == 75 && *direction != 77) || (*newDirection == 77 && *direction != 75)) *direction = *newDirection;
    }
}

int callMenu();

int startGame() {
	srand(time(NULL));
	int speed = 250;
	int curx = 10;
	int cury = 15;
	int size = 1;
	int endGame = 0;
	int colide = 0;
	int food[2] = {0,0};
	char direction = 77;
	char newDirection = 0;
	
	registerPiece(curx,cury,&size);
	buildScenery();
	
	int i;
	for(i=0;i<260;i++) { //Para achar códigos
		//printf("code: %d %c\n",i,i);
	}
	int exTimes = 0;
	
	while(endGame == 0) {
        
		listenKeyboard(&direction,&newDirection);
		
		registerFood(food,&size,&speed);
		drawnNext(&curx,&cury,&direction,&size,&colide,food);
		
		listenKeyboard(&direction,&newDirection);
		
		if(colide == 1) {
			gotoxy(23,1);
			printf("GAME OVER. Pressione Enter\n");
			getch();
			callMenu();
		}
		
		if(exTimes > 50 && 1!=1) {
			system("cls");
			gotoxy(0,0);
			int i;
			for(i=0;i<size;i++) {
				printf("Pos x: %d ------- Pos Y: %d\n",pi[i].x,pi[i].y);
			}
			return 0;
		}
		exTimes++;
		Sleep(speed);
	}
}

int callMenu() {
	system("cls");
	int option = 0;
	printf("\n\n\n\n\n\tCSnake V0.1\n");
	printf("\n\t1 - Jogar\n");
	printf("\n\t2 - Codigo Fonte\n");
	printf("\n\n\tDigite o numero do menu: ");
	scanf("%d",&option);
	//while(option == 0);
	system("cls");
	if(option == 1) startGame();
	else if(option == 2) {
		printf("\n\n\n\n\n\thttps://github.com/JoaoBGusmao/classicgames/snake/source.cpp");
		getch();
		system("cls");
		return callMenu();
	}
}

int main() {
	callMenu();
}
