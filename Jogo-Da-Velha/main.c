#include <stdio.h>
#include <windows.h>
#include <conio.h>

void gotoxy(int x, int y){
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x,y});
}

int buildScenary() {
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int i=0;
	for(i=0;i<255;i++) {
		//printf("%d - %c\n\n",i,i);
	}
	//return 0;
	//Build walls
	int xpos=35;
	int ypos=5;
	for(int k=0;k<2;k++) {
		for(int i=0;i<14;i++) {
			gotoxy(xpos,ypos);
			printf("%c",186);
			ypos++;
		}
		xpos=xpos+8;
		ypos=5;
	}
	
	xpos=28;
	ypos=9;
	for(int k=0;k<2;k++) {
		for(i=0;i<22;i++) {
			gotoxy(xpos,ypos);
			printf("%c",205);
			xpos++;
		}
		ypos=ypos+5;
		xpos=28;
	}
	
	gotoxy(35,9);
	printf("%c",206);
	gotoxy(43,9);
	printf("%c",206);
	gotoxy(35,14);
	printf("%c",206);
	gotoxy(43,14);
	printf("%c",206);
	
	gotoxy(28,6);
	printf("O");
	//gotoxy(28,7);
	//printf("X");
}

int main() {
	buildScenery();
	getch();
	//system("pause");
}
